/*
Blink LEDS Connected at PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED PD0
#define LED_PORT PORTD
#define LED_DIRECTION DDRD

int main(void) {
    LED_DIRECTION = (1<<LED);              /* Data Direction Register D: all on */
	LED_PORT &= ~(1<<LED);

  while (1) {

		LED_PORT |= (1<<LED);
		_delay_ms(100);
		LED_PORT &= ~(1<<LED);
		_delay_ms(100);
  }

  return 0;
}
