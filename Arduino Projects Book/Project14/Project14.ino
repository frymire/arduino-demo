
// Initialize serial communication.
void setup() {  
  Serial.begin(9600);
}

// Read the value of the pot on A0, and write it to the serial port,
// first mapping it to 256-bits. Serial.write() will write raw bytes, 
// while println() writes strings. Note that adding other instructions 
// here can make the data stream very choppy.
void loop() {
  Serial.write(analogRead(A0) / 4);
}
