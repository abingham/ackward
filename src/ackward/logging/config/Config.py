import functools, operator

from ackward import (function,
                     Namespace,
                     TranslationUnit)

fileConfig1_doc = '''
/** Read the logging configuration from a ConfigParser-format file.
    
    This can be called several times from an application, allowing an end user
    the ability to select from various pre-canned configurations (if the
    developer provides a mechanism to present the choices and load the chosen
    configuration).

    This disables existing loggers which are not named in the logging
    configuration.

    @param filename The filename to read from. */'''

fileConfig2_doc = '''
/** Read the logging configuration from a ConfigParser-format file.
    
    This can be called several times from an application, allowing an end user
    the ability to select from various pre-canned configurations (if the
    developer provides a mechanism to present the choices and load the chosen
    configuration).

    This disables existing loggers which are not named in the logging
    configuration.

    @param filename The filename to read from. 
    @param defaults Defaults to be passed to the ConfigParser. */'''

listen1_doc = '' # TODO
listen2_doc = '' # TODO
stopListening_doc = '' # TODO

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_CONFIG_CONFIG_HPP',
        forward_declarations=[('boost', 'python', 'class dict')],
        header_includes=[('string',)],
        impl_includes=[
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('ackward', 'core', 'Exceptions.hpp'),
            ('ackward', 'logging', 'config', 'Module.hpp'),
            ])

def functions():
    funcs = [ 
        (fileConfig1_doc,
         'void fileConfig(std::wstring filename)'),
        (fileConfig2_doc, 
         'void fileConfig(std::wstring filename, boost::python::dict defaults)'),
        (listen1_doc, 
         'void listen()'),
        (listen2_doc, 
         'void listen(unsigned int port)'),
        (stopListening_doc, 
         'void stopListening()'),
        ]

    for d,f in funcs:
        func = function(f)
        if d: func.doc = d

def definition(env):
    with tunit() as t:
        with  Namespace('ackward', 'logging', 'config'):
            functions()
    return t
