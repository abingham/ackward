from ackward import (Class,
                     Constructor,
                     method,
                     Namespace,
                     Property,
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
        header_includes=[
            ('string',),
            ('boost', 'python', 'tuple.hpp'),
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

                properties = [
                    ('args', 'boost::python::tuple'),
                    ('asctime', 'std::wstring',
                     'Only exists after the LogRecord is emitted.'),
                    ('created', 'float'),
                    ('exc_info', 'boost::python::tuple',
                     'Will be "None" if there is not exception info.'),
                    ('filename', 'std::wstring'),
                    ('funcName', 'std::wstring',
                     'Will be "None" prior to being emitted.'),
                    ('levelname', 'std::wstring'),
                    ('levelno', 'int'),
                    ('lineno', 'int'),
                    ('module', 'std::wstring'),
                    ('msecs', 'float'),
                    ('message', 'std::wstring',
                     'Will be "None" prior to being emitted.'),
                    ('msg', 'std::wstring'),
                    ('name', 'std::wstring'),
                    ('pathname', 'std::wstring'),
                    ('process', 'int'),
                    ('processName', 'std::wstring'),
                    ('relativeCreated', 'float'),
                    ('stack_info', 'boost::python::object'),
                    ('thread', 'unsigned long'),
                    ('threadName', 'std::wstring')
                    ]

                for prop in properties:
                    if len(prop) == 3:
                        prop_name,prop_type,doc = prop
                    else:
                        prop_name,prop_type,doc = prop + (None,)
                    Property(prop_name, prop_type, read_only=True,doc=doc)

    return t
