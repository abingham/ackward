from ..template import ContainerTemplate, ElementTemplate
from ..util import trace

header_template = '''
class $class_name $bases {
public:
  $class_name(boost::python::object);

$body

  using Object::obj;

private:
    static boost::python::object cls();
};
'''

impl_template = '''
$class_name::$class_name(boost::python::object o) :
  Object (o)
{}

$body

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

class Class(ContainerTemplate):
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

        super(Class, self).__init__(
            header_template,
            impl_template,
            { 'class_name' : name,
              'wrapped_class' : wrapped_class,
              'bases' : bases,
              })

        self.name = name
        self.wrapped_class = wrapped_class

class ClassElement(ElementTemplate):
    '''A base for templates describing elements of a class
    (e.g. methods, properties, etc.)
    '''
    def __init__(self, 
                 cls, 
                 header_template, 
                 impl_template,
                 args={}):
        args.update({
                'wrapped_class' : cls.wrapped_class,
                'class_name' : cls.name
                })
        
        self.cls = cls
        cls.elements.append(self)

        super(ClassElement, self).__init__(
            header_template,
            impl_template,
            args)
