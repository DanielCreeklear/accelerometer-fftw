#include "fft.h"

void fft(int sizeData, coordinates input, coordinates* output, double collectionTime)
{
    double samplingRate, inverseSamplingRate;

    fftw_complex* inputDataX;
    fftw_complex* inputDataY;
    fftw_complex* inputDataZ;
    fftw_complex* outputDataX;
    fftw_complex* outputDataY;
    fftw_complex* outputDataZ;

    inputDataX = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);
    inputDataY = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);
    inputDataZ = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);
    outputDataX = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);
    outputDataY = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);
    outputDataZ = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sizeData);

    int i = 0;
    for (auto& data : input)
    {
        inputDataX[i][REAL] = X(data);
        inputDataY[i][REAL] = Y(data);
        inputDataZ[i][REAL] = Z(data);
        inputDataX[i][IMAG] = 0;
        inputDataY[i][IMAG] = 0;
        inputDataZ[i][IMAG] = 0;
        i++;
    }

    fftw_plan plan;

    // X
    plan = fftw_plan_dft_1d(sizeData, inputDataX, outputDataX, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();

    // Y
    plan = fftw_plan_dft_1d(sizeData, inputDataY, outputDataY, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();

    // Z
    plan = fftw_plan_dft_1d(sizeData, inputDataZ, outputDataZ, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();

    for (i = 0; i < sizeData; i++)
    {
        (*output).push_back(make_tuple(outputDataX[i][REAL], outputDataY[i][REAL], outputDataZ[i][REAL]));
    }

    fftw_free(inputDataX);
    fftw_free(inputDataY);
    fftw_free(inputDataZ);
    fftw_free(outputDataX);
    fftw_free(outputDataY);
    fftw_free(outputDataZ);
}