#include "WiFi_minilib.h"
#include "sound.h"

void send_freq(int freq);
void send_amp(float amp);
void send_phase(int phase);
void send_wave(WaveType wave);
void send_mute(int mute);
void send_gate(int gate);
void send_gate_speed(int gate_speed);
int is_sync_enabled();
void set_sync_enabled(int enabled);
void change_sync_enabled();
int get_wifi_status();
void flush_wifi_buffer();