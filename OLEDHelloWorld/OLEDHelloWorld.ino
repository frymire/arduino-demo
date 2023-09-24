/*
 * Velleman VMA 437 OLED Hello World.
 * 
 * Gnd -> Gnd
 * Vcc -> 5V 
 * CLK -> D7
 * MOSI -> D6
 * Res -> Reset
 * CS -> D10
 * DC -> D9
 */

#include "U8glib.h"

const int clkPin = 7;
const int mosiPin = 6;
const int csPin = 10;
const int dcPin = 9;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);

// 4 lines is recommended, but 5 also works.
#define numLines 4

const boolean flipped = true;
int deltaRow = 16, firstRow = 14;

char const* text[] = {
  "0123456789ABCDEF",
  "Hello, world!",
  "Hello, again!",
  "Hi, yet again!",
  "Enough already!"
};

//char const* text[] = {
//  "Please...",
//  "   don't touch!",
//  "Por favor...",
//  "   no tocar!",
//  ""
//};

void setup(void) {
  
  u8g.setFont(u8g_font_unifont); // 16 x 16  
  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }
  
  if (numLines == 5) { deltaRow = 12; }
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while(u8g.nextPage());
}

void draw(void) {  
  for (int i = 0; i < numLines; i++) {
    // The first two parameters specify the lower left corner of the first character.
    u8g.drawStr(0, firstRow + i*deltaRow, text[i]);
  }
}
