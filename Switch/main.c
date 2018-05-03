#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	
	DDRD |= (1<<PD6);
	DDRD &= ~(1<<PD7);
	PORTD |= (1<<PD7);
	


	while(1){
			
		if((PIND & (1<<PD7)) == 0){
			_delay_ms(100);
			PORTD |= (1<<PD6);
		}else{
			PORTD &= ~(1<<PD6);
		}

	}                
	
	return 0;
}
