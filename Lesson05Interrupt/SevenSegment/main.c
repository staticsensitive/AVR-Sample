#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SSD_DDR DDRD
#define SSD_PORT PORTD
#define DIGIT_DDR DDRB
#define DIGIT_PORT PORTB
#define DIGIT1 PB0
#define DIGIT2 PB1

#define enableDigit1() DIGIT_PORT &= ~(1<<DIGIT1); DIGIT_PORT |= (1<<DIGIT2);
#define enableDigit2() DIGIT_PORT |= (1<<DIGIT1); DIGIT_PORT &= ~(1<<DIGIT2);

void initializeTimer0 (void);

uint8_t ssd[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};

volatile uint8_t mynumber =0;
volatile uint8_t digit = 0;

int main (void)
{

    initializeTimer0();
	
	SSD_DDR |= 0xFF;
	DIGIT_DDR |= ((1<<DIGIT1) | (1<<DIGIT2));
	
	SSD_PORT = 0xFF;
	
	sei();

		
		while (1)
		{
				mynumber++;
				if(mynumber > 99){mynumber = 0;}
				_delay_ms(500);
		}
}

ISR(TIMER0_COMPA_vect) // timer0 overflow interrupt
{
	uint8_t temp = 0;
	
	switch(digit){
		case 0:
		temp = mynumber%10;
		SSD_PORT = ssd[temp];
		enableDigit1()
		break;
		
		case 1:
		temp = (mynumber/10)%10;
		SSD_PORT = ssd[temp];
		enableDigit2()
		break;	
	}
	
	digit++;
	if(digit > 1){digit = 0;}
	
}

void initializeTimer0 (void)
{
		// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01 );
	// Set the value that you want to count to 10ms
	OCR0A = 0x96 ;
	TIMSK0 |= (1 << OCIE0A ); // Set the ISR COMPA vect
	sei (); // enable interrupts
	TCCR0B |= ((1 << CS02 ) | (1 << CS00));
	// set prescaler to 1024 and start the timer
}