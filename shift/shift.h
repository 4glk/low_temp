//#define SHIFT_LATCH_PIN
//#define SHIFT_CLOCK_PIN
//#define SHIFT_DATA_PIN

//#define CHIP 74HC595
#include <avr/io.h>
#include "../pin_macros.h"
/*
#define Pin1 A,2,H
#define Pin2 B,3,L
             ^ ^ ^
          port | |
             bit \active level
*/
//#define SHIFT_PORT // �� ��� ������� ���� , �� ��� � ���� ������� )))
//#define SHIFT_DDR
//#define SHIFT_PIN

#define SHIFT_data  C,1,H// pin_macros format
#define SHIFT_clk   C,0,H
#define SHIFT_latch C,2,H

//DRIVER (SHIFT_data, OUT);  // pin_macros format
//DRIVER ((SHIFT_clk),OUT);
//DRIVER ((SHIFT_latch),OUT);
