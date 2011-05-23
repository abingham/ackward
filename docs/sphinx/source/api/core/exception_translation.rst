========================
ExceptionTranslation.hpp
========================

The ``ExceptionTranslation`` module provides a small system for
translating Python exceptions into C++ exceptions using the
``ExceptionTranslator`` class. Essentially, ``ExceptionTranslation``
is a convenience layer over ``ExceptionTranslator``. It provides a
singleton ``ExceptionTranslator`` instance, a simplified translation
registration mechanism, and some methods for performing translation
using the singleton. It also include the
``TRANSLATE_PYTHON_EXCEPTION`` macro which implements the most common
usage pattern in the module.

Example
=======

.. literalinclude:: ../../../../../examples/core/ExceptionTranslation.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfile:: ackward/core/ExceptionTranslation.hpp
