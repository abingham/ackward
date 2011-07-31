=============
 UserHandler
=============

``ackward::logging::UserHandler`` allows you to define new ``Handler``
types in C++. To use ``UserHandler``, you first define a type with an
``emit()`` method. You then define a new ``UserHandler``
template-instantiation using this type. When the ``UserHandler``\ 's
``emit()`` is called, the ``LogRecord`` will be forwarded to the the
``emit()`` defined in type you defined earlier.

Example
=======

.. literalinclude:: ../../../../../examples/logging/UserHandler.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::UserHandler
   :members:
