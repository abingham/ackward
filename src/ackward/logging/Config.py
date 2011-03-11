import functools, operator

from ackward import (function,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_CONFIG_HPP',
        forward_declarations=[('boost', 'python', 'class dict')],
        header_includes=[('string',)],
        impl_includes=[
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('ackward', 'core', 'Exceptions.hpp'),
            ('ackward', 'logging', 'Module.hpp'),
            ])

def functions():
    f = [ 
        'void fileConfig(std::wstring filename)',
        'void fileConfig(std::string filename, boost::python::dict defaults)',
        'void listen()',
        'void listen(unsigned int port)',
        'void stopListening()',
        ]

    list(map(function, f))

def definition():
    with tunit() as t:
        with  Namespace('ackward', 'logging'):
            functions()
    return t
