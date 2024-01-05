#include "main_screen.h"
#include "BGMain.h"
#include <nds.h>
#include <stdio.h>
#include "sound.h"

#define VERTICALRANGE 171
#define GENERALOFFSET 10

int actualZoom = 1;
int actualOffset = 0;

u8 tileNum10[64] = {
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0
};
u8 tileNum0[64] = {
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0
};



u8 tileNum1[64] = {
   0,0,9,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,9,9,9,9,0,0
};

u8 tileNum2[64] = {
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,0,0,0,0,9,0,0,
   0,0,0,0,9,0,0,0,
   0,0,0,9,0,0,0,0,
   0,0,9,0,0,0,0,0,
   0,9,0,0,0,0,0,0,
   0,9,9,9,9,9,9,0
};

u8 tileNum3[64] = {
   0,0,0,0,0,0,0,0,
   0,0,9,9,9,9,0,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0
};

u8 tileNum4[64] = {
   0,0,0,0,0,9,0,0,
   0,0,0,0,9,9,0,0,
   0,0,0,9,0,9,0,0,
   0,0,9,0,0,9,0,0,
   0,9,9,9,9,9,9,0,
   0,0,0,0,0,9,0,0,
   0,0,0,0,0,9,0,0,
   0,0,0,0,0,9,0,0
};

u8 tileNum5[64] = {
   0,9,9,9,9,9,9,0,
   0,9,0,0,0,0,0,0,
   0,9,0,0,0,0,0,0,
   0,9,9,9,9,9,0,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,0,9,0,
   0,9,9,9,9,9,0,0
};

u8 tileNum6[64] = {
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,0,0,
   0,9,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0
};


u8 tileNum7[64] = {
   0,9,9,9,9,9,9,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,0,9,0,
   0,0,0,0,0,9,0,0,
   0,0,9,9,9,9,9,0,
   0,0,0,9,0,0,0,0,
   0,0,0,9,0,0,0,0,
   0,0,0,9,0,0,0,0
};

u8 tileNum8[64] = {
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0
};
u8 tileNum9[64] = {
   0,0,9,9,9,9,0,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,9,0,
   0,0,0,0,0,0,9,0,
   0,9,0,0,0,0,9,0,
   0,0,9,9,9,9,0,0
};

u8 tileDot[64] = {
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0
};

u8 tileDegree[64] = {
   0,0,0,0,0,0,0,0,
   0,0,9,9,0,0,0,0,
   0,9,0,0,9,0,0,0,
   0,9,0,0,9,0,0,0,
   0,0,9,9,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0
};

u8 tileHz[64] = {
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,
   9,0,0,9,0,0,0,0,
   9,0,0,9,0,9,9,9,
   9,9,9,9,0,0,0,9,
   9,0,0,9,0,0,9,0,
   9,0,0,9,0,9,9,9
};

void InitMainScreen() {

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE;


	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG;

	BGCTRL[3] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(BGMainBitmap,BG_BMP_RAM(0),BGMainBitmapLen/2);

	swiCopy(BGMainPal,BG_PALETTE,BGMainPalLen/2);

	BGCTRL[2] = BG_BMP_BASE(5) | BgSize_B16_256x256;

	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	//custom colors for tiles

	BG_PALETTE[9] = RGB15(31,31,31);

	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(24) | BG_TILE_BASE(4);

	dmaCopy(tileNum0, &BG_TILE_RAM(4)[0], 64);
	dmaCopy(tileNum1, &BG_TILE_RAM(4)[32], 64);
	dmaCopy(tileNum2, &BG_TILE_RAM(4)[64], 64);
	dmaCopy(tileNum3, &BG_TILE_RAM(4)[96], 64);
	dmaCopy(tileNum4, &BG_TILE_RAM(4)[128], 64);
	dmaCopy(tileNum5, &BG_TILE_RAM(4)[160], 64);
	dmaCopy(tileNum6, &BG_TILE_RAM(4)[192], 64);
	dmaCopy(tileNum7, &BG_TILE_RAM(4)[224], 64);
	dmaCopy(tileNum8, &BG_TILE_RAM(4)[256], 64);
	dmaCopy(tileNum9, &BG_TILE_RAM(4)[288], 64);
	dmaCopy(tileNum10, &BG_TILE_RAM(4)[320], 64);
	dmaCopy(tileDot, &BG_TILE_RAM(4)[352], 64); // 11
	dmaCopy(tileDegree, &BG_TILE_RAM(4)[384], 64); // 12
	dmaCopy(tileHz, &BG_TILE_RAM(4)[416], 64); // 13
}

void ClearInfoBG() {
	/*
	 * Clear the info background
	 */
	for(int x = 0; x<32 ; x++){
		for(int y = 0; y<32; y++){
			BG_MAP_RAM(24)[y*32 + x] = 10;
		}
	}
}

void DrawFrequencyMain() {
	int frequency = GetFrequency();

	BG_MAP_RAM(24)[0]=  (frequency / 10000) % 10;
	BG_MAP_RAM(24)[1]=  (frequency / 1000)% 10;
	BG_MAP_RAM(24)[2]=  (frequency / 100) % 10;
	BG_MAP_RAM(24)[3]=  (frequency /10) % 10;
	BG_MAP_RAM(24)[4]=  frequency % 10;
	BG_MAP_RAM(24)[5]= 13;
}

void DrawAmplitudeMain() {
	/*
	 * Draw the amplitude on the main screen
	 */
	float amplitude = GetAmplitude();

	BG_MAP_RAM(24)[32*2 + 0] = (int)amplitude % 2;
	BG_MAP_RAM(24)[32*2 + 1] = 11;
	BG_MAP_RAM(24)[32*2 + 2] = (int)(amplitude * 10) % 10;
	BG_MAP_RAM(24)[32*2 + 3] = (int)(amplitude * 100) % 10;
	BG_MAP_RAM(24)[32*2 + 4] = (int)(amplitude * 1000) % 10;
}

void DrawPhaseMain() {
	/*
	 * Draw the phase on the main screen
	 */
	int phase = GetPhase();

	BG_MAP_RAM(24)[32*4 + 0] = (phase / 100) % 10;;
	BG_MAP_RAM(24)[32*4 + 1] = (phase / 10) % 10;
	BG_MAP_RAM(24)[32*4 + 2] = phase % 10;
	BG_MAP_RAM(24)[32*4 + 3] = 12; // degree symbol
}

void DrawTimeScaleMain() {
	BG_MAP_RAM(24)[32 * 13]= 0;
	BG_MAP_RAM(24)[32 * 13 + 8]= 0;
	BG_MAP_RAM(24)[32 * 13 + 16]= 0;
	BG_MAP_RAM(24)[32 * 13 + 24]= 0;
}

void ZoomIn() {
	actualZoom *= 2;
}

void ZoomOut() {

	if(actualZoom > 1){
		actualZoom /= 2;
		if((actualOffset) >=(256 * (actualZoom-1))){
			actualOffset = actualZoom * 256 - 256;
		}

	}

}
void MoveRight() {

	if((actualOffset + 256 ) < (256 * actualZoom)){
		actualOffset += 10;
		if(actualOffset + 256 > (256 * actualZoom)){
			actualOffset = (256 * actualZoom)-256;
		}
	}
}

void MoveLeft() {

	if(actualOffset > 0){
		actualOffset -= 10;
	}

}


void DrawWaveMain(int16_t * main_buffer, int length) {
	/*
	 * Draw the wave and metrics on the main screen
	 * @param main_buffer : the buffer containing the wave
	 * @param length : the length of the buffer
	*/

	// Metrics draw
	ClearInfoBG();
	DrawFrequencyMain();
	DrawAmplitudeMain();
	DrawPhaseMain();
	DrawTimeScaleMain();

	//  Wave draw

	u16 yellow = ARGB16(1,31,31,0);
	u16 transparent = ARGB16(0,0,0,0);

	for(int x = 0 ; x < 256 ; x ++){
		for(int y = 0 ; y < 192; y++){
			BG_BMP_RAM(5)[x + 256 * y] = transparent;
		}
	}

	WaveType currentWaveType = GetWaveType();

	switch(currentWaveType){

	case SAW_WAVE:
		for(int i = 0; i< length  ; i++){

			int x = (i / (double) length) * 256 * actualZoom ;

			int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			int yNext = ((main_buffer[i+1] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			if( actualOffset < x && x < 256 + actualOffset){

				if(y - yNext > 0){

					for(int i = 0 ; i<=VERTICALRANGE; i++){
						BG_BMP_RAM(5)[x - actualOffset + 256 * (VERTICALRANGE-i + GENERALOFFSET)] = yellow;
					}
				}
				BG_BMP_RAM(5)[x - actualOffset + 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
			}
		}
		break;

	case SIN_WAVE:
		for(int i = 0; i< length  ; i++){

			int x = (i / (double) length) * 256 * actualZoom;

			int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			if( actualOffset < x && x < 256 + actualOffset){
				BG_BMP_RAM(5)[x - actualOffset + 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
			}
		}
		break;

	case WHITE_NOISE:
		for(int i = 0; i< length  ; i++){

			int x = (i / (double) length) * 256 * actualZoom;

			int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			if( actualOffset < x && x < 256 + actualOffset){
				BG_BMP_RAM(5)[x- actualOffset+ 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
			}
		}
		break;
	case SQUARE_WAVE:
		for(int i = 0; i< length  ; i++){

			int x = (i / (double) length) * 256 * actualZoom ;

			int y = ((main_buffer[i] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			int yNext = ((main_buffer[i+1] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			if( actualOffset < x && x < 256 + actualOffset){

				if(y - yNext > 0 || yNext - y > 0 ){

								for(int i = 0 ; i<= VERTICALRANGE; i++){
									BG_BMP_RAM(5)[x - actualOffset + 256 * (VERTICALRANGE-i + GENERALOFFSET)] = yellow;
								}
							}

				BG_BMP_RAM(5)[x - actualOffset+ 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
			}
		}
		break;

	}
}





