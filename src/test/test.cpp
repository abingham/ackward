#include <Python.h>

#define BOOST_TEST_MODULE ackward
#include <boost/test/unit_test.hpp>

#include <ackward/logging/Initialize.hpp>

// Global initialization
struct Initialize {
    Initialize() 
        { 
            Py_Initialize(); 
            ackward::logging::initialize();
        }

    ~Initialize() {
        // NOTE: Py_Finalize not currently compatible with boost::python
        // Py_Finalize();
    }
};

BOOST_GLOBAL_FIXTURE( Initialize );
