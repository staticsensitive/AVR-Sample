/*
Blink LEDS Connected at PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED PD0
#define LED_PORT PORTD
#define LED_DIRECTION DDRD
#define ALL_OUTPUT 0xFF


int main(void) {
    LED_DIRECTION = ALL_OUTPUT;              /* Data Direction Register D: all on */
	LED_PORT &= 0x00;;

  while (1) {

		LED_PORT = 0x81;
		_delay_ms(100);
		LED_PORT = 0x42;
		_delay_ms(100);
		LED_PORT = 0x24;
		_delay_ms(100);
		LED_PORT = 0x18;
		_delay_ms(100);
  }

  return 0;
}
