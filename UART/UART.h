/*
 * UART.h
 *
 * Created: 06/10/2018 18:10:30
 *  Author: Kirollos Gamal
 */ 


#ifndef UART_H_
#define UART_H_
#include "config.h"
#include "types.h"
#include "Board.h"
enum BAUDRATE_OPTIONS{
	B4800=4800,
	B9600 = 9600
	};
enum UART_ERR{
	UART_SUCCESS=0,
	FRAME_ERR,
	DATA_OVERRIDE_ERR,
	PARITY_ERR,
	BAUDRATE_ERR,
	UART_MODE_ERR,
	CHAR_SIZE_ERR,
	STOP_BIT_ERR,
	};
enum UART_PARITY{
	OFF=0,
	EVEN,
	ODD,
	};
enum UART_STOP_BITS{
	ONE=1,
	TWO=2,
	};
enum UART_MODE{
	RX=0,
	TX,
	TRX,
	};
typedef struct UART_params{
	u8 mode;
	u32 baudrate;
	u8 parity;
	u8 char_size;
	u8 stop_bit;
	}UART_params;

u8 UART_init(UART_params*);
u16 UART_read(void);
void UART_write(u16);




#endif /* UART_H_ */