#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "datatype.h"

static void
usage ()
{
  printf ("Usage: ./ms2filter <c1> <c2> <order> <input> <output>");
  printf ("\n\nInput parameters:\n");
  printf ("c1: low cut frequency (Hz)\n");
  printf ("c2: high cut frequency (Hz)\n");
  printf ("order: filter order\n");
  printf ("input: a miniSEED seismic record\n");
  printf ("output: a text file containing filtered result (real and imaginary part)\n");
  printf ("\nOutput format: \n");
  printf ("1. A MATLAB script to plot the input and filter result.\n");
  printf ("2. A text file containing filtered result (real and imaginary part).\n");
}

int
main (int argc, char **argv)
{
  char *mseedfile = NULL;
  data_t *data    = NULL;
  double sampleRate;
  uint64_t totalSamples;
  //double complex *filterResult;
  //double complex *freqResponse;
  float complex *filterResult;
  float complex *freqResponse;
  int nfft = 2000;
  float lowcut, highcut; /* low and high cutoff frequencies */
  int order;
  char *outputFile;
  const char *outputScript = "filter_result.m";
  int rv;

  /* Simple argement parsing */
  if (argc != 6)
  {
    usage ();
    return 1;
  }
  lowcut     = atof (argv[1]);
  highcut    = atof (argv[2]);
  order      = atoi (argv[3]);
  mseedfile  = argv[4];
  outputFile = argv[5];

  /* Get data from input miniSEED file */
  rv = parse_miniSEED (mseedfile, &data, &sampleRate, &totalSamples);
  if (rv != 0)
  {
    return rv;
  }
  if (data == NULL)
  {
    printf ("Input data read unsuccessfully\n");
    return -1;
  }

  /* filter the data with band pass filter */
  filterResult = (float complex *)malloc (sizeof (float complex) * totalSamples);
  freqResponse = (float complex *)malloc (sizeof (float complex) * nfft);
  bandpass_filter_float (data, sampleRate, totalSamples, nfft,
                         lowcut, highcut, order,
                         filterResult, freqResponse);
  if (filterResult == NULL || freqResponse == NULL)
  {
    printf ("Something wrong when applying band pass filter\n");
    return -1;
  }

  /* Save the filtered result to MATLAB script and text file */
  save2Script_float (outputScript, data, order, filterResult, totalSamples,
                     freqResponse, nfft);
  save2file (outputFile, filterResult, totalSamples);

  // free alllocated objects
  free (data);
  free (filterResult);
  free (freqResponse);

  return 0;
}
