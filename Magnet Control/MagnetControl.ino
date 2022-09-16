
// Control two magnets based on a switch and a potentiometer reading.

//#include <U8glib.h>
//
//// OLED display parameters.
//// 4 lines is recommended, but 5 also works.
//#define numLines 4
//const int clkPin = 8;
//const int mosiPin = 9;
//const int csPin = 6;
//const int dcPin = 7;
//const boolean flipped = false;
//U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
//int deltaRow = 16, firstRow = 14;

//const int potPin = 0;
const int touchPin = 2;
boolean touchValue = LOW;
const int pwmPin1 = 10;
const int pwmPin2 = 11;

String text[] = {
  "0123456789012345",
  "Hello, world!",
  "Hello, again!",
  "Hi, yet again!",
  "Enough already!"
};

//int voltageReading = 0; // 10 bit
//float voltage = 0;
int pwmValue = 0; // 8 bit
float dutyCycle = 0.0;
//long lastPrintTime = 0;

void setup() {

  pinMode(touchPin, INPUT);
  
//  // Set up OLED
//  u8g.setFont(u8g_font_unifont); // 16 x 16
//  if (numLines == 5) { deltaRow = 12; }  
//  if (flipped) {
//    u8g.setRot180(); // flip screen
//    firstRow = 12; 
//  }
}

void loop() {
  
//  u8g.firstPage();  
//  do {
    
//    voltageReading = analogRead(potPin);
//    pwmValue = map(voltageReading, 0, 1023, 0, 255);
    pwmValue = 255;

    touchValue = digitalRead(touchPin);
    if (touchValue == HIGH) {
      analogWrite(pwmPin1, 0);
      analogWrite(pwmPin2, pwmValue);
    } else {
      analogWrite(pwmPin1, pwmValue);
      analogWrite(pwmPin2, 0);
    }
    
//    if (millis() - lastPrintTime > 50) {
//      
//      voltage = map(voltageReading, 0, 1023, 0, 5000) / 1000.0;
//      dutyCycle = 100 * pwmValue / 256.0;
//      text[0] = "Reading: " + String(voltageReading, DEC);
//      text[1] = "Voltage: " + String(voltage, 2) + " V";
//      text[2] = "PWM Value: " + String(pwmValue, DEC);
//      text[3] = "PWM Duty: " + String(dutyCycle, 1) + "%";
//      
//      lastPrintTime = millis();
//    }
//    draw();
//  } while(u8g.nextPage());

}

//void draw(void) {
//  char charBuffer[16];
//  for (int i = 0; i < numLines; i++) {
//    text[i].toCharArray(charBuffer, 16);
//    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
//  }
//}
