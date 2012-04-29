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

class ForwardDecl(Element):
    @trace
    def __init__(self,
                 decl):
        '''
        Args:
          decl: A tuple of strings describing a forward declaration.
        '''
        Element.__init__(self)
        self.decl = decl

    def open_phase(self, mod, phase, symbols):
        if phase == 'forward_decl':
            yield _declare(self.decl)