from ackward import (Class,
                     method,
                     Namespace,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
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

    ns = Namespace('ackward', 'logging')
    t += ns

    ns += Class(
        name='Handler',
        wrapped_class='logging.Handler')
        
    methods = [
        'void setLevel(Level level)',
        'void setFormatter(Formatter f)',
        'void addFilter(Filter f)',
        'void removeFilter(Filter f)',
        'void flush() const',
        'void close()',
        'virtual void emit(LogRecord r) const'
        ]

    for m in methods:
        ns += method(m)

    return t
    
        
