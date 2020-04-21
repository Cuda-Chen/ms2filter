#include <stdio.h>

#include "common.h"

#define OUTPUT_FILENAME "filter_result.m"

static void
usage ()
{
  printf ("Usage: ./ms2filter <c1> <c2> <input> <output>");
  printf ("\nOutput format: \n");
  printf ("a MATLAB script to plot the input and filter result\n");
    printf("NOTE: current <output> has no effect. Type anything 
            you like instead.\n");
}

int
main (int argc, char **argv)
{
  char *mseedfile = NULL;
  double *data;
  double sampleRate;

  /* Simple argement parsing */
  if (argc != 5)
  {
    usage ();
    return 1;
  }
  mseedfile = argv[1];
}
