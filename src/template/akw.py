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
        'properties',
        'methods',
        'read_only',
        'const')
for i, tag in enumerate(tags):
    exec('%s = %s' % (tag, i))

# translation templates
_file = Template('''
#ifndef INCLUDE_ACKWARD_${module_name}_${class_name}_HPP
#define INCLUDE_ACKWARD_${module_name}_${class_name}_HPP

#include <boost/python.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Object.hpp>

namespace ackward { namespace $module_name {

$class_definition

}}

#endif
''')

_class = Template('''
class $class_name : private core::Object {

   $body

   using Object::obj;
};
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
$result_type $method_name($signature) const {
    try {
        return boost::python::extract<$result_type>(
            core::getClass("$wrapped_class").attr("$method_name")());
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
                wrapped_class=descr[wrapped_class]))
    return rslt

def translate_properties(descr):
    tmpl = Template('''
$result_type $property_name() const {
    try {
        return boost::python::extract<$result_type>(
            core::getClass("$wrapped_class").attr("$property_name"));
    } catch (const boost::python::error_already_set&) {
        core::translatePythonException();
        throw;
    }
}''')

    rslt = []
    for name, definition in descr[properties].items():
        rslt.append(
            tmpl.substitute(
                result_type=definition[0],
                property_name=name,
                wrapped_class=descr[wrapped_class]))
    return rslt

def translate(descr):
    body = '\n'.join(
        itertools.chain(
                translate_constructors(descr),
                translate_classmethods(descr),
                translate_properties(descr),
                ))

    cls = _class.substitute(
        class_name=descr[class_name],
        body=body)

    rslt = _file.substitute(
        module_name=descr[module_name],
        class_name=descr[class_name],
        class_definition=cls)

    return rslt

def translate_file(infile, outfile=None):
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
