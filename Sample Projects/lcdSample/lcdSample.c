#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main (void)
{
	lcd_init(); //Initialize LCD Port
	lcd_clear();//Clear LCD Contents
	
	lcd_puts("This is a String");
	lcd_set_cursor(0,1);
		lcd_puts("Second Line");
	
	_delay_ms(2000);
	lcd_clear();
	
	
	uint8_t numero = 143; //integer Number
	uint8_t num_ar[20];   //number character array
	
	//itoa(value,buffer,base)
	itoa(numero,num_ar,10); //Convert integer to char array
	
	lcd_puts("Int:");
	lcd_puts(num_ar);
	lcd_set_cursor(0,1);
	
	//Number with Decimal Point
	double mypi = 3.1416;
	uint8_t pi_ar[10];
	
	/**
	dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);

	floatvar						float variable
	StringLengthIncDecimalPoint		This is the length of the string that will be created
	numVarsAfterDecimal				The number of digits after the deimal point to print
	charbuf							The array to store the results
	**/
	
	dtostrf(mypi,6,4,pi_ar); //convert number to array
	lcd_puts("float:");
	lcd_puts(pi_ar);
	
	while(1)
	{
		
	}
}