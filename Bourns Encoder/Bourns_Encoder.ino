
/**
 * Read a Bourns Encoder.
 * 
 * Orient the notch at the top. Connect the middle pin on either side of knob to ground. 
 * Connect the remaining pins in order counter-clockwise from the top left pin to the 
 * sequence of Arduino pins defined in pins[] below.
 * 
 * See https://www.sparkfun.com/products/15036 and
 * https://d3s5r33r268y59.cloudfront.net/datasheets/8759/2017-01-15-20-12-11/ace.pdf
 */

const int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t state = 0;
uint8_t previous_state = 0;

// position2encoding from the data sheet...
//  127,63,62,58,56,184,152,24,
//  8,72,73,77,79,15,47,175,
//  191,159,31,29,28,92,76,12,
//  4,36,164,166,167,135,151,215,
//  223,207,143,142,14,46,38,6,
//  2,18,82,83,211,192,203,235,
//  239,231,199,71,7,23,19,3,
//  1,9,41,169,233,225,229,245,
//  247,243,227,162,131,139,137,129,
//  128,132,148,212,244,240,242,250,
//  251,249,241,209,193,197,196,192,
//  64,66,74,106,122,120,121,125,
//  253,252,248,232,224,226,98,96,
//  32,33,37,53,61,60,188,190,
//  254,126,124,116,112,113,49,48,
//  16,114,146,154,158,30,94,95

const uint8_t encoding2position[256] = {
  0,56,40,55,24,0,39,52,8,57,0,0,23,0,36,13,120,0,41,54,0,0,0,53,7,0,0,0,20,19,125,18,104,105,0,0,25,106,38,0,0,58,0,0,0,0,37,14,119,118,0,0,0,107,0,0,4,0,3,0,109,108,
  2,1,88,0,89,0,0,0,0,51,9,10,90,0,22,11,0,12,0,0,42,43,0,0,0,0,0,0,0,0,21,0,126,127,103,0,102,0,0,0,0,0,0,0,91,0,0,0,0,0,116,117,121,0,115,0,0,0,93,94,92,0,114,95,113,
  0,72,71,0,68,73,0,0,29,0,70,0,69,0,0,35,34,0,0,122,0,74,0,0,30,6,0,123,0,0,0,124,17,0,0,67,0,26,0,27,28,0,59,0,0,0,0,0,15,0,0,0,0,0,0,0,0,5,0,0,0,110,0,111,16,45,84,
  0,0,86,85,0,50,0,0,0,46,0,0,0,33,0,83,0,44,75,0,0,31,0,0,0,0,0,0,0,32,100,61,101,66,0,62,0,49,99,60,0,47,0,0,0,48,77,82,78,65,76,63,0,64,98,81,79,80,97,96,112,0
};

// Since Serial.print(state, BIN) doesn't include leading zeros, write a custom print function.
void printBinary(uint8_t theByte) {
  for (int8_t i = 7; i >= 0; i--)
    Serial.write(bitRead(theByte, i) ? '1' : '0');
}
  
void setup() {
  for (int i = 0; i < 8; i++) { pinMode(pins[i], INPUT_PULLUP); }
  Serial.begin(9600);
}

void loop() {  
  
  state = 0;
  for (int i = 0; i < 8; i++) { bitWrite(state, i, digitalRead(pins[i])); }

  if (state != previous_state) {
    printBinary(state); 
    Serial.print(" ");
    Serial.print(state, DEC);
    Serial.print(" ");
    Serial.println(encoding2position[state], DEC);

    previous_state = state;
    delay(20); // debounce
  }
}
