/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

int main(void) {
	
    consoleDemoInit();
    printf("\nNDSerum\n");

    while(1)
    	printf("\nSUS BIGUS\n");
        swiWaitForVBlank();	
}
