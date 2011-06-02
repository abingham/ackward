=======================
ackward::core::Property
=======================

``ackward::core::Property`` provides convenient access to Python
attributes with basic read/assign semantics. ``Property`` objects
*map* to an attribute on a Python object and allow you to assign-to
and read-from that attribute in a Python-esque manner in C++.

Example
=======

.. literalinclude:: ../../../../../examples/core/Property.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::core::Property
   :members:
