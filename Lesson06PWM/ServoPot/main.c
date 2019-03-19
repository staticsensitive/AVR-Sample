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

long map(long x, long in_min, long in_max, long out_min, long out_max);
void adcInit(void);
uint16_t readADC(uint8_t channel);

int main(void){
	uint16_t i = 2000;
	
	
	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // non-inverting mode for OC1A
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Mode 14, Prescaler 8

	ICR1 = 40000; // 320000 / 8 = 40000

	DDRB |= (1<<PB1); // OC1A set to output 
	adcInit();
	
	
	while(1){
			uint16_t adcRaw = readADC(0);
			uint16_t pos = map(adcRaw,0,1023,2000,4000);
			OCR1A = pos;
			_delay_ms(10);
	}                
	
	
	
	return 0;
	
}

void adcInit(void)
{
	/*Initialize ADC*/
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);     /* ADC clock prescaler /8 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}
uint16_t readADC(uint8_t channel) {
  ADMUX = (0xf0 & ADMUX) | channel;
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return (ADC);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
