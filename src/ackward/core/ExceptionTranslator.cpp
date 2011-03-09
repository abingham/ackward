#include <ackward/core/ExceptionTranslator.hpp>

#include <ackward/core/Util.hpp>

using namespace boost::python;

namespace ackward { namespace core 
{

void
ExceptionTranslator::translate(tuple excInfo)
{
    object exception = excInfo[0];
    object value = excInfo[1];
    object traceBack = excInfo[2];

    if (is_none(exception)) return;

    for (ThrowMap::const_iterator itr = map_.begin();
         itr != map_.end();
         ++itr)
    {
        if (PyErr_GivenExceptionMatches(itr->first.ptr(), 
                                        exception.ptr()))
        {
            itr->second(exception,
                        value,
                        traceBack);

            return;
        }
    }
}

bool ExceptionTranslator::add(boost::python::object excType,
                              Thrower thrower)
{
    for (ThrowMap::iterator itr = map_.begin();
            itr != map_.end();
            ++itr)
    {
        if (itr->first == excType)
        {
            itr->second = thrower;
            return true;
        }
    }

    map_.push_back(Mapping(excType, thrower));
    return false;
}

bool ExceptionTranslator::remove(boost::python::object excType)
{
    for (ThrowMap::iterator itr = map_.begin();
            itr != map_.end();
            ++itr)
    {
        if (itr->first == excType)
        {
            map_.erase(itr);
            return true;
        }
    }

    return false;
}

}}
