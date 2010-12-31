from .cls import ClassElement
from ..util import trace

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

class Constructor(ClassElement):
    '''A template for class constructors.
    '''

    @trace
    def __init__(self, 
                 cls,
                 signature=[]):
        '''
        Args:
          * cls: The class to which this contructor belongs.
          * signature: A sequence of parameter descriptions.
        '''
        super(Constructor, self).__init__(
            cls = cls,
            header_template = header_template,
            impl_template = impl_template,
            args = {
                'signature' : signature,
                })
