#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include "lib/hd44780.h"

int main(void)
{
    while(true) {
	//Setup
    LCD_Setup();
    int hour = 0;
    int minute = 0;
    // Get the current time
    time_t current_time;
    time(&current_time);

	struct tm *local_time = localtime(&current_time);
    hour = local_time->tm_hour;
    minute = local_time->tm_min;

		LCD_GotoXY(0, 0);
		LCD_PrintString("Time: ");
		LCD_PrintInteger(hour);
        LCD_PrintString(":");
		LCD_PrintInteger(minute);
        sleep(1);
    }
}