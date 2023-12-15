#include "sound.h"
#include "white_noise.h"

void WhiteNoiseFill(void* array, int frequency, int* length){

	int nPeriod = NPeriodFromFrequency(frequency);

	short * newArray = (short *) array;

	int sampleNumber = SAMPLERATE / frequency * (nPeriod) ;

	for(int i = 0 ; i < sampleNumber ; i++){

			newArray[i] = (short) rand();
		}



}
