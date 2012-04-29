from .element import Element
from .trace import trace

def to_open(ns):
    return ' '.join(['namespace {0} {{'.format(n) for n in ns])

def to_close(ns):
    return '}' * len(ns)

class Namespace(Element):
    @trace
    def __init__(self, *args, **kwargs):
        Element.__init__(self, **kwargs)
        self.ns = list(args)

    @trace
    def open_phase(self, mod, phase, symbols):
        if phase in ('header', 'impl'):
            yield to_open(self.ns)

    @trace
    def close_phase(self, mod, phase, symbols):
        if phase in ('header', 'impl'):
            yield to_close(self.ns)
