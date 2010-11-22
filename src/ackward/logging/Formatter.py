from ackward.cls import Class, Constructor, Method
from ackward.translation_unit import ClassTranslationUnit

class Formatter(ClassTranslationUnit):
    
    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_FORMATTER'

    def forward_declarations(self):
        return [
            ('ackward', 'logging', 'class LogRecord'),
            ('boost', 'python', 'class tuple'),
            ]
    
    def header_includes(self):
        return [
            ('string',),
            ]

    def impl_includes(self):
        includes = [
            ('ackward', 'logging', 'Formatter.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ('boost', 'python', 'tuple.hpp'),
            ]

        return super(Formatter, self).impl_includes() + includes
    
    def objects(self):
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

        return {
            ('ackward', 'logging') : [c]
            }

def definition():
    return Formatter()
            
         
