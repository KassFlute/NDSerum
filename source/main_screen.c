#include "main_screen.h"
#include "BGMain.h"
#include <nds.h>
#include <stdio.h>
#include "sound.h"

void InitMainScreen(){



	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE; //DISPLAY_BG0_ACTIVE

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B16_256x256;

	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

//	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;
//
//	swiCopy(BGMainTiles,BG_TILE_RAM(1),BGMainTilesLen/2);
//
//	swiCopy(BGMainPal,BG_PALETTE,BGMainPalLen/2);
//
//	swiCopy(BGMainMap,BG_MAP_RAM(0),BGMainMapLen/2);





}


void DrawWaveMain(int16_t * main_buffer, int length, int offset , int zoom){

	for(int x = 0 ; x < 256 ; x ++){
		for(int y = 0 ; y < 192; y++){
			BG_BMP_RAM(0)[x + 256 * y] = 0;
		}
	}

	u16 yellow = ARGB16(1,31,31,0);

	for(int i = 0; i< length; i++){

		int x = (i / (double) 4800) * 256 ;

		int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * 192;

		BG_BMP_RAM(0)[x + 256 * (192-y)] = yellow;


	}

}





