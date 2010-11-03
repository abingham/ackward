import string

from .signature import *
from .util import trace

class Template(object):
    def __init__(self,
                 header_template,
                 impl_template,
                 args={}):
        self.header_template = string.Template(header_template)
        self.impl_template = string.Template(impl_template)
        self.args = args

    @trace
    def _generate(self, template, args):
        args.update(self.args)
        return template.substitute(**args)

    @trace
    def generate_header(self, args={}):
        return self._generate(self.header_template, args)

    @trace
    def generate_impl(self, args={}):
        return self._generate(self.impl_template, args)

class ContainerTemplate(Template):
    def __init__(self,
                 header_template,
                 impl_template,
                 args={},
                 elements_tag='body'):
        super(ContainerTemplate, self).__init__(
            header_template,
            impl_template,
            args)

        self.elements_tag = elements_tag
        self.elements = []

    @trace
    def generate_header(self, args={}):
        body = '\n'.join([e.generate_header() for e in self.elements])

        args.update({self.elements_tag : body})

        return super(ContainerTemplate, self).generate_header(args)

    @trace
    def generate_impl(self, args={}):
        body = '\n'.join([e.generate_impl() for e in self.elements])

        args.update({self.elements_tag : body})

        return super(ContainerTemplate, self).generate_impl(args)

class ElementTemplate(Template):
    def __init__(self,
                 parent, 
                 header_template, 
                 impl_template,
                 args={}):
        try:
            sig = args['signature']
            args.update({
                    'header_signature' : build_signature(sig, True),
                    'impl_signature' : build_signature(sig, False),
                    'parameters' : build_parameters(sig)})
        except KeyError:
            pass

        super(ElementTemplate, self).__init__(
            header_template,
            impl_template,
            args)

        self.parent = parent
        self.parent.elements.append(self)
