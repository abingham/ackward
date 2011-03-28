from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
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
            ('ackward', 'logging', 'Logger.hpp')])

def methods():
    m = [
        'void debug(std::wstring msg) const',
        'void info(std::wstring msg) const',
        'void warning(std::wstring msg) const',
        'void error(std::wstring msg) const',
        'void critical(std::wstring msg) const',
        'void log(Level l, std::wstring msg) const',
        'void process(std::wstring msg, boost::python::dict kwargs) const',
        ]
    list(map(method, m))

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging'):
            with Class(name='LoggerAdapter',
                       wrapped_class='logging.LoggerAdapter'):
                Constructor(
                    signature=[('Logger', 'l'),
                               ('boost::python::dict', 'd')])
                methods()
    return t
