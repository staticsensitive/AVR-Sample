#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

uint16_t adc_read(uint8_t adcx);

int main(void){

	
	ADCSRA |= _BV(ADEN); /*Enable ADC*/

	DDRB |= (1<<PB1); 

	

	while(1){
		
			if(adc_read(0) > 512){
				PORTB |= (1<<PB1);
			}else{
				PORTB &= ~(1<<PB1);
			}
	}                
	
	
	return 0;
	
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
