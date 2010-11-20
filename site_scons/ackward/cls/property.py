from .cls import ClassElement
from ..util import trace

header_getter = '$type $name() const;'

header_setter = 'void $name(const $type& val);'

impl_getter = '''
$type $class_name::$name() const {
    try {
        return boost::python::extract<$type>(
            obj().attr("$python_name"));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

impl_setter = '''
void $class_name::$name(const $type& val) {
    try {
        obj().attr("$python_name") = val;
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class Property(ClassElement):
    @trace
    def __init__(self,
                 cls,
                 name,
                 type,
                 python_name=None,
                 read_only=False):
        header = header_getter
        impl = impl_getter
        if not read_only:
            header  = '\n'.join([header, header_setter])
            impl = '\n'.join([impl, impl_setter])
            
        super(Property, self).__init__(
            cls=cls,
            header_template=header,
            impl_template=impl,
            args={
                'name' : name,
                'type' : type,
                'python_name' : name if python_name is None else python_name,
                })
