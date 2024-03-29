from .element import TemplateElement
from .include import ImplInclude
from .trace import trace

header_template = '$type $module_property_name();'

impl_template = '''
$type $module_property_name() {
    using namespace boost::python;
    try {
        object prop =
            $module_function().attr("$python_name");
        return extract<$type>(prop);
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

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
        impl_includes.extend([
            ('boost', 'python', 'extract.hpp'),
            ('boost', 'python', 'object.hpp'),
            ('ackward', 'core', 'ExceptionTranslation.hpp'),
        ])

        TemplateElement.__init__(
            self,
            open_templates={
                'header': header_template,
                'impl': impl_template,
            },
            symbols={
                'module_property_name' : name,
                'type' : type,
                'python_name' : name if python_name is None else python_name,
                },
            *args,
            **kwargs)

        for h in impl_includes:
            self.add_child(
                ImplInclude(h))
