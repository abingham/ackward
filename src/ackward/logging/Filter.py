from ackward.cls import Class, Constructor
from ackward.translation_unit import ClassTranslationUnit

class Filter(ClassTranslationUnit):

    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_FILTER'

    def header_includes(self):
        return [
            ('string',),
            ('ackward', 'core', 'Object.hpp'),
            ]

    def impl_includes(self):
        includes = [
            ('ackward', 'logging', 'Filter.hpp'),
            ('boost', 'python', 'import.hpp'),
            ]

        return super(Filter, self).impl_includes() + includes

    def objects(self):
        c = Class(name='Filter',
                  wrapped_class='logging.Filter')
        
        Constructor(
            cls=c,
            signature=[('std::wstring', 'name')])

        return {
            ('ackward', 'logging') : [c]}

def definition():
    return Filter()
