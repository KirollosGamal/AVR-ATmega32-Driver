/*
* IncFile2.h
*
* Created: 02/10/2018 18:07:08
*  Author: Kirollos Gamal
*/

#include "Board.h"
#include "types.h"
#define  XTAL 8000000UL


#ifndef TIMER_H_
#define TIMER_H_

typedef struct user_timer {
	u8 timer_no ;
	u32 timer_val ;
	u8(* callback_func)() ; // return succeed or failed //
} user_timer ;

typedef  struct Wait_Value{
	u32 iter_num;
	u16 prescaler;
	u16 last_loop_val;
}Wait_Value;

typedef struct detailed_timer {
	u8 timer_no ;
	union timer_val{u16 val_16 ;
					u8 val_l;
					u8 val_h;
					}timer_val;
	u16 prescaller ;
	u8(* callback_func)() ;
} detailed_timer ;

enum TIMER_ERROR_CODE {
	TIMER_SUCCESS=0,
	TIMER_NO_ERR,
	TIMER_IN_USE_ERR,
	PRESCALER_ERR,
} ;

enum TIFR_BITS{
	TOV0=0,
	OCF0,
	TOV1,
	OCF1B,
	OCF1A,
	ICF1,
	TOV2,
	OCF2
};

u8 timer_start (detailed_timer*);
u8 timer_reset (detailed_timer*);

u8 wait (user_timer*);
u8 count (user_timer*);
u8 clock_generate (user_timer*);
void calc_clocks (u32 time_in_micros,Wait_Value *time);

#endif /* TIMER_H_ */