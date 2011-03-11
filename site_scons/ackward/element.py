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
                 open_header_template='',
                 close_header_template='',
                 open_impl_template='',
                 close_impl_template='',
                 *args,
                 **kwargs):
        Element.__init__(self, *args, **kwargs)
        self.open_header_template = open_header_template
        self.close_header_template = close_header_template
        self.open_impl_template = open_impl_template
        self.close_impl_template = close_impl_template
        
    def open_header(self, mod, symbols):
        t = string.Template(self.open_header_template)
        yield t.substitute(symbols)

    def close_header(self, mod, symbols):
        t = string.Template(self.close_header_template)
        yield t.substitute(symbols)

    def open_impl(self, mod, symbols):
        t = string.Template(self.open_impl_template)
        yield t.substitute(symbols)

    def close_impl(self, mod, symbols):
        t = string.Template(self.close_impl_template)
        yield t.substitute(symbols)


class SigTemplateElement(TemplateElement):
    def __init__(self,
                 symbols,
                 header_includes=None,
                 *args,
                 **kwargs):
        header_includes = header_includes or []
        header_includes.append(('boost', 'call_traits.hpp'))

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
            header_includes=header_includes,
            *args,
            **kwargs)
