class Variant(object):
    def __init__(self, name):
        self.name = name

    def configure(self, env):
        env['SHLIBSUFFIX'] = '-%s' % self.name + env['SHLIBSUFFIX']
        env['SHOBJSUFFIX'] = '.%s' % self.name + env['SHOBJSUFFIX']
        env['OBJSUFFIX'] = '.%s' % self.name + env['OBJSUFFIX']
    
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
variants = {
    'release' : ReleaseVariant(),
    'debug' : DebugVariant()
    }

def configure_variant(env, variant):
    '''Perform variant-specific configuration of the environment. 
    '''
    try:
        variants[variant].configure(env)
    except KeyError:
        print 'ERROR: Invalid variant "%s". Valid options are %s.' % (variant,
                                                                      variants.keys())
        Exit(1)

