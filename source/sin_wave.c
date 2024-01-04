#include "sin_wave.h"
#include <stdio.h>

void SinFill(int16_t *array, int frequency, int *length){
    /*
     * Fill the array with a sin wave of the given frequency
     * @param array : the array to fill
     * @param frequency : the frequency of the sin wave
     * @param length : pointer to write the number of samples written in the array
     */
    int nPeriod = NPeriodFromFrequency(frequency);

    double samplesPerPeriod = SAMPLERATE/ (double) frequency;

    int sampleNumber = samplesPerPeriod * nPeriod;

    double angleStep = (double) 360 * nPeriod / sampleNumber ;

    for(int i = 0 ; i < sampleNumber ; i++){

    	double  x = i * angleStep;

        short sample = (short) (MAXVALUE * sin( M_PI * x / (double)180));

        array[i] = sample;
    }
    *length = sampleNumber;
}
