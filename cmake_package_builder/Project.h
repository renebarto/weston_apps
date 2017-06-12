#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Target.h"

namespace CMake
{

class Project
    : public std::enable_shared_from_this<Project>
{
public:
    using Ptr = std::shared_ptr<Project>;

    Project(const std::string & name = "", const std::string & folder = ".");
    ~Project();

    std::string ProjectName() { return _projectName; }
    std::string ProjectFolder() { return _projectFolder; }
    std::string ProjectFullPath();
    bool IsMainProject();
    void AddSubProject(Ptr subProject);
    void AddTarget(Target::Ptr target);
    const std::vector<Target::Ptr> & GetTargets() { return _targets; }

private:
    std::string _projectName;
    std::string _projectFolder;
    std::weak_ptr<Project> _parentProject;
    std::vector<Ptr> _subProjects;
    std::vector<Target::Ptr> _targets;

    void SetParent(Ptr parentProject) { _parentProject = parentProject; }
};

} // namespace CMake
