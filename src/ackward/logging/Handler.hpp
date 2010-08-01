#ifndef INCLUDE_BA_LOG_HANDLER_HPP
#define INCLUDE_BA_LOG_HANDLER_HPP

#include <boost/python/make_function.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/Object.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp>

namespace ackward { namespace logging 
{

class Filter;
class Formatter;

class Handler : private core::Object
{
public:

    Handler(boost::python::object);

    /**
      Sets the threshold for this handler to lvl. Logging messages
      which are less severe than lvl will be ignored. When a handler
      is created, the level is set to NOTSET (which causes all
      messages to be processed).
    */
    void setLevel(Level l);

    /**
       Sets the Formatter for this handler to form.
    */
    void setFormatter(Formatter f);

    /**
       Adds the specified filter filt to this handler.
    */
    void addFilter(Filter f);
    
    /**
       Removes the specified filter filt from this handler.
    */
    void removeFilter(Filter f);

    /**
       Ensure all logging output has been flushed. This version does
       nothing and is intended to be implemented by subclasses.
    */
    void flush() const;

    /**
       Tidy up any resources used by the handler. This version does no
       output but removes the handler from an internal list of
       handlers which is closed when shutdown() is called. Subclasses
       should ensure that this gets called from overridden close()
       methods.
    */
    void close();

    virtual void emit(const LogRecord&) const;

    using core::Object::obj;
};

class StreamHandler : public Handler
{
public:
    StreamHandler();
    StreamHandler(boost::python::object stream);
};

class FileHandler : public Handler
{
public:
    FileHandler(const std::wstring& filename,
                const std::string& mode="a", 
                const std::string& encoding="", 
                bool delay=false);
};

class WatchedFileHandler : public Handler
{
public:
    WatchedFileHandler(const std::wstring& filename,
                       const std::string& mode="a", 
                       const std::string& encoding="",
                       bool delay=false);
};

class SocketHandler : public Handler
{
public:
    SocketHandler(const std::wstring& host,
                  unsigned int port);
};

template <typename Functor>
class Handler_ : public Handler
{
public:
    Handler_() :
        Handler ( module().attr("Handler")() )
        {
            boost::python::object func = 
                boost::python::make_function(Functor::emit);
            obj().attr("emit") = func;
        }
};

struct NullFunctor
{
    static void emit(const LogRecord&) {}
};

typedef Handler_<NullFunctor> NullHandler;

}}

#endif
