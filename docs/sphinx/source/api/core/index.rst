=============
ackward::core
=============

The ``ackward::core`` namespace contains functions, classes, and such
that are used generally throughout the rest of the ``ackward`` API. In
general, the elements of ``core`` don't pertain to a particular Python module.

Main constructs
===============

.. toctree::
   :maxdepth: 1

   ByteArray <bytearray>
   Bytes <bytes>
   Enum <enum>
   Exceptions <exceptions>
   ExceptionTranslation <exception_translation>
   ExceptionTranslator <exception_translator>
   Object <object>
   Property <property>
   Tuple <tuple>
   Utilities <util>

Eveything else
==============

.. doxygenfunction:: ackward::core::getClass
.. doxygenfile:: ackward/core/Import.hpp
.. doxygenfunction:: ackward::core::initialize()
.. doxygenfunction:: ackward::core::initializePythonConverter
.. doxygenfile:: ackward/core/PythonVersion.hpp
