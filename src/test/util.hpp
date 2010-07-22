#include <string>

#include <boost/filesystem/path.hpp>

unsigned int lineCount(const boost::filesystem::path& p);

std::wstring toWString(const std::string& s);
