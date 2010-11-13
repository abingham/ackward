#ifndef INCLUDE_ACKWARD_LOGGING_LOGGER_MODULE_LEVEL_HPP
#define INCLUDE_ACKWARD_LOGGING_LOGGER_MODULE_LEVEL_HPP

#include <string>

#include <boost/call_traits.hpp>
#include <boost/python/object_fwd.hpp>

#include <ackward/logging/Types.hpp>

namespace boost { namespace python {

class dict;

}}

namespace ackward { namespace logging 
{

class Logger;

#include <ackward/logging/Module_akw.hpp>

/**
   Return either the standard Logger class, or the last class passed
   to setLoggerClass(). This function may be called from within a new
   class definition, to ensure that installing a customised Logger
   class will not undo customisations already applied by other
   code. For example:

     class MyLogger(logging.getLoggerClass()): # ... override
                                               # behaviour here 
*/
boost::python::object getLoggerClass();

/**
   Logs a message with level DEBUG on the root logger. The msg is the
   message format string, and the args are the arguments which are
   merged into msg using the string formatting operator. (Note that
   this means that you can use keywords in the format string, together
   with a single dictionary argument.)

   There are two keyword arguments in kwargs which are inspected:
   exc_info which, if it does not evaluate as false, causes exception
   information to be added to the logging message. If an exception
   tuple (in the format returned by sys.exc_info()) is provided, it is
   used; otherwise, sys.exc_info() is called to get the exception
   information.
   
   The other optional keyword argument is extra which can be used to
   pass a dictionary which is used to populate the __dict__ of the
   LogRecord created for the logging event with user-defined
   attributes. These custom attributes can then be used as you
   like. For example, they could be incorporated into logged
   messages. For example:
   
     FORMAT = "%(asctime)-15s %(clientip)s %(user)-8s %(message)s" 

     logging.basicConfig(format=FORMAT)
     d = {'clientip': '192.168.0.1', 'user': 'fbloggs'}
     logging.warning("Protocol problem: %s", "connection reset", extra=d)

   would print something like

   2006-02-08 22:20:02,165 192.168.0.1 fbloggs Protocol problem:
   connection reset The keys in the dictionary passed in extra should
   not clash with the keys used by the logging system. (See the
   Formatter documentation for more information on which keys are used
   by the logging system.)

   If you choose to use these attributes in logged messages, you need
   to exercise some care. In the above example, for instance, the
   Formatter has been set up with a format string which expects
   ‘clientip’ and ‘user’ in the attribute dictionary of the
   LogRecord. If these are missing, the message will not be logged
   because a string formatting exception will occur. So in this case,
   you always need to pass the extra dictionary with these keys.

   While this might be annoying, this feature is intended for use in
   specialized circumstances, such as multi-threaded servers where the
   same code executes in many contexts, and interesting conditions
   which arise are dependent on this context (such as remote client IP
   address and authenticated user name, in the above example). In such
   circumstances, it is likely that specialized Formatters would be
   used with particular Handlers.

   Changed in version 2.5: extra was added.

   TODO: Semantics for keywords, etc.
*/
void debug(const std::wstring& msg);

/** 
    Logs a message with level INFO on the root logger. The arguments
    are interpreted as for debug().  
*/
void info(const std::wstring& msg);

/**
   Logs a message with level WARNING on the root logger. The arguments
   are interpreted as for debug().  */
void warning(const std::wstring& msg);

/**
   Logs a message with level ERROR on the root logger. The arguments
   are interpreted as for debug().  
*/
void error(const std::wstring& msg);

/**
   Logs a message with level CRITICAL on the root logger. The
   arguments are interpreted as for debug().  
*/
void critical(const std::wstring& msg);

/**
   Logs a message with level ERROR on the root logger. The arguments
   are interpreted as for debug(). Exception info is added to the
   logging message. This function should only be called from an
   exception handler.  

   TODO: Consider this one. Does it make sense in a C++ context?
*/
void exception(const std::wstring& msg);

/**
   Logs a message with level level on the root logger. The other
   arguments are interpreted as for debug().  
*/
void log(Level l, const std::wstring& msg);

/**
   Provides an overriding level lvl for all loggers which takes
   precedence over the logger’s own level. When the need arises to
   temporarily throttle logging output down across the whole
   application, this function can be useful.  
*/
void disable(Level l);

/**
    Associates level lvl with text levelName in an internal
    dictionary, which is used to map numeric levels to a textual
    representation, for example when a Formatter formats a
    message. This function can also be used to define your own
    levels. The only constraints are that all levels used must be
    registered using this function, levels should be positive integers
    and they should increase in increasing order of severity.  
*/
void addLevelName(Level l, const std::wstring& name);

/**
   Returns the textual representation of logging level lvl. If the
   level is one of the predefined levels CRITICAL, ERROR, WARNING,
   INFO or DEBUG then you get the corresponding string. If you have
   associated levels with names using addLevelName() then the name you
   have associated with lvl is returned. If a numeric value
   corresponding to one of the defined levels is passed in, the
   corresponding string representation is returned. Otherwise, the
   string “Level %s” % lvl is returned.  
*/
std::wstring getLevelName(Level l);

/**
   Creates and returns a new LogRecord instance whose attributes are
   defined by attrdict. This function is useful for taking a pickled
   LogRecord attribute dictionary, sent over a socket, and
   reconstituting it as a LogRecord instance at the receiving end.  
*/
// LogRecord makeLogRecord(boost::python::dict attrDict);

/**
   Does basic configuration for the logging system by creating a
   StreamHandler with a default Formatter and adding it to the root
   logger. The function does nothing if any handlers have been defined
   for the root logger. The functions debug(), info(), warning(),
   error() and critical() will call basicConfig() automatically if no
   handlers are defined for the root logger.

   This function does nothing if the root logger already has handlers
   configured.

   Changed in version 2.4: Formerly, basicConfig() did not take any
   keyword arguments.

   The following keyword arguments are supported.

   Format:	Description

   filename: Specifies that a FileHandler be created, using the
   specified filename, rather than a StreamHandler.

   filemode: Specifies the mode to open the file, if filename is
   specified (if filemode is unspecified, it defaults to ‘a’).

   format: Use the specified format string for the handler.

   datefmt: Use the specified date/time format.

   level: Set the root logger level to the specified level.

   stream: Use the specified stream to initialize the
   StreamHandler. Note that this argument is incompatible with ‘filename’
   - if both are present, ‘stream’ is ignored.  
*/
void basicConfig();
void basicConfig(boost::python::dict kwargs);

/**
   Informs the logging system to perform an orderly shutdown by
   flushing and closing all handlers. This should be called at
   application exit and no further use of the logging system should be
   made after this call.  */
void shutdown();

/**
   Tells the logging system to use the class klass when instantiating
   a logger. The class should define __init__() such that only a name
   argument is required, and the __init__() should call
   Logger.__init__(). This function is typically called before any
   loggers are instantiated by applications which need to use custom
   logger behavior.  
*/
void setLoggerClass(boost::python::object klass);

}}

#endif
