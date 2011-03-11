from .element import SigTemplateElement
from .signature import parse
from .trace import trace

header_template = '$return_type $name($header_signature);'

impl_template = '''
$return_type $name($impl_signature) {
  try {
    return boost::python::extract<$return_type>(
      module().attr("$python_name")($parameters));
  } catch (const boost::python::error_already_set&) {
      core::translatePythonException();
      throw;
  }
}'''

impl_void_template = '''
void $name($impl_signature) {
  try {
      module().attr("$python_name")($parameters);
  } catch (const boost::python::error_already_set&) {
      core::translatePythonException();
      throw;
  }
}'''

class Function(SigTemplateElement):
    '''A basic free function.
    '''
    def __init__(self, 
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None,
                 impl_includes=None):

        impl_includes = impl_includes or []

        SigTemplateElement.__init__(
            self,
            header_open_template=header_template,
            impl_open_template=impl_void_template if return_type == 'void' else impl_template,
            impl_includes=impl_includes + [
                ('boost', 'python', 'extract.hpp'),
                ('ackward', 'core', 'Exceptions.hpp')],
            symbols={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                })

@trace
def function(sig):
    '''Parse a function signature and return a Function instance.
    '''
    rtype, name, args, const = parse(sig)

    return Function(
        name=name,
        return_type=rtype,
        signature=args)
