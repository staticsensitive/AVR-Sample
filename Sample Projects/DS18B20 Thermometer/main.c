/*
Simple Thermometer using DS18B20 Waterproof Sensor
and Seven Segment Display
This project uses:
 
 Processor: Atmega 328P (ATA6614Q Compatible - Gizduino LIN)
 Clock : 
 avr-uart - An Interrupt driven UART Library for 8-bit AVR MCU
			Maintained by: Andy Gock Derived from: Peter Fleury
			https://github.com/andygock/avr-uart
DS18B20  sensor library by Davide Gironi	
		https://sourceforge.net/projects/davidegironi/files/avr-lib/avr_lib_ds18b20_02.zip/download
		 
Compiler: AVR-GCC V. 8.3

Author: Richard Myrick T. Arellaga
		Urdaneta City University

Released under GPLv3.		

Warning: NOT ARDUINO COPY PASTE COMPATIBLE

Connections:

Atmel Atmega 328P

                  +-\/-+
          RESET  1|    |28  PC5  UNUSED
      RX    PD0  2|    |27  PC4  UNUSED
      TX    PD1  3|    |26  PC3  UNUSED
     SEG-A  PD2  4|    |25  PC2  UNUSED
     SEG-B  PD3  5|    |24  PC1  UNUSED
     SEG-C  PD4  6|    |23  PC0  DS18B20 Data
            VCC  7|    |22  GND
            GND  8|    |21  AREF
		  XTAL1  9|    |20  AVCC
          XTAL2 10|    |19  PB5 DIGIT 3
	SEG-D	PD5 11|    |18  PB4 DIGIT 2
    SEG-E   PD6 12|    |17  PB3 DIGIT 1
    SEG-F   PD7 13|    |16  PB2 DIGIT 0
    SEG-G   PB0 14|    |15  PB1 SEG-DP
                  +----+


			
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define F_CPU  16000000

#define UART_BAUD_RATE 9600
#include "uart.h" 
#include "ds18b20.h""

/*Seven Segment Look up Table*/
uint8_t ssd[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};

uint8_t degree[2] = {0x9C,0xC6}; //Degree Celsius Symbol

void initializeTimer0 (void);

volatile uint16_t mynumber =1234;
volatile uint8_t digit = 0;



char printbuff[100];
double d = 0;
	
int main (void)
{
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	initializeTimer0();
	
	DDRD |= 0xFC;
	DDRB |= 0xFF;
	
	PORTD = 0xFC;
	PORTB = 0xFF;
	
	char printbuff[100];	
	
	sei();
	uart_puts("DS18B20 Test\r\n");
	
	while(1)
	{
		d = ds18b20_gettemp();
		_delay_ms(1000);
		dtostrf(d, 10, 3, printbuff);
		uart_puts("Temperature: "); uart_puts(printbuff); uart_puts("\r\n");

		mynumber = d * 100; //scale double to whole number
	}
	return 0;
}

ISR(TIMER0_COMPA_vect) // timer0 overflow interrupt
{
	uint8_t temp = 0;
	
	switch(digit){
		case 0:
			
		temp = (mynumber)%10;
		
		PORTD = (ssd[temp] << 2);
		PORTB = (ssd[temp] >> 6);
		
		PORTB &= ~(1<<PB2);
		PORTB |= (1<<PB3);
		PORTB |= (1<<PB4);
		PORTB |= (1<<PB5);
		break;
		
		case 1:
		
		temp = (mynumber/10)%10;
		
		PORTD = (ssd[temp] << 2);
		PORTB = (ssd[temp] >> 6);
		
		PORTB |= (1<<PB2);
		PORTB &= ~(1<<PB3);
		PORTB |= (1<<PB4);
		PORTB |= (1<<PB5);
		break;

		case 2:
		temp = (mynumber/100)%10;
		
		PORTD = (ssd[temp] << 2);
		PORTB = (ssd[temp] >> 6);
		PORTB &= ~(1<<PB1); //turn on dot
		
		PORTB |= (1<<PB2);
		PORTB |= (1<<PB3);
		PORTB & ~(1<<PB4);
		PORTB |= (1<<PB5);
		break;

		case 3:
		temp = (mynumber/1000)%10;
		
		PORTD = (ssd[temp] << 2);
		PORTB = (ssd[temp] >> 6);
		
		
		PORTB |= (1<<PB2);
		PORTB |= (1<<PB3);
		PORTB |= (1<<PB4);
		PORTB &= ~(1<<PB5);
		
		break;	
		
	}
	
	digit++;
	if(digit > 3){digit = 0;}
	
}

void initializeTimer0 (void)
{
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01 );
	// Set the value that you want to count to
	OCR0A = 62 ; //1ms
	TIMSK0 |= (1 << OCIE0A ); // Set the ISR COMPA vect
	sei (); // enable interrupts
	TCCR0B |= (1 << CS02 ) ;
	// set prescaler to 256 and start the timer
}
