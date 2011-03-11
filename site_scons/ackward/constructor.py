from .element import SigTemplateElement
from .trace import trace

header_template = '${class_name}($header_signature);'

impl_template = '''
${class_name}::${class_name}($impl_signature) try :
  core::Object (
    ${class_name}::cls()($parameters) )
{
}
catch (const boost::python::error_already_set&)
{
  core::translatePythonException();
  throw;
}'''

class Constructor(SigTemplateElement):
    '''A template for class constructors.
    '''

    @trace
    def __init__(self, 
                 signature=[]):
        '''
        Args:
          * cls: The class to which this contructor belongs.
          * signature: A sequence of parameter descriptions.
        '''
        SigTemplateElement.__init__(
            self,
            header_open_template = header_template,
            impl_open_template = impl_template,
            symbols = {
                'signature' : signature,
                })