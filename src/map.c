#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <dynamic.h>

#include "map.h"
#include "map_std_unordered.h"
#include "map_densehash.h"
#include "map_ulib.h"
#include "map_khash.h"
#include "map_tommyds.h"
#include "map_dynamic.h"

static const map_metric metrics[] = {
  {.name = "C++ std::unordered_map", .measure = map_std_unordered},
  {.name = "C++ google::dense_hash_map", .measure = map_densehash},
  {.name = "C++ ulib::align_hash_map", .measure = map_ulib},
  {.name = "C khash", .measure = map_khash},
  {.name = "C tommyds", .measure = map_tommyds},
  {.name = "C libdynamic", .measure = map_dynamic}
};
static const size_t metrics_len = sizeof metrics / sizeof metrics[0];

static int    set_int_empty = -1;
static size_t set_int_hash(void *e) {return *(int *) e;}
static int    set_int_equal(void *e1, void *e2) {return *(int *) e1 == *(int *) e2;}
static void   set_int_set(void *e1, void *e2) {*(int *) e1 = *(int *) e2;}

static void shuffle(int *array, size_t n)
{
  size_t i, j;
  int t;

  if (n <= 1)
    return;

  for (i = 0; i < n - 1; i ++)
    {
      j = i + rand() / (RAND_MAX / (n - i) + 1);
      t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
}

static void fill(int *key, int *value, int *lookup, size_t n)
{
  map m;
  size_t i;

  map_construct(&m, sizeof(int), &set_int_empty, set_int_set);

  i = 0;
  while (i < n)
    {
      key[i] = random();
      if (*(int *) map_at(&m, &key[i], set_int_hash, set_int_equal) != -1)
        continue;
      map_insert(&m, &key[i], set_int_hash, set_int_equal, set_int_set, NULL);
      value[i] = key[i];
      lookup[i] = key[i];
      i ++;
    }

  map_destruct(&m, NULL, NULL);
  shuffle(lookup, n);
}

static uint64_t checksum(int *lookup, size_t size, size_t iterations)
{
  uint64_t i, sum = 0;

  for (i = 0; i < iterations; i ++)
    sum += lookup[i % size];
  return sum;
}

static void aggregate(map_result *r, map_result *ri)
{
  if (!r->lookup || ri->lookup < r->lookup)
    r->lookup = ri->lookup;
}

uint64_t ntime(void)
{
  struct timespec ts;

  (void) clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  return ((uint64_t) ts.tv_sec * 1000000000) + ((uint64_t) ts.tv_nsec);
}

int main()
{
  vector results;
  size_t i, round, rounds = 5, n, n_min = 100, n_max = 1000000, iterations = 10000;
  double k = 1.1;
  int *key, *value, *lookup;
  uint64_t sum, si;
  const map_metric *m;
  map_result result, r, *ri;

  vector_construct(&results, sizeof result);
  for (n = n_min; n < n_max; n = ceil(k * n))
    {
      (void) fprintf(stderr, "size %lu\n", n);
      key = malloc(n * sizeof *key);
      value = malloc(n * sizeof *value);
      lookup = malloc(n * sizeof *lookup);
      assert(key && value && lookup);
      fill(key, value, lookup, n);
      sum = checksum(lookup, n, iterations);

      for (m = metrics; m < &metrics[metrics_len]; m ++)
        {
          result = (map_result){.name = m->name, .size = n};
          for (round = 0; round < rounds; round ++)
            {
              si = m->measure(key, value, lookup, n, iterations, &r);
              assert(si == sum);
              aggregate(&result, &r);
            }
          vector_push_back(&results, &result);
        }

      free(key);
      free(value);
      free(lookup);
    }

  (void) fprintf(stdout, "name,size,lookup\n");
  for (i = 0; i < vector_size(&results); i ++)
    {
      ri = vector_at(&results, i);
      (void) fprintf(stdout, "%s,%lu,%f\n", ri->name, ri->size, ri->lookup);
    }

  vector_destruct(&results);
}
