import decorator, logging

@decorator.decorator
def trace(f, *args, **kw):
    '''A simple tracing decorator, mostly to help with debugging.
    '''
    logging.debug("calling %s with args %s, %s" % (f.__name__, args, kw))
    return f(*args, **kw)
