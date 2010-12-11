from ackward.translation_unit import ClassTranslationUnit

from ackward.cls import (Class,
                         Constructor,
                         class_method)

class DateTime(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='DateTime',
                  wrapped_class='datetime.datetime')

        Constructor(
            cls=c,
            signature=[('unsigned int', 'year'),
                       ('unsigned int', 'month'),
                       ('unsigned int', 'day'),
                       ('unsigned int', 'hour', '0'),
                       ('unsigned int', 'minute', '0'),
                       ('unsigned int', 'second', '0'),
                       ('unsigned int', 'microsecond', '0'),
                       #[, tzinfo
                       ])

        class_method('DateTime today()', c)
        class_method('DateTime now()', c)
        class_method('DateTime now(TZInfo tz)', c)
        class_method('DateTime utcnow()', c)
        class_method('DateTime fromtimestamp(float timestamp)', c)

        super(DateTime, self).__init__(
            forward_declarations=[
                ('ackward', 'datetime', 'class TZInfo'),
                ],
            impl_includes=[
                ('ackward', 'datetime', 'DateTime.hpp'),
                ('ackward', 'datetime', 'TZInfo.hpp'),
                ],
            objects={('ackward', 'datetime') : [c]})

def definition():
    return DateTime()
