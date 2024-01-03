#include "sound.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

WaveType currentWaveType; 			 // Actual wave type
int actualFrequency;				 // Actual frequency of the sound
int isPlaying;						 // Is the sound playing

// Maxmod callback for the audio stream buffer filling
mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format) {
	if (length < 4800) return 0;

	if (!isPlaying) {
		memset(dest, 0, 4800*4);
		return 4800;
	}

	int16_t *target = dest;
	int samples_to_copy = main_buffer_length;
	for (int i = 0; i < samples_to_copy; i++)
	{
		// Deux à la suite parce que stereo earrape sur la nds
		*target++ = main_buffer[i];
		*target++ = main_buffer[i];
	}
	return samples_to_copy;
}

void InitSound() {
	/*
	 * Initialize the sound system
	 * @param main_buffer_ptr : pointer to the main buffer storing the sound
	 * @param main_buffer_length_ptr : pointer to the length of the main buffer
	 */

	// Set the sound system parameters
	actualFrequency = 50;
	currentWaveType = SAW_WAVE;
	isPlaying = 1;

	// Initialize the nds sound system
	mm_ds_system sys;
	sys.mod_count = 0;
	sys.samp_count = 0;
	sys.mem_bank = 0;
	sys.fifo_channel = FIFO_MAXMOD;
	mmInit(&sys);

	mm_stream *myStream = malloc(sizeof(mm_stream));
	myStream->sampling_rate = 48000;
	myStream->buffer_length = 9600;
	myStream->callback = OnStreamRequest;
	myStream->format = MM_STREAM_16BIT_STEREO;
	myStream->timer = MM_TIMER0;
	myStream->manual = 0;

	// Set the first wave to play
	FillBuffer();

	// Open the stream
	mmStreamOpen(myStream);
}

int NPeriodFromFrequency(int frequency) {
	/*
	 * Return the number of period of the wave to fill depending on the frequency
	 * @param frequency : the frequency of the wave
	 * @return the number of period of the wave to fill
	 */
	if(frequency < 10) return 1;
	if(frequency > 20000) return 2000;
	return frequency/10;
}

void FillBuffer() {
	/*
	 * Fill the main_buffer with the current wave type, frequency and amplitude
	 * @param frequency : the frequency of the wave
	 * @param waveType : the type of the wave
	 * @param amplitude : the amplitude of the wave
	 * @param main_buffer : the buffer to fill
	 * @param main_buffer_length : pointer to the number of sample the buffer will be filled with
	 */
	switch (currentWaveType)
	{
	case SAW_WAVE:
		SawFill(main_buffer, actualFrequency, &main_buffer_length);
		break;
	case SIN_WAVE:
		SinFill(main_buffer, actualFrequency, &main_buffer_length);
		break;
	case WHITE_NOISE:
		WhiteNoiseFill(main_buffer, actualFrequency, &main_buffer_length);
		break;
		// Add other cases for different wave types
	}
}

void PauseSound() {
	/*
	 * Pause the sound
	 */
	isPlaying = 0;
}

void ResumeSound() {
	/*
	 * Resume the sound
	 */
	isPlaying = 1;
}

void PauseResumeSound() {
	/*
	 * Pause or resume the sound depending on the current state
	 */
	isPlaying = !isPlaying;
}

int IsPlaying() {
	/*
	 * Return if the sound is playing
	 * @return 1 if the sound is playing, 0 otherwise
	 */
	return isPlaying;
}

void SetFrequency(int newFrequency) {
	/*
	 * Set the frequency of the wave
	 * @param newFrequency : the new frequency of the wave
	 */

	actualFrequency = MAX(MIN(newFrequency, 20000), 20);
	FillBuffer();
}

void IncrementFrequency10() {
	/*
	 * Increment the frequency of the wave by 10
	 */
	SetFrequency(actualFrequency + 10);
}

void DecrementFrequency10() {
	/*
	 * Decrement the frequency of the wave by 10
	 */
	SetFrequency(actualFrequency - 10);
}

int GetFrequency() {
	/*
	 * Return the frequency of the wave
	 * @return the frequency of the wave
	 */
	return actualFrequency;
}

void SetWaveType(WaveType newWaveType){
	/*
	 * Set the type of the wave
	 * @param newWaveType : the new type of the wave
	 */
	currentWaveType = newWaveType;
	FillBuffer();

}
void IncrementWaveType(){
	/*
	 * Increment the type of the wave
	 */
	currentWaveType = (currentWaveType + 1) % waveTypeCount;
	FillBuffer();
}

WaveType GetWaveType(){
	/*
	 * Return the type of the wave
	 * @return the type of the wave
	 */
	return currentWaveType;
}