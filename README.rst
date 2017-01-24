Results
=======

* ``Intel(R) Core(TM) i7-3720QM CPU @ 2.60GHz/gcc v6.3.1``

  .. figure:: https://cloud.githubusercontent.com/assets/2116262/22257487/86d6985e-e25e-11e6-9e41-9ed8381668b4.png

* ``Intel(R) Xeon(R) CPU E5530 @ 2.40GHz/gcc v4.9.3``

  .. figure:: https://cloud.githubusercontent.com/assets/2116262/22249382/175dc198-e243-11e6-9594-556c6f0eb15e.png

README
======

This is a benchmark of libdynamic performance in comparison to other relevant
libraries.

It currently contains a single benchmark comparing lookups in a hash map using
random integer keys. Since design strategies of how to construct a hash map
differ, care has been taken to remove the differences out of the equation.

The key set is random so the hash function performance is not tested and all
candidates use the identity hash, removing differences in hash function
implementations as well.

This is a simple benchmark comparing raw hash map lookups. Take it for what is
is.

Compiling
=========

The source uses GNU Autotools (autoconf_, automake_, libtool_).

To benchmark depends on libdynamic_ and `Google sparsehash`_ so please build
and install these first.

To create the PDF graph, `R`_ needs to be installed, together with the
R-packages ggplot2, scales and sitools. Information about how to install
R-packages can be found for example here: https://www.r-bloggers.com/installing-r-packages/. 

To compile run:

.. code-block:: shell

    $ ./autogen.sh
    $ ./configure
    $ make

Benchmarking
============

To create the map.pdf result, run:

.. code-block:: shell

    $ make benchmark

.. _libdynamic: https://github.com/fredrikwidlund/libdynamic
.. _`Google sparsehash`: https://github.com/sparsehash/sparsehash
.. _`R`: https://www.r-project.org/
.. _autoconf: http://www.gnu.org/software/autoconf/
.. _automake: http://www.gnu.org/software/automake/
.. _libtool: http://www.gnu.org/software/libtool/
