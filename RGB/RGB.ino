
// Demo PWMing a Velleman VMA 318 RGB LED.

const int bluePin = 6;
const int redPin = 9;
const int greenPin = 10;

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {

  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  // analogWrite() assumes an 8-bit value. I'm only using half of the range 
  // here, since the brightness seems to saturate at high values.
  for (int i = 0; i <= 127; i++) { 
    analogWrite(redPin, i);
    delay(8);
  }

  analogWrite(redPin, 0);
  analogWrite(bluePin, 0);

  for (int i = 0; i <= 127; i++) {
    analogWrite(greenPin, i);
    delay(8);
  }

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);

  for (int i = 0; i <= 127; i++) {
    analogWrite(bluePin, i);
    delay(8);
  }
}
