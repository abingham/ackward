from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard = 'INCLUDE_ACKWARD_LOGGING_LOG_RECORD_HPP',
        forward_declarations = [('boost', 'python', 'class tuple')],
        header_includes=[
            ('string',),
            ('ackward', 'logging', 'Types.hpp'),
            ],
        impl_includes=[
            ('boost', 'python', 'tuple.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ])

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging'):

            with Class(name='LogRecord',
                       wrapped_class='logging.LogRecord'):

                Constructor(
                    signature=[
                        ('std::wstring', 'name'),
                        ('Level', 'lvl'),
                        ('std::wstring', 'pathname'),
                        ('int', 'lineno'),
                        ('std::wstring', 'msg'),
                        ('boost::python::tuple', 'args'),
                        ('boost::python::object', 'exc_info', 'boost::python::object()'),
                        ])

                method('std::wstring getMessage() const')

    return t
