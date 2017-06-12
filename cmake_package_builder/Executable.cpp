#include "Executable.h"

#include <sstream>

using namespace std;
using namespace CMake;

Executable::Executable(const std::string & name)
    : Target(name)
{

}

Executable::~Executable()
{

}

string Executable::CollectContents()
{
    ostringstream stream;
    stream << "add_executable(" << _name << " ";
    for(auto source: _sources)
    {
        stream << source << " ";
    }
    stream << ")" << endl;
    return stream.str();
}
