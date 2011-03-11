import string

from .signature import build_signature

class Element:
    
    _stack = []

    def __init__(self, 
                 children=None,
                 header_includes=None,
                 impl_includes=None,
                 forward_declarations=None,
                 using=None,
                 symbols=None):
        self.children = children or []

        self.header_includes = header_includes or []
        self.impl_includes = impl_includes or []
        self.forward_declarations = forward_declarations or []
        self.using = using or []
        self.symbols = symbols or {}

        if Element._stack:
            Element._stack[-1] += self

    def open_header(self, mod, symbols):
        return ['']

    def close_header(self, mod, symbols):
        return ['']

    def open_impl(self, mod, symbols):
        return ['']

    def close_impl(self, mod, symbols):
        return ['']

    def __iter__(self):
        yield self
        for c in self.children:
            for e in c:
                yield e

    def __iadd__(self, child):
        self.children.append(child)
        return self

    def __enter__(self):
        Element._stack.append(self)
        return self

    def __exit__(self, t, v, tb):
        Element._stack.pop()

class TemplateElement(Element):
    def __init__(self,
                 header_open_template='',
                 header_close_template='',
                 impl_open_template='',
                 impl_close_template='',
                 *args,
                 **kwargs):
        # TODO: Fix these names. Should be open_header_template, etc.
        Element.__init__(self, *args, **kwargs)
        self.header_open_template = header_open_template
        self.header_close_template = header_close_template
        self.impl_open_template = impl_open_template
        self.impl_close_template = impl_close_template
        
    def open_header(self, mod, symbols):
        t = string.Template(self.header_open_template)
        yield t.substitute(symbols)

    def close_header(self, mod, symbols):
        t = string.Template(self.header_close_template)
        yield t.substitute(symbols)

    def open_impl(self, mod, symbols):
        t = string.Template(self.impl_open_template)
        yield t.substitute(symbols)

    def close_impl(self, mod, symbols):
        t = string.Template(self.impl_close_template)
        yield t.substitute(symbols)


class SigTemplateElement(TemplateElement):
    def __init__(self,
                 symbols,
                 *args,
                 **kwargs):
        try:
            sig = symbols['signature']
            symbols = dict(symbols)
            symbols.update({
                    'header_signature' : build_signature(sig, True),
                    'impl_signature' : build_signature(sig, False),
                    'parameters' : ', '.join([s[1] for s in sig])})
        except KeyError:
            pass

        TemplateElement.__init__(
            self,
            symbols=symbols,
            *args,
            **kwargs)
