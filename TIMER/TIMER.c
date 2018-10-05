/*
* TIMER.c
*
* Created: 05/10/2018 17:35:28
*  Author: Kirollos Gamal
*/


#include "TIMER.h"
#include "types.h"

u8 timer_start(detailed_timer * detailed_timer){
	switch(detailed_timer->timer_no)
	{
		/*TIMER 0 */
		case 0:
		*(volatile u8 *)(TCNT0)=detailed_timer->timer_val.val_l;
		
		if (detailed_timer-> prescaller==0){
			*(volatile u8 *)(TCCR0)|=0x01;
			}else if (detailed_timer-> prescaller==8){
			*(volatile u8 *)(TCCR0)=0x02;
			}else if (detailed_timer-> prescaller==64){
			*(volatile u8 *)(TCCR0)=0x03;
			}else if (detailed_timer-> prescaller==256){
			*(volatile u8 *)(TCCR0)=0x04;
			}else if (detailed_timer-> prescaller==1024){
			*(volatile u8 *)(TCCR0)=0x05;
			} else {
			return PRESCALER_ERR;
		}
		
		while(!(*(volatile u8 *)TIFR & (1<<TOV0))){
		;}
		
		*(volatile u8 *)(TCCR0)=0x00;
		SET_BIT(*(volatile u8 *)TIFR,TOV0);
		return TIMER_SUCCESS;
		
		/*TIMER 1*/
		case 1:
		*(volatile u8 *)(TCNT1L) = detailed_timer->timer_val.val_l;
		*(volatile u8 *)(TCNT1H) = detailed_timer->timer_val.val_h;
		*(volatile u8 *)(TCCR1A) = 0x00;
		if (detailed_timer-> prescaller==0){
			*(volatile u8 *)(TCCR1B)|=0x01;
			}else if (detailed_timer-> prescaller==8){
			*(volatile u8 *)(TCCR1B)=0x02;
			}else if (detailed_timer-> prescaller==64){
			*(volatile u8 *)(TCCR1B)=0x03;
			}else if (detailed_timer-> prescaller==256){
			*(volatile u8 *)(TCCR1B)=0x04;
			}else if (detailed_timer-> prescaller==1024){
			*(volatile u8 *)(TCCR1B)=0x05;
			} else {
			return PRESCALER_ERR;
		}
		while(!(*(volatile u8 *)TIFR & (1<<TOV1))){
		;}
		
		*(volatile u8 *)(TCCR1B)=0x00;
		SET_BIT(*(volatile u8 *)TIFR,TOV1);
		return TIMER_SUCCESS;
		
		/*TIMER 2*/
		case 2:
		*(volatile u8 *)(TCNT2)=detailed_timer->timer_val.val_l;
		
		if (detailed_timer-> prescaller==0){
			*(volatile u8 *)(TCCR2)|=0x01;
		}
		if (detailed_timer-> prescaller==8){
			*(volatile u8 *)(TCCR2)=0x02;
		}
		if (detailed_timer-> prescaller==32){
			*(volatile u8 *)(TCCR2)=0x03;
		}
		if (detailed_timer-> prescaller==64){
			*(volatile u8 *)(TCCR2)=0x04;
		}
		if (detailed_timer-> prescaller==128){
			*(volatile u8 *)(TCCR2)=0x05;
		}
		if (detailed_timer-> prescaller==256){
			*(volatile u8 *)(TCCR2)=0x06;
		}
		if (detailed_timer-> prescaller==1024){
			*(volatile u8 *)(TCCR2)=0x07;
		}
		while(!(*(volatile u8 *)TIFR & (1<<TOV2))){
		;}
		
		*(volatile u8 *)(TCCR0)=0x00;
		SET_BIT(*(volatile u8 *)TIFR,TOV2);
		
		return TIMER_SUCCESS;
		
		default:
		return TIMER_NO_ERR ;
	}
	
}

u8 wait (user_timer* user_timer){
	Wait_Value wait_time ;
	calc_clocks(user_timer->timer_val,&wait_time) ;
	detailed_timer wait_detailed_timer= {user_timer->timer_no,0,wait_time.prescaler,0};
	u8 i;
	for(i=0;i<wait_time.iter_num;i++){
		timer_start(&wait_detailed_timer);
	}
	wait_detailed_timer.timer_val.val_16=wait_time.last_loop_val;
	timer_start(&wait_detailed_timer);
}

void calc_clocks (u32 time_in_micros,Wait_Value *time){
	u32 clks_no= (XTAL/1000000)*time_in_micros ;
	u32 num_iter = clks_no/256;
	if (num_iter>1024){
		num_iter/=1024;
		time->iter_num=num_iter;
		time->last_loop_val = num_iter%256;
		time->prescaler=1024;
	} else if (num_iter>256){
		num_iter/=256;
		time->iter_num=num_iter;
		time->last_loop_val = num_iter%256;
		time->prescaler=256;
	} else if (num_iter>64){
		num_iter/=64;
		time->iter_num=num_iter;
		time->last_loop_val = num_iter%256;
		time->prescaler=64;
	}else if (num_iter>8){
		num_iter/=8;
		time->iter_num=num_iter;
		time->last_loop_val = num_iter%256;
		time->prescaler=8;
	}else {
		time->iter_num=num_iter;
		time->last_loop_val = clks_no%256;
		time->prescaler=0;
	}
}

