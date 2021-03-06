/*
* GPIO.c
*
* Created: 29/09/2018 14:48:55
*  Author: Kirollos Gamal
*/
/*
* GPIO Drivers for AVR Microcontrollers (ATmega32)
*/

/*TODO: Add Documentation and comments*/ 
/*TODO: Replacing Switch with if-else*/
/*TODO: Replacing Bit manipulation with SET_BIT/CLEAR_BIT*/
#include "Board.h"
#include "GPIO.h"


GPIO_ERR GPIO_port_init (GPIO_config * GPIO_conf){
	switch (GPIO_conf->port)
	{
		case 'A':
		case 'a':
		*(volatile  u8 *)(DDRA)=GPIO_conf->direction ; /* GPIO_conf->direction is treated here as a binary Pattern*/
		return SUCCESS;
		
		case 'B':
		case 'b':
		*(volatile  u8 *)(DDRB)=GPIO_conf->direction ;
		return SUCCESS;
		
		case 'C':
		case 'c':
		*(volatile  u8 *)(DDRC)=GPIO_conf->direction ;
		return SUCCESS;
		
		case 'D':
		case 'd':
		*(volatile  u8 *)(DDRD)=GPIO_conf->direction ;
		return SUCCESS;
		default:
		return PORT_NAME_ERR ;
	}
}

GPIO_ERR GPIO_pin_init(GPIO_config* GPIO_conf){
	
	if (GPIO_conf->pin_num>7)
	return PIN_VAL_ERR;
	
	switch (GPIO_conf->port) 
	{
		case 'A':
		case 'a':
		if (GPIO_conf->direction) 	 /* note:GPIO_conf->direction is used as a boolean variable 0=false ,any other value = true*/
		{
			*(volatile  u8 *)(DDRA)|= (1<<GPIO_conf->pin_num);
		}
		else
		{
			*(volatile  u8 *)(DDRA)&= ~(1<<GPIO_conf->pin_num);
		}
		
		return SUCCESS;
		
		case 'B':
		case 'b':
		if (GPIO_conf->direction)
		{
			*(volatile  u8 *)(DDRB)|= (1<<GPIO_conf->pin_num);
		}
		else
		{
			*(volatile  u8 *)(DDRB)&= ~(1<<GPIO_conf->pin_num);
		}
		
		return SUCCESS;
		
		case 'C':
		case 'c':
		if (GPIO_conf->direction) /* note:GPIO_conf->direction is used as a boolean variable 0=false ,any other value = true*/
		{
			*(volatile  u8 *)(DDRC)|= (1<<GPIO_conf->pin_num);
		}
		else
		{
			*(volatile  u8 *)(DDRC)&= ~(1<<GPIO_conf->pin_num);
		}
		
		return SUCCESS;
		
		case 'D':
		case 'd':
		if (GPIO_conf->direction) 
		{
			*(volatile  u8 *)(DDRD)|= (1<<GPIO_conf->pin_num);
		}
		else
		{
			*(volatile  u8 *)(DDRD)&= ~(1<<GPIO_conf->pin_num);
		}
		
		return SUCCESS;
		default:
		return PORT_NAME_ERR ;
	}
	
}

GPIO_ERR GPIO_port_read(GPIO_config* GPIO_conf){
	switch (GPIO_conf->port)
	{
		case 'A':
		case 'a':
		if (	*(volatile  u8 *)(DDRA)==0x00 ){ /** @warning in order to read a port,all of its pin must be initiated as input*/
			GPIO_conf->val=*(volatile  u8 *)(PINA);
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		
		case 'B':
		case 'b':
		if (	*(volatile  u8 *)(DDRB)==0x00 ){
			GPIO_conf->val=*(volatile  u8 *)(PINB);
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		
		case 'C':
		case 'c':
		if (	*(volatile  u8 *)(DDRC)==0x00 ){
			GPIO_conf->val=*(volatile  u8 *)(PINC);
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		case 'D':
		case 'd':
		if (	*(volatile  u8 *)(DDRD)==0x00 ){
			GPIO_conf->val=*(volatile  u8 *)(PIND);
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		default:
		return PORT_NAME_ERR ;
	}
}

GPIO_ERR GPIO_port_write(GPIO_config* GPIO_conf){
	switch (GPIO_conf->port)
	{
		case 'A':
		case 'a':
		if (	GPIO_conf->val==(*(volatile  u8 *)(DDRA)&GPIO_conf->val) ){ /** @warning any attempt to write over an input pin will result in a PORT_DIR_ERR */
			*(volatile  u8 *)(PORTA)=GPIO_conf->val;
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		
		case 'B':
		case 'b':
		if (	GPIO_conf->val==(*(volatile  u8 *)(DDRB)&GPIO_conf->val) ){
			*(volatile  u8 *)(PORTB)=GPIO_conf->val;
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		
		case 'C':
		case 'c':
		if (	GPIO_conf->val==(*(volatile  u8 *)(DDRC)&GPIO_conf->val) ){
			*(volatile  u8 *)(PORTC)=GPIO_conf->val;
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		case 'D':
		case 'd':
		if (	GPIO_conf->val==(*(volatile  u8 *)(DDRD)&GPIO_conf->val) ){
			*(volatile  u8 *)(PORTD)=GPIO_conf->val;
			return SUCCESS;
		}
		else
		{
			return PORT_DIR_ERR;
		}
		default:
		return PORT_NAME_ERR ;
	}
}

GPIO_ERR GPIO_pin_read(GPIO_config* GPIO_conf){
	if (GPIO_conf->pin_num>7)
	return PIN_VAL_ERR;
	
	switch (GPIO_conf->port)
	{
		case 'A':
		case 'a':
		if (~(*(volatile  u8 *)(DDRA)&(1<<GPIO_conf->pin_num)))
		{
			GPIO_conf->val=*(volatile  u8 *)(PINA)&(1<<GPIO_conf->pin_num);
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		
		case 'B':
		case 'b':
		if (~(*(volatile  u8 *)(DDRB)&(1<<GPIO_conf->pin_num)))
		{
			GPIO_conf->val=*(volatile  u8 *)(PINB)&(1<<GPIO_conf->pin_num);
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		
		case 'C':
		case 'c':
		if (~(*(volatile  u8 *)(DDRC)&(1<<GPIO_conf->pin_num)))
		{
			GPIO_conf->val=*(volatile  u8 *)(PINC)&(1<<GPIO_conf->pin_num);
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		
		case 'D':
		case 'd':
		if (~(*(volatile  u8 *)(DDRD)&(1<<GPIO_conf->pin_num)))
		{
			GPIO_conf->val=*(volatile  u8 *)(PIND)&(1<<GPIO_conf->pin_num);
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		default:
		return PORT_NAME_ERR ;
	}
	
	
}

GPIO_ERR GPIO_pin_write(GPIO_config* GPIO_conf){
	if (GPIO_conf->pin_num>7)
	return PIN_VAL_ERR;
	
	switch (GPIO_conf->port)
	{
		case 'A':
		case 'a':
		if (*(volatile  u8 *)(DDRA)&(1<<GPIO_conf->pin_num))
		{
			if (GPIO_conf->val)
			{
				*(volatile  u8 *)(PORTA)|= (1<<GPIO_conf->pin_num);
			}
			else
			{
				*(volatile  u8 *)(PORTA)&= ~(1<<GPIO_conf->pin_num);
			}
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		
		case 'B':
		case 'b':
		if (*(volatile  u8 *)(DDRB)&(1<<GPIO_conf->pin_num))
		{
			if (GPIO_conf->val)
			{
				*(volatile  u8 *)(PORTB)|= (1<<GPIO_conf->pin_num);
			}
			else
			{
				*(volatile  u8 *)(PORTB)&= ~(1<<GPIO_conf->pin_num);
			}
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		case 'C':
		case 'c':
		if (*(volatile  u8 *)(DDRC)&(1<<GPIO_conf->pin_num))
		{
			if (GPIO_conf->val)
			{
				*(volatile  u8 *)(PORTC)|= (1<<GPIO_conf->pin_num);
			}
			else
			{
				*(volatile  u8 *)(PORTC)&= ~(1<<GPIO_conf->pin_num);
			}
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		
		case 'D':
		case 'd':
		if (*(volatile  u8 *)(DDRD)&(1<<GPIO_conf->pin_num))
		{
			if (GPIO_conf->val)
			{
				*(volatile  u8 *)(PORTD)|= (1<<GPIO_conf->pin_num);
			}
			else
			{
				*(volatile  u8 *)(PORTD)&= ~(1<<GPIO_conf->pin_num);
			}
			return SUCCESS;
		}
		else
		{
			return PIN_DIR_ERR ;
		}
		default:
		return PORT_NAME_ERR ;
	}
	
	
}


