===============
 StreamHandler
===============

``ackward::logging::handlers::StreamHandler`` wraps Python's standard
`logging.handlers.StreamHandler
<http://docs.python.org/py3k/library/logging.handlers.html#logging.StreamHandler>`_
class, sending logging output to stream of some sort.

Example
=======

.. literalinclude:: ../../../../../examples/logging/StreamHandler.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::handlers::StreamHandler
   :members:
