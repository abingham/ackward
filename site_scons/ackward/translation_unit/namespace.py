def generate(ns, body):
    '''Generates a C++ namespace wrapped around another body of code.

    This takes in a namespace description and a body of code. This
    generates the C++ namespace statements around the supplied body of
    code. The namespace description is a sequence of strings (legal
    namespace names.) 

    Args:
      * ns: A sequence of legal namespace names.
      * body: A body of code (really, just a string.)

    Returns:
      A string with the namespaces described in `ns` wrapped around
      `body`.
    '''
    return ['namespace {0} {{'.format(n) for n in ns] + body + ['}' for n in ns]

