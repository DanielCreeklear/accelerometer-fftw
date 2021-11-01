#ifndef FFT
#define FFT

#include <vector>
#include <tuple>
#include <fftw3.h>
#include "fftfreq.h"

using namespace std;

#define X get<0>
#define Y get<1>
#define Z get<2>
#define REAL 0
#define IMAG 1

typedef vector <tuple <double, double, double>> coordinates;

void fft(int sizeData, coordinates input, coordinates* output, double collectionTime);

#endif