from ackward.cls import Class, Constructor
from ackward.translation_unit import ClassTranslationUnit

class LogRecord(ClassTranslationUnit):
    
    def __init__(self):
        fd = [('boost', 'python', 'class tuple')]

        hincl = [
            ('string',),
            ('ackward', 'logging', 'Types.hpp'),
            ] 

        iincl=[
            ('boost', 'python', 'tuple.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ]

        c = Class(name='LogRecord',
                  wrapped_class='logging.LogRecord')

        Constructor(
            cls=c,
            signature=[
                ('std::wstring', 'name'),
                ('Level', 'lvl'),
                ('std::wstring', 'pathname'),
                ('int', 'lineno'),
                ('std::wstring', 'msg'),
                ('boost::python::tuple', 'args'),
                ])

        super(LogRecord, self).__init__(
            preprocessor_guard = 'INCLUDE_ACKWARD_LOGGING_LOG_RECORD_HPP',
            forward_declarations = fd,
            header_includes=hincl,
            impl_includes=iincl,
            objects={('ackward', 'logging') : [c]})

def definition():
    return LogRecord()
