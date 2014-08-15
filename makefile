CFLAGS   = -Wall -Werror -Wpedantic -O3 -std=c11 -flto
CXXFLAGS = -Wall -Werror -Wpedantic -O3 -std=c++11 -flto
LDADD    = -ldynamic
MAX      = 500000000

.PHONY: all clean

all: vector_grow.pdf

vector_grow_c: vector_grow_c.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDADD)

vector_grow_cpp: vector_grow_cpp.cpp

vector_grow_c.csv: vector_grow_c
	./vector_grow_c $(MAX) > vector_grow_c.csv

vector_grow_cpp.csv: vector_grow_cpp
	./vector_grow_cpp $(MAX) > vector_grow_cpp.csv

vector_grow.pdf: vector_grow_c.csv vector_grow_cpp.csv 
	./vector_grow.R

clean:
	rm -f vector_grow_c vector_grow_cpp *.o *.csv *.pdf
