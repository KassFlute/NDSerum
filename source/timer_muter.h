#include <nds.h>

#include "sound.h"


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void InitTimer();

void SetMuteInterval(int interval);
int GetMuteInterval();
void EnableDisableMuter();
