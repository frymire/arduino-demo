
// Declare a variable to hold the value of the photoresistor.
int sensorValue;

// Declare variables to calibrate sensor values.
int sensorLow = 1023;
int sensorHigh = 0;

// Define pin #8 as the piezo pin.
const int piezoPin = 8;

// You can vary the duration of the tone and pause for different effects.
const int toneDuration = 800;
const int pauseDuration = 200;

void setup() {

  // Calibrate for five seconds.
  while (millis() < 5000) {

    // Record the photoresistor sensor value.
    sensorValue = analogRead(A0);
    
    // Reset the maximum sensor value, if applicable.
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    
    // Reset the minimum sensor value, if applicable.
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  
}

void loop() {
  
  // Map the reading from the photoresistor on A0 to a pitch.
  int pitch = map(analogRead(A0), sensorLow, sensorHigh, 50, 4000);

  // Play the tone, then pause.
  tone(piezoPin, pitch, toneDuration);
  delay(pauseDuration);
  
}

