#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME  20                /*milliseconds*/

#define BUTTON_DDR DDRB
#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB
#define BUTTON PB0

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED0 PD7

uint8_t buttonPressed(void); 			/*Function Prototype*/

int main(void) {
  
  unsigned short wasPressed=0;       	/* Button state */
  unsigned short ledState = 0; 
  BUTTON_DDR &= ~(1<<BUTTON);			/*set PB0 as input*/
  BUTTON_PORT |= (1 << BUTTON);     	/* enable the pullup on the button */
  
  LED_DDR = 0xFF;                      	/* set up LED for output */
  LED_PORT = 0x00;					 	/* Turn of all LEDS */

  
  while (1) {
    if (buttonPressed()) {              /* debounced button press */
      if (wasPressed == 0) {     		/* but not the last time */
        ledState ^= 0x01;               /* toggle led state using XOR*/
        wasPressed = 1;                 /* update the state */
      }
    }
    else {                              /* button is not pressed now */
      wasPressed = 0;                   /* update the state */
    }

		if(ledState == 1){
			LED_PORT = 0xFF;	
		}else{
			LED_PORT = 0x00;	
		}
  }                                                  
  return 0;                            
}

uint8_t buttonPressed(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {      /* button is pressed now */
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {    /* still pressed */
      return (1);
    }
  }
  return 0;
}