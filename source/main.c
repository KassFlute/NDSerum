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
#include "timer_muter.h"

// Uncomment the following line to enable debug mode
//#define DEBUG

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
int main_buffer_length;	   // main buffer length (in samples)

int sub_screen_mode = 0; // 0 = controls, 1 = drawing

int fader_width = 16; // Width of the faders in pixels
int freq_fader_start = 8; // Start of the volume fader in pixels
int amp_fader_start = 32; // Start of the amplitude fader in pixels
int phase_fader_start = 56; // Start of the phase fader in pixels

int wasCalled = 0;

void keys_ISR() {
	printf("Interrupt\n");
	u16 keys = ~(REG_KEYINPUT);
	if (keys & KEY_A) {
		printf("A\n");
		PauseResumeSound();
	}
	if (keys & KEY_B) {
		printf("B\n");
		DecrementFrequency();
		SetFreqFader(GetFrequency());
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_L) {
		printf("L\n");
		DecrementPhase10();
		SetPhaseFader(GetPhase());
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_R) {
		printf("R\n");
		IncrementPhase10();
		SetPhaseFader(GetPhase());
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_UP) {
		printf("UP\n");
		ZoomIn();
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_DOWN) {
		printf("DOWN\n");
		ZoomOut();
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_LEFT) {
		printf("LEFT\n");
		DecrementWaveType();
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_RIGHT) {
		printf("RIGHT\n");
		IncrementWaveType();
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}

	// keys = ~(REG_KEYXY);
	// if (keys & KEY_X)
	// {
	// 	printf("X\n");
	// }
	// if (keys & KEY_Y)
	// {
	// 	printf("Y\n");
	// }
}

int main(void) {
	InitSound(); // Initialize the sound system
	#ifdef DEBUG
		printf("Sound system initialized.\n");
	#endif

	InitMainScreen();
	InitSubScreen();

	//irqInit();
	REG_KEYCNT = (1 << 14) | KEY_A | KEY_B | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN;
	irqSet(IRQ_KEYS, &keys_ISR);
	irqEnable(IRQ_KEYS);

	InitTimer();

	#ifdef DEBUG
		consoleDemoInit();
		printf("\nNDSerum\n");
		printf("Debug mode is on.\n");
	#endif

	DrawWaveMain(main_buffer, main_buffer_length);

    while(1){

    	// Old controls wihout interupt
    			// if(keys == KEY_X) {
    			// 	IncrementFrequency10();
    			// 	SetFreqFader(GetFrequency());
    			// 	printf("Frequency: %d\n", GetFrequency());
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if (keys == KEY_Y) {
    			// 	EnableDisableMuter();
    			// }
    			// if (keys == KEY_A) {
    			// 	PauseResumeSound();
    			// 	printf("Playing: %d\n", IsPlaying());
    			// }
    			// if(keys == KEY_B) {
    			// 	DecrementFrequency10();
    			// 	SetFreqFader(GetFrequency());
    			// 	printf("Frequency: %d\n", GetFrequency());
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if(keys == KEY_START) {
    			// 	IncrementWaveType();
    			// 	printf("Wave type: %d\n", GetWaveType());
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if(keys == KEY_RIGHT) {
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if(keys == KEY_LEFT) {
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if(keys == KEY_UP) {
    			// 	ZoomIn();
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }
    			// if(keys == KEY_DOWN) {
    			// 	ZoomOut();
    			// 	DrawWaveMain(main_buffer, main_buffer_length);
    			// }

    	scanKeys();
		unsigned keys = keysDown();

		if (keys == KEY_X) {
			printf("X\n");
			IncrementFrequency();
			SetFreqFader(GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if (keys == KEY_Y) {
			printf("Y\n");
			EnableDisableMuter();
		}

		// Touch screen
		scanKeys();
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
					//newFrequency = newFrequency -  (newFrequency % 10); // Round to the nearest 10 because some freq don't work
					if (newFrequency != GetFrequency()){
						SetFrequency(newFrequency);
						SetFreqFader(GetFrequency());
						DrawWaveMain(main_buffer, main_buffer_length);
					}
				}

				// Amplitude fader
				if (touch.px >= amp_fader_start && touch.px <= amp_fader_start + fader_width) {
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					float newAmplitude = ((float)(186-touchY)) / 186;
					if (newAmplitude != GetAmplitude()){
						SetAmplitude(newAmplitude);
						SetAmplitudeFader(GetAmplitude());
						DrawWaveMain(main_buffer, main_buffer_length);
					}
				}

				// Phase fader
				if (touch.px >= phase_fader_start && touch.px <= phase_fader_start + fader_width) {
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					int newPhase = ((186-touchY) * 360) / 186;
					if (newPhase != GetPhase()){
						SetPhase(newPhase);
						SetPhaseFader(GetPhase());
						DrawWaveMain(main_buffer, main_buffer_length);
					}
				}
			}
		}
		if(wasCalled){
			irqDisable(IRQ_KEYS);
			irqDisable(IRQ_TIMER1);
			DrawWaveMain(main_buffer, main_buffer_length);
			wasCalled = 0;
			irqEnable(IRQ_KEYS);
			irqEnable(IRQ_TIMER1);

		}


		swiWaitForVBlank();
    }
}
