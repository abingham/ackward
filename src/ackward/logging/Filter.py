from ackward.cls import Class, Constructor
from ackward.translation_unit import ClassTranslationUnit

class Filter(ClassTranslationUnit):
    def module(self):
        return 'logging'

    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_FILTER'

    def header_includes(self):
        return [
            ('string',)
            ]

    def impl_includes(self):
        includes = [
            ('ackward', 'logging', 'Filter.hpp'),
            ('boost', 'python', 'import.hpp'),
            ]

        return super(Filter, self).impl_includes() + includes

    def forward_declarations(self):
        return []

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
