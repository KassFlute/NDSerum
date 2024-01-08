#include "wifi_sync.h"

int wifi_status = 0; // 0 = disabled, 1 = connecting, 2 = connected
int sync_enabled = 0; // 0 = disabled, 1 = enabled

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

void send_parameters() {
    send_gate(IsGated());
    send_gate_speed(GetGateSpeed());
    send_mute(!IsPlaying());
    send_freq(GetFrequency());
    send_amp(GetAmplitude());
    send_phase(GetPhase());
    send_wave(GetWaveType());
}

void send_ask_parameters(){
    unsigned char byte_data_buff[5];
    byte_data_buff[0] = 7; // 7 = ask_parameters
    sendData(byte_data_buff, 5);

}

int is_sync_enabled() {
    return sync_enabled;
}

void set_sync_enabled(int enabled) {
    if (enabled == sync_enabled) { // Nothing to change
        return;
    }
    if (enabled) {
        if (!wifi_status) {
            irqDisable(IRQ_KEYS);
            //printf("Initializing WiFi...\n");
            int old_mute_status = IsGated() ? 2 : (IsPlaying() ? 1 : 0);
            SetGate(0);
            SetGateButton(0);
            PauseSound();
            SetMuteButton(1);
            wifi_status = 1;
            SetWifiStatus(wifi_status);
            if (initWiFi()) {
                //printf("Wifi initilaized successfully!\n");
                if (openSocket()) {
                    //printf("Socket opened successfully!\n");
                    send_ask_parameters();
                    if (old_mute_status == 1) {
                        ResumeSound();
                        SetMuteButton(0);
                    } else if (old_mute_status == 2) {
                        SetGate(1);
                        SetGateButton(1);
                    }
                    wifi_status = 2;
                    SetWifiStatus(wifi_status);
                    sync_enabled = 1;
                    irqEnable(IRQ_KEYS);
                } else {
                    //printf("Error opening socket !\n");
                    if (old_mute_status == 1) {
                        ResumeSound();
                        SetMuteButton(0);
                    } else if (old_mute_status == 2) {
                        SetGate(1);
                        SetGateButton(1);
                    }
                    wifi_status = 0;
                    SetWifiStatus(wifi_status);
                    sync_enabled = 0;
                    irqEnable(IRQ_KEYS);
                }
            } else {
                //printf("Error initializing WiFi !\n");
                if (old_mute_status == 1) {
                    ResumeSound();
                    SetMuteButton(0);
                } else if (old_mute_status == 2) {
                    SetGate(1);
                    SetGateButton(1);
                }
                wifi_status = 0;
                SetWifiStatus(wifi_status);
                sync_enabled = 0;
                irqEnable(IRQ_KEYS);
            }
        } else {
            flush_wifi_buffer();
            send_ask_parameters();
            sync_enabled = 1;
        }
    } else {
        sync_enabled = 0;
    }
}

void change_sync_enabled() {
    set_sync_enabled(!sync_enabled);
}

int get_wifi_status() {
    return wifi_status;
}

void flush_wifi_buffer() {
    unsigned char byte_data_buff[5];
    while (receiveData(byte_data_buff, 5) > 0){};
}
