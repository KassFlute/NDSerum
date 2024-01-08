#include <nds.h>
#include <stdlib.h>
#include "BGMain.h"
#include <stdio.h>
#include "sound.h"

/*
 * Initialize the main engine
 */
void InitMainScreen();

/*
 * Clear the info background
 */
void ClearInfoBG();

/*
 * Draw the frequency on the main screen
 */
void DrawFrequencyMain();

/*
 * Draw the amplitude on the main screen
 */
void DrawAmplitudeMain();

/*
 * Draw the phase on the main screen
 */
void DrawPhaseMain();

/*
 * Draw the time scale on the main screen
 */
void DrawTimeScaleMain();

/*
 * Draw the axe texts on the main screen
 */
void DrawText();

/*
 * Display more periods on the main screen
 */
void ZoomIn();

/*
 * Display less periods on the main screen
 */
void ZoomOut();

/*
 * Draw the wave and metrics on the main screen
 * @param main_buffer : the buffer containing the wave
 * @param length : the length of the buffer
 */
void DrawWaveMain(int16_t *main_buffer, int length);
