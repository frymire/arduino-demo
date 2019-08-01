
#include <U8glib.h>
#include <Wire.h>
#include "Adafruit_MLX90393.h"

// OLED display parameters.
#define numLines 4 // 4 lines is recommended, but 5 also works.
const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
int deltaRow = 16, firstRow = 14;
String text[] = { "", "", "", "", "" };

Adafruit_MLX90393 magnetometer = Adafruit_MLX90393();

void setup(void) {

  magnetometer.begin();

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }      
}

void loop(void) {
  
  float x, y, z, magnitude;

  magnetometer.readData(&x, &y, &z);
  magnitude = sqrt(x*x + y*y + z*z);

  text[0] = "X: " + String(x, 3) + " uT";
  text[1] = "Y: " + String(y, 3) + " uT";
  text[2] = "Z: " + String(z, 3) + " uT";
  text[3] = "R: " + String(magnitude, 3) + " uT";
    
  u8g.firstPage();
  do {
    draw();
  } while(u8g.nextPage());
    
  delay(20);
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}
