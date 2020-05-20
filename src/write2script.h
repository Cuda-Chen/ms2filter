#ifndef WRITE_2_SCRIPT_H
#define WRITE_2_SCRIPT_H

void save2Script (const char *outputfile, double *data, double complex *filterResult, uint64_t totalSamples,
                  double complex *freqResponse, int nfft);
void save2Script_float (const char *outputfile, double *data, int _order, float complex *filterResult, uint64_t totalSamples,
                        float complex *freqResponse, int nfft);

#endif
