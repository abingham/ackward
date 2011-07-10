TODO list
---------

 * Add properties to LogRecord: args, exc_info, etc.
 * Logger should inherit privately from LoggerBase, and then "use" the
   necessary methods.
 * Consider replacing getter/setter methods with Property objects in
   the various property ackward directives.
 * Figure out how to make breathe include documentation for "using"
   methods, e.g. in Logger.hpp.
 * Change ackward doc parameter so that it gets automatically wrapped
   in "/** \rst <contents> \endrst */"

 * Examples for every class and function
  * Logging
   * Config.py
    * fileConfig **DONE**
   * FileHandler.cpp **DONE**
   * FileHandler.hpp **DONE**
   * Filter.py *DONE*
   * Formatter.cpp~
   * Formatter.py **DONE**
   * Handler.py **DONE**
   * Initialize.cpp **DONE**
   * Initialize.hpp **DONE** 
   * LogRecord.py **DONE**
   * Logger.cpp **DONE**
   * Logger.hpp **DONE**
   * LoggerAdapter.py
   * LoggerBase.py **DONE**
   * Module.py
   * NullHandler.cpp
   * NullHandler.hpp
   * SConscript
   * SocketHandler.cpp
   * SocketHandler.hpp
   * StreamHandler.cpp
   * StreamHandler.hpp
   * Types.cpp
   * Types.hpp
   * UserHandler.hpp
   * WatchedFileHandler.cpp
   * WatchedFileHandler.hpp
  * DateTime
  * Queue
  * Time
  * UUID
