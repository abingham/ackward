def build_shared_library(env, name, sources):
    lib = env.SharedLibrary('ackward_%s' % name, sources)
    env['products']['ackward_%s' % name] = lib
    env.Alias('all', lib)
