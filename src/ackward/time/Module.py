from ackward import (function, 
                     Module, 
                     Namespace, 
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_TIME_MODULE_HPP')

def definition():
    with tunit() as t:
        with Namespace('ackward', 'time'):
            Module(name='time')
            function('float time()')

    return t
