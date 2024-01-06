#include <nds.h>

#include "sound.h"
#include "sub_screen.h"


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void InitTimer();

void EnableDisableMuter();
void SetGateSpeed(int speed);
int GetGateSpeed();
int IsGated();
