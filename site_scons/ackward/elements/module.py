from ..template import ElementTemplate

header_template = 'boost::python::object $function_name();'

impl_template = '''
boost::python::object $function_name()
{
  using namespace boost::python;

  static object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = import("$name");
    initialized = true;
  }

  return mod;
}
'''

class Module(ElementTemplate):
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
        super(Module, self).__init__(
            header_template=header_template,
            impl_template=impl_template,
            args={
                'name' : name,
                'function_name' : function_name,
                })
