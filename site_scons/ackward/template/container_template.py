from ..util import trace

from .template import Template

class ContainerTemplate(Template):
    '''A template that maintains a collection of sub-templates. 

    When a ContainerTemplate expands its string-template, it includes
    the expansions of the contained templates in a user-designated
    args key.
    '''
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
