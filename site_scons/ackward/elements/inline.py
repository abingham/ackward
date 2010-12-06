from ..template import ElementTemplate

class InlineFunction(ElementTemplate):
    def __init__(self,
                 code):
        super(InlineFunction, self).__init__(
            header_template=code,
            impl_template='')
