import string

from ..util import trace

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



