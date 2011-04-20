#ifndef INCLUDE_ACKWARD_RE_FLAGS_HPP
#define INCLUDE_ACKWARD_RE_FLAGS_HPP

#include <ackward/core/PythonVersion.hpp>

namespace ackward {
namespace re {

enum Flags {
    // Perform case-insensitive matching; expressions like [A-Z] will
    // match lowercase letters, too. This is not affected by the
    // current locale.
    I = 0x02,
    IGNORECASE = 0x02,

    // Make \w, \W, \b, \B, \s and \S dependent on the current locale.
    L = 0x04
    LOCALE = 0x04, 
   
    // When specified, the pattern character '^' matches at the
    // beginning of the string and at the beginning of each line
    // (immediately following each newline); and the pattern character
    // '$' matches at the end of the string and at the end of each
    // line (immediately preceding each newline). By default, '^'
    // matches only at the beginning of the string, and '$' only at
    // the end of the string and immediately before the newline (if
    // any) at the end of the string.
    M = 0x08
    MULTILINE = 0x08,
    
    // Make the '.' special character match any character at all,
    // including a newline; without this flag, '.' will match anything
    // except a newline.
    S = 0x10,
    DOTALL = 010,
    
    // Make \w, \W, \b, \B, \d, \D, \s and \S dependent on the Unicode
    // character properties database.
    U = 0x20
    UNICODE = 0x20,

    X = 0x40,
    VERBOSE = 0x40

#if ACKWARD_PYTHON_MAJOR_VERSION == 3
    ,
    A = 0x100,
    ASCII = 0x100
#endif
};

#endif
