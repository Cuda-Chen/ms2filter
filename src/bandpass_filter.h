#ifndef BANSPASS_FILTER_H
#define BANSPASS_FILTER_H

#include <complex.h>
#include <stdint.h>

double complex *bandpass_filter (double *data, double sampleRate, uint64_t totalSamples);

#endif
