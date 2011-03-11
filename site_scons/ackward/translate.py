import imp, sys

class Cache:
    '''Imported module cache.

    Avoids re-importing of modules.
    '''
    cache = {}
    count = 0

    @staticmethod
    def load(infile):
        try:
            mod = Cache.cache[infile]
            print('HIT', infile, mod)
        except KeyError:
            pass

        with open(infile, 'r') as f:
            mod = imp.load_module(
                'akw_input_{0}'.format(Cache.count), 
                f, 
                infile, 
                ('', 'r', imp.PY_SOURCE))

        Cache.count += 1
        Cache.cache[infile] = mod
        print('MISS', infile, mod)

        return mod

def process_header(elem, mod, symbols={}):
    symbols = dict(symbols)
    symbols.update(elem.symbols)

    for line in elem.open_header(mod, symbols):
        yield line

    for e in elem.children:
        for line in process_header(e, mod, symbols):
            yield line

    for line in elem.close_header(mod, symbols):
        yield line

def process_impl(elem, mod, symbols={}):
    symbols = dict(symbols)
    symbols.update(elem.symbols)

    for line in elem.open_impl(mod, symbols):
        yield line

    for e in elem.children:
        for line in process_impl(e, mod, symbols):
            yield line

    for line in elem.close_impl(mod, symbols):
        yield line

def _translate(processor, infile, outfile=None):
    mod = Cache.load(infile)

    body = []

    top_elem = mod.definition()

    def proc(f):
        for line in processor(top_elem, mod):
            f.write(line)
            f.write('\n')

    if outfile:
        with open(outfile, 'w') as f:
            proc(f)
    else:
        proc(sys.stdout)

def translate_header(infile, outfile=None):
    _translate(process_header, infile, outfile)

def translate_impl(infile, outfile=None):
    _translate(process_impl, infile, outfile)
