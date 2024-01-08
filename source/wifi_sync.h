#include "WiFi_minilib.h"
#include "sound.h"
#include "globals.h"

/*
 * Sends the frequency to other DSs
 * @param freq The frequency to send
 */
void send_freq(int freq);

/*
 * Sends the amplitude to other DSs
 * @param amp The amplitude to send
 */
void send_amp(float amp);

/*
 * Sends the phase to other DSs
 * @param phase The phase to send
 */
void send_phase(int phase);

/*
 * Sends the wave type to other DSs
 * @param wave The wave type to send
 */
void send_wave(WaveType wave);

/*
 * Sends the mute status to other DSs
 * @param mute The mute status to send
 */
void send_mute(int mute);

/*
 * Sends the gate status to other DSs
 * @param gate The gate status to send
 */
void send_gate(int gate);

/*
 * Sends the gate speed to other DSs
 * @param gate_speed The gate speed to send
 */
void send_gate_speed(int gate_speed);

/*
 * Sends all the parameters to other DSs
 * @param gate_speed The gate speed to send
 */
void send_parameters();

/*
 * Sends a request for the parameters to other DSs
 */
void send_ask_parameters();

/*
 * Return the sync status
 */
int is_sync_enabled();

/*
 * Sets the sync status
 * @param enabled The sync status to set
 */
void set_sync_enabled(int enabled);

/*
 * Changes the sync status (Enable/Disable)
 */
void change_sync_enabled();

/*
 * Returns the wifi status
 */
int get_wifi_status();

/*
 * Flush the wifi buffer
 */
void flush_wifi_buffer();
