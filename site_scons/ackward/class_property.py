from .element import SigTemplateElement
from .trace import trace

header_getter = 'static $type $property_name();'

header_setter = 'static void $property_name($header_signature);'

impl_getter = '''
$type $class_name::$property_name() {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$property_name");
        return extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

impl_setter = '''
void $class_name::$property_name($impl_signature) {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$property_name");
        prop = val;
    } catch (const error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

# TODO: This should be generating code to use the new
# core::Property<T> class

class ClassProperty(SigTemplateElement):
    @trace
    def __init__(self,
                 name,
                 type,
                 read_only=False):
        '''Construct a new static property on a class. 

        Args:
          * name: The name of the property.
          * type: The type of the property.
          * read_only: Whether the property is read-only or read-write.
        '''

        header = header_getter
        impl = impl_getter
        if not read_only:
            header = '\n'.join([header, header_setter])
            impl = '\n'.join([impl, impl_setter])

        SigTemplateElement.__init__(
            self,
            header_open_template=header,
            impl_open_template=impl,
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')]
                })
