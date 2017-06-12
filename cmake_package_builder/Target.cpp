#include "Target.h"

using namespace CMake;

Target::Target(const std::string & sourceName)
    : _name(sourceName)
    , _sources()
    , _defines()
    , _compileOptions()
    , _linkLibraries()
    , _linkOpions()
{
}

Target::~Target()
{
}

void Target::AddSource(const std::string & sourceName)
{
    _sources.push_back(sourceName);
}

void Target::AddSources(const std::vector<std::string> &sourceNames)
{
    _sources.insert(_sources.end(), sourceNames.begin(), sourceNames.end());
}

void Target::AddCompilerDefine(const std::string & define)
{
    _defines.push_back(define);
}

void Target::AddCompilerDefines(const std::vector<std::string> & defines)
{
    _defines.insert(_defines.end(), defines.begin(), defines.end());
}

void Target::AddCompilerOption(const std::string & option)
{
    _compileOptions.push_back(option);
}

void Target::AddCompilerOptions(const std::vector<std::string> & options)
{
    _compileOptions.insert(_compileOptions.end(), options.begin(), options.end());
}

void Target::AddLinkLibrary(const std::string & libraryName)
{
    _linkLibraries.push_back(libraryName);
}

void Target::AddLinkLibraries(const std::vector<std::string> & libraryNames)
{
    _linkLibraries.insert(_linkLibraries.end(), libraryNames.begin(), libraryNames.end());
}

void Target::AddLinkerOption(const std::string & option)
{
    _linkOpions.push_back(option);
}

void Target::AddLinkerOptions(const std::vector<std::string> & options)
{
    _linkOpions.insert(_linkOpions.end(), options.begin(), options.end());
}
