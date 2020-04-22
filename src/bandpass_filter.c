#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "liquid.h"

#include "bandpass_filter.h"

void
bandpass_filter (double *data, double sampleRate, uint64_t totalSamples, int nfft,
                 double complex *filterResult, double complex *freqResponse)
{
  // options
  liquid_iirdes_filtertype ftype = LIQUID_IIRDES_BUTTER;
  liquid_iirdes_bandtype btype   = LIQUID_IIRDES_BANDPASS;
  liquid_iirdes_format format    = LIQUID_IIRDES_SOS;
  unsigned int order             = 6;            // filter order
  float fc                       = 0.01f;        // cutoff frequency
  float f0                       = 0.05f;        // center frequency
  float Ap                       = 1.0f;         // pass-band ripple
  float As                       = 40.0f;        // stop-band attenuation
  uint64_t n                     = totalSamples; // number of samples

  // design filter from prototype
  iirfilt_crcf q = iirfilt_crcf_create_prototype (
      ftype, btype, format, order, fc, f0, Ap, As);
  iirfilt_crcf_print (q);

  uint64_t i;
  for (i = 0; i < n; i++)
  {
    // run filter
    iirfilt_crcf_execute (q, data[i], &filterResult[i]);
  }

  // compute frequency response
  int counter;
  for (counter = 0; counter < nfft; counter++)
  {
    double freq = 0.5f * (double)counter / (double)nfft;
    iirfilt_crcf_freqresponse (q, freq, &freqResponse[counter]);
  }

  // destroy filter object
  iirfilt_crcf_destroy (q);
}
