import SCons.Script

import names

def init_vars(vars):
    '''Initialize the build variables
    '''
    vars.Add('BOOST_INCLUDE_DIR', 'Location of boost headers', '/usr/include')
    vars.Add('BOOST_LIB_DIR', 'Location of boost libraries', '/usr/lib')
    vars.Add('BOOST_LIBS', 
             'Boost libraries to link', 
             ['boost_filesystem', 'boost_python', 'boost_system'])
    
    vars.Add('PYTHON_INCLUDE_DIR', 'Location of Python headers', '/usr/include/python2.6')
    vars.Add('PYTHON_LIB_DIR', 'Location of Python libraries', '/usr/lib')
    vars.Add('PYTHON_LIBS', 'Python libraries to link', ['python2.6'])

    vars.Add('VARIANT', 'Compile with debugging', 'release')

    vars.Add('CXX', 'C++ compiler to use', None)
    vars.Add('CXXFLAGS', 'C++ compiler flags', [])

    vars.Add('BUILD_DIR', 'Build-product directory', None)

    return vars

def check_config(env):
    '''Check the system configuration, build variables, etc.
    '''
    conf = SCons.Script.Configure(env)

    for header, package in { 'boost/python.hpp' : 'boost.python',
                             'Python.h' : 'python' }.items():
        if not conf.CheckCXXHeader(header):
            print 'Missing header %s. %s must be installed!' % (header, package)
            Exit(1)

    for libs, package in [ (env['BOOST_LIBS'], 'boost.python'),
                           (env['PYTHON_LIBS'], 'python')]:
        if not conf.CheckLib(libs, language='C++'):
            print 'Missing library/ies %s. %s must be installed!' % (libs, package)
            Exit(1)

    return conf.Finish()

def configure_release(env):
    '''Release-specific build settings
    '''
    names.configure_variant_suffixes(env)

def configure_debug(env):
    '''Debug-specific build settings
    '''
    env.AppendUnique(CXXFLAGS=['-g', '-O0'])
    env.AppendUnique(CPPDEFINES=['ACKWARD_DEBUG'])
    names.configure_variant_suffixes(env)

# Maps from variant names to variant-specific configuration functions
variant_config = {
    'release' : configure_release,
    'debug' : configure_debug
    }

def configure_variant(env):
    '''Perform variant-specific configuration of the environment. 

    This assumes that env['VARIANT'] has been set e.g. by init_vars().
    '''
    try:
        variant = env['VARIANT']
    except KeyError:
        print 'ERROR: "VARIANT" not set in environment.'

    try:
        variant_config[variant](env)
    except KeyError:
        print 'ERROR: Invalid variant "%s". Valid options are %s.' % (variant,
                                                                      variant_config.keys())
        Exit(1)
