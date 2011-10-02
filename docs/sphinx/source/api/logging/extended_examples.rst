Extended Logging Examples
=========================

These examples show some typical "real life" use of the
``ackward::logging`` API.

Embedded
--------

This example shows typical use of ackward::logging embedded in a C++
program.

.. literalinclude:: ../../../../../examples/logging/embed/log_example.cpp
   :language: c++
   :linenos:

This is what's going on:

 #. Include the header that gives us the ``basicConfig()`` method.
 #. Include the header for initializing the library. You must call
    ``ackward::logging::initialize()`` before using any other parts of the
    library.
 #. Include the header for the ``Logger`` class.
 #. Include the header with module-level functions.
 #. Make sure ``Py_Initialize()`` is called before using ``ackward``.
 #. Initialize ``ackward::logging``. You must call this before using other
    parts of the library.
 #. ``ackward::logging::basicConfig()`` calls the standard
    ``logging.basicConfig()`` method in Python.
 #. Create a ``Logger`` object. These are the objects to which you pass
    log messages.
 #. Log a message at the critical severity level.

Extension module
----------------

This example shows the use of ``ackward::logging`` in a C++ extension
module (i.e. a Python module written in C++.) This first bit of code
implements the extension module itself.

.. literalinclude:: ../../../../../examples/logging/extension/log_test.cpp
   :language: c++
   :linenos:

Here's what's going on in this case:

 #. Include the header for the Logger class.
 #. A Python ``logging.Logger`` object is passed in as a
    ``boost::python::object`` via the extension's API.
 #. This "wraps" the Python logger in a C++-level
    ``ackward::logging::Logger`` instance.
 #. This logs the message at the error severity level.

This second bit of code just shows a basic use of the extension. This
is really just included for completeness; there's nothing special
going on here.

.. literalinclude:: ../../../../../examples/logging/extension/example.py
   :language: python
   :linenos:
