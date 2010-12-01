from ackward.translation_unit import ClassTranslationUnit
from ackward.cls import Class, Constructor, class_method

def definition():
    c = Class(name='Date',
              wrapped_class='datetime.date')

    Constructor(
        cls=c,
        signature=[('unsigned int', 'year'),
                   ('unsigned int', 'month'),
                   ('unsigned int', 'day')])

    class_method('Date today()')

    # akw.ClassMethod(
    #     cls=c,
    #     name='fromtimestamp',
    #     return_type='Date',
    #     signature=[('double', 'timestamp')])
    
    # akw.ClassMethod(
    #     cls=c,
    #     name='fromordinal',
    #     return_type='Date',
    #     signature=[('unsigned int', 'ordinal')])

    # akw.ClassProperty(
    #     cls=c,
    #     name='min',
    #     type='Date',
    #     read_only=True)

    # akw.ClassProperty(
    #     cls=c,
    #     name='max',
    #     type='Date',
    #     read_only=True)
    
    # akw.ClassProperty(
    #     cls=c,
    #     name='resolution',
    #     type='TimeDelta',
    #     read_only=True)

    # akw.Property(
    #     cls=c,
    #     name='year',
    #     type='unsigned int',
    #     read_only=True)

    # akw.Property(
    #     cls=c,
    #     name='month',
    #     type='unsigned int',
    #     read_only=True)

    # akw.Property(
    #     cls=c,
    #     name='day',
    #     type='unsigned int',
    #     read_only=True)

    # akw.Method(
    #     cls=c,
    #     name='_replace',
    #     python_name='replace',
    #     return_type='Date',
    #     signature=[('unsigned int', 'year'),
    #                ('unsigned int', 'month'),
    #                ('unsigned int', 'day')],
    #     const=True)

    # akw.Method(
    #     cls=c,
    #     name='timetuple',
    #     return_type='tm',
    #     const=True)

    # akw.Method(
    #     cls=c,
    #     name='toordinal',
    #     return_type='unsigned int',
    #     const=True)
    
    # akw.Method(
    #     cls=c,
    #     name='weekday',
    #     return_type='int',
    #     const=True)

    # akw.Method(
    #     cls=c,
    #     name='isoweekday',
    #     return_type='int',
    #     const=True)

    # akw.Method(
    #     cls=c,
    #     name='_isocalendar',
    #     return_type='boost::python::tuple',
    #     const=True,
    #     python_name='isocalendar')

    # akw.Method(
    #     cls=c,
    #     name='isoformat',
    #     return_type='std::string',
    #     const=True)

    # akw.Method(
    #     cls=c,
    #     name='ctime',
    #     return_type='std::string',
    #     const=True)


    # akw.Method(
    #     cls=c,
    #     name='strftime',
    #     return_type='std::wstring',
    #     signature=[('std::wstring', 'fmt')],
    #     const=True)

    super(LoggerBase, self).__init__(
        forward_declarations=[],
        header_includes=[],
        impl_includes=[('ackward', 'datetime', 'Date.hpp'),
                       ]
        objects={('ackward', 'datetime') : [c]})

def definition():
    return Date()