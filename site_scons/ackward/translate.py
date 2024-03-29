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

translate_lock = threading.Lock()

@trace
def translate(
    env,
    phases,
    infile,
    outfile=None):
    mod = Cache.load(infile)

    with translate_lock:
        body = []

        top_elem = mod.definition(env)

        def proc(f):
            for phase in phases:
                for line in top_elem.process(mod, phase):
                    f.write(line)
                    f.write('\n')

        if outfile:
            with open(outfile, 'w') as f:
                proc(f)
        else:
            proc(sys.stdout)

@trace
def translate_header(env, infile, outfile=None):
    translate(
        env,
        ['forward_decl', 'header'],
        infile,
        outfile)

@trace
def translate_impl(env, infile, outfile=None):
    translate(
        env,
        ['impl_include', 'using', 'impl'],
        infile,
        outfile)
