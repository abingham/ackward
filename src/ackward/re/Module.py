from ackward import (Module,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_RE_MODULE_HPP')

def definition():
    with tunit() as t:
        with Namespace('ackward', 're'):
            Module(name='re')

        # objs = [
        #     Module(name='re'),
        #     # function('RegexObject compile(boost::python::str pattern, unsigned char flags=0x00)'),
        #     # function('MatchObject search(boost::python::str pattern, boost::python::str string, unsigned char flags=0x00)'),
        #     # function('MatchObject match(boost::python::str pattern, boost::python::str string, unsigned char flags=0x00)'),
        #     # function('std::vector<boost::python::str> split(boost::python::str pattern, boost::python::str string, short maxsplit=0')
        #     ]

        # super(REModule, self).__init__(
        #     header_includes=[
        #         ('boost', 'python', 'str.hpp'),
        #         # ('ackward', 're', 'RegexObject.hpp')
        #         ]
        #     objects={ ('ackward', 're') : objs })

    return t
