#define DECODE_NEC
#include <IRremote.hpp>
#define IR_Pin 7
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buzzer = 6;
int alarmState = 0;
long timeSinceReset = 0;
long timeAfterTimeSet = 0;
long realTime = 0;
long realTimeMin = 0;  //min
int counter = 0;
int arrTime[] = { 0, 0, 0, 0, 0 };
int arrTimeAlarm[] = {0, 0, 0, 0, 0};
long clockTime = 0;  //sec
long alarmTime = 0;


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(IR_Pin, INPUT);
  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);  // Start the receiver
  setTime();
  setAlarm();
}
void loop() {
  timeSinceReset = millis();
  realTime = clockTime + ((timeSinceReset - timeAfterTimeSet) / 1000);
  if (realTime > 86400) {
    realTime = realTime - 86400;
    alarmState=0;
  }
  realTimeMin = realTime / 60;
  arrTime[0] = realTimeMin / 600;
  realTimeMin = (realTimeMin % 600);
  arrTime[1] = realTimeMin / 60;
  realTimeMin = (realTimeMin % 60);
  arrTime[3] = realTimeMin / 10;
  realTimeMin = (realTimeMin % 10);
  arrTime[4] = realTimeMin / 1;
  realTimeMin = (realTimeMin % 1);
  dispTime();
  dispAlarm();
  if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.command == 70) { //CH
        setAlarm();
      } else if (IrReceiver.decodedIRData.command == 9) { //EQ
        setTime();
      }
      IrReceiver.resume();
  }
  if (arrTime[0] == arrTimeAlarm[0] & arrTime[1] == arrTimeAlarm[1] & arrTime[3] == arrTimeAlarm[3] & arrTime[4] == arrTimeAlarm[4] & alarmState == 0) {
    alarmState = 1;
  }
  if (alarmState == 1) {
    alarm(buzzer, 700, 1000);
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.command == 67) {
        alarmState = 2;
      }
      IrReceiver.resume();
    }
  }
}

void dispTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(6,0);
  lcd.print(arrTime[0]);
  lcd.setCursor(7, 0);
  lcd.print(arrTime[1]);
  lcd.setCursor(8, 0);
  lcd.print(":");
  lcd.setCursor(9, 0);
  lcd.print(arrTime[3]);
  lcd.setCursor(10, 0);
  lcd.print(arrTime[4]);
}

void dispAlarm() {
  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  lcd.setCursor(7, 1);
  lcd.print(arrTimeAlarm[0]);
  lcd.setCursor(8, 1);
  lcd.print(arrTimeAlarm[1]);
  lcd.setCursor(9, 1);
  lcd.print(":");
  lcd.setCursor(10, 1);
  lcd.print(arrTimeAlarm[3]);
  lcd.setCursor(11, 1);
  lcd.print(arrTimeAlarm[4]);
  delay(1000);
}

void setTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Time: ");
  lcd.setCursor(10, 0);
  lcd.print("00:00");
  counter = 10;
  while (counter < 15) {
    if (IrReceiver.decode()) {
      if (counter == 12) {
        counter++;
      }
      if (IrReceiver.decodedIRData.command == 22) {
        lcd.setCursor(counter, 0);
        lcd.print("0");
        delay(500);
        arrTime[counter-10] = 0;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 12) {
        lcd.setCursor(counter, 0);
        lcd.print("1");
        delay(500);
        arrTime[counter-10] = 1;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 24) {
        lcd.setCursor(counter, 0);
        lcd.print("2");
        delay(500);
        arrTime[counter-10] = 2;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 94) {
        lcd.setCursor(counter, 0);
        lcd.print("3");
        delay(500);
        arrTime[counter-10] = 3;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 8) {
        lcd.setCursor(counter, 0);
        lcd.print("4");
        delay(500);
        arrTime[counter-10] = 4;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 28) {
        lcd.setCursor(counter, 0);
        lcd.print("5");
        delay(500);
        arrTime[counter-10] = 5;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 90) {
        lcd.setCursor(counter, 0);
        lcd.print("6");
        delay(500);
        arrTime[counter-10] = 6;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 66) {
        lcd.setCursor(counter, 0);
        lcd.print("7");
        delay(500);
        arrTime[counter-10] = 7;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 82) {
        lcd.setCursor(counter, 0);
        lcd.print("8");
        delay(500);
        arrTime[counter-10] = 8;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 74) {
        lcd.setCursor(counter, 0);
        lcd.print("9");
        delay(500);
        arrTime[counter-10] = 9;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 68) {//|<<
        counter--;
        if (counter==12) {
          counter--;
        }
        lcd.setCursor(counter,0);
        lcd.print("0");
        delay(500);
      }
      IrReceiver.resume();
    }
  }
  timeAfterTimeSet = timeSinceReset;
  clockTime = arrTime[0] * 36000 + arrTime[1] * 3600 + arrTime[3] * 600 + arrTime[4] * 60;
  if(clockTime>86400) {
    setTime();
  }
}

void setAlarm() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Set Alarm: ");
  lcd.setCursor(11, 1);
  lcd.print("00:00");
  counter = 11;
  while (counter < 16) {
    if (IrReceiver.decode()) {
      if (counter == 13) {
        counter++;
      }
      if (IrReceiver.decodedIRData.command == 22) {
        lcd.setCursor(counter, 1);
        lcd.print("0");
        delay(500);
        arrTimeAlarm[counter-11] = 0;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 12) {
        lcd.setCursor(counter, 1);
        lcd.print("1");
        delay(500);
        arrTimeAlarm[counter-11] = 1;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 24) {
        lcd.setCursor(counter, 1);
        lcd.print("2");
        delay(500);
        arrTimeAlarm[counter-11] = 2;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 94) {
        lcd.setCursor(counter, 1);
        lcd.print("3");
        delay(500);
        arrTimeAlarm[counter-11] = 3;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 8) {
        lcd.setCursor(counter, 1);
        lcd.print("4");
        delay(500);
        arrTimeAlarm[counter-11] = 4;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 28) {
        lcd.setCursor(counter, 1);
        lcd.print("5");
        delay(500);
        arrTimeAlarm[counter-11] = 5;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 90) {
        lcd.setCursor(counter, 1);
        lcd.print("6");
        delay(500);
        arrTimeAlarm[counter-11] = 6;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 66) {
        lcd.setCursor(counter, 1);
        lcd.print("7");
        delay(500);
        arrTimeAlarm[counter-11] = 7;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 82) {
        lcd.setCursor(counter, 1);
        lcd.print("8");
        delay(500);
        arrTimeAlarm[counter-11] = 8;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 74) {
        lcd.setCursor(counter, 1);
        lcd.print("9");
        delay(500);
        arrTimeAlarm[counter-11] = 9;
        counter++;
      } else if (IrReceiver.decodedIRData.command == 68) {//|<<
        counter--;
        if (counter==13) {
          counter--;
        }
        lcd.setCursor(counter,1);
        lcd.print("0");
        delay(500);
      }
      IrReceiver.resume();
    }
  }
  alarmState=0;
  alarmTime = arrTimeAlarm[0] * 36000 + arrTimeAlarm[1] * 3600 + arrTimeAlarm[3] * 600 + arrTimeAlarm[4] * 60;
  if(alarmTime>86400) {
    setAlarm();
  }
}

void alarm(byte pin, uint16_t frequency, uint16_t duration)
{ // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
  while (millis()-startTime< duration)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod);
  }
  pinMode(pin,INPUT);
}