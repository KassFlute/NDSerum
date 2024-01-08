#include "square_wave.h"

void SquareFill(int16_t* array, int frequency, float amplitude, int phase, int* length ){

	//length of the array
	int sampleNumber= SAMPLERATE/ (double) frequency;

	//length overwritten
	*length = sampleNumber;

	short range = (short) (MAXVALUE * amplitude);

	// Calculate the phase offset in samples
	int phaseOffset = (int)( (360- phase) / 360.0 * sampleNumber) % sampleNumber;

	for(int i = 0 ; i< sampleNumber ; i++) {

		//index with the offset taken into account
		int adjustedIndex = (i + phaseOffset) % sampleNumber;

		//Determine the sample value (top or bottom)
		int top = (int)(adjustedIndex / (sampleNumber/ 2.0) ) % 2;

		if(top){
			array[i] = range;
		} else {
			array[i] = -range;
		}
	}
}
