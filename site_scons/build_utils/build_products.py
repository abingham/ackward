class BuildProducts(object):
    '''A class to help keep track of build products in the build.

    Really this is just a wrapper around a dict stored at the key
    'BUILD_TOOL' in an environment. This class doesn't worry about
    what stored in that dict, though it's generally things like
    SharedLib configurators and such.
    '''

    def __init__(self, env):
        '''This looks up or, if necessary, creates a few keys in the
        `env` that are used by this class.
        '''
        self.env = env

        try:
            products = env['BUILD_TOOL']
        except KeyError:
            env['BUILD_TOOL'] = {}
            products = env['BUILD_TOOL']

        try:
            products = products['BUILD_PRODUCTS']
        except KeyError:
            products['BUILD_PRODUCTS'] = {}
            products = products['BUILD_PRODUCTS']

        self.products = products

    def __getitem__(self, name):
        '''Get the build product at `name`.
        '''
        return self.products[name]
    
    def __setitem__(self, name, product):
        '''Set the build product at `name` to `product`.
        '''
        self.products[name] = product

