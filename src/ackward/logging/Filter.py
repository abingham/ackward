from ackward import Constructor, TranslationUnit

def definition():
    t = TranslationUnit(
        guard='INCLUDE_ACKWARD_LOGGING_FILTER_HPP',
        header_includes=[
            ('string',),
            ('ackward', 'core', 'Object.hpp'),
            ],
        impl_includes=[
            ('ackward', 'logging', 'Filter.hpp'),
            ('boost', 'python', 'import.hpp'),
            ])

    t += Constructor()
    t += Constructor(
        signature=[('std::wstring', 'name')])

    return t
