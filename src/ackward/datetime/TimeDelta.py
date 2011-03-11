from ackward import (Class,
                     ClassProperty,
                     Constructor,
                     InlineFunction,
                     Namespace,
                     Property,
                     TranslationUnit)

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

def tunit():
    return TranslationUnit(
        impl_includes=[
            ('ackward', 'datetime', 'TimeDelta.hpp')
            ])

def timedelta_class():
    with Class(name='TimeDelta',
               wrapped_class='datetime.timedelta'):
        
        Constructor(
            signature=[('double', 'days', '0'),
                       ('double', 'seconds', '0'),
                       ('double', 'microseconds', '0'),
                       ('double', 'milliseconds', '0'),
                       ('double', 'minutes', '0'),
                       ('double', 'hours', '0'),
                       ('double', 'weeks', '0')])

        Property(
            type='int',
            name='days',
            read_only=True)

        Property(
            type='unsigned int',
            name='seconds',
            read_only=True)

        Property(
            type='unsigned int',
            name='microseconds',
            read_only=True)
        
        ClassProperty(
            type='TimeDelta',
            name='min',
            read_only=True)
        
        ClassProperty(
            type='TimeDelta',
            name='max',
            read_only=True)
        
        ClassProperty(
            type='TimeDelta',
            name='resolution',
            read_only=True)
        
        InlineFunction(code=eq_operator)
        InlineFunction(code=ne_operator)
        InlineFunction(code=lt_operator)
        InlineFunction(code=le_operator)
        InlineFunction(code=gt_operator)
        InlineFunction(code=ge_operator)
        
def definition():
    with tunit() as t:
        with Namespace('ackward', 'datetime'):
            timedelta_class()

            InlineFunction(code=add_operator)
            InlineFunction(code=sub_operator)
            InlineFunction(code=mul_operator)
            InlineFunction(code=div_operator)
            InlineFunction(code=neg_operator)
            InlineFunction(code=abs_function)
    return t
