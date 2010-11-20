def generate(ns, body):
    return ['namespace {0} {{'.format(n) for n in ns] + body + ['}' for n in ns]

