#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "liquid.h"

#include "bandpass_filter.h"

double complex *
bandpass_filter (double *data, double sampleRate, uint64_t totalSamples)
{
  // options
  liquid_iirdes_filtertype ftype = LIQUID_IIRDES_BUTTER;
  liquid_iirdes_bandtype btype   = LIQUID_IIRDES_BANDPASS;
  liquid_iirdes_format format    = LIQUID_IIRDES_SOS;
  unsigned int order             = 2;            // filter order
  float fc                       = 0.1f;         // cutoff frequency
  float f0                       = 0.3f;         // center frequency
  float Ap                       = 1.0f;         // pass-band ripple
  float As                       = 40.0f;        // stop-band attenuation
  uint64_t n                     = totalSamples; // number of samples

  // design filter from prototype
  iirfilt_crcf q = iirfilt_crcf_create_prototype (
      ftype, btype, format, order, fc, f0, Ap, As);
  iirfilt_crcf_print (q);

  // allocate memory for data arrays
  double complex *x = (double complex *)malloc (sizeof (double complex) * n);
  double complex *y = (double complex *)malloc (sizeof (double complex) * n);

  // generate input signal (noise sine wave with decaying amplitude)
  uint64_t i;
  for (i = 0; i < n; i++)
  {
    x[i] = data[i];

    // run filter
    iirfilt_crcf_execute (q, x[i], &y[i]);
  }

  // destroy filter object
  iirfilt_crcf_destroy (q);

  free (x);

  return y;
}
