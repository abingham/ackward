from .element import SigTemplateElement
from .trace import trace

header_const = '''
$type $property_name() const;
'''

header_non_const = header_const + '''
void $property_name($header_signature);
'''

impl_const = '''
$type $class_name::$property_name() const {
   try {
     return boost::python::extract<$type>(
       obj().attr("$python_name"));
   } catch (const boost::python::error_already_set&) {
       core::translatePythonException();
       throw;
   }
}
'''

impl_non_const = impl_const + '''
void $class_name::$property_name($impl_signature) {
   try {
     obj().attr("$python_name") = val;
   } catch (const boost::python::error_already_set&) {
       core::translatePythonException();
       throw;
   }
}
'''

class Property(SigTemplateElement):
    '''A "property" in a C++ class.

    This wraps a property on a python object.
    '''

    @trace
    def __init__(self,
                 name,
                 type,
                 python_name=None,
                 read_only=False):
        '''
        Args:
          * name: The C++ name of the property.
          * type: The C++ type of the property.
          * python_name: The name of the wrapped python property. If
              `None`, then `name` is used for this value.
          * read_only: Whether this property is read-only or
              read-write.
        '''
        header = header_const if read_only else header_non_const
        impl = impl_const if read_only else impl_non_const
            
        SigTemplateElement.__init__(
            self,
            header_includes=[],
            header_open_template=header,
            impl_open_template=impl,
            impl_includes=[
                ('boost', 'python', 'extract.hpp'),
                ('ackward', 'core', 'Exceptions.hpp'),
                ],
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')],
                'python_name' : python_name or name,
                })
