import sys
import logging
import itertools
from string import Template
import decorator

@decorator.decorator
def trace(f, *args, **kw):
    logging.debug("calling %s with args %s, %s" % (f.__name__, args, kw))
    return f(*args, **kw)

#def trace(f):
#    return decorator.decorator(_trace, f)

# constants used in templates
tags = ('module_name',
        'class_name',
        'wrapped_class',
        'constructors',
        'classmethods',
        'classproperties',
        'properties',
        'methods',
        'read_only',
        'const')
for i, tag in enumerate(tags):
    exec('%s = %s' % (tag, i))

# translation templates

_class = Template('''
// class $class_name : private core::Object {

   $body

   using Object::obj;
// };
''')

@trace
def build_signature(sig):
    return ', '.join(['%s %s' % (t,n) for (t,n) in sig])

@trace
def build_parameters(sig):
    return ', '.join([n for (t,n) in sig])

def translate_constructors(descr):
    tmpl = Template('''
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

    rslt = []
    for ctor in descr[constructors]:
        rslt.append(
            tmpl.substitute(
                class_name = descr[class_name],
                signature = build_signature(ctor),
                wrapped_class = descr[wrapped_class],
                parameters = build_parameters(ctor)))
    return rslt

def translate_classmethods(descr):
    tmpl = Template('''
static $result_type $method_name($signature) {
    try {
        return boost::python::extract<$result_type>(
            core::getClass("$wrapped_class").attr("$method_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    rslt = []
    for name, definition in descr[classmethods].items():
        rslt.append(
            tmpl.substitute(
                result_type=definition[0],
                method_name=name,
                signature=build_signature(definition[1]),
                parameters=build_parameters(definition[1]),
                wrapped_class=descr[wrapped_class]))
    return rslt

def translate_classproperties(descr):
    tmpl = Template('''
static $result_type $property_name() {
    using namespace boost::python;
    try {
        object cls = 
            core::getClass("$wrapped_class");
        boost::python::object prop = 
            cls.attr("$property_name");
        return boost::python::extract<$result_type>(prop);
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    rslt = []
    for name, definition in descr[classproperties].items():
        rslt.append(
            tmpl.substitute(
                result_type=definition[0],
                property_name=name,
                wrapped_class=descr[wrapped_class]))
    return rslt

def translate_properties(descr):
    getter_tmpl = Template('''
$result_type $property_name() const {
    try {
        return boost::python::extract<$result_type>(
            obj().attr("$property_name"));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    setter_tmpl = Template('''
void $property_name($result_type val) {
    try {
        obj().attr("$property_name") = val;
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    rslt = []
    for name, definition in descr[properties].items():
        flags = definition[1]

        rslt.append(
            getter_tmpl.substitute(
                result_type=definition[0],
                property_name=name,
                wrapped_class=descr[wrapped_class]))

        if not const in flags:
            rslt.append(
                setter_tmpl.substitute(
                    result_type=definition[0],
                    property_name=name))
            
    return rslt

def translate_methods(descr):
    tmpl = Template('''
$result_type $method_name($signature) $const {
    try {
        return boost::python::extract<$result_type>(
            obj().attr("$method_name")($parameters));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    rslt = []
    for name, definition in descr[methods].items():
        flags = definition[2]

        cnst = 'const' if const in flags else ''

        rslt.append(
            tmpl.substitute(
                result_type=definition[0],
                method_name=name,
                signature=build_signature(definition[1]),
                parameters=build_parameters(definition[1]),
                const=cnst))

    return rslt

def translate(descr):
    body = '\n'.join(
        itertools.chain(
                translate_constructors(descr),
                translate_classmethods(descr),
                translate_classproperties(descr),
                translate_properties(descr),
                translate_methods(descr),
                ))

    cls = _class.substitute(
        class_name=descr[class_name],
        body=body)

    return cls

def translate_file(infile, outfile=None):
    print infile, outfile

    with open(infile, 'r') as f:
        rslt = translate(eval(f.read()))

    if outfile:
        with open(outfile, 'w') as f:
            f.write(rslt)
    else:
        sys.stdout.write(rslt)

if __name__ == '__main__':
    outfile = sys.argv[2] if len(sys.argv) > 2 else None
    infile = sys.argv[1]

    translate_file(infile, outfile)
