import os

from .element import Element
from .trace import trace

def _declare(decl):
    '''Generate a single forward declaration statement.
    '''
    if len(decl) == 0:
        return str()

    elif len(decl) == 1:
        return '{0};'.format(decl[0])

    else:
        return 'namespace {0} {{ {1} }}'.format(
            decl[0],
            _declare(decl[1:]))

class TranslationUnit(Element):
    def __init__(self, 
                 guard=None,
                 *args,
                 **kwargs):
        Element.__init__(self, *args, **kwargs)
        self.guard = guard

    @trace
    def open_header(self, mod, symbols):
        guard = self.guard
        if not guard:
            mod_name = mod.__file__.replace(os.path.sep, '_')
            mod_name = mod_name.replace('.', '_')
            guard = 'INCLUDE_{0}'.format(mod_name.upper())        

        # generate include guard
        yield '#ifndef {0}'.format(guard)
        yield '#define {0}'.format(guard)

        # TODO: Remove duplicates from header list (impl also)
        # generate header include statements
        for e in self:
            for h in e.header_includes:
                yield '#include <{0}>'.format(os.path.join(*h))

        # generate forward declarations
        for e in self:
            for d in e.forward_declarations:
                yield _declare(d)

    @trace
    def close_header(self, mod, symbols):
        yield '#endif'

    @trace
    def open_impl(self, mod, symbols):
        # generate impl includes
        for e in self:
            for h in e.impl_includes:
                yield '#include <{0}>'.format(os.path.join(*h))

        # usings
        for e in self:
            for u in e.using:
                yield 'using {0};'.format(u)
        
