#pragma once

#include  <nds.h>
#include <maxmod9.h>
#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "white_noise.h"
#include "saw_wave.h"
#include "sin_wave.h"
#include "square_wave.h"

#define SAMPLERATE 20000 // 48 kHz to go upto 24 kHz of sound 
#define BUFFERLENGTH 400 //4800 // Length of the stream buffer -- THE SMALLER, THE QUICKER IT MUTES
#define MINVALUE -32768 // Audio samples are 16 bits signed integers
#define MAXVALUE 32767
#define NUMBERPERIOD 20 // WTF is this ?
#define MAXFREQ 1000 // Maximum frequency of the wave
#define MINFREQ 20 // Minimum frequency of the wave

#define waveTypeCount 4

/*
 * Maxmod callback for the audio stream buffer filling
 * @param length : number of samples requested by the stream
 * @param dest : buffer of the stream
 * @param format : format requested by the stream
 */
mm_word OnStreamRequest(mm_word length, mm_addr dest, mm_stream_formats format);

/*
 * Initialize the sound system
 */
void InitSound();

/*
 * Fill the main_buffer with the current wave type, frequency and amplitude
 */
void FillBuffer();

/*
 * Pause the sound
 */
void PauseSound();

/*
 * Resume the sound
 */
void ResumeSound();

/*
 * Pause or resume the sound depending on the current state
 */
void PauseResumeSound();

/*
 * Return if the sound is playing
 * @return 1 if the sound is playing, 0 otherwise
 */
int IsPlaying();

/*
 * Set the frequency of the wave
 * @param newFrequency : the new frequency of the wave
 */
void SetFrequency(int newFrequency);

/*
 * Increment the frequency of the wave by 1
 */
void IncrementFrequency();

/*
 * Decrement the frequency of the wave by 1
 */
void DecrementFrequency();

/*
 * Increment the frequency of the wave by 10
 */
void IncrementFrequency10();

/*
 * Decrement the frequency of the wave by 10
 */
void DecrementFrequency10();

/*
 * Return the frequency of the wave
 * @return the frequency of the wave
 */
int GetFrequency();

/*
 * Set the amplitude of the wave
 * @param newAmplitude : the new amplitude of the wave
 */
void SetAmplitude(float newAmplitude);

/*
 * Return the amplitude of the wave
 * @return the amplitude of the wave
 */
float GetAmplitude();

/*
 * Set the phase of the wave
 * @param newPhase : the new phase of the wave
 */
void SetPhase(int newPhase);

/*
 * Increment the phase of the wave by 1
 */
void IncrementPhase();

/*
 * Decrement the phase of the wave by 1
 */
void DecrementPhase();

/*
 * Increment the phase of the wave by 10
 */
void IncrementPhase10();

/*
 * Decrement the phase of the wave by 10
 */
void DecrementPhase10();

/*
 * Return the phase of the wave
 * @return the phase of the wave
 */
int GetPhase();

/*
 * Set the type of the wave
 * @param newWaveType : the new type of the wave
 */
void SetWaveType(WaveType newWaveType);

/*
 * Increment the type of the wave
 */
void IncrementWaveType();

/*
 * Decrement the type of the wave
 */
void DecrementWaveType();

/*
 * Return the type of the wave
 * @return the type of the wave
 */
WaveType GetWaveType();
