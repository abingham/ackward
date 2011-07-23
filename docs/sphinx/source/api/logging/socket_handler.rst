===============
 SocketHandler
===============

``ackward::logging::handlers::SocketHandler`` wraps Python's standard
`logging.handlers.SocketHandler <http://docs.python.org/py3k/library/logging.handlers.html#sockethandler>`_ class, sending logging output to a
network socket.

Example
=======

.. literalinclude:: ../../../../../examples/logging/SocketHandler.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::handlers::SocketHandler
   :members:
