from .cls import ClassElement
from .util import trace

header_template = 'static $return_type $name($header_signature);'

impl_template = '''
$return_type $class_name::$name($impl_signature) {
    try {
        return boost::python::extract<$return_type>(
            $class_name::cls().attr("$python_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class ClassMethod(ClassElement):
    @trace
    def __init__(self,
                 cls,
                 name,
                 python_name=None,
                 return_type='void',
                 signature=[]):
        super(ClassMethod, self).__init__(
            cls=cls,
            header_template=header_template,
            impl_template=impl_template,
            args = {
                'name' : name,
                'python_name' : name if python_name is None else python_name,
                'return_type' : return_type,
                'signature' : signature,
                })

