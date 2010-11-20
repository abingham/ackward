def generate(mod, guard, contents):
    if not guard:
        guard = 'INCLUDE_{0}'.format(mod.__file__.replace(os.path.sep, '_').upper())        
        
    rval = ['#ifndef {0}'.format(guard),
            '#define {0}'.format(guard),]
    rval.extend(contents)
    rval.append('#endif')

    return rval
