import re
from .util import trace

@trace
def build_signature(sig, header):
    '''Builds a method parameter signature given an akw signature

    The `sig` parameter specifies the types, names, and (optionally)
    default values for the signature of a C++ method. This method
    converts that into a string that can be used in C++ code for the
    method signature.

    Args:
      sig: A sequence of signature tuples (type, name[, default])
      header: Whether to generate for a header or not. This
        determines, for example, if default values are included in the
        output.
        
    Returns:
      A string containing the method signature described by `sig`.

    Raises:
      ValueError: The signature input was invalid.
    '''
    def arg(a):
        if len(a) == 3 and header:
            return 'boost::call_traits<%s>::const_reference %s = %s' % (a[0], a[1], a[2])
        elif len(a) == 2 or len(a) == 3:
            return 'boost::call_traits<%s>::const_reference %s' % (a[0], a[1])
        else:
            raise ValueError('Signatures must be of the form (type, name[, default])')

    return ',\n'.join([arg(a) for a in sig])

sig_regex = re.compile('^(.*)\s(\S+)\((.*)\)(\s+const)?$')

@trace
def parse(sig):
    '''Parse a (pseudo-)C++ method signature and return the
    components.

    `sig` should be a C++ method declaration of the form:

      return-type name(arg-type1 arg-name1[=default-value1], . . .) [const]

    This method will parse that string and return a tuple of the form:

      (return-type, name, args, const)

    where `args` is a sequence of tuples where each tuple of of the form:

      (type, name [, default-value])

    and the rest of the elements are simply strings. Note that since
    the `const` part of the signature is optional, it may be an empty
    string.

    This method doesn't so any real error checking; it is assumed that
    you will only make "correct" calls to it. As such, it might fail
    in subtle, mysterious, or even spectacular ways on bad input. It
    might not even "fail" on some bad input.
    '''

    (rtype, name, args, const) = (sig_regex.match(sig).groups())
    
    # Split the args on commas
    args = args.split(',') if args else []

    # split out default arguments: "int x=0" -> ["int x", "0"]; "int x" -> ["int x"]
    args = [a.split('=') for a in args]

    # Create separate lists of default-values and of args
    defaults = [a[1] for a in args if len(a) == 2]
    args = [a[0] for a in args]

    # Split each arg into type ane name
    args = [tuple(a.split()) for a in args]
    
    # combine multi-word types, e.g. (unsigned, int, x) -> (unsigned int, x)
    args = [(' '.join(a[:-1]), a[-1]) for a in args]

    # apply the defaults...append each default value to the arg spec
    # in `args` to which it corresponds.
    for i in range(len(defaults)):
        idx = len(args) - len(defaults) + i 
        args[idx] = list(args[idx]) + [defaults[i]]

    return (rtype, name, args, const)
