'''Configuration and other stuff specific to this particular build.
'''

import logging, os, sys
import bygg

from .variables import init_variables, check_config

def _init_logging(env):
    if int(env['VERBOSE']) == 1:
        level = logging.INFO
    else:
        level = logging.WARNING
    
    logging.basicConfig(stream=sys.stdout,
                        level=level,
                        format='[%(name)s] %(message)s')

def _init_compiler(env):
    if 'g++' in env['TOOLS']:
        env.AppendUnique(CXXFLAGS=['-std=c++0x',
                                   '-Wall'])

def configure(env):
    '''Called immediately after environment is constructed.
    '''
    _init_logging(env)
    _init_compiler(env)

def shared_library(env,
                   name,
                   sources,
                   headers,
                   akw_files=[],
                   deps=[]):
    akw_headers = [env.AkwHeader(akw) for akw in akw_files]

    akw_impls = [env.AkwImpl(akw) for akw in akw_files]

    bygg.build_shared_library(
        env=env,
        name=name,
        sources=sources + akw_impls,
        headers=headers + akw_headers,
        lib_name='ackward_{0}'.format(name),
        lib_dir=os.path.join('$INSTALL_DIR', 'lib'),
        include_dir=os.path.join('$INSTALL_DIR', 'include'),
        include_subdir=os.path.join('ackward', name))
