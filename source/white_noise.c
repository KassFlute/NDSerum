#include "white_noise.h"

#include <stdio.h>

void WhiteNoiseFill(int16_t* array, int frequency, float amplitude, int phase, int* length){

	//length of the array
	int sampleNumber = 4800;

	//length overwritten
	*length = sampleNumber;

	for(int i = 0 ; i < sampleNumber; i++){
			// Generate a random short
			short randomShort = rand() % MAXVALUE*2 - MAXVALUE;
			// Add the random short to the array
			array[i] = (short) (amplitude * randomShort);
		}

}
