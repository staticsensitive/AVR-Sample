/***
Serial Communication Example
Using Setbaud utility

F_CPU 16MHz
Baudrate 9600
***/

#include <avr/io.h>
#include <stdint.h>   
           
#define FOSC 16000000                      		/*F_CPU*/
#define BAUD 9600                				/*Baudrate*/


#include <util/setbaud.h>


/*Function Prototype*/
void UARTInit(void);
void UARTPutc(uint8_t data);
uint8_t UARTgetc(void);
void UARTPuts(const char myString[]) ;

int main( void )
{	
   char rxChar;						/*Store received character here*/
   UARTInit();
   
   UARTPuts("Hello World!\r\n");	/*Print String to serial port*/


    while(1)
    {
          rxChar = UARTgetc();		/*Get Character*/
		  UARTPutc(rxChar);			/*Print Received Character*/
    }    
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
