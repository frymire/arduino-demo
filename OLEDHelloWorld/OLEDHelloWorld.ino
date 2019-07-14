/*
 * Velleman VMA 437 OLED Hello World
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

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr(0, 22, "Hello World!");
}

void setup(void) {
  // flip screen, if required
   u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if (u8g.getMode() == U8G_MODE_R3G3B2) {
    u8g.setColorIndex(255);     // white
  } else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3); // max intensity
  }
  else if (u8g.getMode() == U8G_MODE_BW) {
    u8g.setColorIndex(1); // pixel on
  }
  else if (u8g.getMode() == U8G_MODE_HICOLOR) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  pinMode(8, OUTPUT);
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  //delay(50);
}
