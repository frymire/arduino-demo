
/* 
 *  Soft potentiometer demo.
 *  
 *  Connect one end pin to power and the other to a 10k pulldown resistor connected to ground.
 *  Connect A0 to the middle pin.
 *  
 *  See https://www.adafruit.com/product/1069 and https://www.adafruit.com/product/178
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
  "",
  "",
  "",
  "Hey, there.",
  ""
};

const int fsrPin = 0;
int fsrReading;
float fsrVoltage;
float fsrResistance;
 
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
      
      fsrReading = analogRead(fsrPin);
      fsrVoltage = map(fsrReading, 0, 1023, 0, 3300) / 1000.0;
      fsrResistance = (3.3 - fsrVoltage) * 10000 / fsrVoltage;

      text[0] = "Reading: " + String(fsrReading, DEC);
      text[1] = "Voltage: " + String(fsrVoltage, 2) + " V";
      if (fsrReading > 0) {
        text[2] = "Resist: " + String(fsrResistance / 1000, 1) + " kOhm";  
      } else {
        text[2] = "Resist: Inf";
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
