#include "main_screen.h"

#define VERTICALRANGE 171
#define GENERALOFFSET 9

int actualZoom = 1;

//Empty tile
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

//0
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


//1
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

//2
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

//3
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

//4
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

//5
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

//6
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

//7
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

//8
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

//9
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

//A
u8 tileNum14[64] = {
   0,0,0,0,0,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,9,9,9,9,0,0,
   0,9,9,0,0,9,9,0,
   0,9,9,0,0,9,9,0,
   0,9,9,9,9,9,9,0,
   0,9,9,0,0,9,9,0,
   0,9,9,0,0,9,9,0
};

//E
u8 tileNum15[64] = {
   0,0,0,0,0,0,0,0,
   0,0,9,9,9,9,9,9,
   0,0,9,9,0,0,0,9,
   0,0,9,9,0,9,0,0,
   0,0,9,9,9,9,0,0,
   0,0,9,9,0,9,0,0,
   0,0,9,9,0,0,0,9,
   0,9,9,9,9,9,9,9
};

//I
u8 tileNum16[64] = {
  0,0,0,0,0,0,0,0,
  9,9,9,9,9,9,9,9,
  0,0,0,9,9,0,0,0,
  0,0,0,9,9,0,0,0,
  0,0,0,9,9,0,0,0,
  0,0,0,9,9,0,0,0,
  0,0,0,9,9,0,0,0,
  0,9,9,9,9,9,9,0
};

//M
u8 tileNum17[64] = {
   0,0,0,0,0,0,0,0,
   0,9,9,0,0,0,9,9,
   0,9,9,9,0,9,9,9,
   0,9,9,9,9,9,9,9,
   0,9,9,9,9,9,9,9,
   0,9,9,0,9,0,9,9,
   0,9,9,0,0,0,9,9,
   0,9,9,0,0,0,9,9
};


//N
u8 tileNum18[64] = {
   0,0,0,0,0,0,0,0,
   0,9,9,0,0,0,9,9,
   0,9,9,9,0,0,9,9,
   0,9,9,9,9,0,9,9,
   0,9,9,0,9,9,9,9,
   0,9,9,0,0,9,9,9,
   0,9,9,0,0,0,9,9,
   0,9,9,0,0,0,9,9
};

//P
u8 tileNum19[64] = {
   0,0,0,0,0,0,0,0,
   0,9,9,9,9,9,9,0,
   0,0,9,9,0,0,9,9,
   0,0,9,9,0,0,9,9,
   0,0,9,9,9,9,9,0,
   0,0,9,9,0,0,0,0,
   0,0,9,9,0,0,0,0,
   0,9,9,9,9,0,0,0
};

//T
u8 tileNum20[64] = {
   0,0,0,0,0,0,0,0,
   0,9,9,9,9,9,9,0,
   0,9,0,9,9,0,9,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,9,9,9,9,0,0
};

//X
u8 tileNum21[64] = {
   0,0,0,0,0,0,0,0,
   0,9,9,0,0,0,9,9,
   0,0,9,9,0,9,9,0,
   0,0,0,9,9,9,0,0,
   0,0,0,9,9,9,0,0,
   0,0,9,9,0,9,9,0,
   0,9,9,0,0,0,9,9,
   0,9,9,0,0,0,9,9
};

u8 tilePlus[64] = {
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   9,9,9,9,9,9,9,9,
   9,9,9,9,9,9,9,9,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0,
   0,0,0,9,9,0,0,0
};

void InitMainScreen() {
	//Initialization of the VRAMs
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG;

	//Initialization of the main engine
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE;

	//Setup of Background 3
	BGCTRL[3] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(BGMainBitmap,BG_BMP_RAM(0),BGMainBitmapLen/2);

	swiCopy(BGMainPal,BG_PALETTE,BGMainPalLen/2);

	//Setup of Background 2
	BGCTRL[2] = BG_BMP_BASE(5) | BgSize_B16_256x256;

	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	//custom colors for tiles
	BG_PALETTE[9] = RGB15(31,31,31);

	//Setup of Background 0
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
	dmaCopy(tileDot, &BG_TILE_RAM(4)[352], 64); //11
	dmaCopy(tileDegree, &BG_TILE_RAM(4)[384], 64); // 12
	dmaCopy(tileHz, &BG_TILE_RAM(4)[416], 64); // 13
	dmaCopy(tileNum14, &BG_TILE_RAM(4)[448], 64); //A
	dmaCopy(tileNum15, &BG_TILE_RAM(4)[480], 64);//E
	dmaCopy(tileNum16, &BG_TILE_RAM(4)[512], 64);//I
	dmaCopy(tileNum17, &BG_TILE_RAM(4)[544], 64);//M
	dmaCopy(tileNum18, &BG_TILE_RAM(4)[576], 64);//N
	dmaCopy(tileNum19, &BG_TILE_RAM(4)[608], 64);//P
	dmaCopy(tileNum20, &BG_TILE_RAM(4)[640], 64);//T
	dmaCopy(tileNum21, &BG_TILE_RAM(4)[672], 64);//X
	dmaCopy(tilePlus, &BG_TILE_RAM(4)[704], 64);//22
}

void ClearInfoBG() {

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
	BG_MAP_RAM(24)[5]= 13; //Hz symbol
}

void DrawAmplitudeMain() {

	float amplitude = GetAmplitude();

	BG_MAP_RAM(24)[32*2 + 0] = (int)amplitude % 2;
	BG_MAP_RAM(24)[32*2 + 1] = 11;
	BG_MAP_RAM(24)[32*2 + 2] = (int)(amplitude * 10) % 10;
	BG_MAP_RAM(24)[32*2 + 3] = (int)(amplitude * 100) % 10;
	BG_MAP_RAM(24)[32*2 + 4] = (int)(amplitude * 1000) % 10;
}

void DrawPhaseMain() {

	int phase = GetPhase();

	BG_MAP_RAM(24)[32*4 + 0] = (phase / 100) % 10;;
	BG_MAP_RAM(24)[32*4 + 1] = (phase / 10) % 10;
	BG_MAP_RAM(24)[32*4 + 2] = phase % 10;
	BG_MAP_RAM(24)[32*4 + 3] = 12; // degree symbol
}

void DrawTimeScaleMain() {

	int frequency = GetFrequency();

	//time interval of a period in ms
	double interval = 1 / (double) frequency * 1000;

	//clamp to 999ms
	int intervalFour = MIN(999,(interval/4.0 ) * actualZoom);
	int intervalTwo = MIN(999,(interval/2.0 ) * actualZoom);

	//Displays + if bigger than 999
	if(intervalFour >= 999){
		BG_MAP_RAM(24)[32 * 13 + 27]= 22;
		BG_MAP_RAM(24)[32 * 13 + 11]= 22;
	}
	if(intervalTwo >= 999){
			BG_MAP_RAM(24)[32 * 13 + 3]= 22;
		}


	BG_MAP_RAM(24)[32 * 13]= (intervalTwo/100) % 10;;
	BG_MAP_RAM(24)[32 * 13 + 1]= (intervalTwo/10) % 10;;
	BG_MAP_RAM(24)[32 * 13 + 2]= intervalTwo % 10;

	BG_MAP_RAM(24)[32 * 13 + 8]= (intervalFour/100) % 10;
	BG_MAP_RAM(24)[32 * 13 + 9]= (intervalFour/10) % 10;
	BG_MAP_RAM(24)[32 * 13 + 10]= intervalFour % 10;

	BG_MAP_RAM(24)[32 * 13 + 16]= 0;

	BG_MAP_RAM(24)[32 * 13 + 24]= (intervalFour/100) % 10;
	BG_MAP_RAM(24)[32 * 13 + 25]= (intervalFour/10) % 10;
	BG_MAP_RAM(24)[32 * 13 + 26]= intervalFour % 10;
}

void DrawText(){

	//AMP
	BG_MAP_RAM(24)[17]= 14;
	BG_MAP_RAM(24)[18]= 17;
	BG_MAP_RAM(24)[19]= 19;

	//TIME
	BG_MAP_RAM(24)[10*32 + 28]= 20;
	BG_MAP_RAM(24)[10*32 + 29]= 16;
	BG_MAP_RAM(24)[10*32 + 30]= 17;
	BG_MAP_RAM(24)[10*32 + 31]= 15;

	//MAX
	BG_MAP_RAM(24)[0*32 +12]= 17;
	BG_MAP_RAM(24)[0*32 +13]= 14;
	BG_MAP_RAM(24)[0*32 + 14]= 21;

	//MIN
	BG_MAP_RAM(24)[23*32 +12]= 17;
	BG_MAP_RAM(24)[23*32 +13]= 16;
	BG_MAP_RAM(24)[23*32 + 14]= 18;

}



void ZoomIn() {

	actualZoom *= 2;
}

void ZoomOut() {

	if(actualZoom > 1){
		actualZoom /= 2;
	}

}

void DrawWaveMain(int16_t * main_buffer, int length) {

	// Metrics draw
	ClearInfoBG();
	DrawFrequencyMain();
	DrawAmplitudeMain();
	DrawPhaseMain();
	DrawTimeScaleMain();
	DrawText();

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
		for(int i = 0; i< length * actualZoom ; i++){

			int x = ((i / (double) length) * 256) /actualZoom ;

			int y = ((main_buffer[i % length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			int yNext = ((main_buffer[(i+1) % length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;


				if(y - yNext > 0){

					for(int i = yNext ; i<= y; i++){
						BG_BMP_RAM(5)[x  + 256 * (VERTICALRANGE-i + GENERALOFFSET)] = yellow;
					}
				}
				BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-y + GENERALOFFSET )] = yellow;
		}
		break;

	case SIN_WAVE:
		for(int i = 0; i< length * actualZoom ; i++){

			int x = ((i / (double) length ) * 256) / actualZoom;

			int y = ((main_buffer[i%length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;

		}
		break;

	case WHITE_NOISE:
		for(int i = 0; i< length * actualZoom ; i++){

			int x = ((i / (double) length ) * 256) / actualZoom;
         
			int y = ((main_buffer[i%length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
		}
		break;
	case SQUARE_WAVE:
		for(int i = 0; i< length * actualZoom  ; i++){

			int x = ((i / (double) length) * 256) / actualZoom ;

			int y = ((main_buffer[i % length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

			int yNext = ((main_buffer[(i+1) % length] + MAXVALUE) / ((double)2*MAXVALUE)) * VERTICALRANGE;

				if(y - yNext > 0){

					for(int i = yNext ; i<=  y; i++){
						BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-i + GENERALOFFSET)] = yellow;
					}
				}
				if(yNext - y > 0 ){

					for(int i = y ; i<= yNext; i++){
						BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-i + GENERALOFFSET)] = yellow;
					}
				}

				BG_BMP_RAM(5)[x + 256 * (VERTICALRANGE-y + GENERALOFFSET)] = yellow;
		}
		break;

	}
}





