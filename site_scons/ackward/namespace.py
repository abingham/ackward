def wrap(ns, body):
    if not ns:
        return body
    else:
        return 'namespace {0} {{\n{1}\n}}'.format(ns[0], wrap(ns[1:], body))

def generate(mod, body):
    try:
        ns = mod.namespace()
        return wrap(ns, body)
    except AttributeError:
        return body
