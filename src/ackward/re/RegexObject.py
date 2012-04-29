from ackward import (Class,
                     method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_RE_REGEX_OBJECT_HPP',
        forward_declarations=[('ackward', 're', 'class MatchObject')],
        header_includes=[('string',)],
        impl_includes=[('ackward', 're', 'RegexObject.hpp'),
                       ('ackward', 're', 'MatchObject.hpp')])

def definition(env):
    t = tunit()
    ns = Namespace('ackward', 're', parent=t)
    cls =  Class(name='RegexObject',
                 wrapped_class='_sre.SRE_Pattern',
                 parent=ns)

    method('MatchObject match(std::wstring s) const',
           parent=cls)
    method('MatchObject match(std::wstring s, int pos)',
           parent=cls)
    method('MatchObject match(std::wstring s, int pos, int endpos)',
           parent=cls)

    method('MatchObject search(std::wstring s) const',
           parent=cls)
    method('MatchObject search(std::wstring s, int pos)',
           parent=cls)
    method('MatchObject search(std::wstring s, int pos, int endpos)',
           parent=cls)

    method('boost::python::list split(std::wstring s) const',
           parent=cls)
    method('boost::python::list split(std::wstring s, int maxsplit) const',
           parent=cls)

# RegexObject.findall(string[, pos[, endpos]])
#     Identical to the findall() function, using the compiled pattern.

# RegexObject.finditer(string[, pos[, endpos]])
#     Identical to the finditer() function, using the compiled pattern.

# RegexObject.sub(repl, string[, count=0])
#     Identical to the sub() function, using the compiled pattern.

# RegexObject.subn(repl, string[, count=0])
#     Identical to the subn() function, using the compiled pattern.

# RegexObject.flags
#     The flags argument used when the RE object was compiled, or 0 if no flags were provided.

# RegexObject.groups
#     The number of capturing groups in the pattern.

# RegexObject.groupindex
#     A dictionary mapping any symbolic group names defined by (?P<id>) to group numbers. The dictionary is empty if no symbolic groups were used in the pattern.

# RegexObject.pattern
#     The pattern string from which the RE object was compiled.

    return t
