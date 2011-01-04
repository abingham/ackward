'''Configuration and other stuff specific to this particular build.
'''

import logging, sys

from .variables import init_variables, check_config

def configure(env):
    '''Called immediately after environment is constructed.
    '''
    if env['VERBOSE']:
        level = logging.INFO
    else:
        level = logging.WARNING

    logging.basicConfig(stream=sys.stdout,
                        level=level,
                        format='[%(name)s] %(message)s')
