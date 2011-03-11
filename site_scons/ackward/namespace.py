from .element import Element

def to_open(ns):
    return ' '.join(['namespace {0} {{'.format(n) for n in ns])

def to_close(ns):
    return '}' * len(ns)

class Namespace(Element):
    def __init__(self, *args):
        Element.__init__(self)
        self.ns = list(args)

    def open_header(self, mod, symbols):
        yield to_open(self.ns)

    def close_header(self, mod, symbols):
        yield to_close(self.ns)

    def open_impl(self, mod, symbols):
        yield to_open(self.ns)

    def close_impl(self, mod, symbols):
        yield to_close(self.ns)
