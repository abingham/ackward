import functools, operator

from ackward import (function,
                     Namespace,
                     TranslationUnit)

def definition():
    t = TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_CONFIG_HPP',
        forward_declarations=[('boost', 'python', 'class dict')],
        header_includes=[('string',)],
        impl_includes=[
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('ackward', 'core', 'Exceptions.hpp'),
            ('ackward', 'logging', 'Module.hpp'),
            ])

    ns = Namespace('ackward', 'logging')
    t += ns

    functions = [
            'void fileConfig(std::wstring filename)',
            'void fileConfig(std::string filename, boost::python::dict defaults)',
            'void listen()',
            'void listen(unsigned int port)'
            'void stopListening()',
            ]

    list(map(functools.partial(operator.iadd, ns), [function(f) for f in functions]))

    return t
