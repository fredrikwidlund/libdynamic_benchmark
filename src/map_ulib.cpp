#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <assert.h>
#include <err.h>

#include <ulib/hash_align.h>

#include "map.h"
#include "map_ulib.h"

uint64_t map_ulib(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  ulib::align_hash_map<int, int> m;
  size_t i, n;
  uint64_t t1, t2, sum;

  for (i = 0; i < size; i ++)
    m[key[i]] = value[i];

  sum = 0;
  n = iterations;
  t1 = ntime();
  while (n)
    {
      for (i = 0; i < MIN(size, n); i ++)
        sum += m[lookup[i]];
      n -= i;
    }
  t2 = ntime();

  result->lookup = (double) (t2 - t1) / iterations;
  return sum;
}
