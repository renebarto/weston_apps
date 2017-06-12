#pragma once

#include "Target.h"

namespace CMake
{

class Executable : public Target
{
public:
    Executable(const std::string & name);
    ~Executable();

    virtual std::string CollectContents() override;

private:
};

} // namespace CMake