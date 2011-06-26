from .element import SigTemplateElement
from .trace import trace

header_template = '${class_name}($header_signature);'

impl_template = '''
${class_name}::${class_name}($impl_signature) try :
  core::Object (
    ${class_name}::cls()($parameters) )
{
}
TRANSLATE_PYTHON_EXCEPTION()
'''

class Constructor(SigTemplateElement):
    '''A template for class constructors.
    '''

    @trace
    def __init__(self, 
                 signature=[],
                 doc=None):
        '''
        Args:
          * cls: The class to which this contructor belongs.
          * signature: A sequence of parameter descriptions.
        '''
        SigTemplateElement.__init__(
            self,
            open_header_template = header_template,
            open_impl_template = impl_template,
            impl_includes=[
                ('ackward', 'core', 'ExceptionTranslation.hpp'),
                ],
            symbols = {
                'signature' : signature,
                },
            doc=doc)
