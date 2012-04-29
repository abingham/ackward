from .element import SigTemplateElement
from .include import HeaderInclude
from .trace import trace

header_const = 'ackward::core::ROProperty<$type> $property_name;'

header_non_const = 'ackward::core::Property<$type> $property_name;'

constructor_initializer = '$property_name(obj(), "$python_name")'

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
            open_templates={
                'header': header,
                'constructor_initializer': constructor_initializer,
            },
            symbols={
                'property_name' : name,
                'type' : type,
                'signature' : [(type, 'val')],
                'python_name' : python_name or name,
                },
            **kwargs)

        self.add_child(
            HeaderInclude(
                ('ackward', 'core', 'Property.hpp')))
