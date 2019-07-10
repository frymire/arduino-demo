/*
 * Demo reading an HC-SR04 ultrasonic sensor.
 * 
 * Adapted from code by Rui Santos, https://randomnerdtutorials.com
 *
 *  Ultrasonic sensor Pins:
 *      VCC: +5VDC
 *      Trig : Trigger (INPUT) - Pin 9
 *      Echo: Echo (OUTPUT) - Pin 10
 *      GND: GND
 */
 
int triggerPin = 9;
int echoPin = 10;
long duration, cm, inches;
 
void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance.
  // The speed of sound is: 343 m/s = 0.0343 cm/uS = 1/29.1 cm/uS
  // Or in inches: 13503.9 in/s = 0.0135 in/uS = 1/74 in/uS
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}
