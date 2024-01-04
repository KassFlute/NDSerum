#include "sub_screen.h"

//Tile #0 (transparent tile)
u8 tile0[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

//Tile #1 (black tile)
u8 tile1[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void InitSubScreen(){

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;

    // BG2, Rotoscale
    BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;
    // BG0, Tile
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(23) | BG_TILE_BASE(3);

    // Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    // Copy tiles and palette for the background
    swiCopy(BGSubPal, BG_PALETTE_SUB, BGSubPalLen / 2);
    //printf("BGSubPalLen: %d\n", BGSubPalLen);
    swiCopy(BGSubBitmap, BG_GFX_SUB, BGSubBitmapLen / 2);

    // Copy tiles for the buttons
    dmaCopy(tile0, &BG_TILE_RAM_SUB(3)[0], 64);
    dmaCopy(tile1, &BG_TILE_RAM_SUB(3)[32], 64);

    // Generate the map
    for(int i=0; i<32; i+=2) {
        for(int j=0; j<32; j+=2) {
            BG_MAP_RAM(23)[32*i + j] = 0;
        }
    }
}
