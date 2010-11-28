from ackward.translation_unit import ClassTranslationUnit
from ackward.cls import Constructor, Class, method

class LoggerAdapter(ClassTranslationUnit):
    def __init__(self):
        c = Class(
            name='LoggerAdapter',
            wrapped_class='logging.LoggerAdapter')

        Constructor(
            cls=c,
            signature=[('Logger', 'l'),
                       ('boost::python::dict', 'd')])

        method('void debug(std::wstring msg) const', c)
        method('void info(std::wstring msg) const', c)
        method('void warning(std::wstring msg) const', c)
        method('void error(std::wstring msg) const', c)
        method('void critical(std::wstring msg) const', c)
        method('void log(Level l, std::wstring msg) const', c)
        method('void process(std::wstring msg, boost::python::dict kwargs) const', c)
        
        super(LoggerAdapter, self).__init__(
            forward_declarations=[
                ('boost', 'python', 'class dict'),
                ('ackward', 'logging', 'class Logger'),
                ],
            header_includes=[
                ('string',),
                ('ackward', 'logging', 'Types.hpp'),
                ],
            impl_includes=[
                ('boost', 'python', 'dict.hpp'),
                ('ackward', 'logging', 'LoggerAdapter.hpp'),
                ('ackward', 'logging', 'Logger.hpp')],
            objects={('ackward', 'logging') : [c]})

def definition():
    return LoggerAdapter()
