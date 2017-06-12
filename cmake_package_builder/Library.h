#pragma once

#include <string>
#include "Target.h"

namespace CMake
{

enum class LibraryType
{
    Static,
    Shared,
    Both,
};
class Library : public Target
{
public:
    Library(const std::string & name, LibraryType type = LibraryType::Static);
    ~Library();

    virtual std::string CollectContents() override;

private:
    LibraryType _type;
};

} // namespace CMake