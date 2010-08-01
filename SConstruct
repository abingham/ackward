import os

def init_vars():
    '''Initialize the build variables
    '''
    vars = Variables('custom.py')
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

    vars.Add('BUILD_DIR', 'Build-product directory', None)

    return vars

def check_config(env):
    '''Check the system configuration, build variables, etc.
    '''
    conf = Configure(env)

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

def configure_debug(env):
    '''Debug-specific build settings
    '''
    env.AppendUnique(CXXFLAGS=['-g', '-O0'])

# Maps from variant names to variant-specific configuration functions
variant_config = {
    'release' : lambda env: None,
    'debug' : configure_debug
    }

vars = init_vars()

env = Environment(variables=vars)

env['products'] = {}

Help(vars.GenerateHelpText(env))

# Run variant-specific configuration
try:
    variant_config[env['VARIANT']](env)
except KeyError:
    print 'ERROR: Invalid variant "%s". Valid options are %s' % (env['VARIANT'],
                                                                 variant_config.keys())
    Exit(1)

env.AppendUnique(CPPPATH=['$BOOST_INCLUDE_DIR',
                          '$PYTHON_INCLUDE_DIR'])

env.AppendUnique(LIBPATH=['$BOOST_LIB_DIR',
                          '$PYTHON_LIB_DIR'])

env.AppendUnique(LIBS=['$BOOST_LIBS',
                       '$PYTHON_LIBS'])

if not env.GetOption('clean') and not env.GetOption('help'):
    env = check_config(env)

env.AppendUnique(CPPPATH='#/src')

subdirs = [
    'src/ackward',
    'src/test'
    ]

for subdir in subdirs:
    try:
        bdir = os.path.join(env['BUILD_DIR'], 
                            env['VARIANT'], 
                            subdir)
    except KeyError:
        bdir = None

    env.SConscript(
        os.path.join(subdir, 
                     'SConscript'), 
        exports='env',
        build_dir=bdir)

env.Default('all')
