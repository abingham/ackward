from ..signature import *

from .template import Template

class ElementTemplate(Template):
    '''A Template for a translation-unit element that has a method
    signature.

    If the key "signature" is found in the args for this template,
    then the keys "header_signature", "impl_signature", and
    "parameters" is also generated and added to the args. This is
    convenient for things like methods, functions, and so forth.
    '''
    def __init__(self,
                 header_template, 
                 impl_template,
                 args={}):
        try:
            sig = args['signature']
            args.update({
                    'header_signature' : build_signature(sig, True),
                    'impl_signature' : build_signature(sig, False),
                    'parameters' : ', '.join([s[1] for s in sig])})
        except KeyError:
            pass

        super(ElementTemplate, self).__init__(
            header_template,
            impl_template,
            args)
