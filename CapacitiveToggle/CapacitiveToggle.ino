
/* 
 *  Capacitive toggle demo.
 *  
 *  Connect A0 and D2 to the out pin on the Capacitive Touch Sensor Breakout.
 *  
 *  See https://www.adafruit.com/product/1375
 */

#include <U8glib.h>

// OLED display parameters.
// 4 lines is recommended, but 5 also works.
#define numLines 4
const int kClkPin = 8;
const int kCOPIPin = 9;
const int kCSPin = 6;
const int kDCPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 oled(kClkPin, kCOPIPin, kCSPin, kDCPin);
int deltaRow = 16, firstRow = 14;

long lastPrintTime = 0;

String text[] = {
  "",
  "",
  "",
  "",
  ""
};

const int kAnalogPin = 0;
int analogReading;
float analogVoltage;

const int kDigitalPin = 2;
int digitalState;

void setup(void) {

  // Set up OLED
  oled.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    oled.setRot180(); // flip screen
    firstRow = 12; 
  }

  // Set pin 2 to receive the result of the switch.
  pinMode(2, INPUT);
}
 
void loop(void) {

  oled.firstPage();  
  do {
    
    if (millis() - lastPrintTime > 50) {

      digitalState = digitalRead(kDigitalPin);
      text[0] = "State: " + String(digitalState, DEC);
      
      analogReading = analogRead(kAnalogPin);
      analogVoltage = map(analogReading, 0, 1023, 0, 3300) / 1000.0;
      text[1] = "Reading: " + String(analogReading, DEC);
      text[2] = "Voltage: " + String(analogVoltage, 2) + " V";
      
      lastPrintTime = millis();
    }
    draw();
  } while(oled.nextPage());
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    oled.drawStr(0, firstRow + deltaRow*i, charBuffer);
  }
}
