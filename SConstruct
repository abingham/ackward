def init_vars():
    vars = Variables('custom.py')
    vars.Add('BOOST_INCLUDE_DIR', 'Location of boost headers', '/usr/include')
    vars.Add('BOOST_LIB_DIR', 'Location of boost libraries', '/usr/lib')
    vars.Add('BOOST_LIBS', 
             'Boost libraries to link', 
             ['boost_filesystem', 'boost_python', 'boost_system'])
    
    vars.Add('PYTHON_INCLUDE_DIR', 'Location of Python headers', '/usr/include/python2.6')
    vars.Add('PYTHON_LIB_DIR', 'Location of Python libraries', '/usr/lib')
    vars.Add('PYTHON_LIBS', 'Python libraries to link', ['python2.6'])

    vars.Add('DEBUG', 'Compile with debugging', False)

    vars.Add('CXX', 'C++ compiler to use', None)

    return vars

def check_config(env):
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

vars = init_vars()

env = Environment(variables=vars)

env['products'] = {}

Help(vars.GenerateHelpText(env))

if env['DEBUG']:
    env.AppendUnique(CXXFLAGS=['-g', '-O0'])

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

env.SConscript(dirs=subdirs, exports='env')

env.Default('all')
