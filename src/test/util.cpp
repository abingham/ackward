#include <fstream>

#include <boost/filesystem.hpp>

unsigned int lineCount(const boost::filesystem::path& p)
{
    std::ifstream ifs(p.string().c_str());
    std::string l;
    unsigned int count = 0;
    while (getline(ifs, l))
        ++count;
    return count;
}

std::wstring toWString(const std::string& s)
{
    return std::wstring(s.begin(), s.end());
}
