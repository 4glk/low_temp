#include "shift.h"

void Shift_Init(){
    DRIVER (SHIFT_data, OUT);  // pin_macros format
    DRIVER (SHIFT_clk,OUT);
    DRIVER (SHIFT_latch,OUT);
}
//
void Send_Byte(char byte){
    // отправляем байт последовательно по битам , при этом кликая каждый бит и дергая защелку каждый байт
    for (char i=0;i<8;i++){
          if ((byte&0x80)==0x00) ON(SHIFT_data);
          else OFF(SHIFT_data);
            byte<<=1;
            ON(SHIFT_clk);
            OFF(SHIFT_clk);
        }
        OFF(SHIFT_latch);
        ON(SHIFT_latch);
        OFF(SHIFT_latch);
}
