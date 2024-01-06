#pragma once

#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "sound.h"
#include "BGSub.h"
#include "timer_muter.h"

void InitSubScreen();

void DrawFreqFader();
void SetFreqFader(int freq);

void DrawAmplitudeFader();
void SetAmplitudeFader(float amplitude);

void DrawPhaseFader();
void SetPhaseFader(int phase);

void DrawWaveSelector();
void SetWaveSelector(WaveType wave);

void DrawMuteButton();
void SetMuteButton(int enabled);

void DrawGateButton();
void SetGateButton(int enabled);

void DrawGateFader();
void SetGateFader(int gate_speed);
