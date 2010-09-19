import imp, logging, sys
from string import Template

import decorator

@decorator.decorator
def trace(f, *args, **kw):
    logging.debug("calling %s with args %s, %s" % (f.__name__, args, kw))
    return f(*args, **kw)

@trace
def build_signature(sig):
    return ', '.join(['%s %s' % (t,n) for (t,n) in sig])

@trace
def build_parameters(sig):
    return ', '.join([n for (t,n) in sig])

class Class(object):
    template = Template('''
    $body

    using Object::obj;
''')

    @trace
    def __init__(self,
                 name,
                 wrapped_class):
        self.name = name
        self.wrapped_class=wrapped_class
        
        self.elements = []

    @trace
    def generate(self):
        body = '\n'.join([e.generate() for e in self.elements])

        return Class.template.substitute(
            body=body)

class Element(object):
    def __init__(self, cls, template, args):
        self.cls = cls
        self.template = template
        self.args = args

        self.args.update({
                'wrapped_class' : cls.wrapped_class,
                'class_name' : cls.name
                })

        self.cls.elements.append(self)

    def generate(self):
        return self.template.substitute(**self.args)

class Constructor(Element):
    template = Template('''
${class_name}($signature) try :
  core::Object (
    core::getClass("$wrapped_class")($parameters) )
{
}
catch (const boost::python::error_already_set&)
{
  core::translatePythonException();
  throw;
}''')

    @trace
    def __init__(self, 
                 cls,
                 signature=[]):
        super(Constructor, self).__init__(
            cls = cls,
            template = Constructor.template,
            args = {
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature)
                })
    
class ClassMethod(Element):

    template = Template('''
static $return_type $name($signature) {
    try {
        return boost::python::extract<$return_type>(
            core::getClass("$wrapped_class").attr("$python_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    @trace
    def __init__(self,
                 cls,
                 name,
                 python_name=None,
                 return_type='void',
                 signature=[]):
        super(ClassMethod, self).__init__(
            cls=cls,
            template=ClassMethod.template,
            args = {
                'name' : name,
                'python_name' : name if python_name is None else python_name,
                'return_type' : return_type,
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature)
                })

class ClassProperty(Element):
    getter = '''
static $type $name() {
    using namespace boost::python;
    try {
        object cls = 
            core::getClass("$wrapped_class");
        boost::python::object prop = 
            cls.attr("$name");
        return boost::python::extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    setter = '''
static void $name(const $type& val) {
    using namespace boost::python;
    try {
        object cls = 
            core::getClass("$wrapped_class");
        boost::python::object prop = 
            cls.attr("$name");
        prop = val;
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    @trace
    def __init__(self,
                 cls,
                 name,
                 type,
                 read_only=False):
        t = ClassProperty.getter
        if not read_only:
            t = '\n'.join([t, ClassProperty.setter])

        super(ClassProperty, self).__init__(
            cls=cls,
            template=Template(t),
            args={
                'name' : name,
                'type' : type,
                })
                 
class Property(Element):
    getter = '''
$type $name() const {
    try {
        return boost::python::extract<$type>(
            obj().attr("$name"));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    setter = '''
void $name(const $type& val) {
    try {
        obj().attr("$name") = val;
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    @trace
    def __init__(self,
                 cls,
                 name,
                 type,
                 read_only=False):
        t = Property.getter
        if not read_only:
            t  = '\n'.join([t, Property.setter])
            
        super(Property, self).__init__(
            cls=cls,
            template=Template(t),
            args={
                'name' : name,
                'type' : type,
                })

class Method(Element):
    template = Template('''
$return_type $name($signature) $const {
    try {
        return boost::python::extract<$return_type>(
            obj().attr("$python_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    @trace
    def __init__(self,
                 cls,
                 name,
                 return_type='void',
                 signature=[],
                 const=False,
                 python_name=None):
        super(Method, self).__init__(
            cls,
            template=Method.template,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature),
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else ''
                })

def translate_file(infile, outfile=None):
    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    cls = mod.classDef()

    if outfile:
        with open(outfile, 'w') as f:
            f.write(cls.generate())
    else:
        sys.stdout.write(cls.generate())

if __name__ == '__main__':
    outfile = sys.argv[2] if len(sys.argv) > 2 else None
    infile = sys.argv[1]

    translate_file(infile, outfile)
