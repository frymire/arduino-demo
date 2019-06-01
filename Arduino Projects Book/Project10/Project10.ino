
// Track whether the motor is on, and its direction.
bool motorOn = false;
const int LEFT = 0;
const int RIGHT = 1;
int motorDirection = RIGHT;

// Arduino pin 5 detects the state of the on/off switch.
// Declare variables to hold its current and previous values.
const int ON_OFF_PIN = 5;
int onOffState = LOW;
int previousOnOffState = LOW;

// Arduino pin 4 detects the state of the direction-switch pin.
// Declare variables to hold its current and previous values.
const int DIRECTION_SWITCH_PIN = 4;
int directionSwitchState = LOW;
int previousDirectionSwitchState = LOW;

// Arduino pins 2 and 3 connect to H-bridge pins 7 and 2, respectively.
// The motor will rotate left or right, depending on which pin has higher voltage.
const int GO_LEFT_PIN = 2;
const int GO_RIGHT_PIN = 3;

// Arduino pin A0 detects the potentiometer's output, which will control the motor speed.
// We will PMW Arduino pin 9 to control the rotation speed via H-bridge pin 1.
const int POT_PIN = A0;
const int SPEED_PIN = 9;


void setup() {
  
  // Intialize the input pins.
  pinMode(ON_OFF_PIN, INPUT);
  pinMode(DIRECTION_SWITCH_PIN, INPUT);

  // Initialize the output pins, setting the initial speed to LOW.
  pinMode(GO_RIGHT_PIN, OUTPUT);
  pinMode(GO_LEFT_PIN, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
  digitalWrite(SPEED_PIN, LOW);
  
}


void loop() {
  
  // Read the switch controls.
  onOffState = digitalRead(ON_OFF_PIN);
  directionSwitchState = digitalRead(DIRECTION_SWITCH_PIN);

  // The system should change when the user *presses* the switch, not when they release it.
  // So, we will only act if a switch state goes from LOW to HIGH, not from HIGH to LOW.
  
  // If the On/Off button is pressed, switch the state of the motor.
  if ((previousOnOffState == LOW) && (onOffState == HIGH)) {
    motorOn = !motorOn;
  }

  // If the switch-direction button is pressed, switch the direction of the motor.
  if ((previousDirectionSwitchState == LOW) && (directionSwitchState == HIGH)) {
    motorDirection = !motorDirection;
  }
  
  // Store the state of each switch for the next iteration.
  previousOnOffState = onOffState;
  previousDirectionSwitchState = directionSwitchState;

  // Set the motor direction by putting a higher voltage 
  // on the control pin in the desired direction.
  if (motorDirection == RIGHT) {
    digitalWrite(GO_LEFT_PIN, LOW);
    digitalWrite(GO_RIGHT_PIN, HIGH);
  } else {
    digitalWrite(GO_LEFT_PIN, HIGH);
    digitalWrite(GO_RIGHT_PIN, LOW);
  }

  // If the motor is supposed to be on, read the pot and map its 10-bit value 
  // to an 8-bit value to PMW the motor speed. Otherwise, set the speed to 0.
  if (motorOn) {
    analogWrite(SPEED_PIN, analogRead(POT_PIN) / 4);    
  } else { 
    analogWrite(SPEED_PIN, 0);    
  }
  
}
