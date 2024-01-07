#include "sub_screen.h"

int fader_range = 23; // Range of the faders (in tiles) for the main faders

int x_volume_fader = 1; // Static fader position
int y_volume_fader = 1; // Dynamic fader position

int x_amplitude_fader = 4; // Static fader position
int y_amplitude_fader = 1; // Dynamic fader position

int x_phase_fader = 7; // Static fader position
int y_phase_fader = 1; // Dynamic fader position

int x_wave_selector = 28; // Static selector position
int y_wave_selector = 1; // Dynamic selector position

int x_mute_button = 28; // Static button position
int y_mute_button = 15; // Static button position
int is_muted = 0; // 0 = not muted, 1 = muted   !! opposite of playing in sound.c

int x_gate_button = 23; // Static button position
int y_gate_button = 15; // Static button position
int is_gated = 0; // 0 = not gated, 1 = gated

int x_gate_fader = 24; // Static fader position
int y_gate_fader = 12; // Dynamic fader position

int x_wifi_button = 23; // Static wifi status position
int y_wifi_button = 15; // Static wifi status position
bool wifi_button_enable = 1; // 0 = disabled, 1 = enabled

//Tile #0 (transparent tile)
u8 tile0[64] = {
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0
};

//Tile #1 (black tile)
u8 tile1[64] = {
    200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200,
	200, 200, 200, 200, 200, 200, 200, 200
};

//Tile #2 (top left corner tile)
u8 tile2[64] = {
    201,201,201,201,201,201,201,201,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0
};

//Tile #3 (top tile)
u8 tile3[64] = {
    201,201,201,201,201,201,201,201,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    
};

// Tile #4 (top right corner tile)
u8 tile4[64] = {
    201,201,201,201,201,201,201,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201
};

// Tile #5 (left tile)
u8 tile5[64] = {
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0
};

// Tile #6 (center tile)
u8 tile6[64] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

// Tile #7 (right tile)
u8 tile7[64] = {
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201
};

// Tile #8 (bottom left corner tile)
u8 tile8[64] = {
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,0,0,0,0,0,0,0,
    201,201,201,201,201,201,201,201
};

// Tile #9 (bottom tile)
u8 tile9[64] = {    
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    201,201,201,201,201,201,201,201
};

// Tile #10 (bottom right corner tile)
u8 tile10[64] = {
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    0,0,0,0,0,0,0,201,
    201,201,201,201,201,201,201,201
};

// Tile #11 (red dot tile)
u8 tile11[64] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,201,201,0,0,0,
    0,0,0,201,201,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void InitSubScreen() {
    /*
        * Initialize the sub screen
    */
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;

    // BG2, Rotoscale
    BGCTRL_SUB[2] = BG_BMP_BASE(2) | BgSize_B8_256x256;

    // BG0, Tile
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(0);

    // Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    // Copy tiles and palette for the background
    swiCopy(BGSubPal, BG_PALETTE_SUB, BGSubPalLen / 2);
    swiCopy(BGSubBitmap, BG_BMP_RAM_SUB(2), BGSubBitmapLen / 2);

    //custom colors for tiles
    BG_PALETTE_SUB[200] = ARGB16(1,0,0,0); // Black
    BG_PALETTE_SUB[201] = ARGB16(1,31,0,0); // Red LE MAXIMUM C'EST 31 PAS 32 SON PÈRE QUI MANGE DIP ASDPPADSFAINNNN

    // Copy tiles for the buttons
    dmaCopy(tile0, &BG_TILE_RAM_SUB(0)[0], 64);
    dmaCopy(tile1, &BG_TILE_RAM_SUB(0)[32], 64);
    dmaCopy(tile2, &BG_TILE_RAM_SUB(0)[64], 64);
    dmaCopy(tile3, &BG_TILE_RAM_SUB(0)[96], 64);
    dmaCopy(tile4, &BG_TILE_RAM_SUB(0)[128], 64);
    dmaCopy(tile5, &BG_TILE_RAM_SUB(0)[160], 64);
    dmaCopy(tile6, &BG_TILE_RAM_SUB(0)[192], 64);
    dmaCopy(tile7, &BG_TILE_RAM_SUB(0)[224], 64);
    dmaCopy(tile8, &BG_TILE_RAM_SUB(0)[256], 64);
    dmaCopy(tile9, &BG_TILE_RAM_SUB(0)[288], 64);
    dmaCopy(tile10, &BG_TILE_RAM_SUB(0)[320], 64);

    SetFreqFader(GetFrequency());    
    SetAmplitudeFader(GetAmplitude());
    SetPhaseFader(GetPhase());
    SetWaveSelector(GetWaveType());
    SetMuteButton(!IsPlaying());
    SetGateButton(IsGated());
    SetGateFader(GetGateSpeed());
}

void DrawFreqFader() {
    /*
        * Draw the frequency fader
    */

    // Erase the previous fader
    for(int x=x_volume_fader; x<x_volume_fader+2; x+=1) {
        for(int y=0; y<32; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 0;
        }
    }

    // Draw the new fader
    for(int x=x_volume_fader; x<x_volume_fader+2; x+=1) {
        for(int y=y_volume_fader; y<y_volume_fader+1; y+=1) { // this loop is useless, y_volume_fader is always 1 but allows to change faders size if needed
           BG_MAP_RAM_SUB(1)[32*y + x] = 1;
        }
    }
}

void SetFreqFader(int freq) {
    /*
        * Set the position of the frequency fader
        * @param freq : the new frequency for the fader
    */
    y_volume_fader = 23 - (int) ceil((((double)(freq - 20.0)) / (980.0 / ((double)fader_range))));
    DrawFreqFader();
}

void DrawAmplitudeFader() {
    /*
     * Draw the amplitude fader
     */

    // Erase the previous fader
    for(int x=x_amplitude_fader; x<x_amplitude_fader+2; x+=1) {
        for(int y=0; y<32; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 0;
        }
    }

    // Draw the new fader
    for(int x=x_amplitude_fader; x<x_amplitude_fader+2; x+=1) {
        for(int y=y_amplitude_fader; y<y_amplitude_fader+1; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 1;
        }
    }
}

void SetAmplitudeFader(float amplitude) {
    /*
     * Set the position of the amplitude fader
     * @param amplitude : the new amplitude for the fader
     */
    printf("Amplitude: %f\n", amplitude);
    y_amplitude_fader = 23 - (int) ceil((((double)(amplitude)) / (1.0 / ((double)fader_range))));
    DrawAmplitudeFader();
}

void DrawPhaseFader() {
    /*
     * Draw the phase fader
     */

    // Erase the previous fader
    for(int x=x_phase_fader; x<x_phase_fader+2; x+=1) {
        for(int y=0; y<32; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 0;
        }
    }

    // Draw the new fader
    for(int x=x_phase_fader; x<x_phase_fader+2; x+=1) {
        for(int y=y_phase_fader; y<y_phase_fader+1; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 1;
        }
    }
}

void SetPhaseFader(int phase) {
    /*
     * Set the position of the phase fader
     * @param phase : the new phase for the fader
     */
    y_phase_fader = 23 - (int) ceil((((double)(phase)) / (360.0 / ((double)fader_range))));
    DrawPhaseFader();
}

void DrawWaveSelector() {
    /*
     * Draw the wave selector
     */

    // Erase the previous selector
    for(int x=x_wave_selector; x<x_wave_selector+3; x+=1) {
        for(int y=1; y<=12; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 0;
        }
    }

    // Draw the new selector
    for(int x=x_wave_selector; x<x_wave_selector+3; x+=1) {
        for(int y=y_wave_selector; y<y_wave_selector+3; y+=1) {
            BG_MAP_RAM_SUB(1)[32*y + x] = 2;
           BG_MAP_RAM_SUB(1)[32*y + x] = 2 + 3*(y-y_wave_selector) + (x-x_wave_selector);
        }
    }
}

void SetWaveSelector(WaveType wave) {
    /*
     * Set the position of the wave selector
     * @param wave : the new wave for the selector
     */
    y_wave_selector = 1 + wave * 3;
    DrawWaveSelector();
}

void DrawMuteButton() {
    /*
     * Draw the mute button
     */
    if (is_muted) {
        // Draw the red highlight
        for (int x = x_mute_button; x < x_mute_button+3; x += 1) {
            for (int y = y_mute_button; y < y_mute_button+3; y += 1) {
                BG_MAP_RAM_SUB(1)[32 * y + x] = 2 + 3 * (y - y_mute_button) + (x - x_mute_button);
            }
        }
    } else {
        // Erase the previous red highlight
        for(int x=x_mute_button; x<x_mute_button+3; x+=1) {
            for(int y=y_mute_button; y<=y_mute_button+3; y+=1) {
                BG_MAP_RAM_SUB(1)[32*y + x] = 0;
            }
        }
    }
}

void SetMuteButton(int enabled) {
    /*
     * Set the position of the mute button
     * @param enabled : the new state of the button
     */
    is_muted = enabled ? 1 : 0;
    DrawMuteButton();
}

void DrawGateButton() {
    /*
     * Draw the gate button
     */
    if (is_gated) {
        // Draw the red highlight
        for (int x = x_gate_button; x < x_gate_button+3; x += 1) {
            for (int y = y_gate_button; y < y_gate_button+3; y += 1) {
                BG_MAP_RAM_SUB(1)[32 * y + x] = 2 + 3 * (y - y_gate_button) + (x - x_gate_button);
            }
        }
    } else {
        // Erase the previous red highlight
        for(int x=x_gate_button; x<x_gate_button+3; x+=1) {
            for(int y=y_gate_button; y<=y_gate_button+3; y+=1) {
                BG_MAP_RAM_SUB(1)[32*y + x] = 0;
            }
        }
    }
}

void SetGateButton(int enabled) {
    /*
     * Set the position of the gate button
     * @param enabled : the new state of the button
     */
    is_gated = enabled ? 1 : 0;
    DrawGateButton();
}

void DrawGateFader() {
    /*
     * Draw the gate fader
     */

    // Erase the previous fader
    for(int x=x_gate_fader; x<x_gate_fader+2; x+=1) {
        for(int y=1; y<=12; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 0;
        }
    }

    // Draw the new fader
    for(int x=x_gate_fader; x<x_gate_fader+2; x+=1) {
        for(int y=y_gate_fader; y<y_gate_fader+1; y+=1) {
           BG_MAP_RAM_SUB(1)[32*y + x] = 1;
        }
    }
}

void SetGateFader(int gate_speed) {
    /*
     * Set the position of the gate fader
     * @param gate_speed : the new gate speed for the fader
     */
    y_gate_fader = (11 - (gate_speed / 8)) + 1; // Transform gate speed that goes from 0 to 96 to fader position (in tile) that goes from 12 to 1
    DrawGateFader();
}

void DrawWifiButton() {
    /*
     * Draw the wifi button
     */
    if (wifi_button_enable) {
        // Draw the red highlight
        for (int x = x_wifi_button; x < x_wifi_button+3; x += 1) {
            for (int y = y_wifi_button; y < y_wifi_button+3; y += 1) {
                BG_MAP_RAM_SUB(1)[32 * y + x] = 2 + 3 * (y - y_wifi_button) + (x - x_wifi_button);
            }
        }
    } else {
        // Erase the previous red highlight
        for(int x=x_wifi_button; x<x_wifi_button+3; x+=1) {
            for(int y=y_wifi_button; y<=y_wifi_button+3; y+=1) {
                BG_MAP_RAM_SUB(1)[32*y + x] = 0;
            }
        }
    }
}

void SetWifiStatus(int enabled) {
    /*
     * Set the position of the wifi status
     * @param enabled : the new state of the wifi
     */
    wifi_button_enable = enabled ? 1 : 0;
    DrawWifiButton();
}
