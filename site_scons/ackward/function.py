from .element import SigTemplateElement
from .include import ImplInclude
from .signature import parse
from .trace import trace

header_template = '$return_type $name($header_signature);'

impl_template = '''
$return_type $name($impl_signature) {
  try {
    return boost::python::extract<$return_type>(
      module().attr("$python_name")($parameters));
  } TRANSLATE_PYTHON_EXCEPTION()
}'''

impl_void_template = '''
void $name($impl_signature) {
  try {
      module().attr("$python_name")($parameters);
  } TRANSLATE_PYTHON_EXCEPTION()
}'''

class Function(SigTemplateElement):
    '''A basic free function.
    '''

    @trace
    def __init__(self,
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None,
                 impl_includes=None,
                 parent=None,
                 doc=None):

        impl_includes = impl_includes or []
        impl_includes.extend(
            [('boost', 'python', 'extract.hpp'),
             ('ackward', 'core', 'ExceptionTranslation.hpp')])

        SigTemplateElement.__init__(
            self,
            open_templates={
                'header': header_template,
                'impl': impl_void_template if return_type == 'void' else impl_template
            },
            symbols={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                },
            parent=parent,
            doc=doc)

        for h in impl_includes:
            self.add_child(
                ImplInclude(h))

@trace
def function(sig, parent=None, doc=None):
    '''Parse a function signature and return a Function instance.
    '''
    rtype, name, args, const = parse(sig)

    return Function(
        name=name,
        parent=parent,
        return_type=rtype,
        signature=args,
        doc=doc)
