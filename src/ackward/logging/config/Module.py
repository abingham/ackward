from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_CONFIG_MODULE_HPP')

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'logging', 'config', parent=t)
    m = Module(name='logging.config', parent=ns)
    return t
