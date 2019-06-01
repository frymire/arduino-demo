
// Store the frequencies of middle C, D, E, and F notes.
//int notes[] = {262,294,330,349};
const int C = 262;
const int D = 294;
const int E = 330;
const int F = 349;

// Define the piezo pin.
const int piezoPin = 8;


//Start the serial monitor.
void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // Read the input on pin A0, and write it to the Serial Monitor.
  int keyVal = analogRead(A0);
  Serial.println(keyVal);

  // Play the note corresponding to the measured value.
  if (keyVal == 1023) {
    tone(piezoPin, C);
  } else if (keyVal >= 990 && keyVal <= 1010) {
    tone(piezoPin, D);
  } else if (keyVal >= 505 && keyVal <= 515) {
    tone(piezoPin, E);
  } else if (keyVal >= 230 && keyVal <= 240) {
    tone(piezoPin, F);
  } else {
    noTone(piezoPin);
  }
  
}

