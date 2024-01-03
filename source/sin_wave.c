#include "sin_wave.h"

void SinFill(int16_t *array, int frequency, int *length){
    /*
     * Fill the array with a sin wave of the given frequency
     * @param array : the array to fill
     * @param frequency : the frequency of the sin wave
     * @param length : pointer to write the number of samples written in the array
     */
    int nPeriod = NPeriodFromFrequency(frequency);
    int sampleNumber = SAMPLERATE / frequency * (nPeriod);
    for(int i = 0 ; i < sampleNumber ; i++){
        int x = frequency * i / SAMPLERATE;
        short sample = (short) (MAXVALUE * sin(2 * M_PI * x));
        array[2*i] = sample;
        array[2*i + 1] = sample;
    }
    *length = sampleNumber;
}