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
        objects={}):
        '''
        Args:
          * preprocessor_guard: The preprocessor guard string for the
              header. If None, one is generated based on the module
              containing this translation unit.
          * header_includes: A sequence of tuples describing the
              header files to include in the header generated for this
              translation unit. Each tuple results in an include spec
              like this:
                ('A', 'B', 'C.hpp') -> "#include <A/B/C.hpp>"
          * forward_declarations: A sequence of tuples describing the
              forward declarations in the generated header. Each tuple
              is a series of namespaces followed by a type. For
              example:
                ('A', 'B', 'struct C') -> "namespace A { namespace B { struct C; } }"
          * impl_includes: A sequence of tuples describing the header
              files to include in the generated implementation
              file. See `header_includes` for me details.
          * using: A sequence of strings that are used verbatim in
              `using` statements in the generated implementation file. For example:
                "namespace Foo" -> "using namespace Foo;"
              or:
                "class Llama" -> "using class Llama;"
          
          * objects: A dict-like object mapping namespace tuples to
              sequences of Template subclasses. Each Template will be
              expanded (i.e. have `generate_header/impl()` called on
              it) in the specified namespace. In general, Templates
              represent things like methods and classes.
        '''
        self.preprocessor_guard=preprocessor_guard
        self.header_includes=set(header_includes)
        self.forward_declarations=set(forward_declarations)
        self.impl_includes=set(impl_includes)
        self.using=set(using + ['namespace boost::python'])
        self.objects=objects
        
