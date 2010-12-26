import os

class SharedLib(object):
    '''Represents a single shared library in the build_products map.

    This can be used to configure build environments to link/build
    against this library.
    '''
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
            os.path.join('$INSTALL_DIR', 'lib'), 
            source = [lib]))
    
def _install_headers(env, headers, subdir):
    env.Alias(
        'install',
        env.Install(
            os.path.join('$INSTALL_DIR', 'include', 'ackward', subdir),
            headers))

def build_shared_library(env,
                         name,
                         sources,
                         headers,
                         akw_files=[],
                         deps=[]):
    '''A central rule for building shared libraries in ackward.

    This takes care of setting up the building and installation of a
    shared library and its header files. This ultimately adds targets
    to the 'build' and 'install' alias.

    Args:
      * name: The root name of the library, e.g. "uuid", not "ackward_uuid".
      * sources: A list of "cpp" files/nodes (implementation files)
          for the library.
      * headers: A list of header files/nodes for the library.
      * akw_files: A list of ackward source files.
      * deps: A list of other shared libraries upon which this library
          depends. Use short names (e.g. "foo", not "ackward_foo")
    '''
    akw_headers = [env.AkwHeader(akw) for akw in akw_files]

    akw_impls = [env.AkwImpl(akw) for akw in akw_files]

    _build_shared_library(
        env,
        name,
        sources + akw_impls)

    _install_headers(env,
                     headers + akw_headers,
                     name)
