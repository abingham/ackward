'''Configuration and other stuff specific to this particular build.
'''

import logging, sys

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
