from .element import TemplateElement

header_template = 'boost::python::object $module_function();'

impl_template = '''
boost::python::object $module_function()
{
  using namespace boost::python;

  static object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = import("$module_name");
    initialized = true;
  }

  return mod;
}
'''

class Module(TemplateElement):
    '''Generates a method that returns a python module object.
    '''
    def __init__(self, 
                 name,
                 function_name='module'):
        '''Create a new Module object.

        Args:
          * name: The name of the python module to be returned by the
              generated method.
          * function_name: The name of the C++ method to generate.
        '''
        TemplateElement.__init__(
            self,
            open_header_template=header_template,
            open_impl_template=impl_template,
            header_includes=[('boost', 'python', 'object.hpp')],
            impl_includes=[('boost', 'python', 'import.hpp')],
            symbols={
                'module_name' : name,
                'module_function' : function_name,
                })
