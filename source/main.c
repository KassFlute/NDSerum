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
#include "sub_screen.h" // Mystique 1

// Uncomment the following line to enable debug mode
//#define DEBUG

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
int main_buffer_length;	   // main buffer length (in samples)

int sub_screen_mode = 0; // 0 = controls, 1 = drawing

int fader_width = 16; // Width of the faders in pixels
int freq_fader_start = 8; // Start of the volume fader in pixels
int ampp_fader_start = 32; // Start of the amplitude fader in pixels

int main(void) {

	InitSound(); // Initialize the sound system
	#ifdef DEBUG
		printf("Sound system initialized.\n");
	#endif

	InitMainScreen();
	InitSubScreen();

	#ifdef DEBUG
		consoleDemoInit();
		printf("\nNDSerum\n");
		printf("Debug mode is on.\n");
	#endif


	REG_KEYCNT = (1<<14) | KEY_UP | KEY_DOWN | KEY_START | KEY_A;

	DrawWaveMain(main_buffer, main_buffer_length);

    while(1){
    	scanKeys();
		unsigned keys = keysDown();
		if(keys == KEY_X) {
			IncrementFrequency10();
			SetFreqFader(GetFrequency());
			printf("Frequency: %d\n", GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if (keys == KEY_A) {
			PauseResumeSound();
			printf("Playing: %d\n", IsPlaying());
		}
		if(keys == KEY_B) {
			DecrementFrequency10();
			SetFreqFader(GetFrequency());
			printf("Frequency: %d\n", GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if(keys == KEY_START) {
			IncrementWaveType();
			printf("Wave type: %d\n", GetWaveType());
			DrawWaveMain(main_buffer, main_buffer_length);
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

		// Touch screen
		keys = keysHeld();
		if (keys & KEY_TOUCH) {
			touchPosition touch;
			touchRead(&touch);
			if (touch.px || touch.py) {
				// Frequency fader
				if (touch.px >= freq_fader_start && touch.px <= freq_fader_start + fader_width) {
					printf("Touch: %d, %d\n", touch.px, touch.py);
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					int newFrequency = (((186-touchY) * 980) / 186) + 20;
					printf("New frequency: %d\n", newFrequency);
					newFrequency = newFrequency -  (newFrequency % 10); // Round to the nearest 10 because some freq don't work
					if (newFrequency != GetFrequency()){
						SetFrequency(newFrequency);
						printf("Frequency: %d\n", GetFrequency());
						SetFreqFader(GetFrequency());
						DrawWaveMain(main_buffer, main_buffer_length);
					}
				}

				if (touch.px >= ampp_fader_start && touch.px <= ampp_fader_start + fader_width) {
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					float newAmplitude = ((float)(186-touchY)) / 186;
					if (newAmplitude != GetAmplitude()){
						SetAmplitude(newAmplitude);
						SetAmplitudeFader(GetAmplitude());
						DrawWaveMain(main_buffer, main_buffer_length);
					}
				}
			}
		}
		swiWaitForVBlank();
    }
}
