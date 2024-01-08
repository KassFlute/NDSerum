#pragma once

#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "globals.h"
#include "sound.h"
#include "BGSub.h"
#include "timer_muter.h"
#include "wifi_sync.h"

/*
 * Initialize the sub screen
 */
void InitSubScreen();

/*
 * Draw the frequency fader
 */
void DrawFreqFader();

/*
* Set the position of the frequency fader
* @param freq : the new frequency for the fader
*/
void SetFreqFader(int freq);

/*
 * Draw the amplitude fader
 */
void DrawAmplitudeFader();

/*
 * Set the position of the amplitude fader
 * @param amplitude : the new amplitude for the fader
 */
void SetAmplitudeFader(float amplitude);

/*
 * Draw the phase fader
 */
void DrawPhaseFader();

/*
 * Set the position of the phase fader
 * @param phase : the new phase for the fader
 */
void SetPhaseFader(int phase);

/*
 * Draw the wave selector
 */
void DrawWaveSelector();

/*
 * Set the position of the wave selector
 * @param wave : the new wave for the selector
 */
void SetWaveSelector(WaveType wave);

/*
 * Draw the mute button
 */
void DrawMuteButton();

/*
 * Set the position of the mute button
 * @param enabled : the new state of the button
 */
void SetMuteButton(int enabled);

/*
 * Draw the gate button
 */
void DrawGateButton();

/*
 * Set the position of the gate button
 * @param enabled : the new state of the button
 */
void SetGateButton(int enabled);

/*
 * Draw the gate fader
 */
void DrawGateFader();

/*
 * Set the position of the gate fader
 * @param gate_speed : the new gate speed for the fader
 */
void SetGateFader(int gate_speed);

/*
 * Draw the wifi button
 */
void DrawSyncButton();

/*
 * Set the position of the wifi status
 * @param enabled : the new state of the wifi
 */
void SetSyncButton(int enabled);

/*
 * Draw the wifi status
 */
void DrawWifiSatus();

/*
 * Set the position of the wifi status
 * @param status : the new status for the wifi
 */
void SetWifiStatus(int status);
