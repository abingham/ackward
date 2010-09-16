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
}
''')

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
    return boost::python::extract<$result_type>(core::getClass("$wrapped_class").attr("$method_name")());
}
''')

    rslt = []
    for name, definition in descr[classmethods].items():
        rslt.append(
            tmpl.substitute(
                result_type=definition[0],
                method_name=name,
                signature=build_signature(definition[1]),
                wrapped_class=descr[wrapped_class]))
    return rslt

def translate(descr):
    # s = Template('$who likes $what')
    # s.substitute(who='tim', what='kung pao')

    body = '\n'.join(
        itertools.chain(
                translate_constructors(descr),
                translate_classmethods(descr)
                ))

    cls = _class.substitute(
        class_name=descr[class_name],
        body=body)

    f = _file.substitute(
        module_name=descr[module_name],
        class_name=descr[class_name],
        class_definition=cls)

    print f

def translate_file(filename):
    with open(filename, 'r') as f:
        return translate(eval(f.read()))

if __name__ == '__main__':
    translate_file(sys.argv[1])
