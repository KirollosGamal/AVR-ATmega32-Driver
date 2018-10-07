/*
 * SPI.c
 *
 * Created: 07/10/2018 18:20:20
 *  Author: Kirollos Gamal
 */ 
#include "SPI.h"


SPI_ERR SPI_init(SPI_params * SPI_param){

	if (SPI_param->mode==MASTER)
		SET_BIT(*(volatile u8*)SPCR,4);
	else if 	(SPI_param->mode==SLAVE)
		CLEAR_BIT(*(volatile u8*)SPCR,4);
	else return SPI_MODE_ERR ; 
	
	if (SPI_param->option==OPTION0){
		CLEAR_BIT(*(volatile u8*)SPCR ,2);
		CLEAR_BIT(*(volatile u8*)SPCR ,3);
	}
	else if (SPI_param->option==OPTION1){
		SET_BIT(*(volatile u8*)SPCR ,2);
		CLEAR_BIT(*(volatile u8*)SPCR ,3);
	}	
	else if (SPI_param->option==OPTION2){
		CLEAR_BIT(*(volatile u8*)SPCR ,2);
		SET_BIT(*(volatile u8*)SPCR ,3);
	}
	else if (SPI_param->option==OPTION3){
		SET_BIT(*(volatile u8*)SPCR ,2);
		SET_BIT(*(volatile u8*)SPCR ,3);
	}
	else return SPI_OPTION_ERR ;

	if(SPI_param->order==LSB)
		SET_BIT (*(volatile u8*)SPCR,5);
	else if (SPI_param->order==MSB)
		CLEAR_BIT (*(volatile u8*)SPCR,5);
	else return SPI_BIT_ORDER_ERR

	if (SPI_param->rate==XTAlD2){
		CLEAR_BIT (*(volatile u8*)SPCR,0);
		CLEAR_BIT (*(volatile u8*)SPCR,1);
		SET_BIT (*(volatile u8*)SPSR,0);	
	}else if (SPI_param->rate==XTALD4){
		CLEAR_BIT (*(volatile u8*)SPCR,0);
		CLEAR_BIT (*(volatile u8*)SPCR,1);
		CLEAR_BIT (*(volatile u8*)SPSR,0);
	}
	else if (SPI_param->rate==XTALD8){
		SET_BIT (*(volatile u8*)SPCR,0);
		CLEAR_BIT (*(volatile u8*)SPCR,1);
		SET_BIT (*(volatile u8*)SPSR,0);
	}
	else if (SPI_param->rate==XTALD16){
		SET_BIT (*(volatile u8*)SPCR,0);
		CLEAR_BIT (*(volatile u8*)SPCR,1);
		CLEAR_BIT (*(volatile u8*)SPSR,0);
	}
	else if (SPI_param->rate==XTALD32){
		CLEAR_BIT (*(volatile u8*)SPCR,0);
		SET_BIT (*(volatile u8*)SPCR,1);
		SET_BIT (*(volatile u8*)SPSR,0);
	}
	else if (SPI_param->rate==XTALD64){
		SET_BIT (*(volatile u8*)SPCR,0);
		SET_BIT (*(volatile u8*)SPCR,1);
		SET_BIT (*(volatile u8*)SPSR,0);
	}
	else if (SPI_param->rate==XTALD128){
		SET_BIT (*(volatile u8*)SPCR,0);
		SET_BIT (*(volatile u8*)SPCR,1);
		CLEAR_BIT (*(volatile u8*)SPSR,0);
	}
	else return SPI_BIT_RATE_ERR ;

SET_BIT(*(volatile u8*)SPCR,6);
return SPI_SUCCESS;
}

SPI_ERR SPI_send_data(u8 data);
u8 SPI_recieve_data(void);