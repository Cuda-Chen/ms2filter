#include <complex.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "write2script.h"

void
save2Script (const char *outputfile, double *data, double complex *filterResult, uint64_t totalSamples,
             double complex *freqResponse, int nfft)
{
  int order = 2;

  FILE *fptr = fopen (outputfile, "w");
  fprintf (fptr, "%% %s: auto-generated file. DO NOT EDIT.\n", outputfile);
  fprintf (fptr, "clear all;\n");
  fprintf (fptr, "close all;\n");
  fprintf (fptr, "\n");
  fprintf (fptr, "order=%d;\n", order);
  fprintf (fptr, "n=%" PRId64 ";\n", totalSamples);
  fprintf (fptr, "nfft=%d;\n", nfft);
  fprintf (fptr, "x=zeros(1,n);\n");
  fprintf (fptr, "y=zeros(1,n);\n");
  fprintf (fptr, "H=zeros(1,nfft);\n");

  uint64_t i;
  for (i = 0; i < totalSamples; i++)
  {
    fprintf (fptr, "x(%4" PRId64 ") = %12.4e + j*%12.4e;\n", i + 1, crealf (data[i]), cimagf (data[i]));
    fprintf (fptr, "y(%4" PRId64 ") = %12.4e + j*%12.4e;\n", i + 1, crealf (filterResult[i]), cimagf (filterResult[i]));
  }

  int counter;
  for (counter = 0; counter < nfft; counter++)
  {
    fprintf (fptr, "H(%4u) = %12.8f + j*%12.8f;\n", counter + 1,
             crealf (freqResponse[counter]), cimagf (freqResponse[counter]));
  }

  // plot output
  fprintf (fptr, "t=0:(n-1);\n");
  fprintf (fptr, "figure;\n");
  fprintf (fptr, "subplot(2,1,1);\n");
  fprintf (fptr, "  plot(t,real(x),'-','Color',[1 1 1]*0.5,'LineWidth',1,...\n");
  fprintf (fptr, "       t,real(y),'-','Color',[0 0.5 0.25],'LineWidth',2);\n");
  fprintf (fptr, "  xlabel('time');\n");
  fprintf (fptr, "  ylabel('real');\n");
  fprintf (fptr, "  legend('input','filtered output','location','northeast');\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "subplot(2,1,2);\n");
  fprintf (fptr, "  plot(t,imag(x),'-','Color',[1 1 1]*0.5,'LineWidth',1,...\n");
  fprintf (fptr, "       t,imag(y),'-','Color',[0 0.25 0.5],'LineWidth',2);\n");
  fprintf (fptr, "  xlabel('time');\n");
  fprintf (fptr, "  ylabel('imag');\n");
  fprintf (fptr, "  legend('input','filtered output','location','northeast');\n");
  fprintf (fptr, "  grid on;\n");

  // plot frequency response
  fprintf (fptr, "f=0.5*[0:(nfft-1)]/nfft;\n");
  fprintf (fptr, "figure;\n");
  fprintf (fptr, "subplot(3,1,1);\n");
  fprintf (fptr, "  plot(f,20*log10(abs(H)),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  //fprintf (fptr, "  plot(f, abs(H), 'Color', [0 0.25 0.5], 'LineWidth', 2);\n");
  //fprintf (fptr, "  axis([0 0.5 -3 0]);\n");
  fprintf (fptr, "  axis([0 0.5 -100 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Pass band [dB]');\n");
  fprintf (fptr, "subplot(3,1,2);\n");
  fprintf (fptr, "  plot(f,20*log10(abs(H)),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  fprintf (fptr, "  axis([0 0.5 -100 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Stop band [dB]');\n");
  fprintf (fptr, "subplot(3,1,3);\n");
  fprintf (fptr, "  plot(f,180/pi*arg(H),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  //fprintf(fptr,"  axis([0 0.5 -100 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Phase [degrees]');\n");
  fprintf (fptr, "  xlabel('Normalized Frequency [f/F_s]');\n");
  fclose (fptr);
}

void
save2Script_float (const char *outputfile, double *data, float complex *filterResult, uint64_t totalSamples,
                   float complex *freqResponse, int nfft)
{
  int order = 2;

  FILE *fptr = fopen (outputfile, "w");
  fprintf (fptr, "%% %s: auto-generated file. DO NOT EDIT.\n", outputfile);
  fprintf (fptr, "clear all;\n");
  fprintf (fptr, "close all;\n");
  fprintf (fptr, "\n");
  fprintf (fptr, "order=%d;\n", order);
  fprintf (fptr, "n=%" PRId64 ";\n", totalSamples);
  fprintf (fptr, "nfft=%d;\n", nfft);
  fprintf (fptr, "x=zeros(1,n);\n");
  fprintf (fptr, "y=zeros(1,n);\n");
  fprintf (fptr, "H=zeros(1,nfft);\n");

  uint64_t i;
  for (i = 0; i < totalSamples; i++)
  {
    fprintf (fptr, "x(%4" PRId64 ") = %12.4e + j*%12.4e;\n", i + 1, crealf (data[i]), cimagf (data[i]));
    fprintf (fptr, "y(%4" PRId64 ") = %12.4e + j*%12.4e;\n", i + 1, crealf (filterResult[i]), cimagf (filterResult[i]));
  }

  int counter;
  for (counter = 0; counter < nfft; counter++)
  {
    fprintf (fptr, "H(%4u) = %12.8f + j*%12.8f;\n", counter + 1,
             crealf (freqResponse[counter]), cimagf (freqResponse[counter]));
  }

  // plot output
  fprintf (fptr, "t=0:(n-1);\n");
  fprintf (fptr, "figure;\n");
  fprintf (fptr, "subplot(2,1,1);\n");
  fprintf (fptr, "  plot(t,real(x),'-','Color',[1 1 1]*0.5,'LineWidth',1,...\n");
  fprintf (fptr, "       t,real(y),'-','Color',[0 0.5 0.25],'LineWidth',2);\n");
  fprintf (fptr, "  xlabel('time');\n");
  fprintf (fptr, "  ylabel('real');\n");
  fprintf (fptr, "  legend('input','filtered output','location','northeast');\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "subplot(2,1,2);\n");
  fprintf (fptr, "  plot(t,imag(x),'-','Color',[1 1 1]*0.5,'LineWidth',1,...\n");
  fprintf (fptr, "       t,imag(y),'-','Color',[0 0.25 0.5],'LineWidth',2);\n");
  fprintf (fptr, "  xlabel('time');\n");
  fprintf (fptr, "  ylabel('imag');\n");
  fprintf (fptr, "  legend('input','filtered output','location','northeast');\n");
  fprintf (fptr, "  grid on;\n");

  // plot frequency response
  fprintf (fptr, "f=0.5*[0:(nfft-1)]/nfft;\n");
  fprintf (fptr, "figure;\n");
  fprintf (fptr, "subplot(3,1,1);\n");
  fprintf (fptr, "  plot(f,20*log10(abs(H)),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  //fprintf (fptr, "  plot(f, abs(H), 'Color', [0 0.25 0.5], 'LineWidth', 2);\n");
  //fprintf (fptr, "  axis([0 0.5 -3 0]);\n");
  fprintf (fptr, "  axis([0 0.2 -3 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Pass band [dB]');\n");
  fprintf (fptr, "subplot(3,1,2);\n");
  fprintf (fptr, "  plot(f,20*log10(abs(H)),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  //fprintf (fptr, "  axis([0 0.5 -100 0]);\n");
  fprintf (fptr, "  axis([0 0.2 -100 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Stop band [dB]');\n");
  fprintf (fptr, "subplot(3,1,3);\n");
  fprintf (fptr, "  plot(f,180/pi*arg(H),'Color',[0 0.25 0.5],'LineWidth',2);\n");
  //fprintf(fptr,"  axis([0 0.5 -100 0]);\n");
  fprintf (fptr, "  grid on;\n");
  fprintf (fptr, "  ylabel('Phase [degrees]');\n");
  fprintf (fptr, "  xlabel('Normalized Frequency [f/F_s]');\n");
  fclose (fptr);
}
