#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
//#include "lib/hd44780.h"

int main(void)
{
    int wholeAlarm;
    int alarmHour;
    int alarmMinute;
    printf("Please enter your desired alarm time using military time\n");
    scanf("%d",&wholeAlarm);
    alarmMinute = wholeAlarm % 100;
    alarmHour = wholeAlarm / 100;
    printf("Your alarm is set for %d:%d\n", alarmHour, alarmMinute);
    while(1) {
	//Setup
    //LCD_Setup();
    int hour = 0;
    int minute = 0;
    // Get the current time
    time_t current_time;
    time(&current_time);

	struct tm *local_time = localtime(&current_time);
    hour = local_time->tm_hour;
    minute = local_time->tm_min;
    printf("Time: %d:%d\n",hour,minute);
		/*LCD_GotoXY(0, 0);
		LCD_PrintString("Time: ");
		LCD_PrintInteger(hour);
        LCD_PrintString(":");
		LCD_PrintInteger(minute);*/
        sleep(1);
    if(hour==alarmHour && minute==alarmMinute) {
        printf("ALARM!!!");
        return(0);
    }
    }
}
