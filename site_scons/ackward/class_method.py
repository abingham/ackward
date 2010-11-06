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
    '''A normal method on a class.
    '''
    @trace
    def __init__(self,
                 cls,
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None):
        '''Construct a new method on a class.

        If `python_name` is None (default), it takes the value of `name`.

        Args:
          * cls: The `Class` object parent of this method.
          * name: The C++ name of this method.
          * python_name: The Python name of this method.
          * return_type: The C++ return type of the method.
          * signature: A sequence of method-signature tuples (see
              `signature` module.)
        '''
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

