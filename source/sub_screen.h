#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "sound.h"
#include "BGSub.h"

void InitSubScreen();

void DrawFreqFader();
void SetFreqFader(int freq);

void DrawAmplitudeFader();
void SetAmplitudeFader(float amplitude);

void DrawPhaseFader();
void SetPhaseFader(int phase);

void DrawWaveSelector();
void SetWaveSelector(WaveType wave);