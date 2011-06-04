========================================
ackward::core::initializePythonConverter
========================================

The ``initializePythonConverter()`` family of functions allow you to
easily register to- and from-python converters for
``ackward::core::Object`` subclasses. Essentially, they take care of
the ``boost.python`` type registration details, and they associate a
given Python class-name with a particular C++ type.

Example
=======

.. literalinclude:: ../../../../../examples/core/PythonConverter.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfunction:: ackward::core::initializePythonConverter

.. doxygenfunction:: ackward::core::initializeFromPythonConverter

.. doxygenfunction:: ackward::core::initializeToPythonConverter
