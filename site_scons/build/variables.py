import SCons.Script

import os, string

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

    vars.Add('VERBOSE', 'Print extra info about the build', 0)

    vars.Add('INSTALL_DIR', 'Installation directory',
             os.path.join('#', 'install', '$VARIANT'))
    
    return vars

def check_python_version(v):
    code = string.Template('''
#include <Python.h>
int main(int argc, char** argv) {
#if PY_MAJOR_VERSION == $version
  return 0;
#else
  this will not compile
#endif
}
''').substitute(version=v)

    print(code)
    
    def check(context):
        context.Message(
            'Checking if Python major version == {0}...'.format(v))
        result = context.TryCompile(code, '.c')
        context.Result(result)
        return result

    return check

def check_config(env):
    '''Check the system configuration, build variables, etc.
    '''
    conf = SCons.Script.Configure(
        env,
        custom_tests = {
            'CheckForPython2' : check_python_version(2),
            'CheckForPython3' : check_python_version(3),
            })

    for header, package in { 'boost/python.hpp' : 'boost.python',
                             'Python.h' : 'python' }.items():
        if not conf.CheckCXXHeader(header):
            print('Missing header {0}. {1} must be installed!'.format(
                    header, package))
            env.Exit(1)

    for libs, package in [ (env['BOOST_LIBS'], 'boost'),
                           (env['PYTHON_LIBS'], 'python')]:
        for lib in libs:
            if not conf.CheckLib(lib, language='C++'):
                print('Missing library {0}. {1} must be installed!'.format(
                        lib, package))
                env.Exit(1)

    if conf.CheckForPython2():
        env['PYTHON_VERSION'] = 2
    elif conf.CheckForPython3():
        env['PYTHON_VERSION'] = 3
    else:
        print('Python version must be either 2 or 3!')
        env.Exit(1)

    return conf.Finish()
