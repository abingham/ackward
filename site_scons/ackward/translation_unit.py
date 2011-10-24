import os
from itertools import chain

from .element import Element
from .trace import trace

@trace
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
    @trace
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

        # This avoids the posix-redefinition warnings
        yield '#include <Python.h>'

        # generate header include statements
        for header in set(chain(*[e.header_includes for e in self])):
            yield '#include <{0}>'.format(os.path.join(*header))

        # generate forward declarations
        for decl in set(chain(*[e.forward_declarations for e in self])):
            yield _declare(decl)

    @trace
    def close_header(self, mod, symbols):
        yield '#endif'

    @trace
    def open_impl(self, mod, symbols):
        # generate impl includes
        for header in set(chain(*[e.impl_includes for e in self])):
            yield '#include <{0}>'.format(os.path.join(*header))

        # usings
        for using in set(chain(*[e.using for e in self])):
            yield 'using {0};'.format(using)

