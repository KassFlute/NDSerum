#include "sub_screen.h"

int fader_range = 23;

int x_volume_fader = 1;
int y_volume_fader = 1;

int x_amplitude_fader = 4;
int y_amplitude_fader = 1;

int x_phase_fader = 7;
int y_phase_fader = 1;

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
    BG_PALETTE_SUB[200] = RGB15(0,0,0);

    // Copy tiles for the buttons
    dmaCopy(tile0, &BG_TILE_RAM_SUB(0)[0], 64);
    dmaCopy(tile1, &BG_TILE_RAM_SUB(0)[32], 64);

    SetFreqFader(GetFrequency());    
    SetAmplitudeFader(GetAmplitude());
    SetPhaseFader(GetPhase());
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
        for(int y=y_volume_fader; y<y_volume_fader+1; y+=1) {
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