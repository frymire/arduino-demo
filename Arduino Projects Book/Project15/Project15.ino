
// Map pin 2 to the optocoupler.
const int OPTO_PIN = 2;

// Make the pin with the optocoupler an output.
void setup() {  
  pinMode(OPTO_PIN, OUTPUT);
}

void loop() {

  // Flash the optocoupler for 15 ms.
  digitalWrite(OPTO_PIN, HIGH);
  delay(30);
  digitalWrite(OPTO_PIN, LOW);

  // Wait for 2 sec.
  delay(2000);
  
}
