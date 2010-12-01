from ackward.translation_unit import TranslationUnit
from ackward.elements import function, Module

class TimeModule(TranslationUnit):
    def __init__(self):
        objs=[
            Module(name='time'),
            function('float time()')
            ]

        super(TimeModule, self).__init__(
            preprocessor_guard='INCLUDE_ACKWARD_TIME_MODULE_HPP',
            objects={ ('ackward', 'time') : objs })

def definition():
    return TimeModule()
