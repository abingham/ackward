from ackward.translation_unit import TranslationUnit
from ackward.elements import function, Module

class REModule(TranslationUnit):
    def __init__(self):
        objs = [
            Module(name='re'),
            # function('RegexObject compile(boost::python::str pattern, unsigned char flags=0x00)'),
            # function('MatchObject search(boost::python::str pattern, boost::python::str string, unsigned char flags=0x00)'),
            # function('MatchObject match(boost::python::str pattern, boost::python::str string, unsigned char flags=0x00)'),
            # function('std::vector<boost::python::str> split(boost::python::str pattern, boost::python::str string, short maxsplit=0')
            ]

        super(REModule, self).__init__(
            header_includes=[
                ('boost', 'python', 'str.hpp'),
                # ('ackward', 're', 'RegexObject.hpp')
                ]
            objects={ ('ackward', 're') : objs })

def definition():
    return REModule()
