#include "fftfreq.h"

void fftfreq(double frequencys[], int samplesNumbers, double inverseSamplingRate)
{
	double val;
	int aux, N, * p1, * p2, maxP2;

	val = 1.0 / (samplesNumbers * inverseSamplingRate);
	N = ((samplesNumbers - 1) / 2) + 1.0;
	aux = -(samplesNumbers / 2);
	maxP2 = (aux * -1);

	p1 = (int*) malloc(sizeof(int) * N);
	p2 = (int*) malloc(sizeof(int) * maxP2);

	for (int i = 0; i < N; i++) p1[i] = i;
	for (int i = 0; i < maxP2; i++)
	{
		p2[i] = aux;
		aux++;
	}

	aux = 0;
	for (int i = 0; i < N; i++) frequencys[i] = p1[i];
	for (int i = N; i < samplesNumbers; i++)
	{
		frequencys[i] = p2[aux];
		aux++;
	}
	free(p1);
	free(p2);

	for (int i = 0; i < samplesNumbers; i++) frequencys[i] *= val;
}