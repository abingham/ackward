import os
from itertools import chain

from .element import Element
from .forward_decl import ForwardDecl
from .include import HeaderInclude, ImplInclude
from .trace import trace
from .using import Using

class TranslationUnit(Element):
    @trace
    def __init__(self,
                 guard=None,
                 header_includes=None,
                 impl_includes=None,
                 forward_declarations=None,
                 using=None,
                 *args,
                 **kwargs):
        '''An Element representing C++ translation units (compilation
        units.)

        Args:
          guard: The include guard token to use. If ``None``, an
            include guard will be generated automatically.
          header_includes: A sequence of tuples describing the headers
            that this Element needs in the header.
          impl_includes: A sequence of tuples describing the headers
            that this Element needs in the implementation file.
          forward_declarations: A sequence of tuples describing
            forward declarations in the translation unit's header
            file.
          using: A sequence of using statements to include in the
            implementation file.
        '''
        Element.__init__(self, *args, **kwargs)
        self.guard = guard

        if forward_declarations:
            for f in forward_declarations:
                self.add_child(
                    ForwardDecl(f))

        if using:
            for u in using:
                self.add_child(
                    Using(u))

        if header_includes:
            for h in [('Python.h',)] + header_includes + [('boost', 'call_traits.hpp')]:
                self.add_child(
                    HeaderInclude(h))

        if impl_includes:
            for h in impl_includes:
                self.add_child(
                    ImplInclude(h))

    @trace
    def open_phase(self, mod, phase, symbols):
        if phase == 'header':
            for line in self.include_guard(mod):
                yield line

            for line in self.process(mod, 'header_include', symbols):
                yield line

    @trace
    def include_guard(self, mod):
        guard = self.guard
        if not guard:
            mod_name = mod.__file__.replace(os.path.sep, '_')
            mod_name = mod_name.replace('.', '_')
            guard = 'INCLUDE_{0}'.format(mod_name.upper())

        # generate include guard
        yield '#ifndef {0}'.format(guard)
        yield '#define {0}'.format(guard)

    @trace
    def close_phase(self, mod, phase, symbols):
        if phase == 'header':
            yield '#endif'


