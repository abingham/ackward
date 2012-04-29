from .element import TemplateElement
from .trace import trace


class Include(TemplateElement):
    '''An include file in an implementation file.

    Args:
      filepath: The path components of the file to include.
    '''

    @trace
    def __init__(self,
                 phase,
                 filepath):
        TemplateElement.__init__(
            self,
            open_templates={
                phase: '#include <$header_file>',
            },
            symbols={
                'header_file': '/'.join(filepath),
            })

def ImplInclude(filepath):
    return Include('impl_include', filepath)

def HeaderInclude(filepath):
    return Include('header_include', filepath)