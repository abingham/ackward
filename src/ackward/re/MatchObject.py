from ackward import (Class,
                     method,
                     Namespace,
                     TranslationUnit)

def tunit():
    return TranslationUnit(
        guard='INCLUDE_ACKWARD_RE_MATCH_OBJECT_HPP',
        header_includes=[('string',)],
        impl_includes=[('ackward', 're', 'MatchObject.hpp')])

def definition():
    with tunit() as t:
        with Namespace('ackward', 're'):
            with Class(name='MatchObject',
                       wrapped_class='_sre.SRE_Match'):
                
                method('std::wstring expand(std::wstring tmpl) const')

# MatchObject.group([group1, ...])

#     Returns one or more subgroups of the match. If there is a single argument, the result is a single string; if there are multiple arguments, the result is a tuple with one item per argument. Without arguments, group1 defaults to zero (the whole match is returned). If a groupN argument is zero, the corresponding return value is the entire matching string; if it is in the inclusive range [1..99], it is the string matching the corresponding parenthesized group. If a group number is negative or larger than the number of groups defined in the pattern, an IndexError exception is raised. If a group is contained in a part of the pattern that did not match, the corresponding result is None. If a group is contained in a part of the pattern that matched multiple times, the last match is returned.

#     >>> m = re.match(r"(\w+) (\w+)", "Isaac Newton, physicist")
#     >>> m.group(0)       # The entire match
#     'Isaac Newton'
#     >>> m.group(1)       # The first parenthesized subgroup.
#     'Isaac'
#     >>> m.group(2)       # The second parenthesized subgroup.
#     'Newton'
#     >>> m.group(1, 2)    # Multiple arguments give us a tuple.
#     ('Isaac', 'Newton')

#     If the regular expression uses the (?P<name>...) syntax, the groupN arguments may also be strings identifying groups by their group name. If a string argument is not used as a group name in the pattern, an IndexError exception is raised.

#     A moderately complicated example:

#     >>> m = re.match(r"(?P<first_name>\w+) (?P<last_name>\w+)", "Malcolm Reynolds")
#     >>> m.group('first_name')
#     'Malcolm'
#     >>> m.group('last_name')
#     'Reynolds'

#     Named groups can also be referred to by their index:

#     >>> m.group(1)
#     'Malcolm'
#     >>> m.group(2)
#     'Reynolds'

#     If a group matches multiple times, only the last match is accessible:

#     >>> m = re.match(r"(..)+", "a1b2c3")  # Matches 3 times.
#     >>> m.group(1)                        # Returns only the last match.
#     'c3'

# MatchObject.groups([default])

#     Return a tuple containing all the subgroups of the match, from 1 up to however many groups are in the pattern. The default argument is used for groups that did not participate in the match; it defaults to None.

#     For example:

#     >>> m = re.match(r"(\d+)\.(\d+)", "24.1632")
#     >>> m.groups()
#     ('24', '1632')

#     If we make the decimal place and everything after it optional, not all groups might participate in the match. These groups will default to None unless the default argument is given:

#     >>> m = re.match(r"(\d+)\.?(\d+)?", "24")
#     >>> m.groups()      # Second group defaults to None.
#     ('24', None)
#     >>> m.groups('0')   # Now, the second group defaults to '0'.
#     ('24', '0')

# MatchObject.groupdict([default])

#     Return a dictionary containing all the named subgroups of the match, keyed by the subgroup name. The default argument is used for groups that did not participate in the match; it defaults to None. For example:

#     >>> m = re.match(r"(?P<first_name>\w+) (?P<last_name>\w+)", "Malcolm Reynolds")
#     >>> m.groupdict()
#     {'first_name': 'Malcolm', 'last_name': 'Reynolds'}

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
