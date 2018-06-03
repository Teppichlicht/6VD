/*
 * GccApplication1.c
 *
 * Created: 30.05.2018 08:13:25
 * Author : user
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "pwm.h"
#include "button.h"




int main(void)
{
	
	TCCR0B=0x05; // div 1024
	TIMSK0=0x01;	//Overflow interrupt enable Counter0
	pwm_Init();
    sei();
	int i=0;
	int j=0;
    while (1) 
    {
		
	if(get_key_long(1<<KEY_MENU))
	{
		
	switch(i)
	{
		case 0:
		pwm_Set(0,0xFF);	//WW,50%
		i=1;
		j=2;
		break;
		
		case 1:
		pwm_Set(0,0x00);	//alles aus
		pwm_Set(1,0x00);	
		i=0;
		j=0;
		break;
		
		case 2:
		pwm_Set(0,0x00);
		pwm_Set(1,0x00);	// alles aus
		i=0;
		j=0;
		break;
		
		case 3:
		pwm_Set(0,0x00);
		pwm_Set(1,0x00);	// alles aus
		 i=0;
		j=0;
		break;
			} /* switch*/
	} /*if getkeylong...*/
	
	if (get_key_short (1 << KEY_MENU ))
	{
		switch(i)
		{
			case 0:
			break;
			
			case 1:
			switch(j)
			{
				case 1:
				pwm_Set(0,0x00);		//w25% off
				pwm_Set(1,0x7D);		//r25% on
				i=2;
				break;
				
				case 2:
				pwm_Set(0,0x00);			//w50% off
				pwm_Set(1,0xFF);		//r50% on
				i=2;
				break;
				
				case 3:
				pwm_Set(0,0x00);		//w75% off
				pwm_Set(1,0x180);		//r75% on
				i=2;
				break;
				
				case 4:
				pwm_Set(0,0x00);		//w100% off
				pwm_Set(1,0x1FF);		//r100% on
				i=2;
				break;
			} /*case i=1, switch (j)....*/
			
			case 2:
			switch(j)
			{
				case 1:
				//starte flash mit r25%
				i=3;
				break;
				
				case 2:
				//starte flash mit r50%
				i=3;
				break;
				
				case 3:
				//starte flash mit r75%
				i=3;
				break;
				
				case 4:
				//starte flash mit r100%
				i=3;
				break;
		}/* case i=2,switch(j)*/
		
		case 3:
		{
			pwm_Set(0,0x00);
			pwm_Set(1,0x00);
			i=0;
			j=0;
			break;
			
		}/* case i=3*/
		
	}/* if (get_key_short (1 << KEY_MENU )) */
	
	if (get_key_short (1 << KEY_UP))
	{
		switch(j)
		{
			
	
		case 1:
		switch(i)
		{
			case 1:
			pwm_Set(0,0xFF);
			pwm_Set(1,0x00);
			j=2;
			break;
			
			case 2:
			pwm_Set(0,0x00);
			pwm_Set(1,0xFF);
			j=2;
			break;
			
			case 3:
			//starte flash mit r50%
			j=2;
			break;
			
		}/*case1 switch i*/
		
		case 2:
		switch(i)
		{
			case 1:
			pwm_Set(0,0x180);
			pwm_Set(1,0x00);
			j=3;
			break;
			
			case 2:
			pwm_Set(0,0x00);
			pwm_Set(1,0x180);
			j=3;
			break;
			
			case 3:
			//starte flash mit r75%
			j=3;
			break;
			
			}/*case2 switch i*/
		
		
		case 3:
		
		switch(i)
		{
			case 1:
			pwm_Set(0,0x1FF);
			pwm_Set(1,0x00);
			j=4;
			break;
			
			case 2:
			pwm_Set(0,0x00);
			pwm_Set(1,0x1FF);
			j=4;
			break;
			
			case 3:
			//starte flash mit r100%
			j=4;
			break;
			
			}/*case3 switch i*/
		case 4:
		break;
		}/*switch i*/


	} /*if (get_key_short (1 << KEY_UP))*/
	
	
	if (get_key_short(1 << KEY_DOWN))
	{
		switch(j)
		{
			
				
		case 1:
		break;
			

			
		case 2:
			switch(i)
			{
				case 1:
				pwm_Set(0,0x7D);
				pwm_Set(1,0x00);
				j=1;
				break;
				
				case 2:
				pwm_Set(0,0x00);
				pwm_Set(1,0x7D);
				j=1;
				break;
				
				case 3:
				//starte flash mit r25%
				j=1;
				break;
				
				}/*case2 switch i*/
				
				
				case 3:
				
				switch(i)
				{
					case 1:
					pwm_Set(0,0xFF);
					pwm_Set(1,0x00);
					j=2;
					break;
					
					case 2:
					pwm_Set(0,0x00);
					pwm_Set(1,0xFF);
					j=2;
					break;
					
					case 3:
					//starte flash mit r50%
					j=2;
					break;
					
					}/*case3 switch i*/
				case 4:
				{
					switch(i)
					{
						case 1:
						pwm_Set(0,0x180);
						pwm_Set(1,0x00);
						j=3;
						break;
						
						case 2:
						pwm_Set(0,0x00);
						pwm_Set(1,0x180);
						j=3;
						break;
						
						case 3:
						//starte flash mit r75%
						j=3;
						break;	
					}/*case 4 switch (i)*/
					
					}

	}/*if if (get_key_short(1 << KEY_DOWN))*/
	
}/*while...*/
	return(0);
	}/*main...*/

