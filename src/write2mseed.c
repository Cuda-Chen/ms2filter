#include <complex.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "libmseed.h"

#include "datatype.h"
#include "write2mseed.h"

int
save2mseed (const char *mseedfile, const char *outputFile, float complex *filteredResult)
{
  MS3TraceList *mstl = NULL;
  MS3TraceID *tid    = NULL;
  MS3TraceSeg *seg   = NULL;
  uint32_t flags     = 0;
  int8_t verbose     = 0;
  uint64_t totalSamples;
  int rv;

  /* output settings */
  int reclen = 1024; /* Desired maximum record length */

  flags |= MSF_VALIDATECRC;
  /* Unpack the data */
  flags |= MSF_RECORDLIST;

  /* Read all miniSEED into a trace list */
  rv = ms3_readtracelist (&mstl, mseedfile, NULL, 0, flags, verbose);
  if (rv != MS_NOERROR)
  {
    ms_log (2, "Cannot read miniSEED from file: %s\n", ms_errorstr (rv));
    return -1;
  }

  /* Traverse trace list structures */
  tid = mstl->traces;
  while (tid)
  {
    /* Allocate the data array of every trace */
    totalSamples = 0;
    /* Count how many samples of this trace */
    seg = tid->first;
    while (seg)
    {
      totalSamples += seg->samplecnt;
      seg = seg->next;
    }
#ifdef DEBUG
    printf ("estimated samples of this trace: %" PRId64 "\n", totalSamples);
#endif

    /* Get the data of this trace */
    seg            = tid->first;
    uint64_t index = 0;
    while (seg)
    {
      /* Unpack and get the data */
      if (seg->recordlist && seg->recordlist->first)
      {
        void *sptr;
        size_t i;
        uint8_t samplesize;
        char sampletype;
        /* Determine sample size and type based on encoding of first record */
        ms_encoding_sizetype (seg->recordlist->first->msr->encoding, &samplesize, &sampletype);

        /* Unpack data samples using record list.
         * No data buffer is supplied, so it will be allocated and assigned to the segment.
         * Alternatively, a user-specified data buffer can be provided here. */
        int64_t unpacked = mstl3_unpack_recordlist (tid, seg, NULL, 0, verbose);

        if (unpacked != seg->samplecnt)
        {
          ms_log (2, "Cannot unpack samples for %s\n", tid->sid);
        }
        else
        {
          if (sampletype == 'a')
          {
            printf ("%*s",
                    (seg->numsamples > INT_MAX) ? INT_MAX : (int)seg->numsamples,
                    (char *)seg->datasamples);
          }
          else
          {
            for (i = 0; i < seg->numsamples; i++)
            {
              sptr = (char *)seg->datasamples + (i * samplesize);
              if (sampletype == 'i')
              {
                (*(int32_t *)sptr) = (int32_t)crealf (filteredResult[index]);
              }
              else if (sampletype == 'f')
              {
                (*(float *)sptr) = (float)crealf (filteredResult[index]);
              }
              else if (sampletype == 'd')
              {
                (*(double *)sptr) = (double)crealf (filteredResult[index]);
              }

              index++;
            }
          }
        }
      }

      seg = seg->next;
    }

    tid = tid->next;
  }

  /* Write to output miniSeed file */
  int64_t packedrecords = mstl3_writemseed (mstl, outputFile, 1, reclen,
                                            DE_INT32, MSF_PACKVER2, verbose);

  if (mstl)
  {
    mstl3_free (&mstl, 0);
  }

  return 0;
}
