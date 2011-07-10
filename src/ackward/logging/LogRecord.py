from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     TranslationUnit)

log_record_doc='''\\rst
A wrapper around Python `logging.LogRecord <http://docs.python.org/py3k/library/logging.html#logging.LogRecord>`_ objects.
\\endrst'''

get_message_doc='''Returns the message for this LogRecord instance
after merging any user-supplied arguments with the message.

If the user-supplied message argument to the logging call is not a
string, str() is called on it to convert it to a string. This allows
use of user-defined classes as messages, whose __str__ method can
return the actual format string to be used.
'''

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
                       wrapped_class='logging.LogRecord',
                       doc=log_record_doc):

                Constructor(
                    signature=[
                        ('std::wstring', 'name'),
                        ('Level', 'lvl'),
                        ('std::wstring', 'pathname'),
                        ('int', 'lineno'),
                        ('std::wstring', 'msg'),
                        ('boost::python::tuple', 'args'),
                        ('boost::python::object', 'exc_info', 'boost::python::object()'),
                        ],
                    doc='Create a new LogRecord.')

                method('std::wstring getMessage() const',
                       doc=get_message_doc)

    return t
