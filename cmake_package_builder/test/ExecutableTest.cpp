#include "Executable.h"
#include <gtest/gtest.h>
#include "Util.h"

using namespace std;

namespace CMake
{
namespace Test
{

class ExecutableTest
    : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

const string TargetName = "my-exe";
const string SourceFile1 = "source1.c";
const string SourceFile2 = "source2.cpp";

TEST_F(ExecutableTest, Construct)
{
    Executable target(TargetName);

    EXPECT_EQ(TargetName, target.GetName());
}

TEST_F(ExecutableTest, CollectContentsNoSources)
{
    Executable target(TargetName);
    EXPECT_EQ(
        "add_executable(" + TargetName + " )\n",
        target.CollectContents());
}

TEST_F(ExecutableTest, CollectContentsSingleSource)
{
    Executable target(TargetName);
    target.AddSource(SourceFile1);
    EXPECT_EQ(
        "add_executable(" + TargetName + " " + SourceFile1 + " )\n",
        target.CollectContents());
}

TEST_F(ExecutableTest, CollectContentsMultipleSources)
{
    Executable target(TargetName);
    target.AddSources({SourceFile1, SourceFile2});
    EXPECT_EQ(
        "add_executable(" + TargetName + " " + SourceFile1 + " " + SourceFile2 + " )\n",
        target.CollectContents());
}

} // namespace Test
} // namespace CMake
