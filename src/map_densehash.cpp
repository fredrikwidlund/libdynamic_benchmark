#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <assert.h>
#include <err.h>

#include <sparsehash/dense_hash_map>

#include "map.h"
#include "map_densehash.h"

/*
#define VARIANT_DECLARE
#define VARIANT_NEW     m = new google::dense_hash_map<int, int>(); m->set_empty_key(-1); m->max_load_factor(0.5);
#define VARIANT_INSERT  m->insert(std::make_pair(data[j], j));
#define VARIANT_LOOKUP  sum += (*m)[data[j]];
#define VARIANT_DELETE  delete m;
#elif ULIB_INT
*/

uint64_t map_densehash(int *key, int *value, int *lookup, size_t size, size_t iterations, map_result *result)
{
  google::dense_hash_map<int, int> m;
  size_t i, n;
  uint64_t t1, t2, sum;

  m.max_load_factor(0.5);
  m.set_empty_key(-1);

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
