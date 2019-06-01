
// Set the switch and motor pins.
const int switchPin = 2;
const int motorPin =  9;

// Initialize the switch pin as an input and the motor pin as an output.
void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

// Set the motor state based on the switch.
void loop() {
  digitalWrite(motorPin, digitalRead(switchPin));
}
