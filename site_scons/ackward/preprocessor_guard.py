def generate(mod, contents):
    try:
        guard = mod.preprocessor_guard()
    except AttributeError:
        guard = 'INCLUDE_{0}'.format(mod.__file__.replace(os.path.sep, '_').upper())
        
    rval = ['#ifndef {0}'.format(guard),
            '#define {0}'.format(guard),]
    rval.extend(contents)
    rval.append('#endif')
    return rval
