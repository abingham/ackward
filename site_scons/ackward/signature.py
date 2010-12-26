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
