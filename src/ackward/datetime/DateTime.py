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

def datetime_class():
    with Class(name='DateTime',
               wrapped_class='datetime.datetime'):

        Constructor(
            signature=[('unsigned int', 'year'),
                       ('unsigned int', 'month'),
                       ('unsigned int', 'day'),
                       ('unsigned int', 'hour', '0'),
                       ('unsigned int', 'minute', '0'),
                       ('unsigned int', 'second', '0'),
                       ('unsigned int', 'microsecond', '0'),
                       #[, tzinfo
                       ])
        
        class_method('DateTime today()')
        class_method('DateTime now()')
        class_method('DateTime now(TZInfo tz)')
        class_method('DateTime utcnow()')
        class_method('DateTime fromtimestamp(float timestamp)')

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'datetime'):
            datetime_class()
    return t
