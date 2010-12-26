import os

class SharedLib(object):
    def __init__(self, node):
        self.node = node
        
    def configure(self, env, rpath=False):
        env.AppendUnique(LIBS=[self.node])

        env.AppendUnique(LIBPATH=[os.path.split(self.node.path)[0]])
        if rpath:
            env.AppendUnique(RPATH=[os.path.split(self.node.path)[0]])

def _build_shared_library(env, name, sources, deps=[]):
    from . import products
    
    local_env = env.Clone()
    lib = local_env.SharedLibrary('ackward_{0}'.format(name), sources)
    for dep in deps:
        products(env)[dep].configure(local_env)

    products(env)[name] = SharedLib(lib[0])
    env.Alias('build', lib)
    env.Alias(
        'install',
        env.Install(
            os.path.join('#', 'install', '$VARIANT', 'lib'), 
            source = [lib]))
    
def _install_headers(env, headers, subdir):
    env.Alias(
        'install',
        env.Install(
            os.path.join('#', 'install', '$VARIANT', 'include', 'ackward', subdir),
            headers))

def build_shared_library(env,
                         name,
                         sources,
                         headers,
                         akw_files=[],
                         deps=[]):
    akw_headers = [env.AkwHeader(akw) for akw in akw_files]

    akw_impls = [env.AkwImpl(akw) for akw in akw_files]

    _build_shared_library(
        env,
        name,
        sources + akw_impls)

    _install_headers(env,
                     headers + akw_headers,
                     name)
