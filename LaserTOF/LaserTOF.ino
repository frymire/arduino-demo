
/*
 * Demo code for the VL6180X LIDAR time of flight sensor, effective between 5 - 100 mm (~200 mm in good conditions).
 * 
 * NOTE: The VL6180X has a default I2C address of 0x29.
 * 
 * Vin: 5V
 * Gnd: Gnd
 * SCL: SCL
 * SDA: SDA
 * 
 * See https://learn.adafruit.com/adafruit-vl6180x-time-of-flight-micro-lidar-distance-sensor-breakout/wiring-and-test
 */

#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X laserTOF = Adafruit_VL6180X();

#include <U8glib.h>

// OLED display parameters.
#define numLines 4 // 4 lines is recommended, but 5 also works.

const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
int deltaRow = 16, firstRow = 14;
String text[] = { "Lux: N/A", "Range: N/A", "Status: Okay", "", "" };


void setup() {

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }  
    
  laserTOF.begin();
}

void loop() {
  
  float lux = laserTOF.readLux(VL6180X_ALS_GAIN_5);
  uint8_t range = laserTOF.readRange();
  uint8_t status = laserTOF.readRangeStatus();

  text[0] = "Lux: " + String(lux, 2);
  if (status == VL6180X_ERROR_NONE) {
    text[1] = "Range: " + String(range, DEC) + " mm";
    text[2] = "System Okay";
  } else {
    text[1] = "Range: N/A";
    reportErrorStatus(status);
  }

  u8g.firstPage();
  do {
    draw();
  } while(u8g.nextPage());
  
  delay(5);
}

// If some error occurred, print it out.
void reportErrorStatus(uint8_t status) {
  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
    text[2] = "System Error";
  } else if (status == VL6180X_ERROR_ECEFAIL) {
    text[2] = "ECE Failure";
  } else if (status == VL6180X_ERROR_NOCONVERGE) {
    text[2] = "No Convergence";
  } else if (status == VL6180X_ERROR_RANGEIGNORE) {
    text[2] = "Ignoring range";
  } else if (status == VL6180X_ERROR_SNR) {
    text[2] = "Sgnl/Nse Error";
  } else if (status == VL6180X_ERROR_RAWUFLOW) {
    text[2] = "Raw Underflow";
  } else if (status == VL6180X_ERROR_RAWOFLOW) {
    text[2] = "Raw Overflow";
  } else if (status == VL6180X_ERROR_RANGEUFLOW) {
    text[2] = "Range Underflow";
  } else if (status == VL6180X_ERROR_RANGEOFLOW) {
    text[2] = "Range Overflow";
  }
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}
