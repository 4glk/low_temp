#include "7seg.h"

//char dig=0;
//prog_char number[];
char number[];
void Digits_Init(){
    DRIVER (DIG1, OUT);  // pin_macros format
    DRIVER (DIG2,OUT);
    DRIVER (DIG3,OUT);
}

void Ind_Buffer(int value){
    // допустим value = 111; нужно чтобы отображало 111
    static char dig;
    // OFF(DIG1);OFF(DIG2);OFF(DIG3);
 for (char dig=0;dig<3;dig++)
    switch (dig){

        case 0 : OFF(DIG2);OFF(DIG3);Send_Byte(number[value%1000/100]);ON(DIG1);break;
        case 1 : OFF(DIG1);OFF(DIG3);Send_Byte(number[value%100/10]);ON(DIG2);break;
        case 2 : OFF(DIG1);OFF(DIG2);Send_Byte(number[value%10/1]);ON(DIG3);break;

//        case 0 : Send_Byte(number[1]);ON(DIG1);break;
//        case 1 : Send_Byte(number[1]);ON(DIG2);break;
//        case 2 : Send_Byte(number[1]);ON(DIG3);break;
        default:break;
    }
    if (dig>=3) dig=0;
}

//prog_char number[] =
char number[] =
{
0b11000000, //0
0b11111001, //1
0b10100100, //2
0b10110000, //3 //
0b10011001, //4
0b10010010, //5
0b10000010, //6
0b11111000, //7
0b10000000, //8
0b10010000, //9
0b11111111, //blank
0b10111111, //-
0b10001000, //A
0b10000011, //b
0b11000110, //c
0b10100001, //d
0b10000110, //e
0b10001110, //f
0b11000111, //L
0b11001110, //t
0b10001001, //h
};
