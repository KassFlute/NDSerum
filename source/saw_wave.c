#include "sound.h"
#include "saw_wave.h"

void SawFill(void* array, int frequency, int* length){

	int periodSampleNumber = SAMPLERATE / frequency;

	*length = periodSampleNumber;

	//int slope = (valMax - valMin) / periodSampleNumber;

	//int currentValue = valMin;

	for(int i = 0 ; i < periodSampleNumber ; i++){

		//array[i] = currentValue;

		//currentValue += slope;
	}


}
