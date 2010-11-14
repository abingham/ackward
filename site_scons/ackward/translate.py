import imp, sys

import includes
import forward_declarations
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

    body = [
        includes.generate(
            [('boost', 'call_traits.hpp'),
             ('boost', 'python', 'object_fwd.hpp')])]

    try:
        body.append(
            includes.generate(
                mod.header_includes()))
    except AttributeError:
        pass

    try:
        body.append(
            forward_declarations.generate(
                mod.forward_declarations()))
    except AttributeError:
        pass

    body.append(
        namespace.generate(
            mod,
            mod.definition().generate_header()))

    body = preprocessor_guard.generate(mod, body)

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

    try:
        body.append(
            includes.generate(
                mod.impl_includes()))
    except AttributeError:
        pass

    try:
        body.append(
            using.generate(
                mod.using()))
    except AttributeError:
        pass
    
    body.append(
        namespace.generate(
            mod,
            mod.definition().generate_impl()))

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
