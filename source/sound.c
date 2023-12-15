#include "sound.h"

int NPeriodFromFrequency(int frequency){
	if(frequency < 10) return 1;
	return frequency/10;
}
