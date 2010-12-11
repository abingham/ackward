from ackward.translation_unit import ClassTranslationUnit
from ackward.cls import (Class,
                         ClassProperty,
                         Constructor,
                         InlineMethod,
                         Method,
                         method,
                         Property)

lt_operator='''
bool operator<(const Time& t) const
{ return obj() < t.obj(); }
'''

eq_operator='''
bool operator==(const Time& t) const
{ return obj() == t.obj(); }
'''

replace_method='''
Time replace(unsigned int h=0, unsigned int m=0, unsigned int s=0, unsigned int ms=0) const {
  return _replace(
    h == 0 ? hour() : h,
    m == 0 ? minute() : m,
    s == 0 ? second() : s,
    ms == 0 ? microsecond() : ms);
}
'''

class Time(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='Time',
                  wrapped_class='datetime.time')
        
        Constructor(
            cls=c,
            signature=[('unsigned int', 'hour'),
                       ('unsigned int', 'minute', '0'),
                       ('unsigned int', 'second', '0'),
                       ('unsigned int', 'microsecond', '0'),
                       #[, tzinfo]]]])
                       ])

        ClassProperty(
            cls=c,
            name='min',
            type='Time',
            read_only=True)

        ClassProperty(
            cls=c,
            name='max',
            type='Time',
            read_only=True)

        ClassProperty(
            cls=c,
            name='resolution',
            type='TimeDelta',
            read_only=True)
        
        Property(
            cls=c,
            name='hour',
            type='unsigned int',
            read_only=True)
        
        Property(
            cls=c,
            name='minute',
            type='unsigned int',
            read_only=True)
        
        Property(
            cls=c,
            name='second',
            type='unsigned int',
            read_only=True)
        
        Property(
            cls=c,
            name='microsecond',
            type='unsigned int',
            read_only=True)

#     # TODO:
#     # time.tzinfo
#     # The object passed as the tzinfo argument to the time
#     # constructor, or None if none was passed.

# # Instance methods:

        Method(
            cls=c,
            name='_replace',
            python_name='replace',
            signature=[('unsigned int', 'hour'),
                       ('unsigned int', 'minute'),
                       ('unsigned int', 'second'),
                       ('unsigned int', 'microsecond')],
            return_type='Time',
            const=True)
        InlineMethod(
            cls=c,
            code=replace_method)

        method('std::string isoformat() const', c)
        method('std::wstring strftime(std::wstring fmt) const', c)

# # time.strftime(format)
# # Return a string representing the time, controlled by an explicit format string. See section strftime() Behavior.
# # time.utcoffset()
# # If tzinfo is None, returns None, else returns self.tzinfo.utcoffset(None), and raises an exception if the latter doesn't return None or a timedelta object representing a whole number of minutes with magnitude less than one day.
# # time.dst()
# # If tzinfo is None, returns None, else returns self.tzinfo.dst(None), and raises an exception if the latter doesn't return None, or a timedelta object representing a whole number of minutes with magnitude less than one day.
# # time.tzname()
# # If tzinfo is None, returns None, else returns self.tzinfo.tzname(None), or raises an exception if the latter doesn't return None or a string object.
    
#     return c

        InlineMethod(
            cls=c,
            code=lt_operator)

        InlineMethod(
            cls=c,
            code=eq_operator)

        super(Time, self).__init__(
            header_includes=[
                ('ackward', 'datetime', 'TimeDelta.hpp'),
                ],
            impl_includes=[
                ('ackward', 'datetime', 'Time.hpp'),
                ],
            objects={('ackward', 'datetime') : [c]})

def definition():
    return Time()
