# ms2filter
Get a miniSEED record, filter with bandpass, then output.

# Dependencies
- FFTW 3.x (optimal)
- liquid-dsp

# Usage
```
$ ./ms2filter 
Usage: ./ms2filter [c1] [c2] [order] [passes] [input] [output]

Input parameters:
c1: low cut frequency (Hz)
c2: high cut frequency (Hz)
order: filter order
passes: set '1' for forward filtering or set '2' for forward-backward filtering
input: a miniSEED seismic record
output: a text file containing filtered result (read and imaginary part)

Output files: 
1. A MATLAB script to plot the input and filter result.
2. A text file containing filtered result (real and imaginary part).
3. A filted miniSEED record (real part only).
```
