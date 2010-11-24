import os

def generate(mod, guard, contents):
    if not guard:
        mod_name = mod.__file__.replace(os.path.sep, '_')
        mod_name = mod_name.replace('.', '_')
        guard = 'INCLUDE_{0}'.format(mod_name.upper())        
        
    rval = ['#ifndef {0}'.format(guard),
            '#define {0}'.format(guard),]
    rval.extend(contents)
    rval.append('#endif')

    return rval
