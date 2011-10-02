from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

basicConfig_doc = '''
Does basic configuration for the logging system by creating a StreamHandler with a default Formatter and adding it to the root logger.

The following keyword arguments are supported.

\\rst
======== =============================================================================================================================================================
Format   Description
======== =============================================================================================================================================================
filename Specifies that a FileHandler be created, using the specified filename, rather than a StreamHandler.
filemode Specifies the mode to open the file, if filename is specified (if filemode is unspecified, it defaults to 'a').
format   Use the specified format string for the handler.
datefmt  Use the specified date/time format.
level    Set the root logger level to the specified level.
stream   Use the specified stream to initialize the StreamHandler. Note that this argument is incompatible with 'filename' - if both are present, 'stream' is ignored.
======== =============================================================================================================================================================
\\endrst
'''

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_MODULE_HPP',
        header_includes=[
            ('string',),
            ('ackward', 'logging', 'Types.hpp')
            ],
        impl_includes=[
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('boost', 'python', 'module.hpp'),
            ('boost', 'python', 'object.hpp'),
            ('ackward', 'logging', 'Logger.hpp'),
            ('ackward', 'logging', 'Module.hpp'),
            ],
        forward_declarations=[
            ('ackward', 'logging', 'class Logger'),
            ('boost', 'python', 'class dict')
            ],
        using=['namespace boost::python'])

def functions():
    functions = [
        ('Logger getLogger()',
         'Return the root logger.'),
        ('Logger getLogger(std::wstring name)',
         'Return a logger with the specified name.'),
        ('boost::python::object getLoggerClass()',
         'Return either the standard Logger class, or the last class passed to setLoggerClass().'),
        ('void log(Level l, std::wstring msg)',
         'Logs a message with level level on the root logger.'),
        ('void disable(Level l)',
         'Provides an overriding level lvl for all loggers which takes precedence over the logger\'s own level.'),
        ('void addLevelName(Level l, std::wstring name)',
         'Associates level lvl with text levelName in an internal dictionary, which is used to map numeric levels to a textual representation, for example when a Formatter formats a message. '),
        ('std::wstring getLevelName(Level l)',
         'Returns the textual representation of logging level lvl.'),
        # TODO: makeLogRecord
        ('void shutdown()',
         'Informs the logging system to perform an orderly shutdown by flushing and closing all handlers. This should be called at application exit and no further use of the logging system should be made after this call.'),
        ('void setLoggerClass(boost::python::object klass)',
         'Tells the logging system to use the class klass when instantiating a logger.'),
        ('void exception(std::wstring msg)',
         'Logs a message with level ERROR on the root logger. Exception info is added to the logging message. This function should only be called from an exception handler.'),
        ]

    for f in functions:
        function(f[0], doc=f[1])

    for lvl in ['debug', 'info', 'warning', 'error', 'critical']:
        function('void {0}(std::wstring msg)'.format(lvl),
                 doc='Logs a message with level {0} on the root logger.'.format(lvl.upper()))

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging'):
            with Module(name='logging'):
                functions()
    return t
