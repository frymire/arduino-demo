
// Blink an LED using an interrupt directly off of the Arduino timer.

#include "TimerOne.h"

const int ledPin = 13;
 
// Set up a timer with a 500,000 microsecond (0.5 s) interval.
// The LED will blink once per second, 1 cycle on-and-off.
void setup() {
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(500000); 
  Timer1.attachInterrupt(timerInterrupt);
}
 
// Custom timer interrupt routine to toggle the LED.
void timerInterrupt() {
  digitalWrite(ledPin, digitalRead(ledPin)^1);
}

void loop() {
  // TODO: Add code here.
}
