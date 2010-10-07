import os

import names

def build_shared_library(env, name, sources, deps=[]):
    local_env = env.Clone()
    lib = local_env.SharedLibrary(names.libname(name), sources)
    for dep in deps:
        local_env.AppendUnique(LIBS=[names.liblinkname(env, dep)])
        local_env.AppendUnique(LIBPATH=[os.path.join('#', 'src', 'ackward', dep)])

    env['products']['ackward_%s' % name] = lib
    env.Alias('all', lib)
