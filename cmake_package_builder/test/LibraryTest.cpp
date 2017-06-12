#include "Library.h"
#include <gtest/gtest.h>
#include "Util.h"

using namespace std;

namespace CMake
{
namespace Test
{

class LibraryTest
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

const string TargetName = "my-lib";
const string SourceFile1 = "source1.c";
const string SourceFile2 = "source2.cpp";

TEST_F(LibraryTest, Construct)
{
    Library target(TargetName);

    EXPECT_EQ(TargetName, target.GetName());
}

TEST_F(LibraryTest, CollectContentsStaticNoSources)
{
    Library target(TargetName, LibraryType::Static);
    EXPECT_EQ(
        "add_library(" + TargetName + " STATIC )\n",
        target.CollectContents());
}

TEST_F(LibraryTest, CollectContentsSharedNoSources)
{
    Library target(TargetName, LibraryType::Shared);
    EXPECT_EQ(
        "add_library(" + TargetName + " SHARED )\n",
        target.CollectContents());
}

TEST_F(LibraryTest, CollectContentsBothNoSources)
{
    Library target(TargetName, LibraryType::Both);
    EXPECT_EQ(
        "add_library(" + TargetName + "-static STATIC )\n"
        "add_library(" + TargetName + "-shared SHARED )\n",
        target.CollectContents());
}

TEST_F(LibraryTest, CollectContentsSingleSource)
{
    Library target(TargetName);
    target.AddSource(SourceFile1);
    EXPECT_EQ(
        "add_library(" + TargetName + " STATIC " + SourceFile1 + " )\n",
        target.CollectContents());
}

TEST_F(LibraryTest, CollectContentsMultipleSources)
{
    Library target(TargetName);
    target.AddSources({SourceFile1, SourceFile2});
    EXPECT_EQ(
        "add_library(" + TargetName + " STATIC " + SourceFile1 + " " + SourceFile2 + " )\n",
        target.CollectContents());
}

TEST_F(LibraryTest, CollectContentsBothMultipleSources)
{
    Library target(TargetName, LibraryType::Both);
    target.AddSources({SourceFile1, SourceFile2});
    EXPECT_EQ(
        "add_library(" + TargetName + "-static STATIC " + SourceFile1 + " " + SourceFile2 + " )\n"
        "add_library(" + TargetName + "-shared SHARED " + SourceFile1 + " " + SourceFile2 + " )\n",
        target.CollectContents());
}

} // namespace Test
} // namespace CMake
