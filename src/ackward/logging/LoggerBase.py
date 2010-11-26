from ackward.translation_unit import ClassTranslationUnit

from ackward.cls import Class, Method

const=True

def build_sig(sig):
    return [tuple(a.split()) for a in sig]

def method(rtype, cls, name, sig, const=False):
    Method(
        cls=cls,
        name=name,
        return_type=rtype,
        signature=build_sig(sig),
        const=const)

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

        method('bool', c, 'isEnabledFor', ['Level l'], const)
        method('Level', c, 'getEffectiveLevel', [], const)
        for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
            method('void', c, lvl, ['std::wstring msg'], const)
        
        method('void', c, 'log', ['Level l', 'std::wstring msg'], const)

        method('void', c, 'addFilter', ['Filter f'])
        method('void', c, 'removeFilter', ['Filter f'])
        method('bool', c, 'filter', ['LogRecord r'], const)

        method('void', c, 'addHandler', ['Handler h'])
        method('void', c, 'removeHandler', ['Handler h'])

        # TODO: findCaller...

        method('void', c, 'handle', ['LogRecord r'], const)

        # TODO: Record makeRecord(
             # const std::wstring& name, 
             # Level lvl, 
             # const std::wstring& fn, 
             # unsigned int lno, 
             # const std::wstring& msg
             # // args, exc_info[, func, extra]
             # ) const;

        super(LoggerBase, self).__init__(
            forward_declarations=[('ackward', 'logging', 'class Filter'),
                                  ('ackward', 'logging', 'class Handler'),
                                  ('ackward', 'logging', 'class LogRecord')],
            header_includes=[('ackward', 'logging', 'Types.hpp')],
            impl_includes=[('ackward', 'logging', 'LoggerBase.hpp'),
                           ('ackward', 'logging', 'Filter.hpp'),
                           ('ackward', 'logging', 'Handler.hpp'),
                           ('ackward', 'logging', 'LogRecord.hpp')],
            objects={('ackward', 'logging') : [c]})

def definition():
    return LoggerBase()
                
