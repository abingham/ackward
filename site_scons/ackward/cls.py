from .element import TemplateElement
from .trace import trace

header_open_template = '''
class $class_name $bases {
public:
  $class_name(boost::python::object);
'''

header_close_template = '''
  using Object::obj;

private:
    static boost::python::object cls();
};
'''

impl_open_template = '''
$class_name::$class_name(boost::python::object o) :
  Object (o)
{}

boost::python::object $class_name::cls() {
        static boost::python::object c;
        static bool initialized = false;
        if (!initialized)
        {
            c = ackward::core::getClass("$wrapped_class");
            initialized = true;
        }
        return c;
}
'''

class Class(TemplateElement):
    '''A template for generating C++ classes the "wrap" python
    classes.
    '''

    @trace
    def __init__(self,
                 name,
                 wrapped_class,
                 bases=['private core::Object']):
        '''Create a new Class object.

        Args:
          * name: The C++ name of the class to generate.
          * wrapped_class: The name of the python class that the C++
              class wraps.
          * bases: The base classes for the generated C++ class. A
              sequence base-class descriptions of the form
              "[private|protected|public] <class-name>"
        '''

        if bases:
            bases = ': ' + ','.join(bases)
        else:
            bases = ''

        TemplateElement.__init__(
            self,
            header_open_template=header_open_template,
            header_close_template=header_close_template,
            impl_open_template=impl_open_template,
            header_includes=[
                ('ackward', 'core', 'Object.hpp'),
                ],
            impl_includes=[
                ('ackward','core','GetClass.hpp'),
                ],
            symbols={ 
                'class_name' : name,
                'wrapped_class' : wrapped_class,
                'bases' : bases,
                })
