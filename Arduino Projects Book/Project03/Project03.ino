// Pin A0 will read the voltage from the temperature sensor.
const int sensorPin = A0;

// Assume that we start at 20 degrees C.
const int baselineTemp = 20;

void setup() {

  // Open a serial port.
  Serial.begin(9600);

  // Set pins 3-5 as outputs, and initialize them to LOW.
  for (int pinNumber = 3; pinNumber <= 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  
}

void loop() {

  // Get the analog reading from the sensorPin.
  // Then get the corresponding voltage and temperature.
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  
  // Write the sensor reading to the serial monitor.
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", Temperature: ");
  Serial.println(temperature);

  // If the temperature is below the baseline...
  if (temperature < baselineTemp) {

    // ... turn the LEDs off.
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

  // If the temperature is in a low range...  
  } else if (temperature >= baselineTemp && temperature < baselineTemp + 2) {

    // ... turn on one of the LEDs.
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

  // If the temperature is in a high range... 
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {

    // ... turn on two of the LEDs.
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

  // Finally, if the temperature is above the high threshold...
  } else if (temperature >= baselineTemp + 4) {

    // ... turn on all three LEDs.
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);

  } 

  // Pause for 1 ms to stabilize the sensor reading.
  delay(1);
  
}
