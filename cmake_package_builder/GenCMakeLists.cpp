#include "GenCMakeLists.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static const string CMakeListsFileName = "CMakeLists.txt";

string ComposePath(const string & directory, const string & fileName)
{
    string path = directory;
    if (path[path.length() - 1] != '/')
        path = path + "/";
    path = path + fileName;
    return path;
}

bool CMakeLists::Generate(const string & directory)
{
    string fileContents = CollectContents();

    try
    {
        ofstream file(ComposePath(directory, CMakeListsFileName));
        file.write(fileContents.c_str(), fileContents.length());
    }
    catch (exception & e)
    {
        cerr << "Exception thrown: " << e.what() << endl;
        return false;
    }

    return true;
}

string CMakeLists::CollectContents()
{
    return "";
}