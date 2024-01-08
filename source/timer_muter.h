#include <nds.h>

#include "globals.h"
#include "sound.h"
#include "sub_screen.h"

/*
 * Initialize the timer
 */
void InitTimer();

/*
 * Enable or disable the muter
 */
void EnableDisableMuter();

/*
 * Enable or disable the gate
 * @param enabled : 1 to enable the gate, 0 to disable it
 */
void SetGate(int enabled);

/*
 * Set the speed of the gate
 * @param speed : the new speed of the gate
 */
void SetGateSpeed(int speed);

/*
 * Return the speed of the gate
 * @return the speed of the gate
 */
int GetGateSpeed();

/*
 * Return if the muter is enabled
 * @return 1 if the muter is enabled, 0 otherwise
 */
int IsGated();
