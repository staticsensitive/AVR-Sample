/*
Blink LEDS Connected at PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED PD0
#define LED_PORT PORTD
#define LED_DIRECTION DDRD
#define ALL_OUTPUT 0xFF

uint8_t pattern[4] = {0x81,0x42,0x24,0x18};
int main(void) {
	uint8_t i = 0;
	
    LED_DIRECTION = ALL_OUTPUT;              /* Data Direction Register D: all on */
	LED_PORT &= 0x00;;

  while (1) {

		for(i=0; i<=4; i++){
			LED_PORT = pattern[i];
			_delay_ms(100);
		}
  }

  return 0;
}
