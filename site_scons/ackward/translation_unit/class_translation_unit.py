from .translation_unit import TranslationUnit

class ClassTranslationUnit(TranslationUnit):
    def impl_includes(self):
        return [
            ('ackward', 'core', 'GetClass.hpp'),
            ('ackward', 'core', 'Object.hpp'),
            ]
