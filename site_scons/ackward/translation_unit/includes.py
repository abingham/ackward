import os.path

def _include(incl):
    return '#include <{0}>'.format(os.path.join(*incl))

def generate(incls):
    '''Generate the C++ include statements from a sequence of
    inclusion descriptions.

    This takes in a sequence of inclusion descriptions, and converts
    them into C++ include statements. Each entry in the sequence is a
    tuple like this::

      ('foo', 'bar', 'Baz.hpp')

    and is translated into an include statement like this::

      #include <foo/bar/Baz.hpp>

    Args:
      * incls: A sequence of include descriptions

    Returns:
      A string containing the generated C++ include statements.
    '''
    return [_include(incl) for incl in incls]
