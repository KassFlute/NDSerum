#pragma once

#include <nds.h>
#include <maxmod9.h>

#include "globals.h"
#include "white_noise.h"
#include "saw_wave.h"
#include "sin_wave.h"

#define SAMPLERATE 48000
#define MINVALUE -32768
#define MAXVALUE 32768
#define NUMBERPERIOD 20

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

void SetFrequency(int newFrequency);
void IncrementFrequency10();
void DecrementFrequency10();
int GetFrequency();

void SetWaveType(WaveType newWaveType);
void IncrementWaveType();
WaveType GetWaveType();
