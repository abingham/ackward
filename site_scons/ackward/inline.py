from .element import TemplateElement

class InlineFunction(TemplateElement):
    '''Simple, verbatim inline code for a header file.
    '''
    def __init__(self,
                 code,
                 *args,
                 **kwargs):
        TemplateElement.__init__(
            self,
            open_header_template=code,
            *args,
            **kwargs)

