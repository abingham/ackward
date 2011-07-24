======================
Module-level Functions
======================

There are a number of module-level functions in
``ackward::logging``. Many of these are simply operations on the root
logger.

Example
=======

.. literalinclude:: ../../../../../examples/logging/Module.cpp
   :language: c++
   :linenos:

API
===

.. doxygenfunction:: ackward::logging::getLogger
.. doxygenfunction:: ackward::logging::getLoggerClass
.. doxygenfunction:: ackward::logging::log
.. doxygenfunction:: ackward::logging::disable
.. doxygenfunction:: ackward::logging::addLevelName
.. doxygenfunction:: ackward::logging::getLevelName
.. doxygenfunction:: ackward::logging::basicConfig
.. doxygenfunction:: ackward::logging::shutdown
.. doxygenfunction:: ackward::logging::setLoggerClass
.. doxygenfunction:: ackward::logging::exception

.. doxygenfunction:: ackward::logging::DEBUG
.. doxygenfunction:: ackward::logging::INFO
.. doxygenfunction:: ackward::logging::WARNING
.. doxygenfunction:: ackward::logging::ERROR
.. doxygenfunction:: ackward::logging::CRITICAL
