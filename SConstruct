import imp, os

import bygg
import build

# Create and register our own debug variant
class DebugVariant(bygg.DebugVariant):
    def configure(self, env):
        super(DebugVariant, self).configure(env)
        env.AppendUnique(CPPDEFINES=['ACKWARD_DEBUG'])

bygg.register_variant('debug', DebugVariant())

# Initialize the custom build variables
vars = Variables('custom.py')
build.init_variables(vars)

env = Environment(variables=vars,
                  tools=['default', TOOL_ACKWARD])

build.configure(env)

Help(vars.GenerateHelpText(env))

# Run variant-specific configuration
bygg.configure_variant(env, env['VARIANT'])

env.AppendUnique(CPPPATH=['$BOOST_INCLUDE_DIR',
                          '$PYTHON_INCLUDE_DIR'])

env.AppendUnique(LIBPATH=['$BOOST_LIB_DIR',
                          '$PYTHON_LIB_DIR'])

env.AppendUnique(LIBS=['$BOOST_LIBS',
                       '$PYTHON_LIBS'])
env.AppendUnique(CXXFLAGS=['-Wall'])

if not env.GetOption('clean') and not env.GetOption('help'):
    env = build.check_config(env)

env.AppendUnique(CPPPATH='#/src')

# Add build dir to include path
try:
    env.AppendUnique(CPPPATH=os.path.join('#',
                                          env['BUILD_DIR'],
                                          env['VARIANT'],
                                          'src'))
except KeyError:
    pass

subdirs = [
    'src/ackward',
    'src/test',
    'examples',
    ]

for subdir in subdirs:
    try:
        vdir = os.path.join(env['BUILD_DIR'], 
                            env['VARIANT'], 
                            subdir)
    except KeyError:
        vdir = None

    env.SConscript(
        os.path.join(subdir, 
                     'SConscript'), 
        exports='env',
        variant_dir=vdir)

env.Alias('all', ['build', 'install'])
env.Default('all')
