from .cls import ClassElement
from ..util import trace

header_getter = 'static $type $name();'

header_setter = 'static void $name(const $type& val);'

impl_getter = '''
$type $class_name::$name() {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$name");
        return extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

impl_setter = '''
void $class_name::$name(const $type& val) {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$name");
        prop = val;
    } catch (const error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''


class ClassProperty(ClassElement):
    @trace
    def __init__(self,
                 cls,
                 name,
                 type,
                 read_only=False):
        header = header_getter
        impl = impl_getter
        if not read_only:
            header = '\n'.join([header, header_setter])
            impl = '\n'.join([impl, impl_setter])

        super(ClassProperty, self).__init__(
            cls=cls,
            header_template=header,
            impl_template=impl,
            args={
                'name' : name,
                'type' : type,
                })
