#include <stdlib.h>
#include <stdint.h>
#include <sys/param.h>
#include <assert.h>
#include <err.h>

#include <sparsehash/dense_hash_map>

#include "map.h"
#include "map_google_densehash.h"

void map_google_densehash(int *keys, int *keys_shuffled, int *values, size_t size, size_t lookups,
                          double *insert, double *lookup, double *erase, uint64_t *sum)
{
  google::dense_hash_map<int, int> m;
  google::dense_hash_map<int, int>::iterator iter;
  size_t i, n;
  uint64_t t1, t2, s;

  m.max_load_factor(0.5);
  m.set_empty_key(-1);
  m.set_deleted_key(-2);

  t1 = ntime();
  for (i = 0; i < size; i ++)
    m[keys[i]] = values[i];
  t2 = ntime();
  *insert = (double) (t2 - t1) / size;

  s = 0;
  t1 = ntime();
  for (n = lookups; n; n -= i)
    for (i = 0; i < MIN(size, n); i ++)
      s += m[keys_shuffled[i]];
  t2 = ntime();
  *sum = s;
  *lookup = (double) (t2 - t1) / lookups;

  t1 = ntime();
  for (i = 0; i < size; i ++)
    {
      iter = m.find(keys[i]);
      if (iter != m.end())
        m.erase(iter);
    }
  t2 = ntime();
  if (m.size())
      errx(1, "inconsistency");
  *erase = (double) (t2 - t1) / size;

  m.clear();
}
