#include <stdio.h>

#include "common.h"

static void
usage ()
{
  printf ("Usage: ./ms2filter <c1> <c2> <input> <output>");
  printf ("\nOutput format: \n");
  printf ("a MATLAB script to plot the input and filter result\n");
  printf ("NOTE: current <output> has no effect. Type anything you like instead.\n");
}

int
main (int argc, char **argv)
{
  char *mseedfile = NULL;
  double *data;
  double sampleRate;
  int totalSamples;
  double complex *filterResult;
  double lowcut, highcut; /* low and high cutoff frequencies */
  const char *outputFile = "filter_result.m";
  int rv;

  /* Simple argement parsing */
  if (argc != 5)
  {
    usage ();
    return 1;
  }
  mseedfile = argv[1];

  /* Get data from input miniSEED file */
  rv = parse_miniSEED (mseedfile, data, &sampleRate, &totalSamples);
  if (rv != 0)
  {
    return rv;
  }

  /* filter the data with band pass filter */
  filterResult = bandpass_filter (data, sampleRate, totalSamples);
  if (filterResult == NULL)
  {
    printf ("Something wrong when applying band pass filter\n");
    return -1;
  }

  /* Save the filtered result to MATLAB script */
  save2Script (outputFile, filterResult, totalSamples);

  return 0;
}
