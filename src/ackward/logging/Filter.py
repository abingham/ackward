from ackward.cls import Class, Constructor
from ackward.translation_unit import ClassTranslationUnit

class Filter(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='Filter',
                  wrapped_class='logging.Filter')
        
        Constructor(
            cls=c,
            signature=[('std::wstring', 'name')])
        
        super(Filter, self).__init__(
            preprocessor_guard='INCLUDE_ACKWARD_LOGGING_FILTER',
            header_includes=[
                ('string',),
                ('ackward', 'core', 'Object.hpp'),
                ],
            impl_includes=[
                ('ackward', 'logging', 'Filter.hpp'),
                ('boost', 'python', 'import.hpp'),
                ],
            objects={ ('ackward', 'logging') : [c] })

def definition():
    return Filter()
