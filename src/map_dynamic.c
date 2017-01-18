#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <err.h>
#include <dynamic.h>

#include "map.h"

typedef struct map_element map_element;
struct map_element {int key; int value;};
static size_t hash(void *e) {return *(int *) e;}
static int    equal(void *e1, void *e2) {return *(int *) e1 == *(int *) e2;}
static void   set(void *e1, void *e2) {*(map_element *) e1 = *(map_element *) e2;}

uint64_t map_dynamic(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  map m;
  size_t i, n;
  uint64_t t1, t2, sum;

  map_construct(&m, sizeof(map_element), (map_element[]) {{.key = -1, .value = -1}}, set);

  for (i = 0; i < size; i ++)
    map_insert(&m, (map_element[]) {{.key = key[i], .value = value[i]}}, hash, equal, set, NULL);

  sum = 0;
  n = iterations;
  t1 = ntime();
  while (n)
    {
      for (i = 0; i < MIN(size, n); i ++)
        sum += ((map_element *) map_at(&m, (map_element[]){{.key = lookup[i]}}, hash, equal))->value;
      n -= i;
    }
  t2 = ntime();

  map_destruct(&m, NULL, NULL);
  result->lookup = (double) (t2 - t1) / iterations;
  return sum;
}
