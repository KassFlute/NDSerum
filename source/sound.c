#include "sound.h"

#include <stdlib.h>
#include <stdio.h>

WaveType currentWaveType; 			 // Actual wave type
int actualFrequency;				 // Actual frequency of the sound
float actualAmplitude;				 // Actual amplitude of the sound
int actualPhase;					 // Actual phase of the sound
int isPlaying;						 // Is the sound playing
int actualArrayIndex;				 // Index of the buffer being written

mm_stream *myStream;				 // The audio stream

mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format) {

	int amount = (int) length;
	
	//Fill with 0s when we do not want to play sound
	if (!isPlaying) {
		memset(dest, 0, amount*4);
		actualArrayIndex = (actualArrayIndex + amount) % main_buffer_length;
		return length;
	}

	int16_t *target = dest;

	for (int i = 0; i < amount; i++)
	{
		//Write the actual sound samples
		*target++ = main_buffer[actualArrayIndex];
		*target++ = main_buffer[actualArrayIndex];
		actualArrayIndex = (actualArrayIndex + 1) % main_buffer_length;
	}

	return length;
}

void InitSound() {

	// Set the sound system parameters
	actualFrequency = 100;
	actualAmplitude = 0.5;
	actualPhase = 180;
	currentWaveType = SAW_WAVE;
	isPlaying = 1;

	// Initialize the nds sound system
	mm_ds_system sys;
	sys.mod_count = 0;
	sys.samp_count = 0;
	sys.mem_bank = 0;
	sys.fifo_channel = FIFO_MAXMOD;
	mmInit(&sys);

	myStream = malloc(sizeof(mm_stream));
	myStream->sampling_rate = SAMPLERATE;
	myStream->buffer_length = BUFFERLENGTH;
	myStream->callback = OnStreamRequest;
	myStream->format = MM_STREAM_16BIT_STEREO;
	myStream->timer = MM_TIMER0;
	myStream->manual = 0;

	// Set the first wave to play
	FillBuffer();

	// Open the stream
	mmStreamOpen(myStream);
}

void FillBuffer() {

	actualArrayIndex = 0;

	switch (currentWaveType)
	{
	case SAW_WAVE:
		SawFill(main_buffer, actualFrequency, actualAmplitude, actualPhase, &main_buffer_length);
		break;
	case SIN_WAVE:
		SinFill(main_buffer, actualFrequency, actualAmplitude, actualPhase, &main_buffer_length);
		break;
	case WHITE_NOISE:
		WhiteNoiseFill(main_buffer, actualFrequency, actualAmplitude, actualPhase, &main_buffer_length);
		break;
	case SQUARE_WAVE:
		SquareFill(main_buffer, actualFrequency, actualAmplitude, actualPhase, &main_buffer_length);
		break;
	}
}

void PauseSound() {

	isPlaying = 0;
}

void ResumeSound() {

	isPlaying = 1;
}

void PauseResumeSound() {

	isPlaying = !isPlaying;
}

int IsPlaying() {

	return isPlaying;
}

void SetFrequency(int newFrequency) {

	actualFrequency = MAX(MIN(newFrequency, MAXFREQ), MINFREQ);
}

void IncrementFrequency() {

	SetFrequency(actualFrequency + 1);
}

void DecrementFrequency() {

	SetFrequency(actualFrequency - 1);
}

void IncrementFrequency10() {

	SetFrequency(actualFrequency + 10);
}

void DecrementFrequency10() {

	SetFrequency(actualFrequency - 10);
}

int GetFrequency() {

	return actualFrequency;
}

void SetAmplitude(float newAmplitude) {

	actualAmplitude = MAX(MIN(newAmplitude, 1), 0);
}

float GetAmplitude() {

	return actualAmplitude;
}

void SetPhase(int newPhase) {

	actualPhase = MAX(MIN(newPhase, 360), 0);
}

void IncrementPhase() {

	SetPhase(actualPhase + 1);
}

void DecrementPhase() {

	SetPhase(actualPhase - 1);
}

void IncrementPhase10() {

	SetPhase(actualPhase + 10);
}

void DecrementPhase10() {

	SetPhase(actualPhase - 10);
}

int GetPhase() {

	return actualPhase;
}

void SetWaveType(WaveType newWaveType){

	currentWaveType = newWaveType;
}
void IncrementWaveType(){

	currentWaveType = (currentWaveType + 1) % waveTypeCount;
}

void DecrementWaveType(){

	if (currentWaveType == 0) {
		currentWaveType = waveTypeCount - 1;
	} else {
		currentWaveType -= 1;
	}
}

WaveType GetWaveType(){

	return currentWaveType;
}
