/*
 * Velleman VMA 437 OLED Hello World.
 * 
 * Gnd -> Gnd
 * Vcc -> 5V 
 * CLK -> D8
 * MOSI -> D9
 * Res -> Reset
 * CS -> D6
 * DC -> D7
 */

#include "U8glib.h"

const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);

void setup(void) {
  u8g.setRot180(); // flip screen
  u8g.setFont(u8g_font_unifont); // 16 x 16
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while(u8g.nextPage());
}

void draw(void) {

  // 4 lines x 16 characters (recommended for u8g_font_unifont).
  // (0, 12) is the lower left corner of the first character
  u8g.drawStr(0, 12, "Hello, world!");
  u8g.drawStr(0, 28, "Hello, again!");
  u8g.drawStr(0, 44, "Hi, yet again!");
  u8g.drawStr(0, 60, "1234567890123456");  

  // 5 lines x 16 characters.
//  u8g.drawStr(0, 12, "Hello, world!");
//  u8g.drawStr(0, 24, "Hello, again!");
//  u8g.drawStr(0, 36, "Hi, yet again!");
//  u8g.drawStr(0, 48, "Enough already!");
//  u8g.drawStr(0, 60, "1234567890123456");
}
