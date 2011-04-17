#include <Python.h>

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/queue/Queue.hpp>

using namespace ackward::queue;
using namespace boost::assign;

namespace
{

std::list<int> qTypes = list_of(1)(2)(3);

Queue makeQ(int t, int maxsize)
{
    switch (t) {
        case 1:
            return makeQueue(maxsize);

        case 2:
            return makeLifoQueue(maxsize);

        case 3:
            return makePriorityQueue(maxsize);

        default:
            throw std::runtime_error("wtf?");
    }
}

}

BOOST_AUTO_TEST_SUITE( Queue_methods )

BOOST_AUTO_TEST_CASE( queue_makeQueue )
{
    BOOST_FOREACH(int t, ::qTypes) {
        Queue q = ::makeQ(t, 100);
        BOOST_CHECK_EQUAL(q.qsize(), 0);
    }
}

BOOST_AUTO_TEST_SUITE_END()
