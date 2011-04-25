#include <Python.h>

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/python/object.hpp>
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

BOOST_AUTO_TEST_CASE( queue_put )
{
    BOOST_FOREACH(int t, ::qTypes) {
        Queue q = ::makeQ(t, 100);

        for (int i = 0; i < 100; ++i)
        {
            BOOST_CHECK_EQUAL(q.qsize(), i);
            q.put(i);
        }

        for (int i = 0; i < 100; ++i)
        {
            int val = q.get<int>();
            BOOST_CHECK_EQUAL(val, i);
        }
    }
}

// TODO: put with block and timeout
// TODO: test for Full exception

BOOST_AUTO_TEST_CASE( queue_get )
{
    BOOST_FOREACH(int t, ::qTypes) {
        Queue q = ::makeQ(t, 100);
        
        for (int i = 0; i < 100; ++i)
        {
             q.put(i);
        }
        
        for (int i = 0; i < 100; ++i)
        {
            BOOST_CHECK_EQUAL(q.qsize(), 100 - i);
            int val = q.get<int>();
            BOOST_CHECK_EQUAL(val, i);
        }
    }
}

// TODO: get w/ block and timeout
// TODO: test for Empty exception

BOOST_AUTO_TEST_CASE( queue_full )
{
    BOOST_FOREACH(int t, ::qTypes) {
        Queue q = ::makeQ(t, 2);
        BOOST_CHECK(!q.full());
        q.put(0);
        BOOST_CHECK(!q.full());
        q.put(1);
        BOOST_CHECK(q.full());
        q.get<int>();
        BOOST_CHECK(!q.full());
    }
}

BOOST_AUTO_TEST_SUITE_END()
