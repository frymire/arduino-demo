
// Track whether the switch is open (LOW) or closed (HIGH).
int switchState = LOW;

void setup() {

  // Set pin 2 to receive the result of the switch.
  pinMode(2, INPUT);

  // Set pins 3-5 to produce output.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
}

void loop() {

  // Get the state of the voltage on pin 2.
  switchState = digitalRead(2);

  // If the switch if open, the voltage will be low...
  if (switchState == LOW) {

    // ...so turn the green light on and the red light off.
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    
  } else { // Otherwise, if the switch is closed, blink the lights.

    // Turn the red lights on and the green light off, then pause for a bit.
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(100);

    // Then, toggle the LEDs, and pause again.
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(100);

  }
}
