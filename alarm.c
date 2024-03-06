#include <stdint.h>
#include <stdio.h>
#include "C:/Arduino_Code/lcd/lib/HD44780.h"
#include "lib/src/remotes.h"


int main(void)
{
	//Setup
	LCD_Setup();
	LCD_Clear();
	initIR(5,0x00FF, *IR_REMOTE);
	
	getIRCommandRec();
	
	print(getIRCommandRec());
	while (1);
	
	return 0;
}
