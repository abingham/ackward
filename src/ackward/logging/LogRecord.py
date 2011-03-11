from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
        preprocessor_guard = 'INCLUDE_ACKWARD_LOGGING_LOG_RECORD_HPP',
        forward_declarations = [('boost', 'python', 'class tuple')],
        header_includes=[
            ('string',),
            ('ackward', 'logging', 'Types.hpp'),
            ],
        impl_includes=[
            ('boost', 'python', 'tuple.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ])

    ns = Namespace('ackward', 'logging')x
    t += ns

    c = Class(name='LogRecord',
              wrapped_class='logging.LogRecord')
    ns += c

    c += Constructor(
        signature=[
            ('std::wstring', 'name'),
            ('Level', 'lvl'),
            ('std::wstring', 'pathname'),
            ('int', 'lineno'),
            ('std::wstring', 'msg'),
            ('boost::python::tuple', 'args'),
            ('boost::python::object', 'exc_info', 'boost::python::object()'),
            ])

    c += method('std::wstring getMessage() const')

    return t
