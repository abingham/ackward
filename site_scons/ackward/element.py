import string

from .signature import build_signature

class Element:
    '''An Element represents a concept in an ackward mapping.

    Elements are composed into a tree via their `children`
    member. Elements are visited in-order and allowed to generate
    output a) before their children are visited and b) after their
    children are visited. This is the basic model for how ackward
    generates output.

    When Elements are used in a with-statement, then any Element
    created inside that with-statement will be automatically added to
    the children of the most-recently with'd Element. So, for example::

     with FooElement() as foo:
        with BarElement() as bar:
          baz = BazElement()
     llama = LlamaElement()

    Here, `bar` is a child of `foo`, and `baz` is a child of `bar`, but
    `llama` is not a child of any Element.

    Args:
      * children: child Elements of the Element.
      * header_includes: A sequence of tuples describing the headers
        that this Element needs in the header.
      * impl_includes: A sequence of tuples describing the headers
        that this Element needs in the implementation file.
      * forward_declarations: A sequence of tuples describing
      * using: A sequence of using statements to include in the
        implementation file.
      * symbols: The symbols defined in the overall symbol map when
        this Element is active.
    '''
    
    _stack = []

    def __init__(self, 
                 children=None,
                 header_includes=None,
                 impl_includes=None,
                 forward_declarations=None,
                 using=None,
                 symbols=None,
                 doc=None):
        self.children = list(children or [])

        self.header_includes = list(header_includes or [])
        self.impl_includes = list(impl_includes or [])
        self.forward_declarations = list(forward_declarations or [])
        self.using = list(using or [])
        self.symbols = symbols or {}
        
        self.doc = doc

        if Element._stack:
            Element._stack[-1] += self

    def open_header(self, mod, symbols):
        '''Called before processing `children` when generating a
        header.

        Args:
          * mod: The module object from which the Element comes.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output.
        '''

        return ['']

    def close_header(self, mod, symbols):
        '''Called after processing `children` when generating a
        header.

        Args:
          * mod: The module object from which the Element comes.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output.
        '''
        return ['']

    def open_impl(self, mod, symbols):
        '''Called before processing `children` when generating an
        implementation file.

        Args:
          * mod: The module object from which the Element comes.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output.
        '''
        return ['']

    def close_impl(self, mod, symbols):
        '''Called after processing `children` when generating an
        implementation file.

        Args:
          * mod: The module object from which the Element comes.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output.
        '''
        return ['']

    def __iter__(self):
        '''Iterate of the Element tree rooted at `self`. 

        This includes iteration of `self`.

        Returns:
          An iterable over Elements.
        '''
        yield self
        for c in self.children:
            for e in c:
                yield e

    def __iadd__(self, child):
        '''Append a child to the Element.
        '''
        self.children.append(child)
        return self

    def __enter__(self):
        '''Make this the auto-parent for Elements created inside the
        associated with-statement:
        '''
        Element._stack.append(self)
        return self

    def __exit__(self, t, v, tb):
        '''Stop using this as the auto-parent target.
        '''
        Element._stack.pop()

    def render_doc(self):
        '''Return the text to be used for the element's documentation.
        '''
        if self.doc:
            yield '''/**
                     {0}
                     */'''.format(self.doc)
        
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
