CFLAGS   	= -Wall -Werror -Wpedantic -O3 -std=c11 -flto
CXXFLAGS 	= -Wall -Werror -Wpedantic -O3 -std=c++11 -flto
LDADD    	= -ldynamic
MAX      	= 100000000
CLASSPATH	= .:/opt/trove/lib/trove-3.0.3.jar

.SUFFIXES: .java .class
.PHONY: all clean

all: vector_grow.pdf

vector_grow_c: vector_grow_c.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDADD)

vector_grow_cpp: vector_grow_cpp.cpp

vector_grow_rust:
	rustc vector_grow_rust.rs

.java.class:
	javac -Xlint $<

vector_grow_c.csv: vector_grow_c
	./vector_grow_c $(MAX) > vector_grow_c.csv

vector_grow_cpp.csv: vector_grow_cpp
	./vector_grow_cpp $(MAX) > vector_grow_cpp.csv

vector_grow_java.csv: VectorGrowJava.class
	java -Xmx3500m VectorGrowJava $(MAX) > vector_grow_java.csv

vector_grow_java_trove.csv: VectorGrowJavaTrove.class
	java -Xmx3500m VectorGrowJavaTrove $(MAX) > vector_grow_java_trove.csv

vector_grow_lua.csv:
	luajit vector_grow_lua.lua $(MAX) > vector_grow_lua.csv

vector_grow_rust.csv:
	./vector_grow_rust $(MAX) > vector_grow_rust.csv

vector_grow.pdf: vector_grow_c.csv vector_grow_cpp.csv vector_grow_java.csv vector_grow_java_trove.csv vector_grow_lua.csv vector_grow_rust.csv
	./vector_grow.R

clean:
	rm -f vector_grow_c vector_grow_cpp vector_grow_rust *.class *.o *.csv *.pdf
