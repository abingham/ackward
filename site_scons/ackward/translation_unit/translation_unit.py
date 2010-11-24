class TranslationUnit(object):
    '''Describes a C++ translation unit.

    A TranslationUnit is used by the ackward code generator to produce
    a C++ header and implementation file. Subclasses define the
    headers, forward-declarations, using statements, and everything
    that this translation unit will use.
    '''
    def __init__(
        self,
        preprocessor_guard=None,
        header_includes=[],
        forward_declarations=[],
        impl_includes=[],
        using=[],
        objects=[]):
        self.preprocessor_guard=preprocessor_guard
        self.header_includes=set(header_includes)
        self.forward_declarations=set(forward_declarations)
        self.impl_includes=set(impl_includes)
        self.using=set(using)
        self.objects=objects
        
