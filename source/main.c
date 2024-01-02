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

int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)

int main_buffer_length; // à passer au méthode de remplissage pour quelle disent combien elles ont écrit (en bytes)

mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format){
	// should only do this

	int targetlength = length;

	printf("target length: %d\n",targetlength);

	int16_t * target = dest;
	int samples_to_copy = main_buffer_length;
	for (int i = 0; i < samples_to_copy; i++) {
		// Deux à la suite parce que stereo earrape sur la nds
		*target++ = main_buffer[i];
		*target++ = main_buffer[i];
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

	actualFrequency = 440;

	SawFill(main_buffer,actualFrequency,&main_buffer_length);

	mmStreamOpen(myStream);

    while(1){
    	scanKeys();
		unsigned keys = keysDown();
		if(keys == KEY_UP){
			printf("UP\n");
			actualFrequency += 100;
			SawFill(main_buffer,actualFrequency,&main_buffer_length); // Quentin à appeller dans saw_wave.c
		}if(keys == KEY_DOWN){
			printf("DOWN\n");
			actualFrequency -= 100;
			SawFill(main_buffer,actualFrequency,&main_buffer_length); // Quentin à appeller dans saw_wave.c
		}
		swiWaitForVBlank();
    }
}
