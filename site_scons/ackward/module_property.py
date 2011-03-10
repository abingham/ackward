from .element import TemplateElement
from .trace import trace

# TODO: Consider making this a "child" of a Module element, from which
# it could get the module function name, etc.

# TODO: the function-name "module()" should not be hard-coded. See the above TODO as well.

header_template = '$type $module_property_name();'

impl_template = '''
$type $module_property_name() {
    using namespace boost::python;
    try {
        object prop = 
            $module_function().attr("$python_name");
        return extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

# TODO: Should this be using the Property<T> construct?

class ModuleProperty(TemplateElement):
    '''Template to generate a module-level property wrapper.

    This assumes the presence of a C++ method called "module()" that
    returns the appropriate module for this property.
    '''

    @trace
    def __init__(self, 
                 name,
                 type,
                 python_name=None,
                 impl_includes=None,
                 *args,
                 **kwargs):
        '''Construct a new ModuleProperty object.

        Args:
          * name: The C++ name of the module-level property.
          * type: The C++ type of the module-level property.
          * python_name: The python name of the property to expose.
        '''

        impl_includes = impl_includes or []

        TemplateElement.__init__(
            self,
            header_open_template=header_template,
            impl_open_template=impl_template,
            impl_includes=impl_includes + [('boost', 'python', 'extract.hpp'),
                                           ('boost', 'python', 'object.hpp')],
            symbols={
                'module_property_name' : name,
                'type' : type,
                'python_name' : name if python_name is None else python_name,
                },
            *args,
            **kwargs)
