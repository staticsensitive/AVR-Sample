/*
Blink LEDS Connected at PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LED PD0
#define LED_PORT PORTD
#define LED_DIRECTION DDRD
#define ALL_OUTPUT 0xFF
#define SHIFT_LEFT 0x00
#define SHIFT_RIGHT 0x01

int main(void) {
	uint8_t dir = 0x00;
	uint8_t val = 0x01;
	
    LED_DIRECTION = ALL_OUTPUT;              /* Data Direction Register D: all on */
	LED_PORT &= 0x00;;

  while (1) {

		if(dir == SHIFT_LEFT){
			
			LED_PORT = val;
			val = val << 1;
			if(val == 0x80){
				dir = SHIFT_RIGHT;
			}
			_delay_ms(100);
		}
		
		if(dir == SHIFT_RIGHT){
			LED_PORT = val;
			val = val >> 1;
			if(val == 0x01){
				dir = SHIFT_LEFT;
			}
			_delay_ms(100);
		}
  }

  return 0;
}
