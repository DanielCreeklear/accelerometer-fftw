#include "filetxt.h"
#include "fft.h"
#include "fftfreq.h"

long long date, collectionTime;
string idSensor;
double samplingRate, inverseSamplingRate;
coordinates sensorValues;
coordinates fft_output;

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        readNameFile(argv[1],&date, &collectionTime, &idSensor);
        getDataTxt(argv[1], &sensorValues);
    }
    else
    {
        cout << "Please, pass the file path." << endl;
        return 0;
    }
    int sizeData = sensorValues.size();
    double *frequencys;

    frequencys = (double*)malloc(sizeof(double) * sizeData);

    samplingRate = double(long long(1000) * sizeData) / double(collectionTime);
    inverseSamplingRate = double(collectionTime) / double(long long(1000) * sizeData);

    fftfreq(frequencys, sizeData, inverseSamplingRate);
    fft(sizeData, sensorValues, &fft_output, collectionTime);

    exportData(fft_output, frequencys);

    free(frequencys);
    return 0;
}

