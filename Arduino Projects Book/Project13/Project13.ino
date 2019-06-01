
// User libraries must be located in the Arduino/libraries directory.
#include <CapacitiveSensor.h>

// Instantiate a capacitive sensor instance with pin 4 as 
// the current source and pin 2 as the detector.
CapacitiveSensor foilSensor = CapacitiveSensor(4, 2);

// Map the LED to pin 12, and set a threshold for lighting it.
const int LED_PIN = 12;
const int THRESHOLD = 500;

// Start a serial connection, and set the LED pin as an output.
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  // Measure the capacitative sensor with 30 samples.
  long sensorValue = foilSensor.capacitiveSensor(30);
  Serial.println(sensorValue);

  // Set the LED depending on the reading relative to the THRESHOLD.
  digitalWrite(LED_PIN, sensorValue > THRESHOLD);

}
