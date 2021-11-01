#include "filetxt.h"

void readNameFile(char* filePath, long long* date, long long* collectionTime, string* idSensor)
{
    string filePathString = filePath;
    int sizeString = filePathString.size();
    int a = 0, b, typeValue = 0;
    for (b = 0; b < sizeString; b++)
    {
        string value;
        switch (filePathString[b])
        {
        case '-':
            for (a; a < b; a++)
            {
                value.push_back(filePathString[a]);
            }
            setValuesHeader(&typeValue, value, date, collectionTime, idSensor);
            a++;
            typeValue++;
            break;
        case '.':
            for (a; a < b; a++)
            {
                value.push_back(filePathString[a]);

            }
            setValuesHeader(&typeValue, value, date, collectionTime, idSensor);
            a++;
            typeValue++;
            break;

        default:
            break;
        }
    }
}

void setValuesHeader(int* typeValue, string value, long long *date, long long *collectionTime, string *idSensor)
{
    switch (*typeValue)
    {
    case 0:
        *date = strtoll(value.c_str(), nullptr, 10);
        break;

    case 1:
        *collectionTime = strtoll(value.c_str(), nullptr, 10);
        break;

    case 2:
        *idSensor = value;
        break;

    default:
        break;
    }

}

void getDataTxt(char* filePath, coordinates *sensorValues)
{
    FILE* dataFile;
    char* buffer;
    long sizeDataFile;

    fopen_s(&dataFile, filePath, "r");

    if (dataFile == NULL)
    {
        cout << "File error." << endl;
    }

    sizeDataFile = getSizeFile(dataFile);

    buffer = (char*)malloc(sizeof(char) * sizeDataFile);

    if (!copyDataFile(dataFile, buffer, &sizeDataFile))
    {
        cout << "Error on copy file." << endl;
    }

    readValues(sensorValues, buffer, &sizeDataFile);
    free(buffer);
}

long getSizeFile(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long sizeDataFile = ftell(file);
    rewind(file);
    return sizeDataFile;
}

bool copyDataFile(FILE* dataFile, char* buffer, long* sizeDataFile)
{

    size_t result = fread(buffer, 1, *sizeDataFile, dataFile);

    if (result != *sizeDataFile)
    {
        fputs("Reading error", stderr);
        return false;
    }
    else
    {
        return true;
    }
}

void readValues(coordinates *sensorValues, char* buffer, long* sizeDataFile)
{
    int a = 0, valuesColumn = 0;
    double tempValues[3];

    for (int b = 0; b < *sizeDataFile; b++)
    {
        switch (buffer[b])
        {
        case ',':
            readValue(sensorValues, tempValues, &valuesColumn, buffer, &a, &b);
            break;

        case '\n':
            readValue(sensorValues, tempValues, &valuesColumn, buffer, &a, &b);
            break;

        default:
            break;
        }
    }

}

void readValue(coordinates *sensorValues, double* tempValues, int* valuesColumn, char* buffer, int* startingPosition, int* endPosition)
{
    char* tempArray;
    tempArray = (char*)malloc(sizeof(char) * (*endPosition - *startingPosition));

    int i = 0;
    for (*startingPosition; *startingPosition < *endPosition; (*startingPosition)++)
    {
        tempArray[i] = buffer[*startingPosition];
        i++;
    }

    double num = atof(tempArray);
    tempValues[*valuesColumn] = num;

    (*startingPosition)++;
    free(tempArray);

    if (*valuesColumn == 2)
    {
        *valuesColumn = 0;
        (*sensorValues).push_back(make_tuple(tempValues[0], tempValues[1], tempValues[2]));
    }
    else
    {
        (*valuesColumn)++;
    }
}

void exportData(coordinates fft_data, double* frequencys)
{
    int i = 0;
    ofstream out("output.txt");
    for (auto data : fft_data)
    {
        out << X(data) << ", " << Y(data) << ", " << Z(data) << ", " << frequencys[i] << endl;
        i++;
    }
    out.close();
}