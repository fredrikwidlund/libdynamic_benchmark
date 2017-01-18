#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <unordered_map>
#include <assert.h>
#include <err.h>

#include "map.h"
#include "map_std_unordered.h"

uint64_t map_std_unordered(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  std::unordered_map<int, int> m;
  size_t i, n;
  uint64_t t1, t2, sum;

  m.max_load_factor(0.5);

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
