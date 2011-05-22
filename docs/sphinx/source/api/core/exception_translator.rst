=================================
ackward::core ExceptionTranslator
=================================

``ExceptionTranslator`` maintains a mapping between Python exception
classes and *actions* to take when those exceptions are detected. An
``ExceptionTranslator`` only does translation when its ``translate()``
method is called, at which point it compares the arguments to that
method with the Python exceptions in its mapping. At the first match,
it performs the specified action for that mapping.

Example
=======

.. literalinclude:: ../../../../../examples/core/ExceptionTranslator.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfile:: ackward/core/ExceptionTranslator.hpp
