#include "WiFi_minilib.h"
#include "sound.h"

void send_freq(int freq);
void send_amp(float amp);
void send_phase(int phase);
void send_wave(WaveType wave);
void send_mute(int mute);
void send_gate(int gate);
void send_gate_speed(int gate_speed);
int is_wifi_enabled();
void set_wifi_enabled(int enabled);
