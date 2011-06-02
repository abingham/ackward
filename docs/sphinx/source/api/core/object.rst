=====================
ackward::core::Object
=====================

``ackward::core::Object`` is a base-class for classes that wrap an
underlying Python object. The ``Object`` API is very small, and is
designed to provide just a simple platform for the ``ackward``
code-generation system.

Example
=======

.. literalinclude:: ../../../../../examples/core/Object.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::core::Object
   :members:

.. doxygendefine:: ACKWARD_ATTR

.. doxygendefine:: ACKWARD_METHOD
