from ackward import (Class,
                     method,
                     Method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_HANDLER_HPP',
        forward_declarations=[
            ('ackward', 'logging', 'class Formatter'),
            ('ackward', 'logging', 'class Filter'),
            ('ackward', 'logging', 'class LogRecord'),
            ],
        header_includes=[
            ('ackward', 'core', 'Object.hpp'),
            ('ackward', 'logging', 'Types.hpp'),
            ],
        impl_includes=[
            ('ackward', 'logging', 'Formatter.hpp'),
            ('ackward', 'logging', 'Filter.hpp'),
            ('ackward', 'logging', 'Handler.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ])

def methods():
    m = [
        'void setLevel(Level level)',
        'void setFormatter(Formatter f)',
        'void addFilter(Filter f)',
        'void removeFilter(Filter f)',
        'void flush() const',
        'void close()',
        ]
    list(map(method, m))

    Method(
        name='emit',
        signature=[('LogRecord', 'r')],
        const=True,
        virtual=True)

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging'):
            with Class(name='Handler',
                       wrapped_class='logging.Handler'):
                methods()

    return t
    
        
