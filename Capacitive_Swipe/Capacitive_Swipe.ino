/**
 *  Demonstration of the SparkFun CAP1203 capacitive swipe sensor. Swipe right to turn on an LED or left to turn it off.
 *  NOTE: You have to swipe very slowly.
 */
  
#include <Wire.h>
#include "SparkFun_CAP1203.h" // Get the library here: http://librarymanager/All#SparkFun_CAP1203

int led = 13;
CAP1203 sensor;

void setup() {
  Wire.begin(); // join I2C bus
  sensor.begin();
}

void loop() {
  if (sensor.isRightSwipePulled()) { digitalWrite(led, HIGH);}
  if (sensor.isLeftSwipePulled()) { digitalWrite(led, LOW); }
}
