#include <ackward/core/Exceptions.hpp>
#include <ackward/core/ExceptionTranslator.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

using namespace ackward::core;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( ExceptionTranslator_tests )

BOOST_AUTO_TEST_CASE( add )
{
    ExceptionTranslator e;
    e.add( builtins().attr("IndexError"), 
           throw_with_python_info<IndexError> );
    
    bp::list l;

    try {

        l[5];

    } catch (const bp::error_already_set&) {

        BOOST_CHECK_THROW(
            e.translate(getExceptionInfo()),
            IndexError);
                        
    }
}

BOOST_AUTO_TEST_CASE( remove )
{
    ExceptionTranslator e;
    e.add( builtins().attr("IndexError"), 
           throw_with_python_info<IndexError> );
    
    bp::list l;

    try {

        l[5];

    } catch (const bp::error_already_set&) {

        BOOST_CHECK_THROW(
            e.translate(getExceptionInfo()),
            IndexError);
                        
    }

    e.remove(builtins().attr("IndexError"));
    
    try {

        l[5];

    } catch (const bp::error_already_set&) {
        
        e.translate(getExceptionInfo());
        BOOST_ASSERT(true);
                        
    }
}

BOOST_AUTO_TEST_SUITE_END() 
