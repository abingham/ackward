'''Configuration and other stuff specific to this particular build.
'''

import itertools, logging, os, sys
import bygg

from .variables import init_variables, check_config

def _init_logging(env):
    levels = {
        'debug': logging.DEBUG,
        'info': logging.INFO,
        'warning': logging.WARNING,
        'error': logging.ERROR,
        'critical': logging.CRITICAL
        }

    try:
        level = levels[env['LOG_LEVEL']]
    except KeyError:
        raise KeyError(
            'Illegal LOG_LEVEL: {}'.format(
                env['LOG_LEVEL']))

    logging.basicConfig(
        stream=sys.stdout,
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
                   headers=[],
                   akw_files=[],
                   deps=[]):
    akw_headers = itertools.chain(*[env.AkwHeader(akw) for akw in akw_files])
    headers.extend(akw_headers)

    akw_impls = itertools.chain(*[env.AkwImpl(akw) for akw in akw_files])
    sources.extend(akw_impls)

    return bygg.build_shared_library(
        env=env,
        name=name,
        sources=sources,
        headers=headers,
        lib_name='ackward_{0}-{1}'.format(
            name,
            bygg.variant.active_variant().name),
        lib_dir=os.path.join('$INSTALL_DIR', 'lib'),
        include_dir=os.path.join('$INSTALL_DIR', 'include'),
        include_subdir=os.path.join('ackward', name))

def program(env,
            name,
            sources,
            deps=[]):
    return bygg.build_program(
        env,
        name,
        sources,
        os.path.join('$INSTALL_DIR', 'bin'),
        deps)
