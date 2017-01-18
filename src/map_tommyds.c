#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <err.h>
#include <dynamic.h>

#include <tommyds/tommyhashdyn.h>
#include "map.h"

typedef struct element element;
struct element {
  tommy_node node;
  int       key;
  int       value;
};

static int compare(const void *arg, const void *obj)
{
  return *(int *) arg != ((struct element *)obj)->key;
}

uint64_t map_tommyds(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  tommy_hashdyn m;
  element *e;
  size_t i, n;
  uint64_t t1, t2, sum;

  tommy_hashdyn_init(&m);

  e = calloc(size, sizeof *e);
  for (i = 0; i < size; i ++)
    {
      e[i].key = key[i];
      e[i].value = value[i];
      tommy_hashdyn_insert(&m, &e[i].node, &e[i], key[i]);
    }

  sum = 0;
  n = iterations;
  t1 = ntime();
  while (n)
    {
      for (i = 0; i < MIN(size, n); i ++)
        sum += ((element *) tommy_hashdyn_search(&m, compare, &lookup[i], lookup[i]))->value;
      n -= i;
    }
  t2 = ntime();

  tommy_hashdyn_done(&m);
  free(e);
  result->lookup = (double) (t2 - t1) / iterations;
  return sum;
}
