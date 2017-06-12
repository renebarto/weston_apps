#pragma once

#include <string>
#include "Project.h"

namespace CMake
{

class GeneratorSettings
{
public:
    GeneratorSettings();
    void SetCMakeMinimumVersion(const std::string & version) { _minimumCMakeVersion = version; }
    const std::string & GetCMakeMinimumVersion() const { return _minimumCMakeVersion; }
    void SetVerbose(bool on) { _verboseCMakeFile = on; }
    bool GetVerbose() const { return _verboseCMakeFile; }
    void SetColor(bool on) { _colorCMakeFile = on; }
    bool GetColor() const { return _colorCMakeFile; }
    void SetStandardInstall(bool on) { _standardInstall = on; }
    bool GetStandardInstall() const { return _standardInstall; }
    void SetUseTargetSeparator(bool on) { _useTargetSeparator = on; }
    bool GetUseTargetSeparator() const { return _useTargetSeparator; }
    void SetDebug(bool on) { _debug = on; }
    bool GetDebug() const { return _debug; }
    void SetTemplateDirectory(const std::string & directory) { _templateDirectory = directory; }
    const std::string & GetTemplateDirectory() const { return _templateDirectory; }
    void SetMainHeaderTemplateFileName(const std::string & directory) { _mainHeaderTemplateFileName = directory; }
    const std::string & GetMainHeaderTemplateFileName() const { return _mainHeaderTemplateFileName; }
    void SetUninstallCMakeFileName(const std::string & directory) { _uninstallCMakeFileName = directory; }
    const std::string & GetUninstallCMakeFileName() const { return _uninstallCMakeFileName; }

private:
    std::string _minimumCMakeVersion;
    bool _verboseCMakeFile;
    bool _colorCMakeFile;
    bool _standardInstall;
    bool _useTargetSeparator;
    bool _debug;
    std::string _templateDirectory;
    std::string _mainHeaderTemplateFileName;
    std::string _uninstallCMakeFileName;
};

class Generator
{
public:
    Generator(const GeneratorSettings & settings);
    ~Generator() {}

    bool Generate(Project::Ptr project, const std::string & directory);
    std::string CollectContents(Project::Ptr project);

private:
    const GeneratorSettings & _settings;
};

} // namespace CMake
