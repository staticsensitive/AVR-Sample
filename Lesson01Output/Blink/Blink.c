/*
Blink LEDS Connected at PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {
    DDRD = 0b11111111;              /* Data Direction Register D: all on */

  while (1) {

		PORTD |= 0xFF;
		_delay_ms(100);
		PORTD &= 0x00;
		_delay_ms(100);
  }

  return 0;
}
