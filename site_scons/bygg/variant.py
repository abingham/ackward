'''These are a collection of build variants.
'''

import logging, sys

logger = logging.getLogger('bygg.variant')

class Variant(object):
    def __init__(self, name):
        self.name = name

    def configure(self, env):
        #env['SHLIBSUFFIX'] = '-%s' % self.name + env['SHLIBSUFFIX']
        #env['SHOBJSUFFIX'] = '.%s' % self.name + env['SHOBJSUFFIX']
        #env['OBJSUFFIX'] = '.%s' % self.name + env['OBJSUFFIX']
        pass
    
class DebugVariant(Variant):
    def __init__(self, name='debug'):
        super(DebugVariant, self).__init__(name)

    def configure(self, env):
        super(DebugVariant, self).configure(env)
        env.AppendUnique(CXXFLAGS=['-g', '-O0'])

class ReleaseVariant(Variant):
    def __init__(self, name='release'):
        super(ReleaseVariant, self).__init__(name)

# Maps from variant names to variant-specific configuration functions
_variants = {
    'release' : ReleaseVariant(),
    'debug' : DebugVariant()
    }

def register_variant(name, variant):
    _variants[name] = variant

register_variant('release', ReleaseVariant())
register_variant('debug', DebugVariant())

def configure_variant(env, variant):
    '''Perform variant-specific configuration of the environment. 

    `variant` is the name of the variant that should configure `env`.
    '''
    try:
        logger.info('Configuring for variant {0}'.format(variant))
        _variants[variant].configure(env)
    except KeyError:
        logger.error('Invalid variant "{0}". Valid options are {1}.'.format(variant,
                                                                            variants.keys()))
        sys.exit(1)

