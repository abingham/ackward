import string

from .signature import *
from .util import trace

class Template(object):
    '''Manages the header-file and implementation-file code-generation
    templates for the elements in a TranslationUnit.

    A Template contains two string-templates, one for the header-file
    and one for the implementation-file. It also contains the
    arguments that will be interpolated into the templates.

    This is a low-level class, and users will generally interact with
    specializations of this.
    '''
    def __init__(self,
                 header_template,
                 impl_template,
                 args={}):
        '''
        Args:
          * header_template: The template-string to be used when this
              is expanded in a header-file.
          * impl_template: The template-string to be used when this is
              expanded in an implementation file
          
          * args: The dict mapping interpolation keys to interpolation
              values for the string-templates.
        '''
        self.header_template = string.Template(header_template)
        self.impl_template = string.Template(impl_template)
        self.args = args

    @trace
    def _generate(self, template, args):
        args.update(self.args)
        return template.substitute(**args)

    @trace
    def generate_header(self, args={}):
        '''Generate the header-template with args interpolated.

        Args:
          * args: Extra arguments to use in the interpolation. The
              args contained in the Template instance will be
              `updated` with `args`.

        Return: The header-template with args interpolated in.
        '''
        return self._generate(self.header_template, args)

    @trace
    def generate_impl(self, args={}):
        return self._generate(self.impl_template, args)

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
                    'parameters' : build_parameters(sig)})
        except KeyError:
            pass

        super(ElementTemplate, self).__init__(
            header_template,
            impl_template,
            args)
