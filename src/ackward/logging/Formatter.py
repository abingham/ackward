from ackward.cls import Class, Constructor, Method
from ackward.translation_unit import ClassTranslationUnit

class Formatter(ClassTranslationUnit):

    def __init__(self):
        c = Class(name='Formatter',
                  wrapped_class='logging.Formatter')

        Constructor(cls=c)

        Constructor(
            cls=c,
            signature=[
                ('boost::python::object', 'obj'),
                ])

        Method(
            cls=c,
            name='format',
            return_type='std::wstring',
            signature=[('LogRecord', 'record')],
            const=True)

        Method(
            cls=c,
            name='formatTime',
            return_type='std::wstring',
            signature=[('LogRecord', 'record')],
            const=True)

        Method(
            cls=c,
            name='formatTime',
            return_type='std::wstring',
            signature=[('LogRecord', 'record'),
                       ('std::wstring', 'datefmt')],
            const=True)

        Method(
            cls=c,
            name='formatException',
            return_type='std::wstring',
            signature=[('boost::python::tuple', 'exc')],
            const=True)

        super(Formatter, self).__init__(
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
                ],
            objects={ ('ackward', 'logging') : [c] })

def definition():
    return Formatter()
