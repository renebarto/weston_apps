#include "ObjectSet.h"
#include <gtest/gtest.h>
#include "Util.h"

using namespace std;

namespace CMake
{
namespace Test
{

class ObjectSetTest
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

const string TargetName = "my-obj";
const string SourceFile1 = "source1.c";
const string SourceFile2 = "source2.cpp";

TEST_F(ObjectSetTest, Construct)
{
    ObjectSet target(TargetName, ObjectType::PIC);

    EXPECT_EQ(TargetName, target.GetName());
}

TEST_F(ObjectSetTest, CollectContentsNoSourcesPIC)
{
    ObjectSet target(TargetName, ObjectType::PIC);
    EXPECT_EQ(
        "add_library(" + TargetName + " OBJECT )\n"
        "set_target_properties(" + TargetName + " PROPERTIES POSITION_INDEPENDENT_CODE ON)\n",
        target.CollectContents());
}

TEST_F(ObjectSetTest, CollectContentsNoSourcesNoPIC)
{
    ObjectSet target(TargetName, ObjectType::NoPIC);
    EXPECT_EQ(
        "add_library(" + TargetName + " OBJECT )\n"
        "set_target_properties(" + TargetName + " PROPERTIES POSITION_INDEPENDENT_CODE OFF)\n",
        target.CollectContents());
}

TEST_F(ObjectSetTest, CollectContentsSingleSource)
{
    ObjectSet target(TargetName, ObjectType::PIC);
    target.AddSource(SourceFile1);
    EXPECT_EQ(
        "add_library(" + TargetName + " OBJECT " + SourceFile1 + " )\n"
        "set_target_properties(" + TargetName + " PROPERTIES POSITION_INDEPENDENT_CODE ON)\n",
        target.CollectContents());
}

TEST_F(ObjectSetTest, CollectContentsMultipleSources)
{
    ObjectSet target(TargetName, ObjectType::PIC);
    target.AddSources({SourceFile1, SourceFile2});
    EXPECT_EQ(
        "add_library(" + TargetName + " OBJECT " + SourceFile1 + " " + SourceFile2 + " )\n"
        "set_target_properties(" + TargetName + " PROPERTIES POSITION_INDEPENDENT_CODE ON)\n",
        target.CollectContents());
}

} // namespace Test
} // namespace CMake
