from ackward import (Class,
                     method,
                     Method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_HANDLER_HPP',
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
            ])

def methods(parent):
    m = [
        ('void setLevel(Level level)',
         'Set the logging level of this handler.'),
        ('void setFormatter(Formatter f)',
         'Set the formatter for this handler.'),
        ('void addFilter(Filter f)',
         'Add the specified filter to this handler.'),
        ('void removeFilter(Filter f)',
         'Remove the specified filter from this handler.'),
        ('void flush() const',
         'Ensure all logging output has been flushed.'),
        ('void close()',
         'Tidy up any resources used by the handler.')
        ]
    list(map(lambda m: method(m[0], parent=parent, doc=m[1]), m))

    Method(
        name='emit',
        signature=[('LogRecord', 'r')],
        const=True,
        virtual=True,
        parent=parent,
        doc='Do whatever it takes to actually log the specified logging record.')

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'logging', parent=t)
    cls = Class(name='Handler',
                wrapped_class='logging.Handler',
                parent=ns,
                doc='Handler instances dispatch logging events to specific destinations.')
    methods(cls)

    return t


