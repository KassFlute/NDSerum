#include "saw_wave.h"

#include <stdio.h>

void SawFill(int16_t* array, int frequency, float amplitude, int phase, int* length ){

	//Length of the array
	int sampleNumber = SAMPLERATE/ (double) frequency;

	//Length overwritten
	*length = sampleNumber;

	//Range determination
	double range = MAXVALUE * amplitude;

	//Slope of the sinwave determination
	double slope = (2*range) / sampleNumber;

	double y;
	int actualPeriod;

	// Calculate the phase offset in samples
	int phaseOffset = (int)( (360- phase) / 360.0 * sampleNumber) % sampleNumber;

	for (int i = 0; i < sampleNumber; i++) {

		//index with the phase offset
		int adjustedIndex = (i + phaseOffset) % sampleNumber;

		actualPeriod = adjustedIndex / sampleNumber;

		y = adjustedIndex * slope - (actualPeriod * 2 * range);

		int16_t finalY = (int16_t)y - range;
		array[i] = finalY;
	}
}
