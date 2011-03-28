from ackward import (Class,
                     Constructor, 
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_FILTER_HPP',
        header_includes=[
            ('string',),
            ('ackward', 'core', 'Object.hpp'),
            ],
        impl_includes=[
            ('ackward', 'logging', 'Filter.hpp'),
            ('boost', 'python', 'import.hpp'),
            ])

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 'logging'):
            with Class(name='Filter', 
                       wrapped_class='logging.Filter'):
                Constructor()
                Constructor(
                    signature=[('std::wstring', 'name')])
    return t
