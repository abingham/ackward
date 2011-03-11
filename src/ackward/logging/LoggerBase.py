from ackward import (Class, 
                     method,
                     Namespace,
                     Property,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        forward_declarations=[('ackward', 'logging', 'class Filter'),
                              ('ackward', 'logging', 'class Handler'),
                              ('ackward', 'logging', 'class LogRecord')],
        header_includes=[('ackward', 'logging', 'Types.hpp')],
        impl_includes=[('ackward', 'logging', 'LoggerBase.hpp'),
                       ('ackward', 'logging', 'Filter.hpp'),
                       ('ackward', 'logging', 'Handler.hpp'),
                       ('ackward', 'logging', 'LogRecord.hpp')])

def methods():
    m = [
        'void setLevel(Level l)',
        'bool isEnabledFor(Level l) const',
        'Level getEffectiveLevel() const',
        'void log(Level l, std::wstring msg) const',
        'void addFilter(Filter f)',
        'void removeFilter(Filter f)',
        'bool filter(LogRecord r) const',
        'void addHandler(Handler h)',
        'void removeHandler(Handler h)',
        'void handle(LogRecord r) const',
        ]

    for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
        m.append('void {0}(std::wstring msg) const'.format(lvl))

    list(map(method, m))

def definition():
    with tunit() as t:
        with Namespace('ackward', 'logging'):
            with Class(name='LoggerBase',
                       wrapped_class='logging.Logger'):
    
                Property(name='propagate', type='bool')
                methods()

    return t
                
