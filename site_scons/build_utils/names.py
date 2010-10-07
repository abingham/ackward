def configure_variant_suffixes(env):
    suff = '.%s' % env['VARIANT']
    env['SHLIBSUFFIX'] = '-%s' % env['VARIANT'] + env['SHLIBSUFFIX']
    env['SHOBJSUFFIX'] = suff + env['SHOBJSUFFIX']

def libname(base):
    return 'ackward_%s' % base

def liblinkname(env, base):
    return 'ackward_%s-%s' % (base, env['VARIANT'])
