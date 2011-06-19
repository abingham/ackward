from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_CONFIG_MODULE_HPP')

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging', 'config'):
            with Module(name='logging.config'):
                pass
    return t
