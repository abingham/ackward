def declare(decl):
    if len(decl) == 0:
        return str()

    elif len(decl) == 1:
        return '{0};'.format(decl[0])

    else:
        return 'namespace {0} {{ {1} }}'.format(decl[0],
                                                declare(decl[1:]))

def generate(decls):
    return [declare(decl) for decl in decls]
