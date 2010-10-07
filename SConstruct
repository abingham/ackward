import imp, os

import build_utils.config as config

vars = Variables('custom.py')
config.init_vars(vars)

env = Environment(variables=vars,
                  tools=['default', TOOL_ACKWARD])

env['products'] = {}

Help(vars.GenerateHelpText(env))

# Run variant-specific configuration
config.configure_variant(env)

env.AppendUnique(CPPPATH=['$BOOST_INCLUDE_DIR',
                          '$PYTHON_INCLUDE_DIR'])

env.AppendUnique(LIBPATH=['$BOOST_LIB_DIR',
                          '$PYTHON_LIB_DIR'])

env.AppendUnique(LIBS=['$BOOST_LIBS',
                       '$PYTHON_LIBS'])

if not env.GetOption('clean') and not env.GetOption('help'):
    env = config.check_config(env)

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
