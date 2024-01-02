/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "sound.h"
#include "white_noise.h"
#include "saw_wave.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int actualFrequency; // Actual frequency of the sound
double slope; // Quentin
double samplesPerPeriod; // Quentin
int sampleNumber; // Quentin
int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
int main_buffer_length; // à passer au méthode de remplissage pour quelle disent combien elles ont écrit (en bytes)

void keys_ISR() {
	printf("KEYS\n");
	actualFrequency += 100;

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin

	samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin

	sampleNumber = samplesPerPeriod  * nPeriod; // Quentin

	slope = (2*MAXVALUE) / samplesPerPeriod; // Quentin

	SawWave(slope, samplesPerPeriod,sampleNumber,current); // Quentin à appeller dans saw_wave.c
}


mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format){

	int16_t* array = dest; // Quentin
	mm_word tempLen = sampleNumber; // Quentin
	SawFill(array,sampleNumber,current); // à appeller uniquement quand un parametre change



	// should only do this
	int samples_to_copy = main_buffer_length;
	for (int i = 0; i < samples_to_copy; i++) {
		// Deux à la suite parce que stereo earrape sur la nds
		dest++ = current[i];
		dest++ = current[i];
	}
	return main_buffer_length;
}

int main(void) {
	
    consoleDemoInit();

    printf("\nNDSerum\n");

    mm_ds_system sys;
   	sys.mod_count = 0;
   	sys.samp_count = 0;
   	sys.mem_bank = 0;
   	sys.fifo_channel = FIFO_MAXMOD;
   	mmInit(&sys);

   	mm_stream * myStream = malloc(sizeof(mm_stream));
	myStream->sampling_rate = 48000;
	myStream->buffer_length = 1200;
	myStream->callback = OnStreamRequest;
	myStream->format = MM_STREAM_16BIT_STEREO;
	myStream->timer = MM_TIMER0;
	myStream->manual = 0;

	REG_KEYCNT = (1<<14) | KEY_UP | KEY_DOWN | KEY_START | KEY_A;

	irqSet(IRQ_KEYS,&keys_ISR);
	irqEnable(IRQ_KEYS);

	actualFrequency = 440;

	int nPeriod = NPeriodFromFrequency(actualFrequency); // Quentin
	samplesPerPeriod = SAMPLERATE/ (double) actualFrequency; // Quentin
	sampleNumber = samplesPerPeriod * nPeriod ; // Quentin
	slope = (2*MAXVALUE) / samplesPerPeriod; // Quentin
	SawWave(slope, samplesPerPeriod,sampleNumber,current); // Quentin à appeller dans saw_wave.c

	mmStreamOpen(myStream);

    while(1){
		swiWaitForVBlank();
    }
}
