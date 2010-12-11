from ackward.translation_unit import ClassTranslationUnit
from ackward.elements import InlineFunction
from ackward.cls import (Class, 
                         class_method, 
                         ClassProperty, 
                         Constructor, 
                         InlineMethod,
                         Method,
                         method,
                         Property)

equality_operator='''
bool operator==(const Date& d) const 
{ return obj() == d.obj(); }
'''

stream_operator='''
inline std::ostream& operator<<(std::ostream& os, const Date& d) {
  os << d.isoformat();
  return os;
}
'''

replace_method='''
Date replace(unsigned int y, unsigned int m, unsigned int d) const { 
  y = (y == 0) ? year() : y;
  m = (m == 0) ? month() : m;
  d = (d == 0) ? day() : d;
  return _replace(y, m, d);
}'''

class Date(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='Date',
                  wrapped_class='datetime.date')
        
        Constructor(
            cls=c,
            signature=[('unsigned int', 'year'),
                       ('unsigned int', 'month'),
                       ('unsigned int', 'day')])
        
        class_method('Date today()', c)
        class_method('Date fromtimestamp(double timestamp)', c)
        class_method('Date fromordinal(unsigned int ordinal)', c)

        ClassProperty(
            cls=c,
            name='min',
            type='Date',
            read_only=True)

        ClassProperty(
            cls=c,
            name='max',
            type='Date',
            read_only=True)
    
        ClassProperty(
            cls=c,
            name='resolution',
            type='TimeDelta',
            read_only=True)

        Property(
            cls=c,
            name='year',
            type='unsigned int',
            read_only=True)

        Property(
            cls=c,
            name='month',
            type='unsigned int',
            read_only=True)

        Property(
            cls=c,
            name='day',
            type='unsigned int',
            read_only=True)

        Method(
            cls=c,
            name='_replace',
            python_name='replace',
            return_type='Date',
            signature=[('unsigned int', 'year'),
                       ('unsigned int', 'month'),
                       ('unsigned int', 'day')],
            const=True)

        InlineMethod(
            cls=c,
            code=replace_method)

        method('tm timetuple() const', c)
        method('unsigned int toordinal() const', c)
        method('int weekday() const', c)
        method('int isoweekday() const', c)
        method('boost::tuple<int, int, int> isocalendar() const', c)
        method('std::string isoformat() const', c)
        method('std::string ctime() const', c)
        method('std::wstring strftime(std::wstring fmt) const', c)

        InlineMethod(
            cls=c,
            code=equality_operator)

        objs = [c]

        stream = InlineFunction(
            code=stream_operator)
        
        objs.append(stream)

        super(Date, self).__init__(
            forward_declarations=[
                ('ackward', 'datetime', 'class TimeDelta'),
                ],
            header_includes=[
                ('boost', 'tuple', 'tuple.hpp')
                ],
            impl_includes=[
                ('ackward', 'datetime', 'Date.hpp'),
                ('ackward', 'datetime', 'TimeDelta.hpp'),
                ],
            objects={('ackward', 'datetime') : objs})
        
def definition():
    return Date()
