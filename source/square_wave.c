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
		if(top){
			array[i] = MAXVALUE;
			counter++;
		}if(!top){
			array[i] = MINVALUE;
			counter++;
		}
		if(counter > (samplesPerPeriod / (double) 2)){
			counter = 0;
			top = (top + 1) % 2;
		}

		//printf("%d\n",array[i]);

	}


}
