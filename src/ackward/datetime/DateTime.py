from ackward import (Class,
                     class_method,
                     Constructor,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        forward_declarations=[
            ('ackward', 'datetime', 'class TZInfo'),
            ],
        impl_includes=[
            ('ackward', 'datetime', 'DateTime.hpp'),
            ('ackward', 'datetime', 'TZInfo.hpp'),
            ])

def datetime_class(parent):
    cls = Class(name='DateTime',
                wrapped_class='datetime.datetime',
                parent=parent)

    Constructor(
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day'),
                   ('unsigned int', 'hour', '0'),
                   ('unsigned int', 'minute', '0'),
                   ('unsigned int', 'second', '0'),
                   ('unsigned int', 'microsecond', '0'),
                   #[, tzinfo
               ],
        parent=cls)

    class_method('DateTime today()', parent=cls)
    class_method('DateTime now()', parent=cls)
    class_method('DateTime now(TZInfo tz)', parent=cls)
    class_method('DateTime utcnow()', parent=cls)
    class_method('DateTime fromtimestamp(float timestamp)', parent=cls)

def definition(env):
    t = tunit()
    n = Namespace('ackward', 'datetime', parent=t)
    datetime_class(parent=n)
    return t
