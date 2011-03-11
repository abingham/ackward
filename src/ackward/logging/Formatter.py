import functools, operator

from ackward import (Class,
                     method,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
        preprocessor_guard='INCLUDE_ACKWARD_LOGGING_FORMATTER',
        forward_declarations=[
            ('ackward', 'logging', 'class LogRecord'),
            ('boost', 'python', 'class tuple'),
            ],
        header_includes=[
            ('string',),
            ],
        impl_includes=[
            ('ackward', 'logging', 'Formatter.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ('boost', 'python', 'tuple.hpp'),
            ])

    
    c = Class(name='Formatter',
              wrapped_class='logging.Formatter')
    t += c

    c += Constructor()

    methods = [
        'std::wstring format(LogRecord record) const',
        'std::wstring formatTime(LogRecord record) const',
        'std::wstring formatTime(LogRecord record, std::wstring datefmt const',
        'std::wstring formatException(boost::python::tuple exc) const']
    list(map(functools.partial(operator.iadd, c), [method(m) for m in method]))
    
    return t
