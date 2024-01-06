#include "white_noise.h"

#include <stdio.h>

void WhiteNoiseFill(int16_t* array, int frequency, float amplitude, int phase, int* length){
	/*
	 * Fill the array with a white noise of the given frequency
	 * @param array : the array to fill
	 * @param frequency : the frequency of the white noise
	 * @param length : pointer to write the number of samples written in the array
	*/
	int sampleNumber = 4800;

	for(int i = 0 ; i < sampleNumber; i++){
			short randomShort = rand() % MAXVALUE*2 - MAXVALUE; // Generate a random short
			array[i] = (short) (amplitude * randomShort); // Add the random short to the array
		}
	*length = sampleNumber;
}
