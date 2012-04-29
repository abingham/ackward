import string

from .signature import build_signature
from .trace import trace

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
      * symbols: The symbols defined in the overall symbol map when
        this Element is active.
    '''

    @trace
    def __init__(self,
                 parent=None,
                 symbols=None,
                 doc=None):
        if parent is not None:
            parent.children.append(self)

        self.children = []

        self.symbols = symbols or {}
        self.doc = doc

    @trace
    def process(self, mod, phase, symbols={}):
        symbols = dict(symbols)
        symbols.update(self.symbols)

        for line in self.open_phase(mod, phase, symbols):
            yield line

        for e in self.children:
            for line in e.process(mod, phase, symbols):
                yield line

        for line in self.close_phase(mod, phase, symbols):
            yield line

    @trace
    def open_phase(self, mod, phase, symbols):
        '''Called before processing `children` when generating
        the output for a phase.

        Args:
          * mod: The module object from which the Element comes.
          * phase: The phase currently being processed.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output for the
          current phase.
        '''

        return ['']

    @trace
    def close_phase(self, mod, phase, symbols):
        '''Called after processing `children` when generating
        the output for a phase.

        Args:
          * mod: The module object from which the Element comes.
          * phase: The phase currently being processed.
          * symbols: The active symbol table. This includes the
            Element's own symbols.

        Returns:
          An iterable of lines to include in the output for the
          current phase.
        '''

        return ['']

    # TODO: This may be unused. Remove it if so.
    # @trace
    # def __iter__(self):
    #     '''Iterate over the Element tree rooted at `self`.

    #     This includes iteration of `self`.

    #     Returns:
    #       An iterable over Elements.
    #     '''
    #     yield self
    #     for c in self.children:
    #         for e in c:
    #             yield e

    @trace
    def add_child(self, child):
        '''Append a child to the Element.
        '''
        self.children.append(child)
        return self

    @trace
    def render_doc(self):
        '''Return the text to be used for the element's documentation.
        '''
        if self.doc:
            yield '''/**
                     {0}
                     */'''.format(self.doc)

class TemplateElement(Element):
    @trace
    def __init__(self,
                 open_templates=None,
                 close_templates=None,
                 *args,
                 **kwargs):
        Element.__init__(self, *args, **kwargs)
        self.open_templates = open_templates or {}
        self.close_templates = close_templates or {}

    @trace
    def open_phase(self, mod, phase, symbols):
        '''
        Raise:
          KeyError: If the template needs an undefined symbol.
        '''
        t = self.open_templates.get(phase)
        if t is not None:
            t = string.Template(t)
            yield t.substitute(symbols)

    @trace
    def close_phase(self, mod, phase, symbols):
        '''
        Raise:
          KeyError: If the template needs an undefined symbol.
        '''
        t = self.close_templates.get(phase)
        if t is not None:
            t = string.Template(t)
            yield t.substitute(symbols)

# TODO: This should probably just be a factory function since it could
# really apply to any sort of Element...the use of the TemplateElement
# as a base is essentially just laziness.
class SigTemplateElement(TemplateElement):
    '''An Element that includes some sort of C++ signature in it.

    If the ``symbols`` argument includes the key "signature" then the
    keys "header_signature", "impl_signature", and "parameters" are
    automatically generated from it.
    '''

    @trace
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
