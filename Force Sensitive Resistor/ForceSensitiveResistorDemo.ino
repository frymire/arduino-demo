
/* 
 *  Force sensitive resistor demo.
 *  
 *  Connect one end of FSR to power and the other to a 10k pulldown resistor connected to ground.
 *  Connect A0 between the FSR and 10K resistor.
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

const int fsrPin = 0;
int fsrReading;
float fsrVoltage;
float fsrResistance;
float fsrConductance; 
float fsrForce;
 
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
      fsrVoltage = map(fsrReading, 0, 1023, 0, 5000) / 1000.0;

      // fsrVoltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V, so FSR = (Vcc - fsrVoltage)*R/V
      fsrResistance = (5.0 - fsrVoltage) * 10000 / fsrVoltage;

      // Use the two FSR guide graphs to approximate the force.
      fsrConductance = 1000000 / fsrResistance; // microOhms 
      if (fsrConductance <= 1000) {
        fsrForce = fsrConductance / 80;
      } else {
        fsrForce = (fsrConductance - 1000) / 30;
      }

      text[0] = "Reading: " + String(fsrReading, DEC);
      text[1] = "Voltage: " + String(fsrVoltage, 2) + " V";
      if (fsrReading > 0) {
        text[2] = "Resist: " + String(fsrResistance / 1000, 1) + " kOhm";  
      } else {
        text[2] = "Resist: Inf";
      }      
      text[3] = "Force: " + String(fsrForce, 2) + " N";
      text[4] = "Cndct: " + String(fsrConductance, 2) + " uOhm";

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
