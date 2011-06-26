from ackward import (Class,
                     Constructor, 
                     Namespace,
                     TranslationUnit)

filter_doc='''/**
\\rst

A wrapper around Python `logging.Filter
<http://docs.python.org/py3k/library/logging.html#filter-objects>`_
objects. 

\\endrst
*/
'''

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
                       wrapped_class='logging.Filter',
                       doc=filter_doc):
                Constructor(
                    doc='/** Create a new Filter. */')
                # Constructor(
                #     signature=[('std::wstring', 'name')])
    return t
