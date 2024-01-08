#include <stdio.h>

#include "sound.h"

/*
 * Fill the array with a square wave of the given frequency, amplitude and phase
 * @param array : array where samples will be written
 * @param frequency : the frequency of the square wave
 * @param amplitude : the amplitude of the square wave
 * @param phase : the phase of the square wave
 * @param length : pointer to write the number of samples written in the array
 */
void SquareFill(int16_t* array, int frequency, float amplitude, int phase, int* length );
