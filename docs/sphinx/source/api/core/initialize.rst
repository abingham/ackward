===========================
ackward::core::initialize()
===========================

``initialize()`` sets up the infrastructure used by ``ackward::core``
(and, thus, by many of the other ``ackward`` modules). This includes
things like to-/from-python type translation and exception-translation
registrations.

In general, you should always call ``ackward::core::initialize()``
before using any other part of ``ackward``, but after initializing
Python. Note that the ``initialize()`` calls of the various other
``ackward`` libraries call ``ackward::core::initialize()`` for you, so
you don't always have to call it directly.

Example
=======

.. literalinclude:: ../../../../../examples/core/Initialize.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfunction:: ackward::core::initialize
