#pragma once

#include <string>
#include <memory>
#include <vector>

namespace CMake
{

class Target
{
public:
    using Ptr = std::shared_ptr<Target>;

    Target(const std::string & name);
    ~Target();

    const std::string & GetName() const { return _name; }
    void AddSource(const std::string & sourceName);
    void AddSources(const std::vector<std::string> & sourceNames);
    void AddCompilerDefine(const std::string & define);
    void AddCompilerDefines(const std::vector<std::string> & defines);
    void AddCompilerOption(const std::string & option);
    void AddCompilerOptions(const std::vector<std::string> & options);
    void AddLinkLibrary(const std::string & libraryName);
    void AddLinkLibraries(const std::vector<std::string> & libraryNames);
    void AddLinkerOption(const std::string & option);
    void AddLinkerOptions(const std::vector<std::string> & options);
    virtual std::string CollectContents() = 0;

protected:
    std::string _name;
    std::vector<std::string> _sources;
    std::vector<std::string> _defines;
    std::vector<std::string> _compileOptions;
    std::vector<std::string> _linkLibraries;
    std::vector<std::string> _linkOpions;
};

} // namespace CMake