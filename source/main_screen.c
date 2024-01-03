#include "main_screen.h"
#include "BGMain.h"
#include <nds.h>
#include <stdio.h>
#include "sound.h"

void InitMainScreen(){

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;


	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG;

	BGCTRL[3] = BG_BMP_BASE(0) | BgSize_B8_256x256;


	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(BGMainBitmap,BG_BMP_RAM(0),BGMainBitmapLen/2);

	swiCopy(BGMainPal,BG_PALETTE,BGMainPalLen/2);

	BGCTRL[2] = BG_BMP_BASE(3) | BgSize_B16_256x256;

	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;
}


void DrawWaveMain(int16_t * main_buffer, int length, int offset , int zoom){

	u16 yellow = ARGB16(1,31,31,0);

	u16 transparent = ARGB16(0,0,0,0);

	for(int x = 0 ; x < 256 ; x ++){
		for(int y = 0 ; y < 192; y++){
			BG_BMP_RAM(3)[x + 256 * y] = transparent;
		}
	}

	for(int i = 0; i< length  ; i++){

		int x = (i / (double) 4800) * 256 ;

		int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * 192;

		int yNext = ((main_buffer[i+1] + MAXVALUE) / ((double)2*MAXVALUE)) * 192;

		if(y - yNext > 0){

			for(int i = 0 ; i<256; i++){
				BG_BMP_RAM(3)[x + 256 * (192-i)] = yellow;
			}
		}

		BG_BMP_RAM(3)[x + 256 * (192-y)] = yellow;

	}

}





