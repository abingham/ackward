from .translation_unit import TranslationUnit

class ClassTranslationUnit(TranslationUnit):
    def __init__(
        self,
        preprocessor_guard=None,
        header_includes=[],
        forward_declarations=[],
        impl_includes=[],
        using=[],
        objects={}):
        '''
        This is mostly the same as TranslationUnit. The differences are:
          * Adds "ackward/core/Object.hpp" to `header_includes`
          * Adds "ackward/core/GetClass.hpp" to `impl_includes`

        Args:
          (see TranslationUnit for the details)
        '''
        
        header_includes += [
            ('ackward', 'core', 'Object.hpp'),
            ]

        impl_includes += [
            ('ackward', 'core', 'GetClass.hpp'),
            ]

        super(ClassTranslationUnit, self).__init__(
            preprocessor_guard,
            header_includes,
            forward_declarations,
            impl_includes,
            using,
            objects)
