#include "square_wave.h"
#include "sound.h"

#include <stdio.h>

void SquareFill(int16_t* array, int actualFrequency, float amplitude, int phase, int* length ){

	int sampleNumber= SAMPLERATE/ (double) actualFrequency;

	*length = sampleNumber;

	int top = 0;

	short range = (short) (MAXVALUE * amplitude);

	// Calculate the phase offset in samples
	int phaseOffset = (int)( (360- phase) / 360.0 * sampleNumber) % sampleNumber;

	for(int i = 0 ; i< sampleNumber ; i++) {

		int adjustedIndex = (i + phaseOffset) % sampleNumber;

		int top = (int)(adjustedIndex / (sampleNumber/ 2.0) ) % 2;


		if(top){
			array[i] = range;
		} else {
			array[i] = -range;
		}
	}
}
