#include <Python.h>

#include <ackward/core/Bytes.hpp>
#include <ackward/core/Import.hpp>
#include <ackward/core/Initialize.hpp>
#include <ackward/core/Object.hpp>
#include <boost/python/extract.hpp>

/** Wrap a ``zlib.Compress`` object, exposing the ``compress`` method.
 */
class ZlibCompress : private ackward::core::Object
{
public:
    /** Construct a ZlibCompress around an existing zlib.Compress
     * object. */
    ZlibCompress(boost::python::object obj) :
        ackward::core::Object (obj)
        {}

    /** Call the `compress` method on a Bytes object.
     */
    ackward::core::Bytes compress(const ackward::core::Bytes& x) const {
        return boost::python::extract<ackward::core::Bytes>(
            obj().attr("compress")(x));
    }
};

int main(int argc, char** argv)
{
    Py_Initialize();
    ackward::core::initialize();

    // Construct the compressor around a Python compressor.
    ZlibCompress c(
        ackward::core::import("zlib").attr("compressobj")());

    // Compress some data.
    ackward::core::Bytes compressed = 
        c.compress(
            ackward::core::Bytes(
                "This is a test", 14));

    return 0;
}
