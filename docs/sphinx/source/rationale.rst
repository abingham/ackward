=========
Rationale
=========

One of Python's strengths is that it can interface easily with other
languages. In particular, it's good at interoperating with
C/C++. However, the idioms and styles needed for dealing with Python
objects in C++ are generally very different from what you would use in
Python itself. In other words, while you *can* work with Python objects
in C++, you lose a lot of the elegance and simplicity associated with
Python.

The Boost.Python library takes great strides in making it more natural
to work with Python objects in C++. Defining Python classes and
modules with Boost.Python feels much more like Python than standard
use of the Python C API, and this is a huge benefit. Developers using
Boost.Python are able to approach problems in a more consistent
manner, and they don't have to "switch gears" as much.

Nevertheless, Boost.Python is only one step in the right direction. It
provides a platform upon which a much richer, more "natural"
integration between Python and C++ can be built, and this is where
ackward tries to extend things even further. ackward aims to provide
simple, idiomatic access to the Python standard library in C++.

By doing this, ackward gives Python extension writers the ability to
work with many common Python objects in their C++ code. Likewise, it
gives them access to the wealth of functionality in the standard
library. This should help foster consistency across code bases and
reduce repetition. It should also help spread the effective domain of
the well-tested, robust, and well-known Python standard library.

It's worth noting that ackward helps embedded Python developers as
much as extension writers. In fact, ackward grew much more out of
embedded work than extensions; it's genesis was an attempt to expose
the Python logging library in C++.

The goal of exposing the entire Python standard library is indeed
lofty. Pragmatically, the project will need to simply tackle
manageable pieces one at a time. In general, it should be possible to
develop independent pieces of the standard library in parallel, so the
project scope should be able to scale with the amount of help it can
get. Ultimately, the direction and scope of ackward will depend on the
number of people who work on it and their interests.
