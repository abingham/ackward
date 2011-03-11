from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
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

    ns = Namespace('ackward', 'logging')
    t += ns

    ns += Module(name='logging')
    
    for func in [
        'Logger getLogger()',
        'Logger getLogger(std::wstring name)',
        'boost::python::object getLoggerClass()',
        'void log(Level l, std::wstring msg)',
        'void disable(Level l)',
        'void addLevelName(Level l, std::wstring name)',
        'std::wstring getLevelName(Level l)',
        # TODO: makeLogRecord
        'void basicConfig()',
        'void basicConfig(boost::python::dict kwargs)',
        'void shutdown()',
        'void setLoggerClass(boost::python::object klass)',
        ]:
        ns += function(func)
        
    for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
        ns += function('void {0}(std::wstring msg)'.format(lvl))

    return t
