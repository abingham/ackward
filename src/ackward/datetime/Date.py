from ackward import (Class,
                     class_method,
                     ClassProperty,
                     Constructor,
                     InlineFunction,
                     method,
                     Method,
                     Namespace,
                     Property,
                     TranslationUnit)

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
  y = (y == 0) ? year : y;
  m = (m == 0) ? month : m;
  d = (d == 0) ? day : d;
  return _replace(y, m, d);
}
'''

def tunit():
    return TranslationUnit(
        forward_declarations=[
            ('ackward', 'datetime', 'class TimeDelta'),
            ],
        header_includes=[
            ('boost', 'tuple', 'tuple.hpp')
            ],
        impl_includes=[
            ('ackward', 'datetime', 'Date.hpp'),
            ('ackward', 'datetime', 'TimeDelta.hpp'),
            ])

def date_class(parent):
    cls = Class(name='Date',
                wrapped_class='datetime.date',
                parent=parent)

    Constructor(
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day')],
        parent=cls)

    class_method('Date today()', parent=cls)
    class_method('Date fromtimestamp(double timestamp)', parent=cls)
    class_method('Date fromordinal(unsigned int ordinal)', parent=cls)

    ClassProperty(
        name='min',
        type='Date',
        read_only=True,
        parent=cls)

    ClassProperty(
        name='max',
        type='Date',
        read_only=True,
        parent=cls)

    ClassProperty(
        name='resolution',
        type='TimeDelta',
        read_only=True,
        parent=cls)

    Property(
        name='year',
        type='unsigned int',
        read_only=True,
        parent=cls)

    Property(
        name='month',
        type='unsigned int',
        read_only=True,
        parent=cls)

    Property(
        name='day',
        type='unsigned int',
        read_only=True,
        parent=cls)

    Method(
        name='_replace',
        python_name='replace',
        return_type='Date',
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day')],
        const=True,
        parent=cls)

    InlineFunction(
        code=replace_method,
        parent=cls)

    for m in [
        'tm timetuple() const',
        'unsigned int toordinal() const',
        'int weekday() const',
        'int isoweekday() const',
        'boost::tuple<int, int, int> isocalendar() const',
        'std::string isoformat() const',
        'std::string ctime() const',
        'std::wstring strftime(std::wstring fmt) const']:
        method(m, parent=cls)

    InlineFunction(
        code=equality_operator,
        parent=cls)

def definition(env):
    t = tunit()

    n = Namespace('ackward', 'datetime', parent=t)
    date_class(parent=n)

    InlineFunction(
        code=stream_operator,
        parent=n)

    return t
