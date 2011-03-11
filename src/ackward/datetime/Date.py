import ackward

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

def definition():
    t = ackward.TranslationUnit(
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
    
    ns = ackward.Namespace('ackward', 'datetime')
    t += ns

    c = ackward.Class(
        name='Date',
        wrapped_class='datetime.date')
    ns += c

    c += ackward.Constructor(
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day')])
        
    c += ackward.class_method('Date today()')
    c += ackward.class_method('Date fromtimestamp(double timestamp)')
    c += ackward.class_method('Date fromordinal(unsigned int ordinal)')

    c += ackward.ClassProperty(
        name='min',
        type='Date',
        read_only=True)

    c += ackward.ClassProperty(
        name='max',
        type='Date',
        read_only=True)
    
    c += ackward.ClassProperty(
        name='resolution',
        type='TimeDelta',
        read_only=True)

    c += ackward.Property(
        name='year',
        type='unsigned int',
        read_only=True)

    c += ackward.Property(
        name='month',
        type='unsigned int',
        read_only=True)

    c += ackward.Property(
        name='day',
        type='unsigned int',
        read_only=True)

    c += ackward.Method(
        name='_replace',
        python_name='replace',
        return_type='Date',
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day')],
        const=True)

    c += ackward.InlineMethod(
        code=replace_method)

    for m in [
        'tm timetuple() const',
        'unsigned int toordinal() const',
        'int weekday() const',
        'int isoweekday() const',
        'boost::tuple<int, int, int> isocalendar() const',
        'std::string isoformat() const',
        'std::string ctime() const',
        'std::wstring strftime(std::wstring fmt) const']:
        c += ackward.method(m)

    c += ackward.InlineMethod(
        code=equality_operator)

    ns += InlineFunction(
        code=stream_operator)

    return t
        
def definition():
    return Date()
