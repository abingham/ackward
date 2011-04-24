from .element import SigTemplateElement
from .signature import parse
from .trace import trace

header_template = '$virtual $return_type $method_name($header_signature) $const $virtual_tail;'

impl_template = '''
$return_type $class_name::$method_name($impl_signature) $const {
    try {
        return boost::python::extract<$return_type>(
            obj().attr("$python_name")($parameters));
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

impl_void_template = '''
void $class_name::$method_name($impl_signature) $const {
    try {
        obj().attr("$python_name")($parameters);
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

class Method(SigTemplateElement):
    '''A basic method of a class.
    '''
    
    VIRTUAL=1
    ABSTRACT=2

    @trace
    def __init__(self,
                 name,
                 return_type='void',
                 signature=[],
                 const=False,
                 python_name=None,
                 virtual=None):
        '''Create a new method on a class.

        Args:
          * name: The C++ name of the method.
          * return_type: The C++ return type of the method.
          * signature: A sequence of argument descriptions.
          * const: Whether the method is const.
          * python_name: The name of the python method represented by
              this method. If this is `None`, then `name` is used as
              the python name as well.
          * virtual: Whether this method is virtual.
        '''

        if virtual == Method.ABSTRACT:
            implt = ''
        elif return_type == 'void':
            implt = impl_void_template
        else:
            implt = impl_template 

        SigTemplateElement.__init__(
            self,
            open_header_template=header_template,
            open_impl_template=implt,
            impl_includes=[
                ('ackward', 'core', 'ExceptionTranslation.hpp'),
                ],
            symbols={
                'method_name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else '',
                'virtual' : '' if virtual is None else 'virtual',
                'virtual_tail' : '= 0' if virtual == Method.ABSTRACT else ''
                })

def method(sig):
    '''Produce a Method object based on a string description of a method.

    This is a convenience method for generated simple Methods.

    Args:
      * sig: The signature of the method.

    Returns:
      A Method object for the method described by `sig`.
    '''
    rtype, name, args, const = parse(sig)

    return Method(
        name=name,
        return_type=rtype,
        signature=args,
        const=bool(const))
