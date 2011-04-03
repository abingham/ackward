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
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

impl_setter = '''
void $class_name::$property_name($impl_signature) {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$property_name");
        prop = val;
    } TRANSLATE_PYTHON_EXCEPTION()
}'''

class ClassProperty(SigTemplateElement):
    '''A static property on a class. 

    Args:
      * name: The name of the property.
      * type: The type of the property.
      * read_only: Whether the property is read-only or read-write.
    '''

    @trace
    def __init__(self,
                 name,
                 type,
                 read_only=False):
        header = header_getter
        impl = impl_getter

        if not read_only:
            header = '\n'.join([header, header_setter])
            impl = '\n'.join([impl, impl_setter])

        SigTemplateElement.__init__(
            self,
            open_header_template=header,
            open_impl_template=impl,
            impl_includes=[
                ('ackward', 'core', 'ExceptionTranslation.hpp'),
                ],
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')]
                })
