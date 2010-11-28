from ..template import ElementTemplate

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

class Function(ElementTemplate):
    def __init__(self, 
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None):
        super(Function, self).__init__(
            header_template=header_template,
            impl_template=impl_void_template if return_type == 'void' else impl_template,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                })

def function(sig):
    import re
    regex = re.compile('^(.*)\s(.*)\((.*)\)$')
    (rtype, name, args) = (regex.match(sig).groups())

    args = args.split(',') if args else []

    return Function(
        name=name,
        return_type=rtype,
        signature=[tuple(a.split()) for a in args])
