from .element import Element
from .trace import trace

class Using(Element):
    @trace
    def __init__(self, using):
        Element.__init__(self)
        self.using = using

    def open_phase(self, mod, phase, symbols):
        if phase == 'using':
            yield 'using {0};'.format(self.using)