#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "sound.h"
#include "BGSub.h"

void InitSubScreen();

void DrawFreqFader();
void SetFreqFader(int freq);

void DrawAmplitudeFader(); // Mystique 2
void SetAmplitudeFader(float amplitude);