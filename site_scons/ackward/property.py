from .element import TemplateElement
from .trace import trace

header_non_const = 'Property<$type> $property_name;'
header_const = 'const Property<$type> $property_name;'

class Property(TemplateElement):
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
            
        TemplateElement.__init__(
            self,
            header_open_template=header,
            impl_open_template='',
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')],
                'python_name' : name if python_name is None else python_name,
                })
