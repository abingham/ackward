class BuildProducts(object):
    def __init__(self, env):
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
        return self.products[name]
    
    def __setitem__(self, name, product):
        self.products[name] = product

