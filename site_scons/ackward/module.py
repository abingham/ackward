from .element import TemplateElement
from .include import HeaderInclude, ImplInclude
from .trace import trace

header_template = 'boost::python::object $module_function();'

impl_template = '''
boost::python::object $module_function()
{
  static boost::python::object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = ackward::core::import("$module_name");
    initialized = true;
  }

  return mod;
}
'''

class Module(TemplateElement):
    '''Generates a method that returns a python module object.
    '''

    @trace
    def __init__(self,
                 name,
                 function_name='module',
                 parent=None):
        '''Create a new Module object.

        Args:
          * name: The name of the python module to be returned by the
              generated method.
          * function_name: The name of the C++ method to generate.
        '''
        TemplateElement.__init__(
            self,
            open_templates={
                'header': header_template,
                'impl': impl_template,
            },
            symbols={
                'module_name' : name,
                'module_function' : function_name,
                },
            parent=parent)

        self.add_child(
            ImplInclude(
                ('ackward', 'core', 'Import.hpp')))

        self.add_child(
            HeaderInclude(
                ('boost', 'python', 'object.hpp')))