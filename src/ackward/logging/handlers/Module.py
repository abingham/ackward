from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_HANDLERS_MODULE_HPP')

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging', 'handlers'):
            with Module(name='logging.handlers'):
                pass
    return t
