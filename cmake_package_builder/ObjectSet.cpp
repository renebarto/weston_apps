#include "ObjectSet.h"

#include <sstream>

using namespace std;
using namespace CMake;

ObjectSet::ObjectSet(const std::string & name, ObjectType type)
    : Target(name)
    , _type(type)
{
}

ObjectSet::~ObjectSet()
{
}

string ObjectSet::CollectContents()
{
    ostringstream stream;
    stream << "add_library(" << _name << " OBJECT ";
    for(auto source: _sources)
    {
        stream << source << " ";
    }
    stream << ")" << endl;
    stream << "set_target_properties(" << _name << " PROPERTIES POSITION_INDEPENDENT_CODE ";
    switch(_type)
    {
        case ObjectType::PIC:
            stream << "ON";
            break;
        case ObjectType::NoPIC:
            stream << "OFF";
            break;
    }
    stream << ")" << endl;
    return stream.str();
}
