from .cls import ClassElement
from ..util import trace

header_getter = '$type $name() const;'

header_setter = 'void $name($header_signature);'

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
void $class_name::$name($impl_signature) {
    try {
        obj().attr("$python_name") = val;
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

class Property(ClassElement):
    '''A "property" in a C++ class.

    This wraps a property on a python object. C++ doesn't really
    support properties in the python sense. Instead, this generates
    one (in the case of read-only properties) or two (for read-write
    properties) methods on a class that allow getting/setting of the
    property values.
    '''

    # TODO: Consider using a Property<Type> class for properties instead of 
    # methods. We didn't do this originally because it feels "wierd" in C++. However, it should be perfectly possible to support syntax like:
    #   
    #  MyClass c;
    #  c.propA = 123;     // MyClass.propA is a Property<int>
    #  int val = c.propA;

    @trace
    def __init__(self,
                 cls,
                 name,
                 type,
                 python_name=None,
                 read_only=False):
        '''
        Args:
          * cls: The class on which to put the property.
          * name: The C++ name of the property.
          * type: The C++ type of the property.
          * python_name: The name of the wrapped python property. If
              `None`, then `name` is used for this value.
          * read_only: Whether this property is read-only or
              read-write.
        '''
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
                'signature' : [(type, 'val')],
                'python_name' : name if python_name is None else python_name,
                })
