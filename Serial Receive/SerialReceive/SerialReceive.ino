/*
 * In this demo, the Arduino reads a single char/byte sent over the serial port,
 * and displays information based on it on an LCD.
 * 
 * Wire LED and 100 ohm resistor circuit to pin 13.
 * Wire LCD as in Arduino Projects Book chapter 11.
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin = 13;
int blinkRate = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Blink: ");
}

void loop() {
  if (Serial.available()) {    
    char ch = Serial.read();
    if (isDigit(ch)) { 
      blinkRate = (ch - '0')*100; // ASCII value converted to numeric value
      lcd.setCursor(7, 0); // col, row
      lcd.print(blinkRate);
      lcd.print(" ms  ");
    }
  }

  blink();
}

void blink() {
  digitalWrite(ledPin, HIGH);
  delay(blinkRate);
  digitalWrite(ledPin, LOW);
  delay(blinkRate);
}
