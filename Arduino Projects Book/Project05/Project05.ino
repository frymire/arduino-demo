
// Create a servo object
#include <Servo.h>
Servo myServo;

// Connect the potentiometer to analog pin A0.
int const potPin = A0;

// Define variable to read the value from the analog pin and hold the angle for the servo motor.
int potVal;
int angle;

void setup() {

  // Attach the servo on pin 9 to the servo object
  myServo.attach(9);

  // Open a serial connection to your computer.
  Serial.begin(9600);
  
}

void loop() {

  // Read the potentiometer value, and map it to the servo angle.
  potVal = analogRead(potPin); 
  angle = map(potVal, 0, 1023, 0, 179);

  // Set the servo position, and pause to give it a chance to get there.
  myServo.write(angle);
  delay(15);
  
  // Print the potentiometer value and servo motor angle to the serial monitor.
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);
  Serial.print(", Angle: ");
  Serial.println(angle);

}

