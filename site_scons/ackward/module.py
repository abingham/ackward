from .template import ContainerTemplate
from .util import trace

header_template = '''
boost::python::object module();

$body
'''

impl_template = '''
object module()
{
  static object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = import("$module_name");
    initialized = true;
  }

  return mod;
}

$body
'''

class Module(ContainerTemplate):
    @trace
    def __init__(self,
                 name):
        super(Module, self).__init__(
            header_template,
            impl_template,
            { 'module_name' : name })
