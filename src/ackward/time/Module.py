import ackward

def definition():
    t = ackward.TranslationUnit(
        guard='INCLUDE_ACKWARD_TIME_MODULE_HPP')
    
    ns = ackward.Namespace('ackward', 'time')
    t += ns

    ns += ackward.Module(
        name='time')

    ns += ackward.function('float time()')

    return t
