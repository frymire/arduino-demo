/*
  Demo the GridEYE sensor:  https://www.sparkfun.com/products/14568

  Import the SparkFun GridEYE AMG88 Library.
  
  This example implements a rudimentary heat camera in the serial terminal, using a matrix of ascii
  characters to represent the temperature of each pixel in the device. Start your terminal at 115200 
  and make the window as small as possible for best effect.
*/

#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>

// Use these values (in degrees C) to adjust the contrast
#define COLD 20.0
#define HOT 40.0

// Temperatures are reported by the library as floats, but we will map to 4 categories
GridEYE grideye;

void setup() {
  Wire.begin(); // I2C
  grideye.begin();
  Serial.begin(115200);
}

void printTemperatureCodeOverSerial(float temperature) {  
  int value = map(temperature, COLD, HOT, 0, 3); // map to {0, 1 ,2 , 3}
  if(value == 0) { Serial.print("."); }
  else if(value == 1) { Serial.print("o"); }
  else if(value == 2) { Serial.print("0"); }
  else if(value == 3) { Serial.print("O"); }  
  Serial.print(' ');  
}

void loop() {

  for(unsigned char row = 0; row < 7; row++) {
    // When you decrement the column below zero, the unsigned char value rolls over to 255.
    for (unsigned char col = 7; col < 255; col--) {
      printTemperatureCodeOverSerial(grideye.getPixelTemperature(8*row + col));
    }
    Serial.println();
  }

  // Visually separate the grids. If using a terminal outside Arduino IDE, use clearscreen instead.
  Serial.println();
  Serial.println();

  delay(200);
}
