/*
 *	Calculations:
 *
 *	Clock cycles completed in 20ms:
 *	F_CPU / 50Hz = 8000000Hz / 50Hz = 160000
 *
 *	Prescaler and compare value:
 *	160000 / Prescaler = compare value
 * 	160000 / 8 = 20000
 *
 *	1.5ms pulse width (middle position):
 *	20ms / 15 = 40000 / 15 = 2666 = OCR1A value
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void){

	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // non-inverting mode for OC1A
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Mode 14, Prescaler 8

	ICR1 = 20000; // 320000 / 8 = 40000

	DDRB |= (1<<PB1); // OC1A set to output 

	while(1){

		OCR1A = 1000; // set to 0° --> pulsewidth = 1ms
		_delay_ms(1000);

		OCR1A = 1500; // set to 90° --> pulsewdith = 1.5ms
		_delay_ms(1000);

		OCR1A = 2000; // set to 180° --> pulsewidth = 2ms
		_delay_ms(1000);
	}                
	
	
	
	return 0;
	
}
