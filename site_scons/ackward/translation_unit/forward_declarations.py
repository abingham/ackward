def _declare(decl):
    '''Generate a single forward declaration statement.
    '''
    if len(decl) == 0:
        return str()

    elif len(decl) == 1:
        return '{0};'.format(decl[0])

    else:
        return 'namespace {0} {{ {1} }}'.format(decl[0],
                                                _declare(decl[1:]))

def generate(decls):
    '''Generate a series of forward declarations.

    Given a sequence of tuples, this returns a string with the corresponding C++ forward declarations. For example, the input::

      [('A', 'B', 'struct C'), ('foo', 'bar', 'class Baz')]

    would produce::

      namespace A { namespace B { struct C; } }
      namespace foo { namespace bar { class Bas; } }

    Args:
      * decls: The sequence of forward declaration descriptions

    Returns:
      A string containing the corresponsing C++ forward declarations.
    '''
    return [_declare(decl) for decl in decls]
