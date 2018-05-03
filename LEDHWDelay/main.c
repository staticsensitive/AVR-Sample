#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define F_CPU 8000000UL
// Calculate the value needed for 
// the CTC match value in OCR1A.
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 8) 
 

volatile unsigned long timer1_millis;

long prevMillis;
long prevMillis2;
 
unsigned long millis (void);
void initTimer (void);
void initPorts(void);

 
int main(void)
{
	initTimer();
    initPorts();
    
    // Now enable global interrupts
    sei();
 
    while (1)
    {
        unsigned long now = millis();
		
		if(now - prevMillis > 500){
			PORTB ^= (1<<PB1);
			prevMillis = now;
		}
		
		if(now - prevMillis2 > 100){
			PORTB ^= (1<<PB2);
			prevMillis2 = now;
		}
    }
}

ISR (TIMER1_COMPA_vect)
{
    timer1_millis++;
}

void initTimer (void)
{
	// CTC mode, Clock/8
    TCCR1B |= (1 << WGM12) | (1 << CS11);
 
    // Load the high byte, then the low byte
    // into the output compare
    OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
    OCR1AL = CTC_MATCH_OVERFLOW;
 
    // Enable the compare match interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void initPorts(void)
{
	DDRB |= (1 << PB1) | (1 << PB2);
}

unsigned long millis (void)
{
    unsigned long millis_return;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        millis_return = timer1_millis;
    }
 
    return millis_return;
}