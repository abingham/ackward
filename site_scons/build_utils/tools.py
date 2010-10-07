import os

class SharedLib(object):
    def __init__(self, node):
        self.node = node
        
    def configure(self, env, rpath=False):
        env.AppendUnique(LIBS=[self.node])
        env.AppendUnique(LIBPATH=[os.path.split(self.node.path)][0])
        if rpath:
            env.AppendUnique(RPATH=[os.path.split(self.node.path)][0])

def build_shared_library(env, name, sources, deps=[]):
    from . import products
    
    local_env = env.Clone()
    lib = local_env.SharedLibrary(name, sources)
    for dep in deps:
        products(env)[dep].configure(local_env)

    products(env)[name] = SharedLib(lib[0])
    env.Alias('all', lib)
