'''These are a collection of build variants.
'''

import logging, sys

logger = logging.getLogger('bygg.variant')

class Variant(object):
    def __init__(self, name):
        self.name = name

    def configure(self, env):
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

class VariantManager:
    def __init__(self):
        self.variants = {}
        self.__active = None
        
    active_variant = property(lambda self: self.__active)

    def register_variant(self, name, variant):
        self.variants[name] = variant

    def configure_variant(self, env, name):
        try:
            logger.info('Configuring for variant {0}'.format(name))
            
            self.variants[name].configure(env)
            self.__active = self.variants[name]
        except KeyError:
            logger.error('Invalid variant "{0}". Valid options are {1}.'.format(name,
                                                                                self.variants.keys()))
            sys.exit(1)

mgr = VariantManager()
register_variant = mgr.register_variant
configure_variant = mgr.configure_variant
active_variant = lambda: mgr.active_variant

register_variant('release', ReleaseVariant())
register_variant('debug', DebugVariant())

