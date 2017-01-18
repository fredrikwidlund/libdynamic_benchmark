#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <err.h>
#include <dynamic.h>

#include "khash/khash.h"

#include "map.h"

KHASH_MAP_INIT_INT(32, int)

uint64_t map_khash(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  khash_t(32) *h = kh_init(32);
  khiter_t k;
  int ret;
  size_t i, n;
  uint64_t t1, t2, sum;


  for (i = 0; i < size; i ++)
    {
      k = kh_put(32, h, key[i], &ret);
      if (ret)
        kh_value(h, k) = value[i];
    }

  sum = 0;
  n = iterations;
  t1 = ntime();
  while (n)
    {
      for (i = 0; i < MIN(size, n); i ++)
        {
          k = kh_get(32, h, lookup[i]);
          sum += kh_value(h, k);
        }
      n -= i;
    }
  t2 = ntime();

  kh_destroy(32, h);
  result->lookup = (double) (t2 - t1) / iterations;
  return sum;
}
