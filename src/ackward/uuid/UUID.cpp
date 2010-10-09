#include <ackward/uuid/UUID.hpp>

#include <boost/python/object.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Tuple.hpp>

using namespace boost::python;

namespace ackward {
namespace uuid {

UUID UUID::fromHex(const std::string& hex) {
    try {
        object obj = UUID::cls()(hex);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

UUID UUID::fromBytes(const std::string& bytes)
{
    try {
        object obj = UUID::cls()(object(), 
                                 bytes);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

UUID UUID::fromBytes_LE(const std::string& bytes_le)
{
    try {
        object obj = UUID::cls()(object(), 
                                 object(),
                                 bytes_le);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

UUID UUID::fromFields(const Fields& f)
{
    try {
        object obj = UUID::cls()(object(), 
                                 object(),
                                 object(),
                                 core::convertTuple(f));
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

// UUID UUID::fromInt(uint128_ref i)
// {
//     try {
//         object obj = UUID::cls()(object(), 
//                                  object(),
//                                  object(),
//                                  object(),
//                                  i);
//         return UUID(obj);
//     } TRANSLATE_PYTHON_EXCEPTION();
// }

Fields UUID::fields() const
{
    try {
        return core::convertTuple<Fields>(
            boost::python::extract<boost::python::tuple>(
                obj().attr("fields")));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}

#include <ackward/uuid/UUID_akw.ipp>

} // namespace uuid
} // namespace ackward