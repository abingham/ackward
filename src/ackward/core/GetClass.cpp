#include <ackward/core/GetClass.hpp>

#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

using namespace boost::algorithm;
using namespace boost::python;

namespace ackward { namespace core {

object getClass(const std::string& name)
{
    if (name.empty())
        return object();
    
    typedef std::vector<std::string> SV; 

    SV splitVec;
    split(splitVec, name, is_any_of("."));
    std::string className = splitVec.back();
    splitVec.pop_back();
    std::string modName = join(splitVec, ".");

    if (modName.empty())
        modName = "__builtin__";

    object mod = import(modName.c_str());
    // object cls = mod.attr(className.c_str());
    object cls = 
        object(
            handle<>(
                PyObject_GetAttrString(
                    mod.ptr(), 
                    className.c_str())));
    return cls;
}

}}
