from ..template import ElementTemplate
from ..util import trace

header_template = '$type $name();'

impl_template = '''
$type $name() {
    using namespace boost::python;
    try {
        object prop = 
            module().attr("$python_name");
        return extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class ModuleProperty(ElementTemplate):
    '''Template to generate a module-level property wrapper.

    This assumes the presence of a C++ method called "module()" that
    returns the appropriate module for this property.
    '''

    @trace
    def __init__(self, 
                 name,
                 type,
                 python_name=None):
        '''Construct a new ModuleProperty object.

        Args:
          * name: The C++ name of the module-level property.
          * type: The C++ type of the module-level property.
          * python_name: The python name of the property to expose.
        '''

        super(ModuleProperty, self).__init__(
            header_template=header_template,
            impl_template=impl_template,
            args={
                'name' : name,
                'type' : type,
                'python_name' : name if python_name is None else python_name,
                })
