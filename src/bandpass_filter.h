#ifndef BANSPASS_FILTER_H
#define BANSPASS_FILTER_H

#include <complex.h>
#include <stdint.h>

void bandpass_filter (double *data, double sampleRate, uint64_t totalSamples, int nfft,
                      double complex *filterResult, double complex *freqResponse);

void bandpass_filter_float (double *data, double sampleRate, uint64_t totalSamples, int nfft,
                            float complex *filterResult, float complex *freqResponse);

#endif
