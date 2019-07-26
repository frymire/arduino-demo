
/* 
 *  Short flex sensor demo.
 *  
 *  Connect one end of FSR to power and the other to a 10k pulldown resistor connected to ground.
 *  Connect A0 between the FSR and 10K resistor.
 *  
 *  Resistance Values (a forward flex is toward smooth side, a reverse flex is toward the side with black/white bars)
 *  -90° to 180°: 21.5 kOhms
 *  0°: 35-50 kOhms
 *  45°: 75 kOhms
 *  90°: 125 kOhms
 *  135°: 150 kOhms
 *  180°: 215 kOhms
 *  360°: 250 kOhms
 *  
 *  Adapted from https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr
 */

#include <U8glib.h>

// OLED display parameters.
// 4 lines is recommended, but 5 also works.
#define numLines 4
const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
int deltaRow = 16, firstRow = 14;

long lastPrintTime = 0;

String text[] = {
  "0123456789012345",
  "Hello, world!",
  "Hello, again!",
  "Hi, yet again!",
  "Enough already!"
};

const int fsPin = 0;
int fsReading;
float fsVoltage;
float fsResistance;
float fsrConductance; 
float fsPosition;
 
void setup(void) {

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }  
}
 
void loop(void) {

  u8g.firstPage();  
  do {
    
    if (millis() - lastPrintTime > 50) {
      
      fsReading = analogRead(fsPin);
      fsVoltage = 5.0 - map(fsReading, 0, 1023, 0, 5000) / 1000.0;
      fsResistance = 10000 * fsVoltage / (5.0 - fsVoltage);

      text[0] = "Reading: " + String(fsReading, DEC);
      text[1] = "Voltage: " + String(fsVoltage, 2) + " V";
      text[2] = "Resist: " + String(fsResistance / 1000, 1) + " kOhm";  

      if (fsResistance < 30000) {
        text[3] = "Reversed";
      } else if (fsResistance < 62500) {
        text[3] = "Unflexed";
      } else if (fsResistance < 100000) {
        text[3] = "45 degrees";
      } else if (fsResistance < 137500) {
        text[3] = "90 degrees";
      } else if (fsResistance < 180000) {
        text[3] = "135 degrees";
      } else if (fsResistance < 232500) {
        text[3] = "180 degrees";
      } else {
        text[3] = "360 degrees";
      }

      lastPrintTime = millis();
    }
    draw();
  } while(u8g.nextPage());
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}
