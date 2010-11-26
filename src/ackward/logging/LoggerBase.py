from ackward.translation_unit import ClassTranslationUnit

from ackward.cls import Class, method

class LoggerBase(ClassTranslationUnit):
    def __init__(self):
        c = Class(
            name='LoggerBase',
            wrapped_class='logging.Logger')

        method('bool propagate() const', c)
        method('bool propagate(bool p) const', c)
        method('void setLevel(Level l)', c)
        method('bool isEnabledFor(Level l) const', c)
        method('Level getEffectiveLevel() const', c)
        for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
            method('void %s(std::wstring msg) const' % lvl, c)

        method('void log(Level l, std::wstring msg) const', c)

        method('void addFilter(Filter f)', c)
        method('void removeFilter(Filter f)', c)
        method('bool filter(LogRecord r) const', c)

        method('void addHandler(Handler h)', c)
        method('void removeHandler(Handler h)', c)

        # # TODO: findCaller...

        method('void handle(LogRecord r) const', c)

        # # TODO: Record makeRecord(
        #      # const std::wstring& name, 
        #      # Level lvl, 
        #      # const std::wstring& fn, 
        #      # unsigned int lno, 
        #      # const std::wstring& msg
        #      # // args, exc_info[, func, extra]
        #      # ) const;

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
                
