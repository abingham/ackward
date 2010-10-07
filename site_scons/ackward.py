import imp, logging, sys
from string import Template

import decorator

@decorator.decorator
def trace(f, *args, **kw):
    logging.debug("calling %s with args %s, %s" % (f.__name__, args, kw))
    return f(*args, **kw)

@trace
def build_signature(sig, header):
    '''Builds a method parameter signature given an akw signature

    Args:
      sig: A sequence of signature tuples (type, name[, default])
      header: Whether to generate for a header or not. This
        determines, for example, if default values are included in the
        output.
        
    Raises:
      ValueError: The signature input was invalid.
    '''
    def arg(a):
        if len(a) == 3 and header:
            return '\tboost::call_traits<%s>::const_reference %s = %s' % (a[0], a[1], a[2])
        elif len(a) == 2 or len(a) == 3:
            return '\tboost::call_traits<%s>::const_reference %s' % (a[0], a[1])
        else:
            raise ValueError('Signatures must be of the form (type, name[, default])')

    return ',\n'.join([arg(a) for a in sig])

@trace
def build_parameters(sig):
    return ', '.join([s[1] for s in sig])

class Module(object):
    header_template = Template('''
boost::python::object module();

$body
''')

    impl_template = Template('''
object module()
{
  static object mod;
  static bool initialized = false;

  if (!initialized)
  {
    mod = import("$module_name");
    initialized = true;
  }

  return mod;
}

$body
''')

    @trace
    def __init__(self,
                 name):
        self.name = name
        self.elements = []

    @trace
    def generate_header(self):
        body = '\n'.join([e.generate_header() for e in self.elements])

        return Module.header_template.substitute(
            body=body)

    @trace
    def generate_impl(self):
        body = '\n'.join([e.generate_impl() for e in self.elements])
        return Module.impl_template.substitute(
            module_name=self.name,
            body=body)

class Class(object):
    header_template = Template('''
$class_name(boost::python::object);

$body

using Object::obj;

private:
    static boost::python::object cls();
''')

    impl_template = Template('''
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
            class_name=self.name,
            wrapped_class=self.wrapped_class,
            body=body)

    @trace
    def generate_impl(self):
        body = '\n'.join([e.generate_impl() for e in self.elements])
        return Class.impl_template.substitute(
            class_name=self.name,
            wrapped_class=self.wrapped_class,
            body=body)
    
class Element(object):
    def __init__(self, 
                 parent, 
                 header_template, 
                 impl_template,
                 args):
        self.parent = parent
        self.header_template = header_template
        self.impl_template = impl_template
        self.args = args

        try:
            sig = self.args['signature']
            self.args.update({
                    'header_signature' : build_signature(sig, True),
                    'impl_signature' : build_signature(sig, False),
                    'parameters' : build_parameters(sig)})
        except KeyError:
            pass

        self.parent.elements.append(self)

    def generate_header(self):
        return self.header_template.substitute(**self.args)

    def generate_impl(self):
        return self.impl_template.substitute(**self.args)

class ClassElement(Element):
    def __init__(self, 
                 cls, 
                 header_template, 
                 impl_template,
                 args):
        args.update({
                'wrapped_class' : cls.wrapped_class,
                'class_name' : cls.name
                })
        
        super(ClassElement, self).__init__(cls,
                                           header_template,
                                           impl_template,
                                           args)

class Function(Element):
    header_template = Template(
        '$return_type $name($header_signature);')

    impl_template = Template('''
$return_type $name($impl_signature) {
  try {
    return boost::python::extract<$return_type>(
      module().attr("$python_name")($parameters));
  } catch (const boost::python::error_already_set&) {
      core::translatePythonException();
      throw;
  }
}''')

    @trace
    def __init__(self,
                 mod,
                 name,
                 return_type='void',
                 signature=[],
                 python_name=None):
        super(Function, self).__init__(
            parent=mod,
            header_template=Function.header_template,
            impl_template=Function.impl_template,
            args={
                'name' : name,
                'return_type' : return_type,
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                })

class Constructor(ClassElement):
    header_template = Template(
        '${class_name}($header_signature);')

    impl_template = Template('''
${class_name}::${class_name}($impl_signature) try :
  core::Object (
    ${class_name}::cls()($parameters) )
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
                'signature' : signature,
                })
    
class ClassMethod(ClassElement):

    header_template = Template(
        'static $return_type $name($header_signature);')

    impl_template = Template('''
$return_type $class_name::$name($impl_signature) {
    try {
        return boost::python::extract<$return_type>(
            $class_name::cls().attr("$python_name")($parameters));
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
                'signature' : signature,
                })

class ClassProperty(ClassElement):
    header_getter = 'static $type $name();'

    header_setter = 'static void $name(const $type& val);'

    impl_getter = '''
$type $class_name::$name() {
    using namespace boost::python;
    try {
        object prop = 
            $class_name::cls().attr("$name");
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
        object prop = 
            $class_name::cls().attr("$name");
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
                 
class Property(ClassElement):
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

class Method(ClassElement):
    header_template = Template(
        '$return_type $name($header_signature) $const;')

    impl_template = Template('''
$return_type $class_name::$name($impl_signature) $const {
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
                'signature' : signature,
                'python_name' : name if python_name is None else python_name,
                'const' : 'const' if const else ''
                })

def translate_file(method, infile, outfile=None):
    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    cls = mod.definition()
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
