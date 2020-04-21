#ifndef PARSE_MINISEED_H
#define PARSE_MINISEED_H

#include <stdint.h>

int parse_miniSEED (const char *mseedfile, double **data, double *sampleRate, uint64_t *totalSamples);

#endif
