
#include <Servo.h>

// Create a servo instance for the lock, and define angle for each state.
// Track whether it is in locked position.
Servo lock;
const int UNLOCKED_ANGLE = 0;
const int LOCKED_ANGLE = 90;
boolean isLocked = false;

// Map pins to the piezo, lock switch, servo, and LEDs.
const int PIEZO_PIN = A0;
const int LOCK_SWITCH_PIN = 2;
const int SERVO_PIN = 9;
const int YELLOW_LED_PIN = 3;
const int GREEN_LED_PIN = 4;
const int RED_LED_PIN = 5;

// Define a threshold for valid knocks, and track the number detected.
const int QUIET_KNOCK = 100;
const int KNOCKS_NEEDED = 3;
int numberOfValidKnocks = 0;


void setup() {
  
  // Start the serial monitor.
  Serial.begin(9600);

  // Set the switch pin as an input
  pinMode(LOCK_SWITCH_PIN, INPUT);

  // Set the LED pins as outputs.
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Connect the lock to its pin, and unlock it.
  lock.attach(SERVO_PIN);
  unlock();
  
}


void unlock() {
  
  // Turn on the green LED and turn off the red one.
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);      

  // Move the servo to the unlocked position, pausing to finish the move.
  lock.write(UNLOCKED_ANGLE);
  delay(200);
      
  // Update the status variable.
  isLocked = false;
  Serial.println("Unlocked.");      
    
}


void loop() {

  // If the box is unlocked and the lock button is pressed, lock the box.
  if (!isLocked && (digitalRead(LOCK_SWITCH_PIN) == HIGH))  {

    // Turn off the green LED and turn on the red one. 
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);      

    // Move the servo to the locked position, pausing to finish the move.
    lock.write(LOCKED_ANGLE);
    delay(200);
      
    // Update the status variable.
    isLocked = true;
    Serial.println("Locked.");      
    
  }

  // If the box is locked...
  if (isLocked) {

    // Listen for a valid knock. 
    if (evaluateKnock(analogRead(PIEZO_PIN)) == true) {
      
      numberOfValidKnocks++;

      // If this is not the final knock, pause to avoid false positives from the "echo".
      if (numberOfValidKnocks < KNOCKS_NEEDED) {
        Serial.print(3 - numberOfValidKnocks);
        Serial.println(" more knocks needed.");
        delay(500);  
      }      
      
    }

    // If enough valid knocks have been detected, unlock the box, and reset the knock count.
    if (numberOfValidKnocks >= KNOCKS_NEEDED) {
      unlock();
      numberOfValidKnocks = 0;
    }
    
  } // if (isLocked)
  
} // loop


// Returns true and flashes the yellow LED if a detected knock is valid.
boolean evaluateKnock(int value) {
  
  // If the knock loud enough...
  if (value > QUIET_KNOCK) {
    
    // Blink the yellow LED.
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(50);
    digitalWrite(YELLOW_LED_PIN, LOW);
    
    // Report a valid knock.
    Serial.print("Detected valid knock of value ");
    Serial.println(value);
    return true;

  }
    
  // Otherwise, report an invalid knock.
  if (value > 10) {
    Serial.print("Detected invalid knock of value ");
    Serial.println(value);    
  }
  return false;

}
