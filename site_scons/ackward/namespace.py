from .element import Element
from .trace import trace

def to_open(ns):
    return ' '.join(['namespace {0} {{'.format(n) for n in ns])

def to_close(ns):
    return '}' * len(ns)

class Namespace(Element):
    @trace
    def __init__(self, *args):
        Element.__init__(self)
        self.ns = list(args)

    @trace
    def open_header(self, mod, symbols):
        yield to_open(self.ns)

    @trace
    def close_header(self, mod, symbols):
        yield to_close(self.ns)

    @trace
    def open_impl(self, mod, symbols):
        yield to_open(self.ns)

    @trace
    def close_impl(self, mod, symbols):
        yield to_close(self.ns)
