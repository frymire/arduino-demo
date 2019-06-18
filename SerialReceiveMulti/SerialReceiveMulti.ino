/*
 * In this demo, the Arduino reads a null terminated byte sequence sent
 * over the serial port, and displays it as text on an LCD.
 * 
 * Wire the LCD as in Arduino Projects Book chapter 11.
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino is ready.");
  lcd.begin(16, 2);
  lcd.print("Arduino is ready.");
}

void loop() {
 receiveData();
 displayData();
}

/////////////////////////////////////////

const byte numBytes = 32;
byte receivedBytes[numBytes];
boolean newDataAvailable = false;

void receiveData() {

  static byte i = 0;
  byte endMarker = '\n';
  byte receivedByte;
 
  while (Serial.available() > 0 && newDataAvailable == false) {
    
    receivedByte = Serial.read();

    if (receivedByte != endMarker) {
      receivedBytes[i] = receivedByte;
      i++;
      if (i >= numBytes) {
        i = numBytes - 1;
      }
    } else {
      receivedBytes[i] = '\0'; // terminate the string
      i = 0;
      newDataAvailable = true;
    }
  }
}

void displayData() {
  if (newDataAvailable == true) {
    Serial.print("This just in ... ");
    Serial.println((char *) receivedBytes);
    lcd.begin(16, 2);
    lcd.print((char *) receivedBytes);
    newDataAvailable = false;
  }
}
