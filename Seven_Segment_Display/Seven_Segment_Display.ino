
#include "TimerOne.h"
#include "TM1637.h"

const int clockPin = 7;
const int dataIOPin = 6;
TM1637 tm1637(clockPin, dataIOPin);

unsigned char hour = 12;
unsigned char minute = 0;
unsigned char second = 0;
unsigned char halfSecond = 0;
int8_t displayValues[] = {0x00,0x00,0x00,0x00};
boolean showColon = HIGH;
boolean displayUpdatePending = false;

void setup() {
  tm1637.set();
  tm1637.init();
  tm1637.point(HIGH); // Set whether to display the middle colon.
  Timer1.initialize(500000); //timing for 500ms
  Timer1.attachInterrupt(updateTime);  
}

void updateTime() {
  
  halfSecond++;
  showColon = !showColon;
  
  if(halfSecond == 2) {    
    halfSecond = 0;
    second++;
    if(second == 60) {
      second = 0;
      minute++;
      if(minute == 60) {
        minute = 0;
        hour++;
        if(hour == 24) hour = 0; 
      }      
    }
  }

  displayUpdatePending = true;
}

void loop() {  
  if(displayUpdatePending == true) {
    updateDisplayValues();
    tm1637.display(displayValues);
    displayUpdatePending = false;
  }
}

void updateDisplayValues(void) {
  // Could replace with hours and minutes here.
  displayValues[0] = minute / 10;
  displayValues[1] = minute % 10;
  displayValues[2] = second / 10;
  displayValues[3] = second % 10;
  tm1637.point(showColon);
}
