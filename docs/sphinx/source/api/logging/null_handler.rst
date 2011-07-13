===========
NullHandler
===========

``ackward::logging::NullHandler`` is a ``Handler_<T>`` subclass that
simply drops ``LogRecord``\ s on the floor. It is primarily just an
example.

Example
=======

.. literalinclude:: ../../../../../examples/logging/NullHandler.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::NullHandler
   :members:
