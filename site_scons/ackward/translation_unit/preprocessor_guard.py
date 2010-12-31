import os

def generate(mod, guard, contents):
    '''Wraps an include-guard around a body of code.

    Args:
      * mod: The module containing the translation unit for the
          `contents`.
      * guard: The include guard string to use for the translation
          unit. If guard evaluate to False, a guard string is
          generated based on `mod`.
      * contents: The body of code around which to wrap the guard.

    Returns:
      A string containing the preprocessor guard wrapped around
      `contents`.
    '''
    if not guard:
        mod_name = mod.__file__.replace(os.path.sep, '_')
        mod_name = mod_name.replace('.', '_')
        guard = 'INCLUDE_{0}'.format(mod_name.upper())        
        
    rval = ['#ifndef {0}'.format(guard),
            '#define {0}'.format(guard),]
    rval.extend(contents)
    rval.append('#endif')

    return rval
