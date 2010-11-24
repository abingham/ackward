from ackward.cls import Class, Method
from ackward.translation_unit import ClassTranslationUnit

class Handler(ClassTranslationUnit):

    def __init__(self):
        c = Class(
            name='Handler',
            wrapped_class='logging.Handler')
        
        Method(
            cls=c,
            name='setLevel',
            signature=[('Level', 'level')])

        Method(
            cls=c,
            name='setFormatter',
            signature=[('Formatter', 'f')])

        Method(
            cls=c,
            name='addFilter',
            signature=[('Filter', 'f')])

        Method(
            cls=c,
            name='removeFilter',
            signature=[('Filter', 'f')])

        Method(
            cls=c,
            name='flush',
            const=True)

        Method(
            cls=c,
            name='close')

        Method(
            cls=c,
            name='emit',
            signature=[('LogRecord', 'r')],
            const=True,
            virtual=Method.VIRTUAL)

        super(Handler, self).__init__(
            preprocessor_guard='INCLUDE_ACKWARD_LOGGING_HANDLER_HPP',
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
                ],
            objects={ ('ackward', 'logging') : [c] })

# class NullHandler : public Handler_<NullHandler>
# {
# public:
#     static void emit_(const LogRecord&) {}
# };

def definition():
    return Handler()
    
        
