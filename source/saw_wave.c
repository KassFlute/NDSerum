#include "saw_wave.h"

#include <stdio.h>

void SawWave(double slope, double samplesPerPeriod, int x, int16_t * array){
	double y;
	int actualPeriod;

	for(int i = 0 ; i < x; i++){

		actualPeriod = i / samplesPerPeriod;

		y = i * slope - (actualPeriod * 2 * MAXVALUE);

		int16_t finalY = (int16_t) y - MAXVALUE;

		array[i] = finalY;

	}
}

void SawFill(int16_t* array, int actualFrequency, int* length ){

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin

	double samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin

	int sampleNumber = samplesPerPeriod * nPeriod ; // Quentin

	*length = sampleNumber;

	printf("sample number: %d\n",sampleNumber);

	double slope = (2*MAXVALUE) / samplesPerPeriod; // Quentin

	SawWave(slope,samplesPerPeriod,sampleNumber,array);

}
