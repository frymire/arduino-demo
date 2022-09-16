
/*
 * Demo code for reading IR signals from a remote control (for our sound bar).
 */

#include <U8glib.h>
#include <IRremote.h>

// OLED display parameters.
// 4 lines is recommended, but 5 also works.
#define numLines 4
const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
int deltaRow = 16, firstRow = 14;

const int irReceiverPin = 4;
IRrecv irReceiver(irReceiverPin);
decode_results results;

String text[] = {
  "0123456789012345",
  "Hello, world!",
  "Hello, again!",
  "Hi, yet again!",
  "Enough already!"
};

void setup(){

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }  
    
  irReceiver.enableIRIn();
  irReceiver.blink13(true);
}

void loop(){

  u8g.firstPage();  
  do {
    if (irReceiver.decode(&results)){
      text[0] = text[1];
      text[1] = text[2];
      text[2] = text[3];
      text[3] = String(results.value, HEX) + " " + getKey(results.value);
      irReceiver.resume();
    }
    draw();
  } while(u8g.nextPage());
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}

String getKey(unsigned long code) {

  switch(code) {
    case 0xCA31DA45:
      return "Power";
      break;
    case 0x17112D07:
      return "Source";
      break;
    case 0xCF2F9DAB:
      return "Vol+";
      break;
    case 0xB2BBAC69:
      return "Vol-";
      break;
    case 0x123CD34B:
      return "Mute";
      break;  
    case 0x3CEB5F42:
      return "Repeat";
      break;               
    case 0xB53DCEA6:
      return "Rewind";
      break;  
    case 0x28DE45AA:
      return "Play";
      break;  
    case 0x1E3D4782:
      return "Forwrd";
      break;  
  }

  return "Unknwn";
}
