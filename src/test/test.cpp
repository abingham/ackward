#include <Python.h>

#define BOOST_TEST_MODULE ackward
#include <boost/test/unit_test.hpp>

#include <ackward/datetime/Initialize.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/uuid/Initialize.hpp>

// Global initialization
struct Initialize {
    Initialize() 
        { 
            Py_Initialize(); 
            ackward::datetime::initialize();
            ackward::logging::initialize();
            ackward::uuid::initialize();
        }

    ~Initialize() {
        // NOTE: Py_Finalize not currently compatible with boost::python
        // Py_Finalize();
    }
};

BOOST_GLOBAL_FIXTURE( Initialize );
