#ifndef BANSPASS_FILTER_H
#define BANSPASS_FILTER_H

#include <complex.h>
#include <stdint.h>

void bandpass_filter (double *data, double sampleRate, uint64_t totalSamples, int nfft,
                      double complex *filterResult, double complex *freqResponse);

#endif
