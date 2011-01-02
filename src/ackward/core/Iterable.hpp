#ifndef INCLUDE_BA_LOG_DETAIL_ITERABLE_HPP
#define INCLUDE_BA_LOG_DETAIL_ITERABLE_HPP

#include <Python.h>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/python/object_fwd.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Object.hpp>
#include <ackward/core/Util.hpp>

namespace ackward { namespace core
{

template <typename T, bool IsConst=boost::is_const<T>::value>
class Iterable;

// iterable of "non-const" objects
template <typename T>
class Iterable<T, false> : private Object
{
public:
    Iterable(boost::python::object obj) :
        Object (obj)
        {}

    std::size_t size() const
        {
            return boost::python::len(obj());
        }

    bool empty() const
        {
            return size() == 0;
        }

public: // iteration

    class iterator
        : public boost::iterator_facade<
          iterator
        , T
        , boost::forward_traversal_tag
        , T
        , T
        >
    {
    public:
        iterator() {}
        iterator(boost::python::object iter) : iter_ (iter) {}

    private:
        friend class boost::iterator_core_access;
        
        void increment() 
            {
                try 
                {
                    try {
                        val_ = iter_.attr("next")();
                    } TRANSLATE_PYTHON_EXCEPTION();
                }
                catch (const StopIteration&) 
                {
                    val_ = iter_ = boost::python::object();
                }
            }
        
        bool equal(iterator const& other) const
            {
                return this->iter_ == other.iter_;
            }
        
        T dereference() const 
            { 
                return T(val_);
            }
        
    private:
        boost::python::object iter_;
        boost::python::object val_;
    };

    class const_iterator
        : public boost::iterator_facade<
          const_iterator
        , const T
        , boost::forward_traversal_tag
        , const T
        , const T
        >
    {
    public:
        const_iterator() {}
        const_iterator(boost::python::object iter) : iter_ (iter) {}

    private:
        friend class boost::iterator_core_access;
        
        void increment() 
            {
                try 
                {
                    try {
                        val_ = iter_.attr("next")();
                    } TRANSLATE_PYTHON_EXCEPTION();
                }
                catch (const StopIteration&) 
                {
                    val_ = iter_ = boost::python::object();
                }
            }
        
        bool equal(const_iterator const& other) const
            {
                return this->iter_ == other.iter_;
            }
        
        T dereference() const 
            { 
                return T(val_);
            }
        
    private:
        boost::python::object iter_;
        boost::python::object val_;
    };

    iterator begin() { return iterator(iter(obj())); }
    iterator end() { return iterator(); }

    const_iterator begin() const { return const_iterator(iter(obj())); }
    const_iterator end() const { return const_iterator(); }

    using Object::obj;
};

// iterable of "const" objects
template <typename T>
class Iterable<T, true> : private Object
{
public:
    Iterable(const Iterable<typename boost::remove_const<T>::type>& other) :
        Object (other.obj())
        {}

    Iterable(boost::python::object obj) :
        Object (obj)
        {}

    std::size_t size() const
        {
            return boost::python::len(obj());
        }

    bool empty() const
        {
            return size() == 0;
        }

public: // iteration

    class iterator
        : public boost::iterator_facade<
          iterator
        , T
        , boost::forward_traversal_tag
        >
    {
    public:
        iterator() {}
        iterator(boost::python::object iter) : iter_ (iter) {}

    private:
        friend class boost::iterator_core_access;
        
        void increment() 
            {
                try 
                {
                    try {
                        val_ = iter_.attr("next")();
                    } TRANSLATE_PYTHON_EXCEPTION();
                }
                catch (const StopIteration&) 
                {
                    val_ = iter_ = boost::python::object();
                }
            }
        
        bool equal(iterator const& other) const
            {
                return this->iter_ == other.iter_;
            }
        
        T dereference() const 
            { 
                return T(val_);
            }
        
    private:
        boost::python::object iter_;
        boost::python::object val_;
    };

    typedef iterator const_iterator;

    iterator begin() { return iterator(iter(obj())); }
    iterator end() { return iterator(); }

    const_iterator begin() const { return const_iterator(iter(obj())); }
    const_iterator end() const { return const_iterator(); }

    using Object::obj;
};

}}

#endif
