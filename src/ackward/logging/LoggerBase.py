from ackward import (Class, 
                     method,
                     Property,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
        forward_declarations=[('ackward', 'logging', 'class Filter'),
                              ('ackward', 'logging', 'class Handler'),
                              ('ackward', 'logging', 'class LogRecord')],
        header_includes=[('ackward', 'logging', 'Types.hpp')],
        impl_includes=[('ackward', 'logging', 'LoggerBase.hpp'),
                       ('ackward', 'logging', 'Filter.hpp'),
                       ('ackward', 'logging', 'Handler.hpp'),
                       ('ackward', 'logging', 'LogRecord.hpp')])

    c = Class(
        name='LoggerBase',
        wrapped_class='logging.Logger')
    t += c
    
    c += Property(name='propagate', type='bool')
    c += method('void setLevel(Level l)')
    c += method('bool isEnabledFor(Level l) const')
    c += method('Level getEffectiveLevel() const')

    for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
        c += method('void %s(std::wstring msg) const' % lvl)

    c += method('void log(Level l, std::wstring msg) const')

    c += method('void addFilter(Filter f)')
    c += method('void removeFilter(Filter f)')
    c += method('bool filter(LogRecord r) const')

    c += method('void addHandler(Handler h)')
    c += method('void removeHandler(Handler h)')

    # TODO: findCaller...

    c += method('void handle(LogRecord r) const')

    # TODO: Record makeRecord(
         # const std::wstring& name, 
         # Level lvl, 
         # const std::wstring& fn, 
         # unsigned int lno, 
         # const std::wstring& msg
         # // args, exc_info[, func, extra]
         # ) const;

    return t
                
