#include "sound.h"
#include "white_noise.h"


void WhiteNoiseFill(int16_t* array, int frequency, mm_word* length){

	int nPeriod = NPeriodFromFrequency(frequency);
	int sampleNumber = SAMPLERATE / frequency * (nPeriod);

	*length = sampleNumber;

	for(int i = 0 ; i < sampleNumber ; i++){

			array[2*i] = (short) rand();
			array[2*i + 1] = (short) rand();

		}

}
