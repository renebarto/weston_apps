#include "Generator.h"
#include <gtest/gtest.h>
#include "Util.h"
#include "Executable.h"

using namespace std;

namespace CMake
{
namespace Test
{

class GeneratorTest
    : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        Util::MakeSureDirectoryExists(TEST_ROOT);
        Util::MakeSureDirectoryDoesNotExist(Util::ComposePath(TEST_ROOT, "cmake-package-builder"));
    }

    virtual void TearDown()
    {
        Util::MakeSureDirectoryDoesNotExist(Util::ComposePath(TEST_ROOT, "cmake-package-builder"));
    }

    GeneratorSettings settings;
};

const string ProjectName = "my-project";
const string ProjectFolder = Util::ComposePath(TEST_ROOT, "cmake-package-builder");
const string TargetName = "my-exe";
const string CMakeMinimumVersion = "3.5.1";

TEST_F(GeneratorTest, Construct)
{
    EXPECT_FALSE(Util::DirectoryExists(ProjectFolder));
    Generator target(settings);
    EXPECT_FALSE(Util::DirectoryExists(ProjectFolder));
}

TEST_F(GeneratorTest, Generate)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    EXPECT_FALSE(Util::DirectoryExists(ProjectFolder));
    Generator target(settings);
//        target.Generate(project, ProjectFolder);
//        EXPECT_TRUE(Util::DirectoryExists(ProjectFolder));
}

TEST_F(GeneratorTest, CollectContentsEmpty)
{
    Project::Ptr project = nullptr;
    Generator target(settings);
    EXPECT_EQ("", target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsEmptyName)
{
    Project::Ptr project = make_shared<Project>("");
    Generator target(settings);
    EXPECT_EQ(
        "set(CMAKE_VERBOSE_MAKEFILE OFF)\n"
        "set(CMAKE_COLOR_MAKEFILE OFF)\n", target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsNameOnly)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    EXPECT_EQ(
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE OFF)\n"
        "set(CMAKE_COLOR_MAKEFILE OFF)\n", target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsNameMinimumVersionOnly)
{
    Project::Ptr project = make_shared<Project>();
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE OFF)\n"
        "set(CMAKE_COLOR_MAKEFILE OFF)\n", target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsNoTargetsNoTemplate)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE OFF)\n"
        "set(CMAKE_COLOR_MAKEFILE OFF)\n",
        target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsNoTargets)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    settings.SetTemplateDirectory(TEMPLATE_DIR);
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE OFF)\n"
        "set(CMAKE_COLOR_MAKEFILE OFF)\n"
        "\n"
        "list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)\n"
        "\n"
        "include(platform)\n"
        "include(list_to_string)\n"
        "\n"
        "set(CMAKE_CXX_STANDARD 11)\n"
        "\n"
        "if(CMAKE_BUILD_TYPE)\n"
        "    message(STATUS \"Current build type: ${CMAKE_BUILD_TYPE}\")\n"
        "else()\n"
        "    message(STATUS \"Setting build to Debug\")\n"
        "    set(CMAKE_BUILD_TYPE \"Debug\" CACHE STRING\n"
        "        \"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.\" FORCE)\n"
        "endif()\n"
        "if(${CMAKE_BUILD_TYPE} STREQUAL \"Debug\")\n"
        "    set(CONFIG_DIR \"debug\" CACHE STRING \"Build config directory\" FORCE)\n"
        "elseif(${CMAKE_BUILD_TYPE} STREQUAL \"Release\")\n"
        "    set(CONFIG_DIR \"release\" CACHE STRING \"Build config directory\" FORCE)\n"
        "elseif(${CMAKE_BUILD_TYPE} STREQUAL \"MinSizeRel\")\n"
        "    set(CONFIG_DIR \"releaseMinSize\" CACHE STRING \"Build config directory\" FORCE)\n"
        "elseif(${CMAKE_BUILD_TYPE} STREQUAL \"RelWithDebInfo\")\n"
        "    set(CONFIG_DIR \"releaseMinSize\" CACHE STRING \"Build config directory\" FORCE)\n"
        "else()\n"
        "    message(FATAL_ERROR \"Invalid build type: \" ${CMAKE_BUILD_TYPE})\n"
        "endif()\n"
        "\n",
        target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsNoTargetsVerboseColorStandardInstall)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    settings.SetVerbose(true);
    settings.SetColor(true);
    settings.SetStandardInstall(true);
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE ON)\n"
        "set(CMAKE_COLOR_MAKEFILE ON)\n"
        "\n"
        "add_custom_target(install-components)\n",
        target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsSingleExecutableTargetNoStandardInstallNoTargetSeparator)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    settings.SetVerbose(true);
    settings.SetColor(true);
    settings.SetStandardInstall(false);
    settings.SetTemplateDirectory(TEMPLATE_DIR);
    settings.SetMainHeaderTemplateFileName("main_header_template_simple.txt");
    project->AddTarget(make_shared<Executable>(TargetName));
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE ON)\n"
        "set(CMAKE_COLOR_MAKEFILE ON)\n"
        "\n"
        "list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)\n"
        "\n"
        "set(CMAKE_CXX_STANDARD 11)\n"
        "\n"
        "if(CMAKE_BUILD_TYPE)\n"
        "    message(STATUS \"Current build type: ${CMAKE_BUILD_TYPE}\")\n"
        "else()\n"
        "    message(STATUS \"Setting build to Debug\")\n"
        "    set(CMAKE_BUILD_TYPE \"Debug\" CACHE STRING\n"
        "        \"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.\" FORCE)\n"
        "endif()\n"
        "\n"
        "\n"
        "add_executable(" + TargetName + " )\n",
        target.CollectContents(project));
}

TEST_F(GeneratorTest, CollectContentsSingleExecutableTarget)
{
    Project::Ptr project = make_shared<Project>(ProjectName);
    Generator target(settings);
    settings.SetCMakeMinimumVersion(CMakeMinimumVersion);
    settings.SetVerbose(true);
    settings.SetColor(true);
    settings.SetStandardInstall(true);
    settings.SetUseTargetSeparator(true);
    settings.SetTemplateDirectory(TEMPLATE_DIR);
    settings.SetMainHeaderTemplateFileName("main_header_template_simple.txt");
    project->AddTarget(make_shared<Executable>(TargetName));
    EXPECT_EQ(
        "cmake_minimum_required(VERSION " + CMakeMinimumVersion + ")\n"
        "project(" + ProjectName + ")\n"
        "set(CMAKE_VERBOSE_MAKEFILE ON)\n"
        "set(CMAKE_COLOR_MAKEFILE ON)\n"
        "\n"
        "list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)\n"
        "\n"
        "set(CMAKE_CXX_STANDARD 11)\n"
        "\n"
        "if(CMAKE_BUILD_TYPE)\n"
        "    message(STATUS \"Current build type: ${CMAKE_BUILD_TYPE}\")\n"
        "else()\n"
        "    message(STATUS \"Setting build to Debug\")\n"
        "    set(CMAKE_BUILD_TYPE \"Debug\" CACHE STRING\n"
        "        \"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.\" FORCE)\n"
        "endif()\n"
        "\n"
        "\n"
        "add_custom_target(install-components)\n"
        "\n"
        "#\n"
        "# " + TargetName + "\n"
        "#\n"
        "\n"
        "add_executable(" + TargetName + " )\n",
        target.CollectContents(project));
}

} // namespace Test
} // namespace CMake
