/*
 *	Calculations:
 *
 *	Clock cycles completed in 20ms:
 *	F_CPU / 50Hz = 16000000Hz / 50Hz = 320000
 *
 *	Prescaler and compare value:
 *	160000 / Prescaler = compare value
 * 	160000 / 8 = 20000
 *
 *	1.5ms pulse width (middle position):
 *	20ms / 15 = 40000 / 15 = 2666 = OCR1A value
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	uint16_t i = 2000;
	
	
	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // non-inverting mode for OC1A
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Mode 14, Prescaler 8

	ICR1 = 40000; // 320000 / 8 = 40000

	DDRB |= (1<<PB1); // OC1A set to output 
	
	OCR1A = i;	
	while(1){
			
				
		for(i=2000; i<=4000; i += 10){
			 OCR1A = i;	
			_delay_ms(20);
		}
		
		for(i=4000; i>=2000; i -= 10){
			 OCR1A = i;	
			_delay_ms(20);
		}
		
	
	}                
	
	
	
	return 0;
	
}
