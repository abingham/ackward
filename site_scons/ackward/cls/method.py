from .cls import ClassElement
from .util import trace

header_template = '$return_type $name($header_signature) $const;'

impl_template = '''
$return_type $class_name::$name($impl_signature) $const {
    try {
        return boost::python::extract<$return_type>(
            obj().attr("$python_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class Method(ClassElement):
    @trace
    def __init__(self,
                 cls,
                 name,
                 return_type='void',
                 signature=[],
                 const=False,
                 python_name=None):
        super(Method, self).__init__(
            cls,
            header_template=header_template,
            impl_template=impl_template,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else ''
                })
