/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "saw_wave.h"

int main(void) {
	
    consoleDemoInit();
    printf("\nNDSerum\n");

    int length = 0;
    short * array = (short*) malloc(sizeof(short) * 100);

    SawFill(array,15000,&length);

    printf("lenght: %d\n",length);

    for(int i = 0 ; i<length;i++){
    	 printf("%d \n",array[i]);
    }


    while(1){

        swiWaitForVBlank();	
    }
}
