libdynamic_benchmarks
=====================

Requirements
------------

* GCC
* jemalloc (http://www.canonware.com/jemalloc/)
* Java JDK
* Java Trove library (https://bitbucket.org/robeden/trove/)
* Rust 0.12.0
* Rust 0.12.0 separately built, configured with --disable-jemalloc, specified with RUSTC_BIN_BUILD in the makefile (the build takes a long time)
* LuaJIT
* Lua socket library
* R
* R ggplot2 and sitools libraries

Candidates can be disabled by editing the makefile and R scripts

Usage
-----

Running make should produce two graphs, vector_grow.pdf and vector_grow_linear.pdf

    make



