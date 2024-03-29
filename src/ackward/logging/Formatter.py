import functools, operator

from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     TranslationUnit)

formatter_doc = '''\\rst
Wrapper around ``logging.Formatter`` objects. See `<http://docs.python.org/py3k/library/logging.html#formatter-objects>`_ for more information.
\\endrst'''

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_FORMATTER',
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

def methods(parent):
    m = [
        'std::wstring format(LogRecord record) const',
        'std::wstring formatTime(LogRecord record) const',
        'std::wstring formatTime(LogRecord record, std::wstring datefmt) const',
        'std::wstring formatException(boost::python::tuple exc) const'
        ]
    list(map(lambda m: method(m, parent=parent), m))

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'logging', parent=t)
    cls = Class(name='Formatter',
                wrapped_class='logging.Formatter',
                parent=ns,
                doc=formatter_doc)
    Constructor(parent=cls)
    methods(parent=cls)

    return t
