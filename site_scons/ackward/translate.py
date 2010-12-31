import imp, os, sys

from translation_unit import (
    includes,
    forward_declarations,
    namespace,
    preprocessor_guard,
    using)

def translate_header_file(infile, outfile=None):
    '''Translate an ackward input file into a C++ header file.

    This imports `infile` as a module and calls the `definition`
    method in that module. `definition` should return a
    TranslationUnit instance, and this method uses the information in
    that TranslationUnit to generate a header file.

    Args:
      * infile: The input ackward source file.
      * outfile: The file into which to write the C++ output code. If
          this is None (default), then the C++ is written to stdout.
    '''
    # Load the ackward source module
    with open(infile, 'r') as f:
        mod = imp.load_module(os.path.splitext(infile)[0].replace(os.path.sep, '_'),
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    # Body will ultimately contain all of the component elements of
    # the output.
    body = []

    # Get the translation unit object from the module.
    tunit = mod.definition() 

    # always include these headers
    header_includes = set([('boost', 'call_traits.hpp'),
                           ('boost', 'python', 'object_fwd.hpp')])
    fwd_decls = set()

    # Get the header-includes.
    header_includes.update(tunit.header_includes)

    # Get the forward declarations.
    fwd_decls.update(tunit.forward_declarations)

    # Generate the header-includes code.
    body.extend(
        includes.generate(
            header_includes))

    # Generate the forward-decls code.
    body.extend(
        forward_declarations.generate(
            fwd_decls))

    # Generate the rest of the objects in the translation unit.
    for ns, objs in tunit.objects.items():
        body.extend(
            namespace.generate(
                ns,
                [obj.generate_header() for obj in objs]))

    # Generate the preprocessor guard for the translation unit.
    body = preprocessor_guard.generate(
        mod,
        tunit.preprocessor_guard, 
        body)

    # Combine all of the body elements into a single strings
    text = '\n\n'.join(body)

    # Write the results out to either the specified file or stdout.
    if outfile:
        with open(outfile, 'w') as f:
            f.write(text)
    else:
        sys.stdout.write(text)

def translate_impl_file(infile, outfile=None):
    '''Translate an ackward input file into a C++ implementation file.

    Args:
      * infile: The input ackward source file.
      * outfile: The file into which to write the C++ output code. If
          this is None (default), then the C++ is written to stdout.
    '''

    # See comments in `translate_header_file` for info on what's going
    # on here. It's largely the same routine, just with a few
    # twists. Yes, it should probably be refactored a bit.

    with open(infile, 'r') as f:
        mod = imp.load_module('akw_input', 
                              f, 
                              infile, 
                              ('', 'r', imp.PY_SOURCE))

    body = []

    tunit = mod.definition()

    impl_includes = set([
            ('boost', 'python.hpp'),
            ('ackward', 'core', 'Exceptions.hpp'),
            ])
    impl_includes.update(tunit.impl_includes)

    body.extend(
        includes.generate(
            impl_includes))

    usings = set(['namespace boost::python'])
    usings.update(tunit.using)
    
    body.append(
        using.generate(
            usings))

    for ns, objs in tunit.objects.items():
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

def main():
    '''Translate an input file into a C++ header and impl file.

    This reads its arguments from `sys.argv` like this:

       prog_name source_file [header_output_file [impl_output_file]]

    If an output file is missing, then those results are written to
    stdout.
    '''
    outheader = sys.argv[2] if len(sys.argv) > 2 else None
    outimpl = sys.argv[3] if len(sys.argv) > 3 else None
    infile = sys.argv[1]

    translate_header_file(infile, outheader)
    translate_impl_file(infile, outimpl)

if __name__ == '__main__':
    main()
