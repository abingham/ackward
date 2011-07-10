from .element import SigTemplateElement
from .trace import trace

header_const = '''
ackward::core::ROProperty<$type> $property_name;
'''

header_non_const = '''
ackward::core::Property<$type> $property_name;
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
                 read_only=False,
                 **kwargs):
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
            
        SigTemplateElement.__init__(
            self,
            header_includes=[
                ('ackward', 'core', 'Property.hpp'),
                ],
            open_header_template=header,
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')],
                'python_name' : python_name or name,
                },
            **kwargs)

    def initializers(self):
        return [
            '{0}(obj(), "{1}")'.format(self.symbols['property_name'],
                                       self.symbols['python_name']),
            ]
