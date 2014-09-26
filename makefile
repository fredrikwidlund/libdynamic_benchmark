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
	rustc --opt-level 3 --cfg ndebug -C lto -C target-cpu=corei7-avx vector_grow_rust.rs

.java.class:
	javac -Xlint $<

vector_grow_c.csv: vector_grow_c
	./vector_grow_c $(MAX) > vector_grow_c.csv

vector_grow_cpp.csv: vector_grow_cpp
	./vector_grow_cpp $(MAX) > vector_grow_cpp.csv

vector_grow_java_vector.csv: VectorGrowJavaVector.class
	java -Xmx3500m VectorGrowJavaVector $(MAX) > vector_grow_java_vector.csv

vector_grow_java_array_list.csv: VectorGrowJavaArrayList.class
	java -Xmx3500m VectorGrowJavaArrayList $(MAX) > vector_grow_java_array_list.csv

vector_grow_java_trove.csv: VectorGrowJavaTrove.class
	java -Xmx3500m VectorGrowJavaTrove $(MAX) > vector_grow_java_trove.csv

vector_grow_lua_table.csv:
	luajit vector_grow_lua_table.lua $(MAX) > vector_grow_lua_table.csv

vector_grow_lua_assign.csv:
	luajit vector_grow_lua_assign.lua $(MAX) > vector_grow_lua_assign.csv

vector_grow_rust.csv: vector_grow_rust
	./vector_grow_rust $(MAX) > vector_grow_rust.csv

vector_grow.pdf: vector_grow_c.csv vector_grow_cpp.csv vector_grow_java_vector.csv \
		 vector_grow_java_array_list.csv vector_grow_java_trove.csv vector_grow_lua_table.csv \
	         vector_grow_lua_assign.csv vector_grow_rust.csv
	./vector_grow.R

clean:
	rm -f vector_grow_c vector_grow_cpp vector_grow_rust *.class *.o *.csv *.pdf
