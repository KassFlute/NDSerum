#include "sound.h"
#include <stdio.h>

void SawWave(double slope,double samplesPerPeriod, int x, int16_t* array);

//Fills the array passed as argument with samples and then writes it's length in the int passed as argument

void SawFill(int16_t* array, int sampleNumber, int* length );
