import ackward

def tunit():
    return ackward.TranslationUnit(
        guard='INCLUDE_ACKWARD_TIME_MODULE_HPP')

def definition():
    with tunit() as t:
        with ackward.Namespace('ackward', 'time'):

            ackward.Module(
                name='time')

            ackward.function('float time()')

    return t
