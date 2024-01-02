#include "sound.h"
#include "saw_wave.h"
#include <stdio.h>





void SawWave(double slope, double samplesPerPeriod, int x, int16_t * array){


	double y;
	int actualPeriod;

	for(int i = 0 ; i < x; i++){

		actualPeriod = i / samplesPerPeriod;

		y = i * slope - (actualPeriod * 2 * MAXVALUE);
		y = y - MAXVALUE;

		array[i] = y;

	}
}


void SawFill(int16_t* array, int sampleNumber, int16_t* current ){

	for(int i = 0 ; i < sampleNumber ; i++){

		array[2*i] = current[i];
		array[2*i + 1] = current[i];

	}


}
