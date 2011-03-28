from ackward import (Class,
                     method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_RE_MATCH_OBJECT_HPP',
        header_includes=[('string',),
                         ('boost', 'python', 'dict.hpp'),
                         ('boost', 'python', 'tuple.hpp'),
                         ('boost', 'python', 'object.hpp')],
        impl_includes=[('ackward', 're', 'MatchObject.hpp')])

def definition(env):
    with tunit() as t:
        with Namespace('ackward', 're'):
            with Class(name='MatchObject',
                       wrapped_class='_sre.SRE_Match'):
                
                method('std::wstring expand(std::wstring tmpl) const')

                # TODO
                # MatchObject.group([group1, ...])

                method('boost::python::tuple groups() const')
                method('boost::python::tuple groups(boost::python::object dflt) const')

                method('boost::python::dict groupdict() const')
                method('boost::python::dict groupdict(boost::python::object dflt) const')

                # MatchObject.start([group])
                # MatchObject.end([group])

#     Return the indices of the start and end of the substring matched by group; group defaults to zero (meaning the whole matched substring). Return -1 if group exists but did not contribute to the match. For a match object m, and a group g that did contribute to the match, the substring matched by group g (equivalent to m.group(g)) is

#     m.string[m.start(g):m.end(g)]

#     Note that m.start(group) will equal m.end(group) if group matched a null string. For example, after m = re.search('b(c?)', 'cba'), m.start(0) is 1, m.end(0) is 2, m.start(1) and m.end(1) are both 2, and m.start(2) raises an IndexError exception.

#     An example that will remove remove_this from email addresses:

#     >>> email = "tony@tiremove_thisger.net"
#     >>> m = re.search("remove_this", email)
#     >>> email[:m.start()] + email[m.end():]
#     'tony@tiger.net'

# MatchObject.span([group])
#     For MatchObject m, return the 2-tuple (m.start(group), m.end(group)). Note that if group did not contribute to the match, this is (-1, -1). group defaults to zero, the entire match.

# MatchObject.pos
#     The value of pos which was passed to the search() or match() method of the RegexObject. This is the index into the string at which the RE engine started looking for a match.

# MatchObject.endpos
#     The value of endpos which was passed to the search() or match() method of the RegexObject. This is the index into the string beyond which the RE engine will not go.

# MatchObject.lastindex
#     The integer index of the last matched capturing group, or None if no group was matched at all. For example, the expressions (a)b, ((a)(b)), and ((ab)) will have lastindex == 1 if applied to the string 'ab', while the expression (a)(b) will have lastindex == 2, if applied to the same string.

# MatchObject.lastgroup
#     The name of the last matched capturing group, or None if the group didnt have a name, or if no group was matched at all.

# MatchObject.re
#     The regular expression object whose match() or search() method produced this MatchObject instance.

# MatchObject.string
#     The string passed to match() or search().

    return t
