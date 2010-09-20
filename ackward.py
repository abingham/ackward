import imp, logging, sys
from string import Template

import decorator

@decorator.decorator
def trace(f, *args, **kw):
    logging.debug("calling %s with args %s, %s" % (f.__name__, args, kw))
    return f(*args, **kw)

@trace
def build_signature(sig):
    return ', '.join(['const %s& %s' % (t,n) for (t,n) in sig])

@trace
def build_parameters(sig):
    return ', '.join([n for (t,n) in sig])

class Class(object):
    header_template = Template('''
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
    def generate_header(self):
        body = '\n'.join([e.generate_header() for e in self.elements])

        return Class.header_template.substitute(
            body=body)

    @trace
    def generate_impl(self):
        return '\n'.join([e.generate_impl() for e in self.elements])
    
class Element(object):
    def __init__(self, 
                 cls, 
                 header_template, 
                 impl_template,
                 args):
        self.cls = cls
        self.header_template = header_template
        self.impl_template = impl_template
        self.args = args

        self.args.update({
                'wrapped_class' : cls.wrapped_class,
                'class_name' : cls.name
                })

        self.cls.elements.append(self)

    def generate_header(self):
        return self.header_template.substitute(**self.args)

    def generate_impl(self):
        return self.impl_template.substitute(**self.args)

class Constructor(Element):
    header_template = Template(
        '${class_name}($signature);')

    impl_template = Template('''
${class_name}::${class_name}($signature) try :
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
            header_template = Constructor.header_template,
            impl_template = Constructor.impl_template,
            args = {
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature)
                })
    
class ClassMethod(Element):

    header_template = Template(
        'static $return_type $name($signature);')

    impl_template = Template('''
$return_type $class_name::$name($signature) {
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
            header_template=ClassMethod.header_template,
            impl_template=ClassMethod.impl_template,
            args = {
                'name' : name,
                'python_name' : name if python_name is None else python_name,
                'return_type' : return_type,
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature)
                })

class ClassProperty(Element):
    header_getter = 'static $type $name();'

    header_setter = 'static void $name(const $type& val);'

    impl_getter = '''
$type $class_name::$name() {
    using namespace boost::python;
    try {
        object cls = 
            core::getClass("$wrapped_class");
        object prop = 
            cls.attr("$name");
        return extract<$type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    impl_setter = '''
void $class_name::$name(const $type& val) {
    using namespace boost::python;
    try {
        object cls = 
            core::getClass("$wrapped_class");
        object prop = 
            cls.attr("$name");
        prop = val;
    } catch (const error_already_set&) {
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
        header = ClassProperty.header_getter
        impl = ClassProperty.impl_getter
        if not read_only:
            header = '\n'.join([header, ClassProperty.header_setter])
            impl = '\n'.join([impl, ClassProperty.impl_setter])

        super(ClassProperty, self).__init__(
            cls=cls,
            header_template=Template(header),
            impl_template=Template(impl),
            args={
                'name' : name,
                'type' : type,
                })
                 
class Property(Element):
    header_getter = '$type $name() const;'

    header_setter = 'void $name(const $type& val);'

    impl_getter = '''
$type $class_name::$name() const {
    try {
        return boost::python::extract<$type>(
            obj().attr("$name"));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}'''

    impl_setter = '''
void $class_name::$name(const $type& val) {
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
        header = Property.header_getter
        impl = Property.impl_getter
        if not read_only:
            header  = '\n'.join([header, Property.header_setter])
            impl = '\n'.join([impl, Property.impl_setter])
            
        super(Property, self).__init__(
            cls=cls,
            header_template=Template(header),
            impl_template=Template(impl),
            args={
                'name' : name,
                'type' : type,
                })

class Method(Element):
    header_template = Template(
        '$return_type $name($signature) $const;')

    impl_template = Template('''
$return_type $class_name::$name($signature) $const {
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
            header_template=Method.header_template,
            impl_template=Method.impl_template,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : build_signature(signature),
                'parameters' : build_parameters(signature),
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else ''
                })

def translate_file(method, infile, outfile=None):
    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    cls = mod.classDef()
    text = method(cls)

    if outfile:
        with open(outfile, 'w') as f:
            f.write(text)
    else:
        sys.stdout.write(text)

def translate_header_file(infile, outfile=None):
    translate_file(
        lambda cls: cls.generate_header(),
        infile, outfile)


def translate_impl_file(infile, outfile=None):
    translate_file(
        lambda cls: cls.generate_impl(),
        infile, outfile)

if __name__ == '__main__':
    outheader = sys.argv[2] if len(sys.argv) > 2 else None
    outimpl = sys.argv[3] if len(sys.argv) > 3 else None
    infile = sys.argv[1]

    translate_header_file(infile, outheader)
    translate_impl_file(infile, outimpl)
