# ms2filter
Get a miniSEED record, filter with bandpass, then output.

# Dependencies
- FFTW 3.x
- liquid-dsp

# Usage
```
$ ./ms2filter 
Usage: ./ms2filter <c1> <c2> <input> <output>

Input parameters:
c1: low cut frequency (Hz)
c2: high cut frequency (Hz)
input: a miniSEED seismic record
output: a text file containing filtered result (read and imaginary part)

Output format: 
1. A MATLAB script to plot the input and filter result.
2. A text file containing filtered result (real and imaginary part).
```
