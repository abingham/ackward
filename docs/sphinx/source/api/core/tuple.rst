====================
ackward::core::Tuple
====================

The tuple module provides facilities for converting between
``boost::tuple<>`` objects and Python tuples. The ``convertTuple``
functions provide explicit conversion between these types: they
directly convert between the two. The ``TupleConverter`` class
provides a means to register type-converters with ``boost.python`` so
that implicit, automatic conversion can happen.

Examples
========

This first example shows how to use the ``convertTuple`` methods to
explicitly convert between Python tuples and ``boost::tuple``.

.. literalinclude:: ../../../../../examples/core/TupleExplicit.cpp
   :language: c++
   :linenos:

This second example show how to use ``TupleConverter`` to enable
automatic conversion between Python and C++ tuples.

.. literalinclude:: ../../../../../examples/core/TupleImplicit.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfile:: ackward/core/Tuple.hpp
