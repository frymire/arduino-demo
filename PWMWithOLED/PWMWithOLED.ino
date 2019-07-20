
// PWM a pin based based on the reading from a potentiometer.

#include "U8glib.h"

const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);

const int potPin = 0;
const int pwmPin = 11;

// 4 lines is recommended, but 5 also works.
#define numLines 4

const boolean flipped = false;
int deltaRow = 16, firstRow = 14;

String text[] = {
  "1234567890123456",
  "Hello, world!",
  "Hello, again!",
  "Hi, yet again!",
  "Enough already!"
};

int voltageReading = 0; // 10 bit
float voltage = 0;
int pwmValue = 0; // 8 bit
float dutyCycle = 0.0;
long lastPrintTime = 0;

void setup() {

  u8g.setFont(u8g_font_unifont); // 16 x 16  
  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }
  
  if (numLines == 5) { deltaRow = 12; }    
}

void loop() {
  
  u8g.firstPage();  
  do {
    
    voltageReading = analogRead(potPin);
    pwmValue = map(voltageReading, 0, 1023, 0, 255);
    analogWrite(pwmPin, pwmValue);

    if (millis() - lastPrintTime > 50) {
      
      voltage = map(voltageReading, 0, 1023, 0, 5000) / 1000.0;
      dutyCycle = 100 * pwmValue / 256.0;
      text[0] = "Reading: " + String(voltageReading, DEC);
      text[1] = "Voltage: " + String(voltage, 2) + " V";
      text[2] = "PWM Value: " + String(pwmValue, DEC);
      text[3] = "PWM Duty: " + String(dutyCycle, 1) + "%";
      
      lastPrintTime = millis();
    }
    draw();
  } while(u8g.nextPage());

}

void draw(void) {

  char charBuffer[16];

  // Display each line. The first two parameters of drawStr() specify the lower left corner of the first character.
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}
