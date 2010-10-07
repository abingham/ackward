def configure_variant_suffixes(env):
    suff = '.%s' % env['VARIANT']
    env['SHLIBSUFFIX'] = '-%s' % env['VARIANT'] + env['SHLIBSUFFIX']
    env['SHOBJSUFFIX'] = suff + env['SHOBJSUFFIX']
