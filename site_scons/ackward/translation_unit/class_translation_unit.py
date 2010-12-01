from .translation_unit import TranslationUnit

class ClassTranslationUnit(TranslationUnit):
    def __init__(
        self,
        preprocessor_guard=None,
        header_includes=[],
        forward_declarations=[],
        impl_includes=[],
        using=[],
        objects=[]):

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
