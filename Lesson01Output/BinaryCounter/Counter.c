/*
Binary Counter
Output to PORTD

 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {
	uint8_t counter = 0;
    DDRD = 0b11111111;              /* Data Direction Register D: all on */
	PORTD = 0x00;

  while (1) {

		counter ++;
		if(counter >= 255){
			counter = 0;
		}
		PORTD = counter;;
		_delay_ms(500);
		
  }

  return 0;
}
