/*
 * UART.c
 *
 * Created: 06/10/2018 18:27:33
 *  Author: Kirollos Gamal
 */ 
#include "types.h"
#include "UART.h"
#include "Board.h"

u8 UART_init(UART_params * params){
	switch (params->baudrate){
		case B4800 :
		*(volatile u8*)(UBRRL)=(XTAL/(16*B4800))-1;
		break;
		case B9600 :
		*(volatile u8*)(UBRRL)=(XTAL/(16*B4800))-1;
		break;
		default:
		return BAUDRATE_ERR;
	}
	if (params->mode==TX){
		SET_BIT(*(volatile u8*)USCRB,3);
	}
	else if (params->mode==RX){
		SET_BIT(*(volatile u8*)USCRB,4);
	}
	else if (params->mode==TRX){
		SET_BIT(*(volatile u8*)USCRB,3);
		SET_BIT(*(volatile u8*)USCRB,4);
	}
	else return UART_MODE_ERR;
	SET_BIT(*(volatile u8 *)USCRC,7);
	switch (params->char_size){
		case 5:
			CLEAR_BIT (*(volatile u8*)USCRB,2);
			CLEAR_BIT (*(volatile u8*)USCRC,1);
			CLEAR_BIT (*(volatile u8*)USCRC,2);
			break;
		case 6:
			CLEAR_BIT (*(volatile u8*)USCRB,2);
			SET_BIT(*(volatile u8*)USCRC,1);
			CLEAR_BIT (*(volatile u8*)USCRC,2);
			break;
		case 7:
			CLEAR_BIT (*(volatile u8*)USCRB,2);
			CLEAR_BIT(*(volatile u8*)USCRC,1);
			SET_BIT (*(volatile u8*)USCRC,2);
			break;
		case 8:
			CLEAR_BIT (*(volatile u8*)USCRB,2);
			SET_BIT (*(volatile u8*)USCRC,1);
			SET_BIT(*(volatile u8*)USCRC,2);
			break;
		case 9:
			SET_BIT (*(volatile u8*)USCRB,2);
			SET_BIT(*(volatile u8*)USCRC,1);
			SET_BIT (*(volatile u8*)USCRC,2);
			break;
	
		default :
		return CHAR_SIZE_ERR ;
	}
	if (params->parity==EVEN) {
		CLEAR_BIT(*(volatile u8 *)USCRC,4);
		SET_BIT(*(volatile u8 *)USCRC,5);
	}else if(params->parity==ODD){
		SET_BIT(*(volatile u8 *)USCRC,4);
		SET_BIT(*(volatile u8 *)USCRC,5);		
	}else if (params->parity==OFF){
		CLEAR_BIT(*(volatile u8 *)USCRC,4);
		CLEAR_BIT(*(volatile u8 *)USCRC,5);
	} else {
		return PARITY_ERR;
	}
	if(params->stop_bit==ONE){
		CLEAR_BIT(*(volatile u8 *)USCRC,3);
	}else if (params->stop_bit==TWO){
		SET_BIT(*(volatile u8 *)USCRC,3);
	}else{
		return STOP_BIT_ERR;
	}
	return UART_SUCCESS;

}

u16 UART_read(void){
	while((*(volatile u8*) (USCRA)) &(1<<7)){
		;}
		SET_BIT(USCRA,7);
		if ((*(volatile u8*)(USCRB))&(1<<2))
		{
			u16 data_9 =*(volatile u8*)(UDR) | ((*(volatile u8*)(USCRB)&(1<<1))<<(8));
			return data_9;
		}
		return (*(volatile u8*)(UDR));
}
void UART_write(u16 data){
		while (!(*(volatile u8 *) (USCRA) & (1<<5))){
			;}
		if ((*(volatile u8*)(USCRB))&(1<<2))
		{
			(*(volatile u8*)(USCRB))|= (data>>8)&(1<<0);
		}	
		*(volatile u8 *) (UDR) == data ;
	
}