import imp, sys

import includes
import forward_declarations
import module
import namespace
import preprocessor_guard
import using


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
    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    body = []

    tunit = mod.definition()

    # always include these headers
    header_includes = set([('boost', 'call_traits.hpp'),
                           ('boost', 'python', 'object_fwd.hpp')])
    fwd_decls = set()

    header_includes.update(tunit.header_includes())
    fwd_decls.update(tunit.forward_declarations())

    body.extend(
        includes.generate(
            header_includes))

    body.extend(
        forward_declarations.generate(
            fwd_decls))

    for ns, objs in tunit.objects().items():
        body.extend(
            namespace.generate(
                ns,
                [obj.generate_header() for obj in objs]))

    body = preprocessor_guard.generate(
        mod,
        tunit.preprocessor_guard(), 
        body)

    text = '\n\n'.join(body)

    if outfile:
        with open(outfile, 'w') as f:
            f.write(text)
    else:
        sys.stdout.write(text)

def translate_impl_file(infile, outfile=None):
    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    body = []

    tunit = mod.definition()

    impl_includes = set([
            ('boost', 'python', 'object.hpp')
            ])
    impl_includes.update(tunit.impl_includes())

    body.extend(
        includes.generate(
            impl_includes))

    usings = set(['namespace boost::python'])
    usings.update(tunit.using())
    
    body.append(
        using.generate(
            usings))

    body.append(module.generate(tunit.module()))

    for ns, objs in tunit.objects().items():
        body.extend(
            namespace.generate(
                ns,
                [obj.generate_impl() for obj in objs]))

    text = '\n\n'.join(body)

    if outfile:
        with open(outfile, 'w') as f:
            f.write(text)
    else:
        sys.stdout.write(text)

if __name__ == '__main__':
    outheader = sys.argv[2] if len(sys.argv) > 2 else None
    outimpl = sys.argv[3] if len(sys.argv) > 3 else None
    infile = sys.argv[1]

    translate_header_file(infile, outheader)
    translate_impl_file(infile, outimpl)
