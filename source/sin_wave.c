#include "sin_wave.h"

void SinFill(int16_t *array, int frequency, float amplitude, int phase, int *length){

	//length of the array
    double sampleNumber = SAMPLERATE / (double) frequency;

    //Length overwritten
    *length = sampleNumber;

    double angleStep = (double) 360 / sampleNumber;

    double angleOffset = (double) 360 * phase / 360;
    double x = -angleOffset;

    double range = MAXVALUE * amplitude;

    for(int i = 0 ; i < sampleNumber ; i++) {
    	x += angleStep;

    	//Conversion from degrees to radians for the sin function
        short sample = (short) (range * sin( M_PI * x / (double)180));
        array[i] = sample;
    }
}
