#include "Util.h"

#include <sys/stat.h>
#include <zconf.h>
#include <cstring>
#include <iostream>

using namespace std;
using namespace Util;

string Util::ComposePath(const string & directory, const string & fileName)
{
    string path = directory;
    if (path[path.length() - 1] != '/')
        path = path + "/";
    path = path + fileName;
    return path;
}

bool Util::DirectoryExists(const string & directory)
{
    struct stat status;
    memset(&status, 0, sizeof(status));
    stat(directory.c_str(), &status);
    return (S_ISDIR(status.st_mode));
}

bool Util::CreateDirectory(const string & directory)
{
    struct stat status;
    memset(&status, 0, sizeof(status));
    stat(directory.c_str(), &status);
    if (S_ISDIR(status.st_mode))
        return true;
    if (S_ISREG(status.st_mode))
        return false;

    return (mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
}

void Util::MakeSureDirectoryExists(string const & directory)
{
    if (!DirectoryExists(directory))
    {
        CreateDirectory(directory);
    }
}

void Util::MakeSureDirectoryDoesNotExist(string const & directory)
{
    if (DirectoryExists(directory))
    {
        unlink(directory.c_str());
    }
}


