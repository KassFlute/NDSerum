#include "saw_wave.h"

#include <stdio.h>

void SawFill(int16_t* array, int actualFrequency, float amplitude, int phase, int* length ){


	int sampleNumber = SAMPLERATE/ (double) actualFrequency; // Quentin

	*length = sampleNumber;
	double range = MAXVALUE * amplitude;
	double slope = (2*range) / sampleNumber; // Quentin
	double y;
	int actualPeriod;

	// Calculate the phase offset in samples
	int phaseOffset = (int)( (360- phase) / 360.0 * sampleNumber) % sampleNumber;

	for (int i = 0; i < sampleNumber; i++) {

		int adjustedIndex = (i + phaseOffset) % sampleNumber;

		actualPeriod = adjustedIndex / sampleNumber;

		y = adjustedIndex * slope - (actualPeriod * 2 * range);

		int16_t finalY = (int16_t)y - range;
		array[i] = finalY;
	}
}
