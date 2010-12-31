from .cls import ClassElement
from ..util import trace

class InlineMethod(ClassElement):
    '''A simple inline method inserted verbatim into the header.

    An InlineMethod is really a catch-all way to insert arbitrary code
    into a class's header. This is useful e.g. for adding methods that
    are hard or impossible to describe using other methods.
    '''

    @trace
    def __init__(self,
                 cls,
                 code):
        super(InlineMethod, self).__init__(
            cls=cls,
            header_template=code,
            impl_template='')
            
