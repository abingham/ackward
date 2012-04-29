from ackward import (function,
                     Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        )

def definition(env):
    t = TranslationUnit(
        guard='INCLUDE_ACKWARD_TIME_MODULE_HPP')
    n = Namespace('ackward', 'time', parent=t)
    Module(name='time', parent=n)
    function('float time()', parent=n)

    return t
