====================
 WatchedFileHandler
====================

``ackward::logging::handlers::WatchedFileHandler`` wraps Python's
standard `logging.handlers.WatchedFileHandler
<http://docs.python.org/py3k/library/logging.handlers.html#watchedfilehandler>`_
class, sending logging a file which is reopened if it is modified.

Example
=======

.. literalinclude:: ../../../../../examples/logging/WatchedFileHandler.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::handlers::WatchedFileHandler
   :members:
