from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_HANDLERS_MODULE_HPP')

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 'logging', 'handlers', parent=t)
    m = Module(name='logging.handlers', parent=ns)
    return t
