#ifndef WRITE_2_SCRIPT_H
#define WRITE_2_SCRIPT_H

void save2Script (const char *outputfile, double *data, double complex *filterResult, uint64_t totalSamples,
                  double complex *freqResponse, int nfft);

#endif
