#include "param_storage.h"

FILE* storage_file; // file used to store the parameters

void init_storage() {
    //fatInitDefault(); // Uncommenting this prevent the program from starting, (#131 on Ed discussion) all storage system then doesn't work.
    // Create file if it doesn't exist
    storage_file = fopen(STORAGE_FILE_PATH, "r+"); // NULL if no file
    printf("storage_file init: %p\n", storage_file);
    if (storage_file == NULL) {
        storage_file = fopen(STORAGE_FILE_PATH, "w");
        printf("storage_file created: %p\n", storage_file);
        if (storage_file != NULL) {
            printf("Filling file\n");
            // Write default values
            int freq = 1000;
            float amp = GetAmplitude();
            int phase = GetPhase();
            WaveType wave = GetWaveType();
            int mute = !IsPlaying();
            int gate = IsGated();
            int gate_speed = GetGateSpeed();
            fprintf(storage_file, "%d %f %d %d %d %d %d", freq, amp, phase, wave, mute, gate, gate_speed);
            fclose(storage_file);
        }
    } else {
        fclose(storage_file);
    }
}

void apply_default_params() {
    int freq;
    float amp;
    int phase;
    WaveType wave;
    int mute;
    int gate;
    int gate_speed;

    storage_file = fopen(STORAGE_FILE_PATH, "r");
    printf("storage_file read: %p\n", storage_file);
    if (storage_file == NULL) {
        return; // No file, no default params (should not happen)
    } else {
        fscanf(storage_file, "%d %f %d %d %d %d %d", &freq, &amp, &phase, &wave, &mute, &gate, &gate_speed);
        printf("freq: %d, amp: %f, phase: %d, wave: %d, mute: %d, gate: %d, gate_speed: %d\n", freq, amp, phase, wave, mute, gate, gate_speed);
    }
    fclose(storage_file);

    SetFrequency(freq);
    SetAmplitude(amp);
    SetPhase(phase);
    SetWaveType(wave);
    if (mute) {
        PauseSound();
    } else {
        ResumeSound();
    }
    SetGate(gate);
    SetGateSpeed(gate_speed);
}

void save_default_params() {
    int freq = GetFrequency();
    float amp = GetAmplitude();
    int phase = GetPhase();
    WaveType wave = GetWaveType();
    int mute = !IsPlaying();
    int gate = IsGated();
    int gate_speed = GetGateSpeed();

    storage_file = fopen(STORAGE_FILE_PATH, "w");
    if (storage_file == NULL) {
        return; // No file, no default params (should not happen)
    } else {
        fprintf(storage_file, "%d %f %d %d %d %d %d", freq, amp, phase, wave, mute, gate, gate_speed);
    }
    fclose(storage_file);
}
