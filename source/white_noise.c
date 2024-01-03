#include "white_noise.h"

void WhiteNoiseFill(int16_t* array, int frequency, int* length){
	/*
	 * Fill the array with a white noise of the given frequency
	 * @param array : the array to fill
	 * @param frequency : the frequency of the white noise
	 * @param length : pointer to write the number of samples written in the array
	*/
	int nPeriod = NPeriodFromFrequency(frequency);
	int sampleNumber = SAMPLERATE / frequency * (nPeriod);
	*length = sampleNumber;
	for(int i = 0 ; i < sampleNumber ; i++){

			array[2*i] = (short) rand();
			array[2*i + 1] = (short) rand();

		}
}
