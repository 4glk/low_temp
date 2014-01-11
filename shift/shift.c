#include "shift.h"

void Shift_Init(){
    DRIVER (SHIFT_data, OUT);  // pin_macros format
    DRIVER (SHIFT_clk,OUT);
    DRIVER (SHIFT_latch,OUT);
}
//
void Send_Byte(char byte){
    // отправляем байт последовательно по битам , при этом кликая каждый бит и дергая защелку каждый байт
    //int i=0;
       // ON(SHIFT_latch);

       //OFF(SHIFT_latch);
       //ON(SHIFT_latch);
    for (char i=0;i<8;i++){

          //  SHIFT_data|=(byte<<i);
          //*
         // char bit;
          //bit&=(byte<<i);
          if (byte&0x80) ON(SHIFT_data);
          else OFF(SHIFT_data);
        //*/
        __asm("nop");
        __asm("nop");
        __asm("nop");
            ON(SHIFT_clk);
        __asm("nop");
        __asm("nop");
        __asm("nop");
            OFF(SHIFT_clk);
            __asm("nop");
            __asm("nop");
            __asm("nop");
             byte<<=1;
        }
        ON(SHIFT_latch);
        __asm("nop");
        __asm("nop");
        __asm("nop");
        OFF(SHIFT_latch);
       //ON(SHIFT_latch);
}
