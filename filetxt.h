#ifndef FILETXT
#define FILETXT

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <math.h>

#define X get<0>
#define Y get<1>
#define Z get<2>

using namespace std;

typedef vector <tuple <double, double, double>> coordinates;

void readNameFile(char *filePath, long long* date, long long* collectionTime, string* idSensor);
void setValuesHeader(int *typeValue, string value, long long* date, long long* collectionTime, string* idSensor);
void getDataTxt(char *filePath, coordinates *sensorValues);
long getSizeFile(FILE *file);
bool copyDataFile(FILE *dataFile, char *buffer, long *sizeDataFile);
void readValues(coordinates *sensorValues, char *buffer, long *sizeDataFile);
void readValue(coordinates *sensorValues, double *tempValues, int *valuesColumn, char *buffer, int *startingPosition, int *endPosition);
void exportData(coordinates fft_data, double* frequencys);

#endif