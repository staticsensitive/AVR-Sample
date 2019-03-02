#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PORT                PORTB
#define LED_PIN                 PINB
#define LED_DDR                 DDRB

#define LED0                    PB0
#define LED1                    PB1

#define BUTTON_PORT             PORTD
#define BUTTON_PIN              PIND
#define BUTTON_DDR              DDRD

#define BUTTON                  PD2


void initInterrupt0 (void);

int main(void) {
  
  LED_DDR |= (1<<LED0) | (1<<LED1);                                    
  BUTTON_PORT |= (1 << BUTTON); //enable button pull-ups                     
  initInterrupt0(); 

 
  while (1) {

   
    LED_PORT ^= (1 << LED0);
	 _delay_ms(200);

  }                                                 
  return 0;                           
}

ISR(INT0_vect) {      
 /* Run every time there is a change on button */  
  if ((BUTTON_PIN & (1<< BUTTON))== 0) {
    LED_PORT |= (1 << LED1);
  }
  else {
    LED_PORT &= ~(1 << LED1);
  }
}

void initInterrupt0(void) {
  EIMSK |= (1 << INT0);   //Enable INT0
  EICRA |= (1 << ISC00);  //Trigger every button Change              /* trigger when button changes */
  sei();                  //Enable global interrupts
}