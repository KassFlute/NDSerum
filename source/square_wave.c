#include "square_wave.h"
#include "sound.h"

#include <stdio.h>

void SquareFill(int16_t* array, int actualFrequency, int* length ){

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin

	double samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin

	int sampleNumber = samplesPerPeriod * nPeriod ; // Quentin

	*length = sampleNumber;

	int counter = 0;

	int top = 0;

	for(int i = 0 ; i< sampleNumber ; i++){

		 top = (int)(i / (samplesPerPeriod /  2)) % 2;

		if(top){
			array[i] = MAXVALUE;
			counter++;
		}if(!top){
			array[i] = MINVALUE;
			counter++;
		}
	}


}
