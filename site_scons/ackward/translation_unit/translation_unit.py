class TranslationUnit(object):
    '''Describes a C++ translation unit.

    A TranslationUnit is used by the ackward code generator to produce
    a C++ header and implementation file. Subclasses define the
    headers, forward-declarations, using statements, and everything
    that this translation unit will use.
    '''

    def module(self):
        raise NotImplementedError('TranslationUnit subclasses must implement `module()`')

    def preprocessor_guard(self):
        return None

    def header_includes(self):
        return []

    def impl_includes(self):
        return []

    def forward_declarations(self):
        return []

    def using(self):
        return []

    def objects(self):
        return []

