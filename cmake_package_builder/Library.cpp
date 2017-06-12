#include "Library.h"

#include <sstream>

using namespace std;
using namespace CMake;

Library::Library(const std::string & name, LibraryType type)
    : Target(name)
    , _type(type)
{
}

Library::~Library()
{
}

string Library::CollectContents()
{
    ostringstream stream;
    switch(_type)
    {
        case LibraryType::Static:
            stream << "add_library(" << _name << " STATIC ";
            for(auto source: _sources)
            {
                stream << source << " ";
            }
            stream << ")" << endl;
            break;
        case LibraryType::Shared:
            stream << "add_library(" << _name << " SHARED ";
            for(auto source: _sources)
            {
                stream << source << " ";
            }
            stream << ")" << endl;
            break;
        case LibraryType::Both:
            stream << "add_library(" << _name << "-static STATIC ";
            for(auto source: _sources)
            {
                stream << source << " ";
            }
            stream << ")" << endl;
            stream << "add_library(" << _name << "-shared SHARED ";
            for(auto source: _sources)
            {
                stream << source << " ";
            }
            stream << ")" << endl;
            break;
    }
    return stream.str();
}
