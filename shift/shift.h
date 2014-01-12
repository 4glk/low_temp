//#define SHIFT_LATCH_PIN
//#define SHIFT_CLOCK_PIN
//#define SHIFT_DATA_PIN

//#define CHIP 74HC595
#include <avr/io.h>
#include "../HAL.h"
#include "../pin_macros.h"
//#include <util/delay.h>

/*
#define Pin1 A,2,H
#define Pin2 B,3,L
             ^ ^ ^
          port | |
             bit \active level
*/
//#define SHIFT_PORT // по пин макросу если , то все в одну строчку )))
//#define SHIFT_DDR
//#define SHIFT_PIN
/* to HAL.h
#define SHIFT_data  C,0,H// pin_macros format
#define SHIFT_clk   C,1,H
#define SHIFT_latch C,2,H
//*/
//DRIVER (SHIFT_data, OUT);  // pin_macros format
//DRIVER ((SHIFT_clk),OUT);
//DRIVER ((SHIFT_latch),OUT);
