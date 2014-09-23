#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <vector>
#include <err.h>

uint64_t ntime()
{
  struct timeval tv;

  (void) gettimeofday(&tv, NULL);
  return ((uint64_t) tv.tv_sec * 1000000000) + ((uint64_t) tv.tv_usec * 1000);
}

int main(int argc, char **argv)
{
  int i, j, n = strtol(argv[1], NULL, 0);
  uint64_t t, m[101];
  std::vector<int> v;
  
  t = ntime();
  m[0] = 0;
  try
    {
      for (i = 0; i < n; i += n / 100)
        {
          for (j = 0; j < n / 100; j ++)
            {
              v.push_back(j);
            }
          m[i / (n / 100) + 1] = ntime() - t;
        }
    }
  catch(const std::bad_alloc&)
    {
      err(1, "std::vector::push_back %d", i);
    }
  
  (void) fprintf(stdout, "\"size\",\"time\"\n");
  for (i = 0; i <= 100; i ++)
    (void) fprintf(stdout, "%d,%f\n", i * (n / 100), (float) m[i] / 1000000000);

  exit(0);
}
