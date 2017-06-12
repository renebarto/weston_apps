#include "Project.h"
#include "Util.h"

using namespace std;
using namespace CMake;

Project::Project(const string & name, const string & folder)
    : _projectName(name)
    , _projectFolder(folder)
    , _parentProject()
    , _subProjects()
    , _targets()
{
}

Project::~Project()
{
}

string Project::ProjectFullPath()
{
    auto parent = _parentProject.lock();
    if (!parent)
        return ProjectFolder();
    return Util::ComposePath(parent->ProjectFullPath(), ProjectFolder());
}

bool Project::IsMainProject()
{
    auto parent = _parentProject.lock();
    return !parent;
}

void Project::AddSubProject(Project::Ptr subProject)
{
    _subProjects.push_back(subProject);
    subProject->SetParent(shared_from_this());
}

void Project::AddTarget(Target::Ptr target)
{
    _targets.push_back(target);
}
