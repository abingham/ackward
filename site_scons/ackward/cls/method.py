from .cls import ClassElement
from ..util import trace

header_template = '$virtual $return_type $name($header_signature) $const $virtual_tail;'

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

impl_void_template = '''
void $class_name::$name($impl_signature) $const {
    try {
        obj().attr("$python_name")($parameters);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class Method(ClassElement):
    
    VIRTUAL=1
    ABSTRACT=2

    @trace
    def __init__(self,
                 cls,
                 name,
                 return_type='void',
                 signature=[],
                 const=False,
                 python_name=None,
                 virtual=None):
        if virtual == Method.ABSTRACT:
            implt = ''
        elif return_type == 'void':
            implt = impl_void_template
        else:
            implt = impl_template 

        super(Method, self).__init__(
            cls,
            header_template=header_template,
            impl_template=implt,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else '',
                'virtual' : '' if virtual is None else 'virtual',
                'virtual_tail' : '= 0' if virtual == Method.ABSTRACT else ''
                })

def method(sig, cls):
    import re
    regex = re.compile('^(.*)\s(.*)\((.*)\)(\s+const)?$')
    (rtype, name, args, const) = (regex.match(sig).groups())

    args = args.split(',') if args else []

    # split out default arguments: "int x=0" -> ["int x", "0"]; "int x" -> ["int x"]
    args = [a.split('=') for a in args]
    defaults = [a[1] for a in args if len(a) == 2]
    args = [a[0] for a in args]

    # Split each arg
    args = [tuple(a.split()) for a in args]
    
    # combine multi-word types, e.g. (unsigned, int, x) -> (unsigned int, x)
    args = [(' '.join(a[:-1]), a[-1]) for a in args]

    # apply the defaults
    for i in range(len(defaults)):
        idx = len(args) - len(defaults) + i 
        args[idx] = list(args[idx]) + [defaults[i]]

    Method(
        cls=cls,
        name=name,
        return_type=rtype,
        signature=args,
        const=bool(const))
