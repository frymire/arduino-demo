                                                    /* Blinker Demo II */

#include <avr/io.h>
#include <util/delay.h>

// PB0 is Arduino digital pin 8, the lower left corner of an ATmega328p DIP package.
#define LED      PB0
#define LED_DDR  DDRB
#define LED_PORT PORTB

#define DELAYTIME 20

#define setBit(sfr, bit)     (_SFR_BYTE(sfr) |= (1 << bit))
#define clearBit(sfr, bit)   (_SFR_BYTE(sfr) &= ~(1 << bit))
#define toggleBit(sfr, bit)  (_SFR_BYTE(sfr) ^= (1 << bit))

int main(void) {

  // Init
  setBit(LED_DDR, LED);                      /* set LED pin for output */

  // Mainloop
  while (1) {

    setBit(LED_PORT, LED);
    _delay_ms(DELAYTIME);

    clearBit(LED_PORT, LED);
    _delay_ms(DELAYTIME);

  }
  return 0;                                          /* end mainloop */
}
