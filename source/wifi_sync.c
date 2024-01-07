#include "wifi_sync.h"

int wifi_enabled = 0; // 0 = disabled, 1 = enabled
int sync_enabled = 0; // 0 = disabled, 1 = enabled

union DataUnion {
    float f;
    int i;
    WaveType w;
    unsigned char bytes[4];
}; // Type capable of storing multiple types of data in the same variable

void send_freq(int freq) {
    union DataUnion freq_union;
    freq_union.i = freq;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 0; // 0 = freq
    memcpy(byte_data_buff + 1, freq_union.bytes, 4); // Copy 4 bytes of the freq (int)
    sendData(byte_data_buff, 5);
}

void send_amp(float amp) {
    union DataUnion amp_union;
    amp_union.f = amp;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 1; // 1 = amp
    memcpy(byte_data_buff + 1, amp_union.bytes, 4); // Copy 4 bytes of the amp (float)
    sendData(byte_data_buff, 5);
}

void send_phase(int phase) {
    union DataUnion phase_union;
    phase_union.i = phase;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 2; // 2 = phase
    memcpy(byte_data_buff + 1, phase_union.bytes, 4); // Copy 4 bytes of the phase (int)
    sendData(byte_data_buff, 5);
}

void send_wave(WaveType wave) {
    union DataUnion wave_union;
    wave_union.w = wave;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 3; // 3 = wave
    memcpy(byte_data_buff + 1, wave_union.bytes, 4); // Copy 4 bytes of the wave (WaveType)
    sendData(byte_data_buff, 5);
}

void send_mute(int mute) {
    union DataUnion mute_union;
    mute_union.i = mute;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 4; // 4 = mute
    memcpy(byte_data_buff + 1, mute_union.bytes, 4); // Copy 4 bytes of the mute (int)
    sendData(byte_data_buff, 5);
}

void send_gate(int gate) {
    union DataUnion gate_union;
    gate_union.i = gate;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 5; // 5 = gate
    memcpy(byte_data_buff + 1, gate_union.bytes, 4); // Copy 4 bytes of the gate (int)
    sendData(byte_data_buff, 5);
}

void send_gate_speed(int gate_speed) {
    union DataUnion gate_speed_union;
    gate_speed_union.i = gate_speed;

    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 6; // 6 = gate_speed
    memcpy(byte_data_buff + 1, gate_speed_union.bytes, 4); // Copy 4 bytes of the gate_speed (int)
    sendData(byte_data_buff, 5);
}

int is_sync_enabled() {
    return sync_enabled;
}

void set_sync_enabled(int enabled) {
    if (enabled) {
        if (!wifi_enabled) {
            printf("Initializing WiFi...\n");
            if (initWiFi()) {
                if (openSocket()) {
                    printf("Wifi initilaized");
                    wifi_enabled = 1;
                    sync_enabled = 1;
                } else {
                    wifi_enabled = 0;
                    sync_enabled = 0;
                }
            } else {
                wifi_enabled = 0;
                sync_enabled = 0;
            }
        } else {
            sync_enabled = 1;
        }
    } else {
        sync_enabled = 0;
    }

    // if (wifi_enabled){
    //     // closeSocket();
    //     // disconnectFromWiFi();
    //     printf("WiFi disabled.\n");
    //     wifi_enabled = 0;
    // } else {
    //     printf("Initializing WiFi...\n");
    //     if (initWiFi()) {
    //         if (openSocket()) {
    //             printf("Wifi initilaized");
    //             wifi_enabled = 1;
    //         } else {
    //             wifi_enabled = 0;
    //         }
    //     } else {
    //         wifi_enabled = 0;
    //     }
    // }
}
