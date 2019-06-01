
// Assign pins to each filtered photoresistor.
const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

// Define variables to hold the values from each sensor.
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

// Assign pins to each LED leg.
const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;

// Define values to write to each LED.
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// Map the 10-bit ADC value to the 8-bit value (0-255) used by analogWrite().
// Normally, you'd just divide by four, but let's scale each color independently.
int transform(int low, int high, int value) {
  int temp = 256.0 * (value - low) / (high - low);
  temp = min(temp, 255);
  temp = max(temp, 0);
  return temp;
}

void setup() {
  
  // Initialize serial communications at 9600 bps.
  Serial.begin(9600);

  // set the digital pins as outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

}

void loop() {

  // Measure each photoresistor.
  redSensorValue = analogRead(redSensorPin);
  greenSensorValue = analogRead(greenSensorPin);
  blueSensorValue = analogRead(blueSensorPin);

  // Transform sensor input values to LED output values.
  redValue = transform(560, 840, redSensorValue);
  greenValue = transform(500, 800, greenSensorValue);
  blueValue = transform(580, 840, blueSensorValue);

  // Pause for stability.
  delay(5);

  // Write the PWM values to the LED pins.
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

  // Print out the raw and transformed values to the serial monitor.
  Serial.print("Raw Values \t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.print(blueSensorValue);
  Serial.print(". Mapped Values \t red: ");
  Serial.print(redValue);
  Serial.print("\t green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

}

