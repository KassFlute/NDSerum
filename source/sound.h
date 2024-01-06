#pragma once

#include  <nds.h>
#include <maxmod9.h>

#include "globals.h"
#include "white_noise.h"
#include "saw_wave.h"
#include "sin_wave.h"
#include "square_wave.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define SAMPLERATE 20000 // 48 kHz to go upto 24 kHz of sound
#define BUFFERLENGTH 4800 //4800 // Length of the stream buffer
#define MINVALUE -32768 // Audio samples are 16 bits signed integers
#define MAXVALUE 32767
#define NUMBERPERIOD 20 // WTF is this ?
#define MAXFREQ 1000 // Maximum frequency of the wave
#define MINFREQ 20 // Minimum frequency of the wave

typedef enum
{
    SAW_WAVE,
    SIN_WAVE,
    WHITE_NOISE,
	SQUARE_WAVE
    // Other wave types ...
} WaveType;
#define waveTypeCount 4 // KEEP UPDATED

mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format);

void InitSound();

int NPeriodFromFrequency(int frequency);

void FillBuffer();

void PauseSound();
void ResumeSound();
void PauseResumeSound();
int IsPlaying();

void SetFrequency(int newFrequency);
void IncrementFrequency();
void DecrementFrequency();
void IncrementFrequency10();
void DecrementFrequency10();
int GetFrequency();

void SetAmplitude(float newAmplitude);
float GetAmplitude();

void SetPhase(int newPhase);
void IncrementPhase10();
void DecrementPhase10();
int GetPhase();

void SetWaveType(WaveType newWaveType);
void IncrementWaveType();
void DecrementWaveType();
WaveType GetWaveType();
