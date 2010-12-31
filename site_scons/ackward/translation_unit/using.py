def generate(usings):
    '''Generate a series of "using" statements from a sequence of
    strings.

    Args:
      * usings: A sequence of strings, each of which will be
          translated into a "using" statement.
        
    Returns:
      A string with a using statement for each element of `usings`.
    '''
    return '\n'.join(['using {0};'.format(u) for u in usings])
        
