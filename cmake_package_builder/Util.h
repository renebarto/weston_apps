#pragma once

#include <string>

namespace Util
{

std::string ComposePath(const std::string & directory, const std::string & fileName);
bool DirectoryExists(const std::string & directory);
bool CreateDirectory(const std::string & directory);
void MakeSureDirectoryExists(std::string const & directory);
void MakeSureDirectoryDoesNotExist(std::string const & directory);

std::string ReadLine(std::istream & stream);

} // namespace Util