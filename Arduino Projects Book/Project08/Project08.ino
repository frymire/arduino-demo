
// Set the next LED to be lit.
int led = 2;

// Store the last time an LED was updated, and the number
// of milliseconds to wait to light each subsequent LED.
unsigned long previousTime = 0; 
const long interval = 1000; 

// Define the tilt switch pin.
const int switchPin = 8;

void setup() {
  
  // Set pins 2-7 as outputs to LEDs.
  for (int pin = 2; pin <= 7; pin++) {
    pinMode(pin, OUTPUT);
  }
  
  // Set the tilt switch pin as an input.
  pinMode(switchPin, INPUT);
  
}

void loop() {
  
  // Get the since the program start.
  unsigned long currentTime = millis();

  // Check whether the interval to light the next LED has passed.
  if (currentTime - previousTime > interval) {
    
    // Turn the LED on, and increment the LED variable.
    digitalWrite(led, HIGH);
    led++;
    
    // Update the time of the last LED change.
    previousTime = currentTime;
    
  }

  // If the switch is disconnected...
  if (digitalRead(switchPin) == LOW) {

    // Turn off all of the LEDs.
    for (int x = 2; x <= 7; x++) {
      digitalWrite(x, LOW);
    }

    // Reset the timer, and reset the LED counter.
    previousTime = currentTime;
    led = 2;
    
  }
  
}

