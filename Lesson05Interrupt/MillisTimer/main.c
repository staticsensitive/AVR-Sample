#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define LED PB0
#define LED1 PB1
#define LED_DDR DDRB
#define LED_PORT PORTB

unsigned long millis (void);
void initTimer0 (void);
volatile unsigned long millis_t = 0;

unsigned long prev_millis = 0;
unsigned long prev_millis2 = 0;

int main (void)
{
	// make LED PORT as output
	LED_DDR |= (1<< LED ) | (1<<LED1);
	initTimer0();
		
		while (1)
			{
				if(millis() - prev_millis > 500){
						prev_millis = millis();
						
						LED_PORT ^= (1<<LED);
				}
				
				if(millis() - prev_millis2 > 100){
						prev_millis2 = millis();
						
						LED_PORT ^= (1<<LED1);
				}
				
				
			}
}
ISR(TIMER0_COMPA_vect) // timer0 overflow interrupt
{
	cli(); 
	millis_t++;
	sei();
}

void initTimer0 (void)
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
unsigned long millis (void)
{
    unsigned long millis_return;

    // Ensure this cannot be disrupted
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        millis_return = millis_t;
    }
	
    return millis_return;
}