from .element import TemplateElement
from .include import HeaderInclude, ImplInclude
from .trace import trace


open_header_template = '''
class $class_name $bases {
public:
  /** Construct a new $class_name from an existing Python object.
   */
  $class_name(boost::python::object);
'''

close_header_template = '''
  using Object::obj;

private:
    static boost::python::object cls();
};
'''

open_impl_template = '''
$class_name::$class_name(boost::python::object o) :
  Object (o)
  $constructor_initializers
{}

/** Get a reference to the Python class object for `$wrapped_class`.
 */
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
                 bases=['private core::Object'],
                 parent=None,
                 doc=None):
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
            open_templates={
                'header': open_header_template,
                'impl': open_impl_template,
            },
            close_templates={
                'header':close_header_template,
            },
            symbols={
                'class_name' : name,
                'wrapped_class' : wrapped_class,
                'bases' : bases,
                },
            parent=parent,
            doc=doc)

        self.add_child(
            HeaderInclude(
                ('ackward', 'core', 'Object.hpp')))

        self.add_child(
            ImplInclude(
                ('ackward','core','GetClass.hpp')))

    @trace
    def open_phase(self, mod, phase, symbols):
        # If this is the impl phase, gather constructor-initializers
        # from any children that need to get initialized.
        if phase == 'impl':
            initializers = list(
                self.process(mod, 'constructor_initializer', symbols))

            initializers = '\n'.join([', {0}'.format(i) for i in initializers])

            symbols['constructor_initializers'] = initializers

        for line in TemplateElement.open_phase(self, mod, phase, symbols):
            yield line
