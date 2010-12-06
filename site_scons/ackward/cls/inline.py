from .cls import ClassElement
from ..util import trace

class InlineMethod(ClassElement):
    '''A simple inline method inserted verbatim into the header.
    '''

    @trace
    def __init__(self,
                 cls,
                 code):
        super(InlineMethod, self).__init__(
            cls=cls,
            header_template=code,
            impl_template='')
            
