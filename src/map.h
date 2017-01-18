#ifndef BENCHMARKS_MAP_H_INCLUDED
#define BENCHMARKS_MAP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct map_result map_result;
struct map_result
{
  char      *name;
  size_t     size;
  double     lookup;
};

typedef struct map_metric map_metric;
struct map_metric
{
  char      *name;
  uint64_t (*measure)(int *, int *, int *, size_t, size_t, map_result *);
  double     lookup;
};

uint64_t ntime(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BENCHMARKS_MAP_H_INCLUDED */
