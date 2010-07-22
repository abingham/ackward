#ifndef BA_LOGGING_LOGGER_HPP
#define BA_LOGGING_LOGGER_HPP

#include <ackward/logging/Types.hpp>
#include <ackward/core/Iterable.hpp>
#include <ackward/core/Object.hpp>

namespace boost { namespace python {

class tuple;

}}

namespace ackward { namespace logging 
{

class Filter;
class Handler;
class LogRecord;

class Logger : private core::Object {
public:
    Logger(boost::python::object);

    /**
       If this evaluates to false, logging messages are not passed by
       this logger or by child loggers to higher level (ancestor)
       loggers. The constructor sets this attribute to 1.
    */
    bool propagate() const;
    void propagate(bool);

    /**
       Sets the threshold for this logger to lvl. Logging messages
       which are less severe than lvl will be ignored. When a logger
       is created, the level is set to NOTSET (which causes all
       messages to be processed when the logger is the root logger, or
       delegation to the parent when the logger is a non-root
       logger). Note that the root logger is created with level
       WARNING.
       
       The term “delegation to the parent” means that if a logger has
       a level of NOTSET, its chain of ancestor loggers is traversed
       until either an ancestor with a level other than NOTSET is
       found, or the root is reached.
       
       If an ancestor is found with a level other than NOTSET, then
       that ancestor’s level is treated as the effective level of the
       logger where the ancestor search began, and is used to
       determine how a logging event is handled.
       
       If the root is reached, and it has a level of NOTSET, then all
       messages will be processed. Otherwise, the root’s level will be
       used as the effective level.
    */
    void setLevel(Level l);

    /**
       Indicates if a message of severity lvl would be processed by
       this logger. This method checks first the module-level level
       set by logging.disable(lvl) and then the logger’s effective
       level as determined by getEffectiveLevel().
    */
    bool isEnabledFor(Level l) const;

    /**
       Indicates the effective level for this logger. If a value other
       than NOTSET has been set using setLevel(), it is
       returned. Otherwise, the hierarchy is traversed towards the
       root until a value other than NOTSET is found, and that value
       is returned.
    */
    Level getEffectiveLevel() const;

    /**
       Logs a message with level DEBUG on this logger. The msg is the
       message format string, and the args are the arguments which are
       merged into msg using the string formatting operator. (Note
       that this means that you can use keywords in the format string,
       together with a single dictionary argument.)
       
       There are two keyword arguments in kwargs which are inspected:
       exc_info which, if it does not evaluate as false, causes
       exception information to be added to the logging message. If an
       exception tuple (in the format returned by sys.exc_info()) is
       provided, it is used; otherwise, sys.exc_info() is called to
       get the exception information.
   
       The other optional keyword argument is extra which can be used
       to pass a dictionary which is used to populate the __dict__ of
       the LogRecord created for the logging event with user-defined
       attributes. These custom attributes can then be used as you
       like. For example, they could be incorporated into logged
       messages. For example:
   
           FORMAT = "%(asctime)-15s %(clientip)s %(user)-8s %(message)s"
           logging.basicConfig(format=FORMAT)
           d = { 'clientip' : '192.168.0.1', 'user' : 'fbloggs' }
           logger = logging.getLogger("tcpserver")
           logger.warning("Protocol problem: %s", "connection reset", extra=d)

       would print something like
   
          2006-02-08 22:20:02,165 192.168.0.1 fbloggs  Protocol problem: connection reset

      The keys in the dictionary passed in extra should not clash with
      the keys used by the logging system. (See the Formatter
      documentation for more information on which keys are used by the
      logging system.)
   
      If you choose to use these attributes in logged messages, you
      need to exercise some care. In the above example, for instance,
      the Formatter has been set up with a format string which expects
      ‘clientip’ and ‘user’ in the attribute dictionary of the
      LogRecord. If these are missing, the message will not be logged
      because a string formatting exception will occur. So in this
      case, you always need to pass the extra dictionary with these
      keys.
   
      While this might be annoying, this feature is intended for use
      in specialized circumstances, such as multi-threaded servers
      where the same code executes in many contexts, and interesting
      conditions which arise are dependent on this context (such as
      remote client IP address and authenticated user name, in the
      above example). In such circumstances, it is likely that
      specialized Formatters would be used with particular Handlers.
   
      Changed in version 2.5: extra was added.

      ----
      
      TODO: Keywords and args semantics
    */
    void debug(const std::wstring& msg) const;

    /**
       Logs a message with level INFO on this logger. The arguments
       are interpreted as for debug().
    */
    void info(const std::wstring& msg) const;

    /**
       Logs a message with level WARNING on this logger. The arguments
       are interpreted as for debug().
    */
    void warning(const std::wstring& msg) const;

    /**
       Logs a message with level ERROR on this logger. The arguments
       are interpreted as for debug().
    */
    void error(const std::wstring& msg) const;
    
    /**
       Logs a message with level CRITICAL on this logger. The
       arguments are interpreted as for debug().
    */
    void critical(const std::wstring& msg) const;

    /**
       Logs a message with integer level lvl on this logger. The other
       arguments are interpreted as for debug().
    */
    void log(Level l, const std::wstring& msg) const;

    /**
       Logs a message with level ERROR on this logger. The arguments
       are interpreted as for debug(). Exception info is added to the
       logging message. This method should only be called from an
       exception handler.
    */
    // void exception(const std::wstring& msg) const;

    /**
       Adds the specified filter filt to this logger.
    */
    void addFilter(Filter f);

    /**
       Removes the specified filter filt from this logger.
    */
    void removeFilter(Filter f);

    typedef core::Iterable<Filter> Filters;
    typedef core::Iterable<const Filter> ConstFilters;
    Filters filters();
    ConstFilters filters() const;

    /**
       Applies this logger’s filters to the record and returns a true
       value if the record is to be processed.
    */
    bool filter(LogRecord r) const;

    /**
       Adds the specified handler hdlr to this logger.
    */
    void addHandler(const Handler& h);

    /**
       Removes the specified handler hdlr from this logger.
    */
    void removeHandler(const Handler& h);

    typedef core::Iterable<Handler> Handlers;
    typedef core::Iterable<const Handler> ConstHandlers;
    Handlers handlers();
    ConstHandlers handlers() const;

    /**
       Finds the caller’s source filename and line number. Returns the
       filename, line number and function name as a 3-element tuple.
       
       Changed in version 2.4: The function name was added. In earlier
       versions, the filename and line number were returned as a
       2-element tuple..

       TODO: Possible from c++?
    */
    // boost::python::tuple findCaller() const;

    /**
       Handles a record by passing it to all handlers associated with
       this logger and its ancestors (until a false value of propagate
       is found). This method is used for unpickled records received
       from a socket, as well as those created locally. Logger-level
       filtering is applied using filter().
    */
    void handle(LogRecord) const;

    /**
       This is a factory method which can be overridden in subclasses
       to create specialized LogRecord instances.

       Changed in version 2.5: func and extra were added.
    */
    // Record makeRecord(
    //     const std::wstring& name, 
    //     Level lvl, 
    //     const std::wstring& fn, 
    //     unsigned int lno, 
    //     const std::wstring& msg
    //     // args, exc_info[, func, extra]
    //     ) const;

    using core::Object::obj;
};                                                                                                                                                                                                                                                       
}}

#endif
