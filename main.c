#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "datatype.h"

static void
usage ()
{
  printf ("Usage: ./ms2filter <c1> <c2> <order> <passes> <input> <output>");
  printf ("\n\nInput parameters:\n");
  printf ("c1: low cut frequency (Hz)\n");
  printf ("c2: high cut frequency (Hz)\n");
  printf ("order: filter order\n");
  printf ("passes: set '1' for forward filtering or set '2' for forward-backward filtering\n");
  printf ("input: a miniSEED seismic record\n");
  printf ("output: a text file containing filtered result (real and imaginary part)\n");
  printf ("\nOutput files and their format: \n");
  printf ("1. A MATLAB script to plot the input and filter result.\n");
  printf ("2. A text file containing filtered result (real and imaginary part).\n");
  printf ("3. A miniSEED file which contains filtered result (real part only).\n");
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
  int passes;
  char *outputFile;
  const char *outputScript = "filter_result.m";
  int rv;

  /* Simple argement parsing */
  if (argc != 7)
  {
    usage ();
    return 1;
  }
  lowcut     = atof (argv[1]);
  highcut    = atof (argv[2]);
  order      = atoi (argv[3]);
  passes     = atoi (argv[4]);
  mseedfile  = argv[5];
  outputFile = argv[6];

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
                         lowcut, highcut, order, passes,
                         filterResult, freqResponse);
  if (filterResult == NULL || freqResponse == NULL)
  {
    printf ("Something wrong when applying band pass filter\n");
    return -1;
  }

  /* Save the filtered result to MATLAB script and text file */
  save2Script_float (outputScript, data, order, filterResult, totalSamples,
                     freqResponse, nfft);
  save2file ("output.txt", filterResult, totalSamples);
  save2mseed (mseedfile, outputFile, filterResult);

  // free alllocated objects
  free (data);
  free (filterResult);
  free (freqResponse);

  return 0;
}
