#include <Python.h>

#include <vector>

#include <boost/foreach.hpp>

#include <ackward/core/ByteArray.hpp>

#include <iostream>

namespace ac = ackward::core;

int main(int argc, char** argv)
{
    // Create some test data
    std::vector<unsigned char> data(100, 0xab);
    
    // Construct a ByteArray from the test data.
    ac::ByteArray arr(data.begin(), data.end());

    // Check the data in the ByteArray.
    assert(arr.size() == data.size());

    BOOST_FOREACH(unsigned char c, arr)
    {
        assert(c == 0xab);
    }

    // Modify some data
    arr[5] = 0x12;
    assert(arr[5] == 0x12);

    return 0;
}
