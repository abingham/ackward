from ackward.translation_unit import ClassTranslationUnit

from ackward.cls import Class, Method

class LoggerBase(ClassTranslationUnit):
    def __init__(self):
        c = Class(
            name='LoggerBase',
            wrapped_class='logging.Logger')

        Method(
            cls=c,
            name='propagate',
            const=True,
            return_type='bool')

        Method(
            cls=c,
            name='propagate',
            signature=[('bool', 'p')])
        
        Method(
            cls=c,
            name='setLevel',
            signature=[('Level', 'l')])

        super(LoggerBase, self).__init__(
            header_includes=[('ackward', 'logging', 'Types.hpp')],
            impl_includes=[('ackward', 'logging', 'LoggerBase.hpp')],
            objects={('ackward', 'logging') : [c]})

def definition():
    return LoggerBase()
                
