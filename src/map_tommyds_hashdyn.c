#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <err.h>

#include "tommyds/tommyhashdyn.h"
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

void map_tommyds_hashdyn(int *keys, int *keys_shuffled, int *values, size_t size, size_t lookups,
                    double *insert, double *lookup, double *erase, uint64_t *sum)
{
  tommy_hashdyn m;
  element **e;
  uint64_t t1, t2, s;
  size_t i, n;

  tommy_hashdyn_init(&m);
  e = calloc(size, sizeof *e);

  t1 = ntime();
  for (i = 0; i < size; i ++)
    {
      e[i] = malloc(sizeof(element));
      e[i]->key = keys[i];
      e[i]->value = values[i];
      tommy_hashdyn_insert(&m, &e[i]->node, e[i], keys[i]);
    }
  t2 = ntime();
  *insert = (double) (t2 - t1) / size;

  s = 0;
  t1 = ntime();
  for (n = lookups; n; n -= i)
    for (i = 0; i < MIN(size, n); i ++)
      s += ((element *) tommy_hashdyn_search(&m, compare, &keys_shuffled[i], keys_shuffled[i]))->value;
  t2 = ntime();
  *sum = s;
  *lookup = (double) (t2 - t1) / lookups;

  t1 = ntime();
  for (i = 0; i < size; i ++)
    {
      tommy_hashdyn_remove(&m, compare,  &keys[i], keys[i]);
      free(e[i]);
    }
  t2 = ntime();
  if (tommy_hashdyn_count(&m))
    errx(1, "inconsistency");
  *erase = (double) (t2 - t1) / size;

  tommy_hashdyn_done(&m);
  free(e);
}
