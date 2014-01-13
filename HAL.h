#ifndef HAL_H
#define HAL_H
//#pragma once
#if defined(__AVR_ATtiny13__)
#define __CPU	AVR_ATtiny13
// Timer/Counter 0 initialization
TCCR0A=0x00;    // bx00000000  >> nothing
TCCR0B=0x03;   // bx00000011   >> CS00 >> CS01   -> clk/64

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x02;    // bx00000010   >> TOIE0

#elif defined (__AVR_ATmega8__)
#define __CPU	AVR_ATmega8

// port initialization
/*
void Timer_Init(){
TIMSK=(1<<TOIE2);
TCCR2=(1<<CS20)|(1<<CS21);
}
//*/
//atmega8 timer
// TCCR2|=FOC2 WGM20 COM21 COM20 WGM21 CS22 CS21 CS20

// pin macros
//shift register to 7seg
#define SHIFT_data  C,1,H     // pin_macros format
#define SHIFT_clk   C,0,H
#define SHIFT_latch C,2,H
//digits (low level for common cathode)
#define DIG1    C,3,L
#define DIG2    C,4,L
#define DIG3    C,5,L
//encoder
/*//now its no works , macros cant be switch :(
#define ENC0    B,0,H
#define ENC1    B,1,H
#define ENC_BTN B,2,H
//*/
#warning "all right its m8"
//#error "works !!!"

#elif defined (__AVR_ATmega32__)
#define __CPU	AVR_ATmega32


#elif defined (__AVR_ATtiny85__)
#define __CPU	AVR_ATtiny85


#else
#error "Your AVR is not supported (or at least not tested)"
#endif

#endif
