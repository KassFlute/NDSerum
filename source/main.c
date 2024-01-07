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
#include "wifi_sync.h"

// Uncomment the following line to enable debug mode
//#define DEBUG

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
int main_buffer_length;	   // main buffer length (in samples)

bool sub_screen_mode = 0; // 0 = controls, 1 = drawing

int freq_fader_start = 8; // Start of the volume fader in pixels
int amp_fader_start = 32; // Start of the amplitude fader in pixels
int phase_fader_start = 56; // Start of the phase fader in pixels
int fader_width = 16;		// Width of all the faders in pixels
int wave_selector_start_x = 224; // Start of the wave selector in pixels (x)
int wave_selector_start_y = 8; // Start of the wave selector in pixels (y)
int wave_selector_width = 24; // Width of the wave selector in pixels
int wave_selector_height = 96; // Height of the wave selector in pixels
int mute_button_start_x = 224; // Start of the mute button in pixels (x)
int mute_button_start_y = 120; // Start of the mute button in pixels (y)
int mute_button_width = 24; // Width of the mute button in pixels
int mute_button_height = 24; // Height of the mute button in pixels
int gate_button_start_x = 184; // Start of the gate button in pixels (x)
int gate_button_start_y = 120; // Start of the gate button in pixels (y)
int gate_button_width = 24; // Width of the gate button in pixels
int gate_button_height = 24; // Height of the gate button in pixels
int gate_fader_start_x = 192; // Start of the gate fader in pixels (x)
int gate_fader_start_y = 8; // Start of the gate fader in pixels (y)
int gate_fader_length = 96; // Length of the gate fader in pixels

int wasCalled = 0;

void keys_ISR() {
	printf("Interrupt\n");
	u16 keys = ~(REG_KEYINPUT);
	if (keys & KEY_A) {
		printf("A\n");
		PauseResumeSound();
		SetMuteButton(!IsPlaying());
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
		SetWaveSelector(GetWaveType());
		//DrawWaveMain(main_buffer, main_buffer_length);
		wasCalled = 1;
	}
	if (keys & KEY_RIGHT) {
		printf("RIGHT\n");
		IncrementWaveType();
		SetWaveSelector(GetWaveType());
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

void wifi_receive(){
	// char byte_data_buff[2];
	// if (receiveData(byte_data_buff, 2) > 0) {
	// 	short data_buff = (byte_data_buff[0] << 8) | byte_data_buff[1];
	// 	int param_index = (data_buff[0] & 0xC000) >> 14;
	// 	int param_value = data_buff[0] & 0x3FFF;

	// 	switch (param_index)
	// 	{
	// 	case 0:
	// 		printf("Frequency: %d\n", param_value);
	// 		break;
	// 	case 1:
	// 		printf("Amplitude: %d\n", param_value);
	// 		break;
	// 	case 2:
	// 		printf("Phase: %d\n", param_value);
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
}

int main(void) {
	InitSound(); // Initialize the sound system
	#ifdef DEBUG
		printf("Sound system initialized.\n");
	#endif

	InitTimer();

	InitMainScreen();
	InitSubScreen();

	//irqInit();
	REG_KEYCNT = (1 << 14) | KEY_A | KEY_B | KEY_X | KEY_Y | KEY_L | KEY_R | KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN;
	irqSet(IRQ_KEYS, &keys_ISR);
	irqEnable(IRQ_KEYS);

	#ifdef DEBUG
		consoleDemoInit();
		printf("\nNDSerum\n");
		printf("Debug mode is on.\n");
	#endif

	DrawWaveMain(main_buffer, main_buffer_length);

    while(1){
    	scanKeys();
		unsigned keys = keysDown();
		// X and Y pressed one time
		if (keys == KEY_X) {
			printf("X\n");
			IncrementFrequency();
			SetFreqFader(GetFrequency());
			DrawWaveMain(main_buffer, main_buffer_length);
		}
		if (keys == KEY_Y) {
			printf("Y\n");
			EnableDisableMuter();
			SetGateButton(IsGated());
		}
		if (keys == KEY_START)
		{
			printf("START\n");
			if (!is_wifi_enabled()) {
				set_wifi_enabled(1);
				SetWifiButton(is_wifi_enabled());
			} else {
				set_wifi_enabled(0);
				SetWifiButton(is_wifi_enabled());
			}
		}
		// Touch screen pressed on time
		if (keys & KEY_TOUCH) {
			touchPosition touch;
			touchRead(&touch);
			if (touch.px || touch.py) {
				// Wave selector
				if (touch.px >= wave_selector_start_x && touch.px <= wave_selector_start_x + wave_selector_width) {
					if (touch.py >= wave_selector_start_y && touch.py <= wave_selector_start_y + wave_selector_height) {
						int touchY_in_selector = touch.py - wave_selector_start_y;
						int newWave = touchY_in_selector / (wave_selector_height / 4);
						if (newWave != GetWaveType()) {
							SetWaveType(newWave);
							SetWaveSelector(GetWaveType());
							DrawWaveMain(main_buffer, main_buffer_length);
						}
					}
				}

				// Mute button
				if (touch.px >= mute_button_start_x && touch.px <= mute_button_start_x + mute_button_width) {
					if (touch.py >= mute_button_start_y && touch.py <= mute_button_start_y + mute_button_height) {
						PauseResumeSound();
						SetMuteButton(!IsPlaying());
					}
				}

				// Gate button
				if (touch.px >= gate_button_start_x && touch.px <= gate_button_start_x + gate_button_width) {
					if (touch.py >= gate_button_start_y && touch.py <= gate_button_start_y + gate_button_height) {
						EnableDisableMuter();
						SetGateButton(IsGated());
					}
				}
			}
		}

		// Touch screen held -> for the faders to always react
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

				// Gate speed fader
				if (touch.px >= gate_fader_start_x && touch.px <= gate_fader_start_x + fader_width) {
					if (touch.py >= gate_fader_start_y && touch.py < gate_fader_start_y + gate_fader_length) {
						printf("Touch (gate speed): %d, %d\n", touch.px, touch.py);
						int newGateSpeed = 95 - (touch.py - 8);
						//printf("New gate speed: %d\n", newGateSpeed);
						if (newGateSpeed != GetGateSpeed()) {
							SetGateSpeed(newGateSpeed);
							SetGateFader(GetGateSpeed());
						}
					}
				}
			}
		}

		// Wifi receive
		// if (is_wifi_enabled()) {
		// 	wifi_receive();
		// }

		// Main screen update for interrupts
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
