#include "square_wave.h"
#include "sound.h"

#include <stdio.h>

void SquareFill(int16_t* array, int actualFrequency, float amplitude, int phase, int* length ){

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin
	double samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin
	int sampleNumber = samplesPerPeriod * nPeriod ; // Quentin

	*length = sampleNumber;
	int counter = 0;
	int top = 0;
	short range = (short) (MAXVALUE * amplitude);

	// Calculate the phase offset in samples
	int phaseOffset = (int)(phase / 360.0 * samplesPerPeriod) % (int)samplesPerPeriod;

	for(int i = 0 ; i< sampleNumber ; i++) {
		int adjustedIndex = (i - phaseOffset) % (int)samplesPerPeriod;
		int top = (int)(adjustedIndex / (samplesPerPeriod / 2)) % 2;

		if(top){
			array[i] = range;
			counter++;
		} else {
			array[i] = -range;
			counter++;
		}
	}
}
