from ackward import (Class,
                     method,
                     Namespace,
                     Property,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        forward_declarations=[('ackward', 'logging', 'class Filter'),
                              ('ackward', 'logging', 'class Handler'),
                              ('ackward', 'logging', 'class LogRecord')],
        header_includes=[('ackward', 'logging', 'Types.hpp')],
        impl_includes=[('ackward', 'logging', 'LoggerBase.hpp'),
                       ('ackward', 'logging', 'Filter.hpp'),
                       ('ackward', 'logging', 'Handler.hpp'),
                       ('ackward', 'logging', 'LogRecord.hpp')])

def methods(parent):
    methods = [
        ('void setLevel(Level l)',
         'Sets the threshold for this logger.'),
        ('bool isEnabledFor(Level l) const',
         'Indicates if a message of severity ``lvl`` would be processed by this logger.'),
        ('Level getEffectiveLevel() const',
         'Indicates the effective level for this logger.'),
        ('void log(Level lvl, std::wstring msg) const',
         'Logs a message with level ``lvl`` on this logger.'),
        ('void addFilter(Filter f)',
         'Adds the specified filter ``filt`` to this logger.'),
        ('void removeFilter(Filter f)',
         'Removes the specified filter ``filt`` from this logger.'),
        ('bool filter(LogRecord r) const',
         'Applies this logger\'s filters to the record and returns a true value if the record is to be processed.'),
        ('void addHandler(Handler h)',
         'Adds the specified handler ``hdlr`` to this logger.'),
        ('void removeHandler(Handler h)',
         'Removes the specified handler hdlr from this logger.'),
        ('void handle(LogRecord r) const',
         'Handles a record by passing it to all handlers associated with this logger and its ancestors (until a false value of propagate is found).'),
        ('void exception(std::wstring msg) const',
         '''Logs a message with level ``ERROR`` on this logger.

            Exception info is added to the logging message. This method
            should only be called from an exception handler.''')
        ]

    for lvl in ['debug', 'info', 'warning', 'error', 'critical']:
        methods.append(
            ('void {0}(std::wstring msg) const'.format(lvl),
             'Logs a message with level ``{0}`` on this logger.'.format(lvl.upper())))

    for m in methods:
        docstring='''\\rst
                     {0}
                     \\endrst'''.format(m[1])
        method(m[0], parent=parent, doc=docstring)

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'logging', parent=t)
    cls = Class(name='LoggerBase',
                wrapped_class='logging.Logger',
                parent=ns)

    # TODO: docstring for propagate
    Property(name='propagate',
             type='bool',
             parent=cls).doc='If this evaluates to false, logging messages are not passed by this logger or by its child loggers to the handlers of higher level (ancestor) loggers.'
    methods(parent=cls)

    return t

