
/*
 * Measure the sound level using an 20 Hz - 20 kHz electret microphone with a MAX 4466 amplifier.
 * 
 * NOTE: The Arduino is sampling at about 9 kHz. This sketch returns the max 
 * range in voltage observed over ~900 samples over a 100 ms sampling window.
 * 
 * Vcc -> 3.3V (5V works, but 3.3V is recommended since it is quieter)
 * Gnd -> Gnd
 * Out -> A0;
 * 
 * Also, the DC bias is Vcc / 2, so the reading will be near 1.65 V when it is quiet.
 * 
 * Adapted from https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 */

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
String text[] = { "", "", "", "", "" };

const int sensorPin = A0;
const int sampleTime = 100; // in mS (100 ms = 10 Hz)
unsigned int sample;
 
void setup() {

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }  
}

void loop() {

  // We'll measure the min and max levels over the sample window.
  unsigned int signalMin = 1024;
  unsigned int signalMax = 0;
  unsigned long startTime = millis();

  // Collect data over the sampling period.
  while (millis() < startTime + sampleTime) {
    sample = analogRead(sensorPin);
    if (sample > signalMax) {
      signalMax = sample;
    } else if (sample < signalMin) {
      signalMin = sample;
    }
  }

  int range = signalMax - signalMin;
  double voltage = 5.0*range/1024;
  text[0] = "Min: " + String(signalMin, DEC);
  text[1] = "Max: " + String(signalMax, DEC);
  text[2] = "Range: " + String(range, DEC);
  text[3] = "Voltage: " + String(voltage, 2) + " V";

  u8g.firstPage();
  do {
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
