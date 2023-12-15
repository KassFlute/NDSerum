#include "sound.h"
#include "saw_wave.h"
#include <stdio.h>

void SawFill(void* array, int frequency, int* length){

	short * newArray = (short *) array;

	int periodSampleNumber = SAMPLERATE / frequency;

	*length = periodSampleNumber;

	double slope = (2*MAXVALUE) / (double) (periodSampleNumber-1);

	double currentValue = MINVALUE;

	for(int i = 0 ; i < periodSampleNumber ; i++){

		newArray[i] = (short)currentValue;

		currentValue += slope;
	}


}
