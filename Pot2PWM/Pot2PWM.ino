
/* 
 * PWM an output pin based on the reading from a potentiometer, 
 * and read the voltage at a second node.
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = 0;
const int nodePin = 1;
const int pwmPin = 9; // 8 bit

int pot = 0; // 10 bit
int node = 0; // 10 bit

long lastPrintTime = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  
  pot = analogRead(potPin);
  analogWrite(pwmPin, pot / 4); // convert 10 bit to 8 bit
  node = analogRead(nodePin);

  if (millis() - lastPrintTime > 50) {
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Pot: ");
    lcd.print(map(pot, 0, 1023, 0, 5000) / 1000.0);
    lcd.print(" V");

    lcd.setCursor(0, 1);
    lcd.print("Node: ");
    lcd.print(map(node, 0, 1023, 0, 5000) / 1000.0);
    lcd.print(" V");

    lastPrintTime = millis();
  }
}
