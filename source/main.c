/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "sound.h"
#include "white_noise.h"
#include "saw_wave.h"

int actualFrequency;
double slope;
double samplesPerPeriod;
int sampleNumber;
int16_t current[SAMPLERATE *10] = {0};

void keys_ISR() {
	printf("KEYS\n");
	actualFrequency += 100;

	int nPeriod = NPeriodFromFrequency(actualFrequency);

	samplesPerPeriod = SAMPLERATE/ (double) actualFrequency;

	sampleNumber = samplesPerPeriod  * nPeriod;

	slope = (2*MAXVALUE) / samplesPerPeriod;

	SawWave(slope, samplesPerPeriod,sampleNumber,current);
}


mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format){

	int16_t* array = dest;

	mm_word tempLen = sampleNumber;

	SawFill(array,sampleNumber,current);

	return tempLen;
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

	int nPeriod = NPeriodFromFrequency(actualFrequency);

	samplesPerPeriod = SAMPLERATE/ (double) actualFrequency;

	sampleNumber = samplesPerPeriod * nPeriod ;

	slope = (2*MAXVALUE) / samplesPerPeriod;

	SawWave(slope, samplesPerPeriod,sampleNumber,current);

	mmStreamOpen(myStream);

    while(1){

		swiWaitForVBlank();
    }
}
