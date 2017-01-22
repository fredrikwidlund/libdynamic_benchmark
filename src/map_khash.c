#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <err.h>
#include <dynamic.h>

#include "khash/khash.h"

#include "map.h"

KHASH_MAP_INIT_INT(32, int)

void map_khash(int *keys, int *keys_shuffled, int *values, size_t size, size_t lookups, double *insert, double *lookup, double *erase, uint64_t *sum)
{
  khash_t(32) *h = kh_init(32);
  khiter_t k;
  int ret;
  size_t i, n;
  uint64_t t1, t2, s;

  t1 = ntime();
  for (i = 0; i < size; i ++)
    {
      k = kh_put(32, h, keys[i], &ret);
      if (ret)
        kh_value(h, k) = values[i];
    }
  t2 = ntime();
  *insert = (double) (t2 - t1) / size;

  s = 0;
  t1 = ntime();
  for (n = lookups; n; n -= i)
    for (i = 0; i < MIN(size, n); i ++)
      {
        k = kh_get(32, h, keys_shuffled[i]);
        s += kh_value(h, k);
      }
  t2 = ntime();
  *sum = s;
  *lookup = (double) (t2 - t1) / lookups;

  t1 = ntime();
  for (i = 0; i < size; i ++)
    {
      k = kh_get(32, h, keys[i]);
      kh_del(32, h, k);
    }
  t2 = ntime();
  *erase = (double) (t2 - t1) / size;

  kh_destroy(32, h);
}
