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
    @trace
    def __init__(self, 
                 name,
                 type,
                 python_name=None):
        super(ModuleProperty, self).__init__(
            header_template=header_template,
            impl_template=impl_template,
            args={
                'name' : name,
                'type' : type,
                'python_name' : name if python_name is None else python_name,
                })
