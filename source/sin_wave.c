#include "sin_wave.h"
#include <stdio.h>

void SinFill(int16_t *array, int frequency, float amplitude, int phase, int *length){
    /*
     * Fill the array with a sin wave of the given frequency
     * @param array : the array to fill
     * @param frequency : the frequency of the sin wave
     * @param length : pointer to write the number of samples written in the array
     */
    int nPeriod = NPeriodFromFrequency(frequency);
    double samplesPerPeriod = SAMPLERATE / (double) frequency;
    int sampleNumber = samplesPerPeriod * nPeriod;

    double angleStep = (double) 360 * nPeriod / sampleNumber ;
    double angleOffset = (double) 360 * phase / 360;
    double x = -angleOffset;

    double range = MAXVALUE * amplitude;

    for(int i = 0 ; i < sampleNumber ; i++) {
    	x += angleStep;
        short sample = (short) (range * sin( M_PI * x / (double)180));
        array[i] = sample;
    }
    
    *length = sampleNumber;
}
