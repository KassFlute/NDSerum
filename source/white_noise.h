#include "sound.h"

/*
 * Fill the array with white noise of the given amplitude and phase
 * @param array : array where samples will be written
 * @param frequency : the frequency of the square wave (not used)
 * @param amplitude : the amplitude of the white noise
 * @param phase : the phase of the white noise (not used)
 * @param length : pointer to write the number of samples written in the array
*/
void WhiteNoiseFill(int16_t* array, int frequency, float amplitude, int phase, int* length);
