#ifndef INCLUDE_ACKWARD_CORE_PROPERTY_HPP
#define INCLUDE_ACKWARD_CORE_PROPERTY_HPP

#include <string>

#include <boost/call_traits.hpp>

#include <ackward/core/ExceptionTranslator.hpp>

namespace ackward {
namespace core {

template <typename T>
class Property
{
public:
    typedef T value_type;

    Property(const std::string& pythonName) :
        pythonName_ (pythonName)
        {}

    operator value_type()
        {
            try {
                return boost::python::extract<value_type>(
                    obj().attr(pythonName_));
            } TRANSLATE_PYTHON_EXCEPTION();
        }

    Property<value_type>& operator=(boost::call_traits<value_type>::const_reference v)
        {
            try {
                obj().attr(pythonName_) = val;
            } TRANSLATE_PYTHON_EXCEPTION();

            return *this;
        }

private:
    std::string pythonName_;

};

}
}

#endif
