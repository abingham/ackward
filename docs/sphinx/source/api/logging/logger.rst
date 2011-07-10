======
Logger
======

``ackward::logging::Logger`` wraps a Python `logging.Logger
<http://docs.python.org/py3k/library/logging.html#logger-objects>`_
object.

.. note::

   ``Logger`` is privately derived from
   ``ackward::logging::LoggerBase`` and promotes most of
   ``LoggerBase``\ 's members into itself. The documentation for
   ``LoggerBase`` is included below, but it should fundamentally be
   considered an implementation detail of ``Logger``.

Example
=======
.. literalinclude:: ../../../../../examples/logging/Logger.cpp
   :language: c++
   :linenos:

API
===

.. doxygenclass:: ackward::logging::Logger
   :members:

.. doxygenclass:: ackward::logging::LoggerBase
   :members:
