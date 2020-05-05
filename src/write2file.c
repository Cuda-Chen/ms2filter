#include <complex.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "write2file.h"

void
save2file (const char *outputFile, float complex *filterResult, uint64_t totalSamples)
{
  FILE *fptr = fopen (outputFile, "w");
  uint64_t i;
  for (i = 0; i < totalSamples; i++)
  {
    fprintf (fptr, "%lf %lf\n", crealf (filterResult[i]), cimagf (filterResult[i]));
  }

  fclose (fptr);
}
