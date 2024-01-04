#include "white_noise.h"

#include <stdio.h>

void WhiteNoiseFill(int16_t* array, int frequency, int* length){
	/*
	 * Fill the array with a white noise of the given frequency
	 * @param array : the array to fill
	 * @param frequency : the frequency of the white noise
	 * @param length : pointer to write the number of samples written in the array
	*/
	int nPeriod = NPeriodFromFrequency(frequency);
	int sampleNumber = SAMPLERATE / (double) frequency * (nPeriod);
	*length = sampleNumber;

	for(int i = 0 ; i < sampleNumber ; i++){
			array[i] = (short) rand();
		}
}
