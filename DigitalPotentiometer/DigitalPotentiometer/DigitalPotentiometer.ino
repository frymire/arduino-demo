
/*
 * Control a MCP4131 10 kOhms digital resistor.
 * 
 * See http://www.learningaboutelectronics.com/Articles/MCP4131-digital-potentiometer-circuit.php
 */
 
#include <SPI.h>

/*
 * Define a variable to represent the command sent to the
 * potentiometer.
 * 
 * Bits 7 down-to 4 represent the address of the register 
 * on the MCP4131 on which to perform a command. '0000' is
 * the address of the wiper terminal. Bits 3 down-to 2 
 * represent the command to perform. '00' means to write
 * a value to the register, but you can also read a value, 
 * increment it, or decrement it. Finally, bits 1 down-to 0
 * are data bits. Bit 1 is undefined and is fixed at '0'. 
 * Set bit 0 to '0' to use 128 steps.
 * 
 * Therefore, the command to write a value to the register 
 * for the wiper in a 128-step potentiometer is 0b00000000.
 * In this code, we will send the same command each time. 
 */
const byte command = 0x00; 

// Active low chip select
const int CS_n = 10;

void setup() {
  pinMode (CS_n, OUTPUT);
  digitalWrite(CS_n, HIGH);
  SPI.begin();
}

void loop() {
  
  for (int i = 0; i <= 128; i++) {
    writeToDigitalPot(i);
    delay(10);
  }
  
  for (int i = 128; i >= 0; i--) {
    writeToDigitalPot(i);
    delay(10);
  }
}

int writeToDigitalPot(int value) {
  digitalWrite(CS_n, LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(CS_n, HIGH);
}
