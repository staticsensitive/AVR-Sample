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
#include <stdint.h>

long map(long x, long in_min, long in_max, long out_min, long out_max);
uint16_t adc_read(uint8_t adcx);

int main(void){

	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // non-inverting mode for OC1A
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Mode 14, Prescaler 8

	ICR1 = 20000; // 320000 / 8 = 40000*/

	DDRB |= (1<<PB1); // OC1A set to output 
	
	ADCSRA |= _BV(ADEN);
	
	
	OCR1A = 1000; // set to 0° --> pulsewidth = 1ms
	_delay_ms(1000);
	
	while(1){
		
			int val = adc_read(0);
			
			val = map(val,0,1023,1000,2000);
			
			OCR1A = val;
	}                
	
	
	
	return 0;
	
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t adc_read(uint8_t adcx) {
	/* adcx is the analog pin we want to use.  ADMUX's first few bits are
	 * the binary representations of the numbers of the pins so we can
	 * just 'OR' the pin's number with ADMUX to select that pin.
	 * We first zero the four bits by setting ADMUX equal to its higher
	 * four bits. */
	ADMUX	&=	0xf0;
	ADMUX	|=	adcx;

	/* This starts the conversion. */
	ADCSRA |= _BV(ADSC);

	/* This is an idle loop that just wait around until the conversion
	 * is finished.  It constantly checks ADCSRA's ADSC bit, which we just
	 * set above, to see if it is still set.  This bit is automatically
	 * reset (zeroed) when the conversion is ready so if we do this in
	 * a loop the loop will just go until the conversion is ready. */
	while ( (ADCSRA & _BV(ADSC)) );

	/* Finally, we return the converted value to the calling function. */
	return ADC;
}
