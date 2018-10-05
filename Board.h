/*
 * Board.h
 * Created: 29/09/2018 14:28:36
 *  Author: Kirollos Gamal
 */ 


#ifndef BOARD_H_
#define BOARD_H_
//GPIO REGISTERS //
#define PINA 0x39 
#define DDRA 0x3A
#define PORTA 0x3B
#define PINB 0x36
#define DDRB 0x37
#define PORTB 0x38
#define PINC 0x33
#define DDRC 0x34 
#define PORTC 0x35 
#define PIND 0x30
#define DDRD 0x31
#define PORTD 0x32

//TIMERS REGISTERS //
#define SREG 0x5F
#define OCR0 0x5C
#define TIMSK 0x59
#define TIFR 0x58
#define TCCR0 0x53
#define TCNT0 0x52
#define TCCR1A 0x4F
#define TCCR1B 0x4E
#define TCNT1H 0x4D
#define TCNT1L 0x4C
#define OCR1AH 0x4B
#define OCR1AL 0X4A
#define OCR1BH 0x49
#define OCR1BL 0x48
#define TCCR2 0x45
#define TCNT2 0x44
#define OCR2 0x43


#endif /* INCFILE2_H_ */