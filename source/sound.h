#pragma once

#include <nds.h>
#include <maxmod9.h>

#include "globals.h"
#include "white_noise.h"
#include "saw_wave.h"
#include "sin_wave.h"

#define SAMPLERATE 48000
#define BUFFERLENGTH 9600 // Length of the stream buffer
#define MINVALUE -32768 // Audio samples are 16 bits signed integers
#define MAXVALUE 32768
#define NUMBERPERIOD 20 // WTF is this ?
#define N_SAMPLES 4800 // Number of samples to be generated at each call of FillBuffer() recalculated each time in the fill functions

typedef enum
{
    SAW_WAVE,
    SIN_WAVE,
    WHITE_NOISE
    // Other wave types ...
} WaveType;
#define waveTypeCount 3; // KEEP UPDATED

mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format);

void InitSound();

int NPeriodFromFrequency(int frequency);

void FillBuffer();

void PauseSound();
void ResumeSound();
void PauseResumeSound();
int IsPlaying();

void SetFrequency(int newFrequency);
void IncrementFrequency10();
void DecrementFrequency10();
int GetFrequency();

void SetWaveType(WaveType newWaveType);
void IncrementWaveType();
WaveType GetWaveType();
