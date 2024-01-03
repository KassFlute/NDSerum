#include "main_screen.h"
#include "BGMain.h"
#include <nds.h>
#include <stdio.h>

void InitMainScreen(){

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;

	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;

	BGCTRL[2] = BG_BMP_BASE(4) | BgSize_B8_256x256;

	swiCopy(BGMainTiles,BG_TILE_RAM(1),BGMainTilesLen/2);

	swiCopy(BGMainPal,BG_PALETTE,BGMainPalLen/2);

	swiCopy(BGMainMap,BG_MAP_RAM(0),BGMainMapLen/2);

	uint16* myPalette = BG_PALETTE;

	myPalette[2] = ARGB16(1,31,31,0);

}


void DrawWaveMain(int16_t * main_buffer, int * length, int offset , int zoom){

	BG_BMP_RAM(4)[0] = 2;

}





