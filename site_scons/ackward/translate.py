import imp, sys

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
