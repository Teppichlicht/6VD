/*Buttons.c */

/* includes */

#include <avr/io.h>

#include <stdint.h>

#include <avr/interrupt.h>

/*defines */

#ifndef F_CPU
#define F_CPU	1600000		//16Mhz processor clock frequency
#endif

#define KEY_DDR		DDRF

#define KEY_PORT	PORTF

#define KEY_PIN		PINF

#define KEY0		0
#define KEY1		1
#define KEY2		2
#define ALL_KEYS	(1 << KEY0| 1 << KEY1 | 1 << KEY2)

#define REPEAT_MASK (1 << KEY1 | 1 << KEY2)

#define REPEAT_START		50		// after 500ms
#define REPEAT_NEXT			20		//every 200ms


volatile uint8_t key_state;			//debounced and inverted keystate: bit=1: key pressed
volatile uint8_t key_press;			//key press detection
volatile uint8_t key_rpt;			// key long press and repeat

ISR(TIMER0_OVF_vect)				//every 10ms
{
	static uint8_t ct0=0xFF, ct1=0xFF,rpt;
	
	uint8_t i;
	TCNT0 =(uint8_t)(int16_t)-(F_CPU/1024*10e-3 + 0.5)	// preload for 10ms
	
	i=key_state ^~KEY_PIN;		//key changed?
	ct0 = ~(ct0 & i);			//reset or count ct0
	ct1 = ct0 ^ ct1 & i;		//reset or count ct1
	
	i  &= ct0 & ct1 ;				//count until rollover?
	
	key_state ^= i;				// toggle debounced state
	
	key_press |= key_state & i;	//0->1 kepress detected		//BIG FAT ERROR!
	
	
	//repeat function
	
	if ((key_state & REPEAT_MASK) == 0)		//check repeat function
			
			rpt=REPEAT_START;				//start delay
			
	if (--rpt == 0)
	{
		rpt=REPEAT_NEXT;					//repeat delay
		
		key_rpt |= key_state & REPEAT_MASK;
	}
	
	
	
	
}	/*ISR(TIMER0_OVF_vect	*/


uint8_t get_key_press(uint8_t key_mask)
{
	cli();							// read and clear atomic
	key_mask &= key_press;			// read keys
	key_press ^= key_mask;			// clear keys
	
	sei();
	
	return(key_mask);
	
}	/*get_key_press(key_mask) */


uint8_t get_key_rpt (uint8_t key_mask)
{
	cli();							//read and clear atomic
	key_mask &= key_rpt;			//read keys
	key_rpt ^= key_mask;			//clear keys
	sei();
	
	return(key_mask);
	
}	/* get_key_rpt(key_mask) */

uint8_t get_key_state( uint8_t key_mask)
{
	key_mask &= key_state;
	
	return(key_mask)
	
}	/*get_key_state(key_mask)

