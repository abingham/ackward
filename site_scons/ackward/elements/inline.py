from ..template import ElementTemplate

class InlineFunction(ElementTemplate):
    '''Simple, verbatim inline code for a header file.
    '''
    def __init__(self,
                 code):
        super(InlineFunction, self).__init__(
            header_template=code,
            impl_template='')
