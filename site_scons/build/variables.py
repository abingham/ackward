import SCons.Script

import os

def init_variables(vars):
    '''Initialize the build variables.
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

    vars.Add('VERBOSE', 'Print extra info about the build', False)

    vars.Add('INSTALL_DIR', 'Installation directory',
             os.path.join('#', 'install', '$VARIANT'))
    
    return vars

def check_config(env):
    '''Check the system configuration, build variables, etc.
    '''
    conf = SCons.Script.Configure(env)

    for header, package in { 'boost/python.hpp' : 'boost.python',
                             'Python.h' : 'python' }.items():
        if not conf.CheckCXXHeader(header):
            print 'Missing header %s. %s must be installed!' % (header, package)
            env.Exit(1)

    for libs, package in [ (env['BOOST_LIBS'], 'boost.python'),
                           (env['PYTHON_LIBS'], 'python')]:
        if not conf.CheckLib(libs, language='C++'):
            print 'Missing library/ies %s. %s must be installed!' % (libs, package)
            env.Exit(1)

    return conf.Finish()
