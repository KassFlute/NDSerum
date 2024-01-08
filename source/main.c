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

typedef enum Messages_e
{
	A, // 0x00
	B, // 0x01
	X, // 0x02
	Y  // 0x03
} Message;

union DataUnion {
	float f;
	int i;
	WaveType w;
	unsigned char bytes[4];
}; // Type capable of storing multiple types of data in the same variable

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
int gate_button_start_x = 184; // Start of the gate button in pixels (x)
int gate_button_start_y = 120; // Start of the gate button in pixels (y)
int gate_fader_start_x = 192; // Start of the gate fader in pixels (x)
int gate_fader_start_y = 8; // Start of the gate fader in pixels (y)
int gate_fader_length = 96; // Length of the gate fader in pixels
int sync_button_start_x = 184; // Start of the sync button in pixels (x)
int sync_button_start_y = 160; // Start of the sync button in pixels (y)
int button_width = 24; // Width of the mute button in pixels
int button_height = 24; // Height of the mute button in pixels

int needUpdate = 0; // if main loop needs to update (when a sound parameter has changed)

void keys_ISR() {
	//printf("Interrupt\n");
	u16 keys = ~(REG_KEYINPUT);
	if (keys & KEY_A) {
		//printf("A\n");
		PauseResumeSound();
		if (is_sync_enabled()) send_mute(!IsPlaying());
		SetMuteButton(!IsPlaying());
	}
	if (keys & KEY_B) {
		//printf("B\n");
		DecrementFrequency();
		SetFreqFader(GetFrequency());
		if (is_sync_enabled()) send_freq(GetFrequency());
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_L) {
		//printf("L\n");
		DecrementPhase();
		SetPhaseFader(GetPhase());
		if (is_sync_enabled()) send_phase(GetPhase());
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_R) {
		//printf("R\n");
		IncrementPhase();
		SetPhaseFader(GetPhase());
		if (is_sync_enabled()) send_phase(GetPhase());
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_UP) {
		//printf("UP\n");
		ZoomIn();
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_DOWN) {
		//printf("DOWN\n");
		ZoomOut();
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_LEFT) {
		//printf("LEFT\n");
		DecrementWaveType();
		SetWaveSelector(GetWaveType());
		if (is_sync_enabled()) send_wave(GetWaveType());
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
	if (keys & KEY_RIGHT) {
		//printf("RIGHT\n");
		IncrementWaveType();
		SetWaveSelector(GetWaveType());
		if (is_sync_enabled()) send_wave(GetWaveType());
		//DrawWaveMain(main_buffer, main_buffer_length);
		needUpdate = 1;
	}
}

void wifi_receive(){
	unsigned char byte_data_buff[5];
	if (receiveData(byte_data_buff, 5) > 0) {
		//printf("Received (SWAGER): %d, %d, %d, %d, %d\n", byte_data_buff[0], byte_data_buff[1], byte_data_buff[2], byte_data_buff[3], byte_data_buff[4]);
		int param_index = byte_data_buff[0];
		union DataUnion param_union;

		// Reconstruct the float or int from the received bytes
		memcpy(param_union.bytes, &byte_data_buff[1], 4);

		switch (param_index) {
			case 0:
				printf("Frequency from Wifi: %d\n", param_union.i);
				SetFrequency(param_union.i);
				SetFreqFader(GetFrequency());
				//DrawWaveMain(main_buffer, main_buffer_length);
				needUpdate = 1;
				break;
			case 1:
				printf("Amplitude from Wifi: %f\n", param_union.f);
				SetAmplitude(param_union.f);
				SetAmplitudeFader(GetAmplitude());
				//DrawWaveMain(main_buffer, main_buffer_length);
				needUpdate = 1;
				break;
			case 2:
				printf("Phase from Wifi: %d\n", param_union.i);
				SetPhase(param_union.i);
				SetPhaseFader(GetPhase());
				//DrawWaveMain(main_buffer, main_buffer_length);
				needUpdate = 1;
				break;
			case 3:
				printf("Wave from Wifi: %d\n", param_union.w);
				SetWaveType(param_union.w);
				SetWaveSelector(GetWaveType());
				//DrawWaveMain(main_buffer, main_buffer_length);
				needUpdate = 1;
				break;
			case 4:
				printf("Mute from Wifi: %d\n", param_union.i);
				if (param_union.i) {
					PauseSound();
				} else {
					ResumeSound();
				}
				SetMuteButton(!IsPlaying());
				break;
			case 5:
				printf("Gate from Wifi: %d\n", param_union.i);
				SetGate(param_union.i);
				SetGateButton(IsGated());
				break;
			case 6:
				printf("Gate speed from Wifi: %d\n", param_union.i);
				SetGateSpeed(param_union.i);
				SetGateFader(GetGateSpeed());
				break;
			case 7:
				printf("Someone asks for the parameters \n");
				send_parameters();
			default:
				break;
		}
	}
}

// void receiveMessage() {
// 	char msg[2];

// 	// Listen for messages from others
// 	if (receiveData(msg, 2) > 0) {
// 		printf("Received (NUL): %d %d\n", msg[0], msg[1]);
// 	}
// }

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
			IncrementFrequency();
			SetFreqFader(GetFrequency());
			if (is_sync_enabled()) send_freq(GetFrequency());
			//DrawWaveMain(main_buffer, main_buffer_length);
			needUpdate = 1;
		}
		if (keys == KEY_Y) {
			//printf("Y\n");
			EnableDisableMuter();
			SetGateButton(IsGated());
			if (is_sync_enabled()) send_gate(IsGated());
			// char msg[2];
			// msg[0] = (char)A;
			// msg[1] = (char)B;
			// // Send the msg
			// sendData(msg, 2);
		}
		if (keys == KEY_START) {
			//printf("START\n");
			change_sync_enabled();
			SetSyncButton(is_sync_enabled());
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
							if (is_sync_enabled()) send_wave(GetWaveType());
							//DrawWaveMain(main_buffer, main_buffer_length);
							needUpdate = 1;
						}
					}
				}

				// Mute button
				if (touch.px >= mute_button_start_x && touch.px <= mute_button_start_x + button_width) {
					if (touch.py >= mute_button_start_y && touch.py <= mute_button_start_y + button_height) {
						PauseResumeSound();
						SetMuteButton(!IsPlaying());
						if (is_sync_enabled()) send_mute(!IsPlaying());
					}
				}

				// Gate button
				if (touch.px >= gate_button_start_x && touch.px <= gate_button_start_x + button_width) {
					if (touch.py >= gate_button_start_y && touch.py <= gate_button_start_y + button_height) {
						EnableDisableMuter();
						SetGateButton(IsGated());
						if (is_sync_enabled()) send_gate(IsGated());
					}
				}

				// Wifi sync button
				if (touch.px >= sync_button_start_x && touch.px <= sync_button_start_x + button_width) {
					if (touch.py >= sync_button_start_y && touch.py <= sync_button_start_y + button_height) {
						change_sync_enabled();
						SetSyncButton(is_sync_enabled());
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
						if (is_sync_enabled()) send_freq(GetFrequency());
						//DrawWaveMain(main_buffer, main_buffer_length);
						needUpdate = 1;
					}
				}

				// Amplitude fader
				if (touch.px >= amp_fader_start && touch.px <= amp_fader_start + fader_width) {
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					float newAmplitude = ((float)(186-touchY)) / 186;
					if (newAmplitude != GetAmplitude()){
						SetAmplitude(newAmplitude);
						SetAmplitudeFader(GetAmplitude());
						if (is_sync_enabled()) send_amp(GetAmplitude());
						//DrawWaveMain(main_buffer, main_buffer_length);
						needUpdate = 1;
					}
				}

				// Phase fader
				if (touch.px >= phase_fader_start && touch.px <= phase_fader_start + fader_width) {
					int touchY = MIN(MAX(touch.py, 3), 189) - 3; // Calculating as if the screen was 186 pixels wide (instead of 192) because impossible to touch
					int newPhase = ((186-touchY) * 360) / 186;
					if (newPhase != GetPhase()){
						SetPhase(newPhase);
						SetPhaseFader(GetPhase());
						if (is_sync_enabled()) send_phase(GetPhase());
						//DrawWaveMain(main_buffer, main_buffer_length);
						needUpdate = 1;
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
							if (is_sync_enabled()) send_gate_speed(GetGateSpeed());
						}
					}
				}
			}
		}

		// Wifi receive
		if (is_sync_enabled()) {
			wifi_receive();
		}

		// Main screen and sound engine update
		if(needUpdate){
			irqDisable(IRQ_KEYS);
			//irqDisable(IRQ_TIMER1);
			FillBuffer();
			DrawWaveMain(main_buffer, main_buffer_length);
			needUpdate = 0;
			irqEnable(IRQ_KEYS);
			//irqEnable(IRQ_TIMER1);

		}
		swiWaitForVBlank();
    }
}
