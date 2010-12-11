from ackward.translation_unit import ClassTranslationUnit
from ackward.elements import InlineFunction
from ackward.cls import (Class,
                         ClassProperty,
                         Constructor,
                         InlineMethod,
                         Property)

eq_operator='''
bool operator==(const TimeDelta& td) const
{ return obj() == td.obj(); }
'''

ne_operator='''
bool operator!=(const TimeDelta& td) const
{ return obj() != td.obj(); }
'''

lt_operator='''
bool operator<(const TimeDelta& td) const
{ return obj() < td.obj(); }
'''

le_operator='''
bool operator<=(const TimeDelta& td) const
{ return obj() <= td.obj(); }
'''

gt_operator='''
bool operator>(const TimeDelta& td) const
{ return obj() > td.obj(); }
'''

ge_operator='''
bool operator>=(const TimeDelta& td) const
{ return obj() >= td.obj(); }
'''

add_operator='''
inline TimeDelta operator+(const TimeDelta& lhs, const TimeDelta& rhs)
{ return lhs.obj() + rhs.obj(); }
'''

sub_operator='''
inline TimeDelta operator-(const TimeDelta& lhs, const TimeDelta& rhs)
{ return lhs.obj() - rhs.obj(); }
'''

mul_operator='''
inline TimeDelta operator*(const TimeDelta& lhs, unsigned long d)
{ return lhs.obj() * d; }
'''

div_operator='''
inline TimeDelta operator/(const TimeDelta& lhs, long rhs)
{ return lhs.obj() / rhs; }
'''

neg_operator='''
inline TimeDelta operator-(const TimeDelta& td) 
{ return td.obj().attr("__neg__")(); }
'''

abs_function='''
inline TimeDelta abs(const TimeDelta& td)
{ return td.obj().attr("__abs__")(); }
'''

class TimeDelta(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='TimeDelta',
                  wrapped_class='datetime.timedelta')
        
        Constructor(
            cls=c,
            signature=[('double', 'days', '0'),
                       ('double', 'seconds', '0'),
                       ('double', 'microseconds', '0'),
                       ('double', 'milliseconds', '0'),
                       ('double', 'minutes', '0'),
                       ('double', 'hours', '0'),
                       ('double', 'weeks', '0')])

        Property(
            cls=c,
            type='int',
            name='days',
            read_only=True)
        Property(
            cls=c,
            type='unsigned int',
            name='seconds',
            read_only=True)
        Property(
            cls=c,
            type='unsigned int',
            name='microseconds',
            read_only=True)

        ClassProperty(
            cls=c,
            type='TimeDelta',
            name='min',
            read_only=True)
        ClassProperty(
            cls=c,
            type='TimeDelta',
            name='max',
            read_only=True)
        ClassProperty(
            cls=c,
            type='TimeDelta',
            name='resolution',
            read_only=True)

        InlineMethod(cls=c, code=eq_operator)
        InlineMethod(cls=c, code=ne_operator)
        InlineMethod(cls=c, code=lt_operator)
        InlineMethod(cls=c, code=le_operator)
        InlineMethod(cls=c, code=gt_operator)
        InlineMethod(cls=c, code=ge_operator)

        objs = [
            c,
            InlineFunction(code=add_operator),
            InlineFunction(code=sub_operator),
            InlineFunction(code=mul_operator),
            InlineFunction(code=div_operator),
            InlineFunction(code=neg_operator),
            InlineFunction(code=abs_function),
            ]

        super(TimeDelta, self).__init__(
            header_includes=[],
            impl_includes=[
                ('ackward', 'datetime', 'TimeDelta.hpp')
                ],
            objects={('ackward', 'datetime') : objs})

def definition():
    return TimeDelta()
