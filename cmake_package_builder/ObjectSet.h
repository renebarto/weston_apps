#pragma once

#include <string>
#include "Target.h"

namespace CMake
{

enum class ObjectType
{
    PIC,
    NoPIC,
};

class ObjectSet : public Target
{
public:
    ObjectSet(const std::string & name, ObjectType type);
    ~ObjectSet();

    virtual std::string CollectContents() override;

private:
    ObjectType _type;
};

} // namespace CMake