/*Output ADC Value to LED*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>   
           
#define FOSC 16000000                      		/*F_CPU*/
#define BAUD 9600                				/*Baudrate*/


#include <util/setbaud.h>


/*Function Prototype*/
void UARTInit(void);
void UARTPutc(uint8_t data);
uint8_t UARTgetc(void);
void UARTPuts(const char myString[]) ;
uint16_t readADC(uint8_t channel);


int main(void) {
	
   uint16_t adcval = 0;	
   double voltage = 0;
   uint8_t buffer[5];
   uint8_t vBuffer[10];
   
  /*Initialize ADC*/
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);     /* ADC clock prescaler /8 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */

  UARTInit(); /*Initialize Serial*/



 
  while (1) {

	adcval = readADC(0); 				/*read ADC Channel 0*/
	voltage = (adcval/1023.0)*5.0;		/*Convert ADC Reading to Voltage*/
	
	UARTPuts("Raw ADC Reading: ");
	itoa(adcval,buffer,10);				/*Convert Integer to String Array*/
	UARTPuts(buffer);			
	UARTPuts(" ADC Voltage: ");
	dtostrf(voltage,4,2,vBuffer);	/*Convert double to String Array with 2 decimal places*/
	UARTPuts(vBuffer);
	UARTPuts(" \r\n");
	
    _delay_ms(50);
  }                                 
  return 0;                         
}

uint16_t readADC(uint8_t channel) {
  ADMUX = (0xf0 & ADMUX) | channel;
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return (ADC);
}


void UARTInit(void) {                           /* requires BAUD */
  UBRR0H = UBRRH_VALUE;                       	/* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
												/* Enable USART transmitter/receiver */
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   	/* 8 data bits, 1 stop bit */
}

void UARTPutc(uint8_t data) {
												/* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;                                  /* send data */
}

uint8_t UARTgetc(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);       	/* Wait for incoming data */
  return UDR0;                                	/* return register value */
}

void UARTPuts(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    UARTPutc(myString[i]);
    i++;
  }
}
