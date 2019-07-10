
// Blink an LED at a rate based on the reading from a potentiometer.

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = 0;
const int ledPin = 13;

int voltageReading = 0; // 10 bit
float voltage = 0;
long lastPrintTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  
  voltageReading = analogRead(potPin);
  
  digitalWrite(ledPin, HIGH);
  delay(voltageReading);
  digitalWrite(ledPin, LOW);
  delay(voltageReading);

  if (millis() - lastPrintTime > 50) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading: ");
    lcd.print(voltageReading);

    voltage = map(voltageReading, 0, 1023, 0, 5000) / 1000.0;
    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(voltage);
    lcd.print(" V");

    lastPrintTime = millis();
  }
}
