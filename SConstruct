import imp, os

import build_utils
import variables

# Create and register our own debug variant
class DebugVariant(build_utils.DebugVariant):
    def configure(self, env):
        super(DebugVariant, self).configure(env)
        env.AppendUnique(CPPDEFINES=['ACKWARD_DEBUG'])

build_utils.variants['debug'] = DebugVariant()

# Initialize the custom build variables
vars = Variables('custom.py')
variables.init_vars(vars)

env = Environment(variables=vars,
                  tools=['default', TOOL_ACKWARD])

Help(vars.GenerateHelpText(env))

# Run variant-specific configuration
build_utils.configure_variant(env, env['VARIANT'])

env.AppendUnique(CPPPATH=['$BOOST_INCLUDE_DIR',
                          '$PYTHON_INCLUDE_DIR'])

env.AppendUnique(LIBPATH=['$BOOST_LIB_DIR',
                          '$PYTHON_LIB_DIR'])

env.AppendUnique(LIBS=['$BOOST_LIBS',
                       '$PYTHON_LIBS'])
env.AppendUnique(CXXFLAGS=['-Wall'])

if not env.GetOption('clean') and not env.GetOption('help'):
    env = variables.check_config(env)

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
