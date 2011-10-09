=============
Release Notes
=============

**Contents**

* :ref:`release_notes_0_5`
* :ref:`release_notes_0_4`
* :ref:`release_notes_0_3`
* :ref:`release_notes_0_2`

.. _release_notes_0_5:

0.5
===

* Added ``ackward::core::versionInfo()``.

.. _release_notes_0_4:

0.4
===

* A large number of bug fixes.
* ``logging`` is fully documented.
* ``logging::UserHandler`` reworked to use template implementations.
* ``ackward::core::import`` now relies more on ``boost::python::import()``.
* ``ackward.Property`` now generates ``ackward::core::Property<T>``
  instead of getters and setters.
* ``ackward.Class`` can be customized with cosntructor initializer
  statements by its children.

.. _release_notes_0_3:

0.3
===

* Added doxygen support to documentation project.
* Added `breathe` sphinx extension to bridge the doxygen-sphinx divide.
* A great deal of documentation updates.

.. _release_notes_0_2:

0.2
===
* Initial version of sphinx documentation.
* Initial work on ``ackward::queue``.
