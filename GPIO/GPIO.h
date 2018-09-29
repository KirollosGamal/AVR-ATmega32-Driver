/*
 * GPIO.h
 *
 * Created: 29/09/2018 14:21:19
 *  Author: Kirollos Gamal
 */ 
#include "types.h"

#ifndef GPIO_H_
#define GPIO_H_


typedef struct GPIO_config {
	u8 port ;
	u8 pin_num ;
	u8 direction ;
	u8 val ;	
	} GPIO_config;


enum ERROR_CODE {
	SUCCESS =0 , 
	PIN_VAL_ERR ,
	PORT_DIR_ERR , 
	PIN_DIR_ERR , 
	PORT_NAME_ERR ,
	PORT_VAL_ERR
	};

u8 GPIO_port_init (GPIO_config*);
u8 GPIO_pin_init (GPIO_config*);
u8 GPIO_port_write (GPIO_config*);
u8 GPIO_port_read (GPIO_config*);
u8 GPIO_pin_write (GPIO_config*);
u8 GPIO_pin_read (GPIO_config*);



#endif /* GPIO_H_ */