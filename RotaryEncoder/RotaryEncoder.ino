
/* 
 *  Uses interrputs and software debouncing to detect clicks in a Bourns PEC11 rotary encoder.
 *  
 *  On the side with 3 pins, connect the left to D2, the middle to ground, and the right to D3.
 *  The side with 2 pins is for the push-in switch. Connect one to ground and the other to D4.
 *  
 *  Adapted from example [here](https://playground.arduino.cc/Main/RotaryEncoders/) with title, 
 *  "Another Interrupt Library THAT REALLY WORKS".
 *  Bourns PEC11: https://www.adafruit.com/product/377 
 */

// Usually, the rotary encoders three pins have the ground pin in the middle.
// On Arduino Uno and Nano boards, pins 2 and 3 support interrupts.
enum PinAssignments {
  pinA = 2, 
  pinB = 3, 
  clearButton = 4
};

volatile int clicks = 0; // dial counter 
int lastReportedClicks = 0; // change detection
static boolean debouncing = false;

// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;

void setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(clearButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA), pinAChangeInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), pinBChangeInterrupt, CHANGE);
  Serial.begin(9600);
  Serial.println("Clicks: " + String(clicks, DEC));
}

void loop() {
  debouncing = true; // reset the debouncer
  if (lastReportedClicks != clicks) {
    Serial.println("Clicks: " + String(clicks, DEC));
    lastReportedClicks = clicks;
  }
  if (digitalRead(clearButton) == LOW) clicks = 0;
}

void pinAChangeInterrupt() {
  
  if (debouncing) delay(1);

  // Test transition, did things really change?
  if (digitalRead(pinA) != A_set) { // debounce once more
    A_set = !A_set;
    if (A_set && !B_set) clicks += 1; // increment counter if A leads B
    debouncing = false;
  }
}

void pinBChangeInterrupt() { 
  
  if (debouncing) delay(1);

  // Test transition, did things really change?
  if (digitalRead(pinB) != B_set) {
    B_set = !B_set;
    if (B_set && !A_set) clicks -= 1; // decrement counter if B leads A
    debouncing = false;
  }
}
