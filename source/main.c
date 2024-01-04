/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "sound.h"
#include "main_screen.h"

// Uncomment the following line to enable debug mode
#define DEBUG

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
int main_buffer_length;	   // main buffer length (in samples)

int main(void) {

	#ifdef DEBUG
		consoleDemoInit();
		printf("\nNDSerum\n");
		printf("Debug mode is on.\n");
	#endif

	InitSound(); // Initialize the sound system

	#ifdef DEBUG
		printf("Sound system initialized.\n");
	#endif


	REG_KEYCNT = (1<<14) | KEY_UP | KEY_DOWN | KEY_START | KEY_A;

	InitMainScreen();
	DrawWaveMain(main_buffer, main_buffer_length);

    while(1){
    	scanKeys();
		unsigned keys = keysDown();
		if(keys == KEY_X) {
			IncrementFrequency10();
			printf("Frequency: %d\n", GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_B) {
			DecrementFrequency10();
			printf("Frequency: %d\n", GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_START) {
			IncrementWaveType();
			printf("Wave type: %d\n", GetWaveType());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_A) {
			PauseResumeSound();
			printf("Playing: %d\n", IsPlaying());
		}
		if(keys == KEY_RIGHT) {
			MoveRight();
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_LEFT) {
			MoveLeft();
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_UP) {
			ZoomIn();
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_DOWN) {
			ZoomOut();
			DrawWaveMain(main_buffer, main_buffer_length);
		}

		swiWaitForVBlank();
    }
}
