from .element import SigTemplateElement
from .include import ImplInclude
from .trace import trace

header_template = '${class_name}($header_signature);'

impl_template = '''
${class_name}::${class_name}($impl_signature) try :
  core::Object (
    ${class_name}::cls()($parameters) )
  $constructor_initializers
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
                 parent=None,
                 doc=None):
        '''
        Args:
          * cls: The class to which this contructor belongs.
          * signature: A sequence of parameter descriptions.
        '''
        SigTemplateElement.__init__(
            self,
            open_templates={
                'header': header_template,
                'impl': impl_template,
            },
            symbols = {
                'signature' : signature,
                },
            parent=parent,
            doc=doc)

        self.add_child(
            ImplInclude(
                ('ackward', 'core', 'ExceptionTranslation.hpp')))
