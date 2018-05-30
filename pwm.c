/* Hardware-pwm mit Timer1 
*/

#include <stdint.h>

#include <avr/io.h>

#include "pwm.h"

uint8_t pwm_Init (void)
{
	
	DDRB |=0x60;	// enable Output-driver for PB5 / PB6
	TCCR1B = 0;		// no output
	
	//fast PWM 9 bit: TCCR1A: 11 11 00 10 = 0xF2; TCCR1B: 00 x0 10 00= 0x08
	
	TCCR1A = 0xF2;
	
	TCCR1B = 0x08;
	
	TCNT1 = 0;
	
	OCR1A = 0;
	
	OCR1B = 0;
	
	TCCR1B |= 0x01; // prescale div 1
	
	return(0);
		
} /*pwm_Init*/


uint8_t pwm_Set(uint8_t ch, uint16_t val)
{
	switch(ch)
	{
		case 0 : OCR1A = val;
		break;
		
		case 1 : OCR1B = val;
		break;
	}
	
	return (0);
	
} /*pwm_Set*/

