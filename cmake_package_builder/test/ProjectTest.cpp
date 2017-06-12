#include "Project.h"
#include <gtest/gtest.h>
#include "Util.h"

using namespace std;

namespace CMake
{
namespace Test
{

class ProjectTest
    : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        Util::MakeSureDirectoryDoesNotExist(Util::ComposePath(TEST_ROOT, "cmake-package-builder"));
    }
};

const string DefaultProjectName = "";
const string DefaultProjectFolder = ".";
const string MainProjectName = "MainProject";
const string MainProjectFolder = Util::ComposePath(TEST_ROOT, "cmake-package-builder");
const string SubProjectName = "SubProject";
const string SubProjectFolder = "sub-project";
const string FullSubProjectFolder = Util::ComposePath(MainProjectFolder, SubProjectFolder);

TEST_F(ProjectTest, ConstructDefault)
{
    Project target;

    EXPECT_EQ(DefaultProjectName, target.ProjectName());
    EXPECT_EQ(DefaultProjectFolder, target.ProjectFolder());
    EXPECT_EQ(DefaultProjectFolder, target.ProjectFullPath());
}

TEST_F(ProjectTest, ConstructNameOnly)
{
    Project target(MainProjectName);

    EXPECT_EQ(MainProjectName, target.ProjectName());
    EXPECT_EQ(DefaultProjectFolder, target.ProjectFolder());
    EXPECT_EQ(DefaultProjectFolder, target.ProjectFullPath());
}

TEST_F(ProjectTest, Construct)
{
    Project target(MainProjectName, MainProjectFolder);

    EXPECT_EQ(MainProjectName, target.ProjectName());
    EXPECT_EQ(MainProjectFolder, target.ProjectFolder());
    EXPECT_EQ(MainProjectFolder, target.ProjectFullPath());
}

TEST_F(ProjectTest, AddSubProject)
{
    Project::Ptr target = make_shared<Project>(MainProjectName, MainProjectFolder);
    Project::Ptr subProject = make_shared<Project>(SubProjectName, SubProjectFolder);

    target->AddSubProject(subProject);
    EXPECT_EQ(MainProjectName, target->ProjectName());
    EXPECT_EQ(MainProjectFolder, target->ProjectFolder());
    EXPECT_EQ(MainProjectFolder, target->ProjectFullPath());
    EXPECT_EQ(SubProjectName, subProject->ProjectName());
    EXPECT_EQ(SubProjectFolder, subProject->ProjectFolder());
    EXPECT_EQ(FullSubProjectFolder, subProject->ProjectFullPath());
}

} // namespace Test
} // namespace CMake
