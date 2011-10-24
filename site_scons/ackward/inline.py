from .element import TemplateElement
from .trace import trace

class InlineFunction(TemplateElement):
    '''Simple, verbatim inline code for a header file.
    '''

    @trace
    def __init__(self,
                 code,
                 *args,
                 **kwargs):
        TemplateElement.__init__(
            self,
            open_header_template=code,
            *args,
            **kwargs)

