=============
ackward::uuid
=============

The ``ackward::uuid`` library wraps the Python ``uuid`` module. Full
documentation for the ``uuid`` module can be found at
`<http://docs.python.org/library/uuid.html>`_.

Initialization
==============

Before you use ``ackward::uuid``, you must call
``ackward::uuid::initialize()``.

.. doxygenfunction:: ackward::uuid::initialize

Construction
============

There are various ways to construct UUID objects.

.. doxygenfunction:: ackward::uuid::uuid1
.. doxygenfunction:: ackward::uuid::uuid3
.. doxygenfunction:: ackward::uuid::uuid4
.. doxygenfunction:: ackward::uuid::uuid5

``name_space`` constants
------------------------

The following constants can be used as the ``name_space`` arguments
for ``uuid3()`` and ``uuid5()``.

.. doxygenfunction:: ackward::uuid::NAMESPACE_DNS
.. doxygenfunction:: ackward::uuid::NAMESPACE_URL
.. doxygenfunction:: ackward::uuid::NAMESPACE_OID
.. doxygenfunction:: ackward::uuid::NAMESPACE_X500

UUID class
==========

.. doxygenclass:: ackward::uuid::UUID
   :members:

Miscellaneous
=============

.. doxygenfunction:: ackward::uuid::getnode
.. doxygentypedef:: ackward::uuid::Node
.. doxygentypedef:: ackward::uuid::Fields
.. doxygenenum:: ackward::uuid::Variant
