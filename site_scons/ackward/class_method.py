from .element import SigTemplateElement
from .include import ImplInclude
from .signature import parse
from .trace import trace


header_template = 'static $return_type $method_name($header_signature);'

impl_template = '''
$return_type $class_name::$method_name($impl_signature) {
    try {
        return boost::python::extract<$return_type>(
            $class_name::cls().attr("$python_name")($parameters));
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

class ClassMethod(SigTemplateElement):
    '''A "class method", e.g. a static method on a class.

    Requires the 'class_name' symbol for expansion.
    '''

    @trace
    def __init__(self,
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None,
                 parent=None):
        '''Construct a new method on a class.

        If `python_name` is None (default), it takes the value of `name`.

        Args:
          * name: The C++ name of this method.
          * python_name: The Python name of this method.
          * return_type: The C++ return type of the method.
          * signature: A sequence of method-signature tuples (see
              `signature` module.)
        '''
        SigTemplateElement.__init__(
            self,
            open_templates={
                'header': header_template,
                'impl': impl_template,
            },
            symbols = {
                'method_name' : name,
                'python_name' : name if python_name is None else python_name,
                'return_type' : return_type,
                'signature' : signature,
                },
            parent=parent)

        self.add_child(
            ImplInclude(
                ('ackward', 'core', 'ExceptionTranslation.hpp')))

@trace
def class_method(sig, parent=None):
    '''Produces a ClassMethod based on a string description of a
    class method.

    This is a convenience method for generating simple ClassMethods.

    Args:
      * sig: The signature of the class method.
      * cls: The class on which to put the method.

    Returns:
      A ClassMethod object for the method described by `sig`.
    '''
    rtype, name, args, const = parse(sig)

    ClassMethod(
        name=name,
        return_type=rtype,
        signature=args,
        parent=parent)
