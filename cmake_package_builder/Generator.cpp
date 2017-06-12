#include "Generator.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Util.h"

using namespace std;
using namespace CMake;

static const string CMakeListsFileName = "CMakeLists.txt";
static const string DefaultMainHeaderTemplateFileName = "main_header_template.txt";
static const string DefaultUninstallCMakeSourceFileName = "uninstall.cmake.in";

GeneratorSettings::GeneratorSettings()
    : _minimumCMakeVersion()
    , _verboseCMakeFile()
    , _colorCMakeFile()
    , _standardInstall()
    , _useTargetSeparator()
    , _debug()
    , _templateDirectory()
    , _mainHeaderTemplateFileName(DefaultMainHeaderTemplateFileName)
    , _uninstallCMakeFileName(DefaultUninstallCMakeSourceFileName)
{
}

Generator::Generator(const GeneratorSettings & settings)
    : _settings(settings)
{
}

bool Generator::Generate(Project::Ptr project, const string & directory)
{
    string fileContents = CollectContents(project);

    try
    {
        ofstream file(Util::ComposePath(directory, CMakeListsFileName));
        file.write(fileContents.c_str(), fileContents.length());
    }
    catch (exception & e)
    {
        cerr << "Exception thrown: " << e.what() << endl;
        return false;
    }

    return true;
}

string Generator::CollectContents(Project::Ptr project)
{
    if (!project)
        return "";

    ostringstream stream;
    if (project->IsMainProject() && !_settings.GetCMakeMinimumVersion().empty())
        stream << "cmake_minimum_required(VERSION " << _settings.GetCMakeMinimumVersion() << ")" << endl;

    if (!project->ProjectName().empty())
        stream << "project(" << project->ProjectName() << ")" << endl;

    if (project->IsMainProject())
    {
        if (_settings.GetVerbose())
            stream << "set(CMAKE_VERBOSE_MAKEFILE ON)" << endl;
        else
            stream << "set(CMAKE_VERBOSE_MAKEFILE OFF)" << endl;
        if (_settings.GetColor())
            stream << "set(CMAKE_COLOR_MAKEFILE ON)" << endl;
        else
            stream << "set(CMAKE_COLOR_MAKEFILE OFF)" << endl;

        try
        {
            string line;
            ifstream headerTemplate(Util::ComposePath(_settings.GetTemplateDirectory(), _settings.GetMainHeaderTemplateFileName()));
            if (headerTemplate)
            {
                stream << endl;
                while (headerTemplate)
                {
                    getline(headerTemplate, line);
                    stream << line;
                    if (!headerTemplate.eof())
                        stream << endl;
                }
                stream << endl;
            }
        }
        catch (exception &e)
        {
            cerr << "Could not open main header template" << endl;
        }

        if (_settings.GetStandardInstall())
        {
            stream << endl;
            stream << "add_custom_target(install-components)" << endl;
        }

        for(auto target : project->GetTargets())
        {
            stream << endl;
            if (_settings.GetUseTargetSeparator())
            {
                stream << "#" << endl;
                stream << "# " << target->GetName() << endl;
                stream << "#" << endl;
                stream << endl;
            }

            stream << target->CollectContents();
        }

        return stream.str();
    }
}