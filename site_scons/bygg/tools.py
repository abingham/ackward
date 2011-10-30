import os

from .build_products import BuildProducts as products

class SharedLib(object):
    '''Represents a single shared library in the build_products map.

    This can be used to configure build environments to link/build
    against this library.
    '''
    def __init__(self,
                 lib_name,
                 lib_dir,
                 include_dir,
                 deps=[]):
        self.lib_name = lib_name
        self.lib_dir = lib_dir
        self.include_dir = include_dir
        self.deps = deps

    def configure(self, env, rpath=False):
        env.AppendUnique(LIBS=[self.lib_name])
        env.AppendUnique(LIBPATH=[self.lib_dir])
        env.AppendUnique(CPPPATH=[self.include_dir])

        print(self.lib_name, self.deps)

        for dep in self.deps:
            products(env)[dep].configure(env)

def _install_headers(env, headers, include_dir):
    for header in headers:
        header_path, _ = os.path.split(str(header))

        env.Alias(
            'install',
            env.Install(
                os.path.join(include_dir, header_path),
                header))

def build_shared_library(env,
                         name,
                         sources,
                         headers,
                         lib_dir,
                         include_dir,
                         include_subdir='',
                         deps=[],
                         lib_name=None):
    '''A central rule for building shared libraries.
    '''

    if not lib_name:
        lib_name = name

    local_env = env.Clone()
    lib = local_env.SharedLibrary(lib_name, sources)
    for dep in deps:
        products(env)[dep].configure(local_env)

    products(env)[name] = SharedLib(
        lib_name,
        lib_dir,
        include_dir,
        deps=deps)

    env.Alias('build', lib)
    env.Alias(
        'install',
        env.Install(
            lib_dir,
            source = [lib]))

    _install_headers(
        env,
        headers,
        os.path.join(include_dir, include_subdir))

def build_program(env,
                  name,
                  sources,
                  bin_dir,
                  deps=[]):
    local_env = env.Clone()
    bin = local_env.Program(name, sources)
    for dep in deps:
        products(env)[dep].configure(local_env)

    env.Alias('build', bin)
    env.Alias(
        'install',
        env.Install(
            bin_dir,
            source = [bin]))
