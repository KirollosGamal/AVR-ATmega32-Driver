/*
* SPI.h
*
* Created: 07/10/2018 18:21:03
*  Author: Kirollos Gamal
*/


#ifndef SPI_H_
#define SPI_H_

#include "types.h"
#include "Board.h"
#include "config.h"

typedef enum SPI_MODE{
	MASTER,
	SLAVE
} SPI_MODE;

typedef enum SPI_OPTION {
	OPTION0,
	OPTION1,
	OPTION2,
	OPTION3
}SPI_OPTION;


typedef enum SPI_BIT_ORDER{
	LSB,
	MSB
}SPI_BIT_ORDER;
typedef enum SPI_BIT_RATE{
	XTAlD2,
	XTALD4,
	XTALD8,
	XTALD16,
	XTALD32,
	XTALD64,
	XTALD128,
}SPI_BIT_RATE;

typedef enum SPI_ERR{
	SPI_SUCCESS=0,
	SPI_MODE_ERR,
	SPI_BIT_ORDER_ERR,
	SPI_OPTION_ERR,
	SPI_BIT_RATE_ERR
}SPI_ERR;

typedef struct SPI_params{
	SPI_MODE mode;
	SPI_OPTION option;
	SPI_BIT_RATE rate;
	SPI_BIT_ORDER order;
};

SPI_ERR SPI_init(SPI_params * SPI_param);
SPI_ERR SPI_send_data(u8 data);
u8 SPI_recieve_data(void);
#endif /* SPI_H_ */