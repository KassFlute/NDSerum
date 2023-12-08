/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

int main(void) {
	
    consoleDemoInit();
    printf("\nTemplate nds\n");

    while(1)
        swiWaitForVBlank();	
}
