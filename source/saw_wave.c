#include "sound.h"
#include "saw_wave.h"

void SawFill(void* array, int frequency, int* length){

	short * newArray = (short *) array;

	int periodSampleNumber = SAMPLERATE / frequency;

	*length = periodSampleNumber;

	double slope = ((MAXVALUE - MINVALUE)/ (double) MAXVALUE) / (double) periodSampleNumber;

	short shortSlope = slope * MAXVALUE;

	short currentValue = MINVALUE;

	for(int i = 0 ; i < periodSampleNumber ; i++){

		newArray[i] = currentValue;

		currentValue += shortSlope;
	}


}
