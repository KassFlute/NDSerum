#include "saw_wave.h"

#include <stdio.h>

void SawFill(int16_t* array, int actualFrequency, float amplitude, int phase, int* length ){

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin
	double samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin
	int sampleNumber = samplesPerPeriod * nPeriod ; // Quentin

	*length = sampleNumber;
	double range = MAXVALUE * amplitude;
	double slope = (2*range) / samplesPerPeriod; // Quentin
	double y;
	int actualPeriod;

	for (int i = 0; i < sampleNumber; i++) {
		actualPeriod = i / samplesPerPeriod;
		y = i * slope - (actualPeriod * 2 * range);
		int16_t finalY = (int16_t)y - range;
		array[i] = finalY;
	}
}
