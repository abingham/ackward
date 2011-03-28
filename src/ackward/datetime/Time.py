from ackward import (Class,
                     ClassProperty,
                     Constructor,
                     InlineFunction,
                     method,
                     Method,
                     Namespace,
                     Property,
                     TranslationUnit)

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

def tunit():
    return TranslationUnit(
        header_includes=[
            ('ackward', 'datetime', 'TimeDelta.hpp'),
            ],
        impl_includes=[
            ('ackward', 'datetime', 'Time.hpp'),
            ])

def time_class():
    with Class(name='Time',
               wrapped_class='datetime.time'):
        Constructor(
            signature=[('unsigned int', 'hour'),
                       ('unsigned int', 'minute', '0'),
                       ('unsigned int', 'second', '0'),
                       ('unsigned int', 'microsecond', '0'),
                       #[, tzinfo]]]])
                       ])

        ClassProperty(
            name='min',
            type='Time',
            read_only=True)

        ClassProperty(
            name='max',
            type='Time',
            read_only=True)

        ClassProperty(
            name='resolution',
            type='TimeDelta',
            read_only=True)
        
        Property(
            name='hour',
            type='unsigned int',
            read_only=True)
        
        Property(
            name='minute',
            type='unsigned int',
            read_only=True)
        
        Property(
            name='second',
            type='unsigned int',
            read_only=True)
                
        Property(
            name='microsecond',
            type='unsigned int',
            read_only=True)

        #     # TODO:
        #     # time.tzinfo
        #     # The object passed as the tzinfo argument to the time
        #     # constructor, or None if none was passed.
        
        # # Instance methods:
        
        Method(
            name='_replace',
            python_name='replace',
            signature=[('unsigned int', 'hour'),
                       ('unsigned int', 'minute'),
                       ('unsigned int', 'second'),
                       ('unsigned int', 'microsecond')],
            return_type='Time',
            const=True)

        InlineFunction(
            code=replace_method)

        method('std::string isoformat() const')
        method('std::wstring strftime(std::wstring fmt) const')
        
        # # time.strftime(format)
        # # Return a string representing the time, controlled by an explicit format string. See section strftime() Behavior.
        # # time.utcoffset()
        # # If tzinfo is None, returns None, else returns self.tzinfo.utcoffset(None), and raises an exception if the latter doesn't return None or a timedelta object representing a whole number of minutes with magnitude less than one day.
        # # time.dst()
        # # If tzinfo is None, returns None, else returns self.tzinfo.dst(None), and raises an exception if the latter doesn't return None, or a timedelta object representing a whole number of minutes with magnitude less than one day.
        # # time.tzname()
        # # If tzinfo is None, returns None, else returns self.tzinfo.tzname(None), or raises an exception if the latter doesn't return None or a string object.
        
#     return c

        InlineFunction(
            code=lt_operator)

        InlineFunction(
            code=eq_operator)    

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'datetime'):
            time_class()

    return t
