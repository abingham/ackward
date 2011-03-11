from ackward import (Class,
                     Constructor,
                     method,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
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

    ns = Namespace('ackward', 'logging')
    t += ns

    c = Class(
        name='LoggerAdapter',
        wrapped_class='logging.LoggerAdapter')
    ns += c

    c += Constructor(
        signature=[('Logger', 'l'),
                   ('boost::python::dict', 'd')])

    for m in [
        'void debug(std::wstring msg) const',
        'void info(std::wstring msg) const',
        'void warning(std::wstring msg) const',
        'void error(std::wstring msg) const',
        'void critical(std::wstring msg) const',
        'void log(Level l, std::wstring msg) const',
        'void process(std::wstring msg, boost::python::dict kwargs) const',
        ]:
        c += method(m)

    return t
