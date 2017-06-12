#pragma once

#include <string>

class CMakeLists
{
public:
    CMakeLists() {}
    ~CMakeLists() {}

    bool Generate(const std::string & directory);
    std::string CollectContents();

private:
    std::string _projectName;
};
