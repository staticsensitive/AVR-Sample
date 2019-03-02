/*Output ADC Value to LED*/

#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR  DDRD
#define LED_PORT PORTD

uint16_t readADC(uint8_t channel) {
  ADMUX = (0xf0 & ADMUX) | channel;
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return (ADC);
}

int main(void) {
	
   uint16_t adcval = 0;	
   
   
  /*Initialize ADC*/
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);     /* ADC clock prescaler /8 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */


  LED_DDR = 0xff;

 
  while (1) {

	adcval = readADC(0); 			/*read ADC Channel 0*/
	LED_PORT = adcval;				/*Output ADC Value to LED, last 2 bits*/
									/*not shown since we only have 8 LEDS at PORTD*/
    _delay_ms(50);
  }                                 
  return 0;                         
}
