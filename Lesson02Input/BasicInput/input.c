/*
LEDS at PORTD0-7
Button Switch at PB0 & PB1
 */

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define SW1 PB0
#define SW2 PB1
#define SW_PORT PORTB
#define SW_DIR DDRB
#define SW_PIN PINB
#define LED_PORT PORTD
#define LED_DIR DDRD

int main(void) {
	
	LED_DIR |= 0xFF; /*Make PORTD Output*/
	LED_PORT &= 0x00; /*Turn Off All LEDS at PORTD*/
	
	SW_DIR = 0x00; /*Make PORTB0 as input*/
	SW_PORT |= ((1<<SW1) | (1<<SW2));  /*Turn on Pull Up*/
	
	

  while (1) {
	  
	  if((SW_PIN & (1<<SW1))==0){  /*Look if switch is pressed*/
			PORTD = 0b00111100;
	  }
	  if((SW_PIN & (1<<SW2))==0){  /*Look if switch is pressed*/
			PORTD = 0b11000011;
	  }
	  
	  PORTD = 0x00; 
  }

  return 0;
}