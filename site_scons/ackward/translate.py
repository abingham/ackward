import imp, sys, threading
from .trace import trace

class Cache:
    '''Imported module cache.

    Avoids re-importing of modules.
    '''
    cache = {}
    count = 0
    load_lock = threading.Lock()

    @staticmethod
    @trace
    def load(infile):
        with Cache.load_lock:
            try:
                mod = Cache.cache[infile]
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

            return mod

@trace
def process_header(elem, mod, symbols={}):
    symbols = dict(symbols)
    symbols.update(elem.symbols)

    for line in elem.render_doc():
        yield line

    for line in elem.open_header(mod, symbols):
        yield line

    for e in elem.children:
        for line in process_header(e, mod, symbols):
            yield line

    for line in elem.close_header(mod, symbols):
        yield line

@trace
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

translate_lock = threading.Lock()

@trace
def _translate(env, processor, infile, outfile=None):
    mod = Cache.load(infile)

    with translate_lock:
        body = []

        top_elem = mod.definition(env)

        def proc(f):
            for line in processor(top_elem, mod):
                f.write(line)
                f.write('\n')

        if outfile:
            with open(outfile, 'w') as f:
                proc(f)
        else:
            proc(sys.stdout)

@trace
def translate_header(env, infile, outfile=None):
    _translate(env, process_header, infile, outfile)

@trace
def translate_impl(env, infile, outfile=None):
    _translate(env, process_impl, infile, outfile)
