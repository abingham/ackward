from .cls import ClassElement
from ..util import trace

header_getter = 'static $type $name();'

header_setter = 'static void $name($header_signature);'

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
void $class_name::$name($impl_signature) {
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
        '''Construct a new static property on a class. 

        Args:
          * cls: The class object on which to create the property.
          * name: The name of the property.
          * type: The type of the property.
          * read_only: Whether the property is read-only or read-write.
        '''

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
                'signature' : [(type, 'val')]
                })
