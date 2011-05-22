#include <Python.h>

#include <vector>

#include <boost/foreach.hpp>

#include <ackward/core/Bytes.cpp>

namespace ac = ackward::core;

int main(int argc, char** argv)
{
    std::vector<unsigned char> data(100, 0x34);

    // Construct a Bytes object.
    ac::Bytes bytes(data.begin(), data.end());

    assert(bytes.size() == 100);
    BOOST_FOREACH(unsigned char c, bytes)
    {
        assert(c == 0x34);
    }

    return 0;
}
