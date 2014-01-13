/* Плавный регулятор температуры
TODO:
- три кнопки или энкодер
- два или три семисегментных индикатора
- один светодиод (возможно двухцветный)
- детектор пересечения нуля
- фазоимпульсное управление
- возможно алгоритм брезенхема
- однопроводной датчик
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "encoder/enc.h"
#include "encoder/encoder.h"
//#include "HAL.h"
//#include <util/delay.h>
//#include "pin_macros.h"
///#include "onewire.h"
///#include "encoder.h"
///#include "7seg.h"
///#include "zero_cross.h"
///#include "ppm.h"

//#define BIT(bit)  	(1<<(bit))

extern void Send_Byte();

extern void Timer_Init();
extern void Shift_Init();
extern void Digits_Init();
extern void Encoder_init();
extern void Encoder_Scan(unsigned int min, unsigned int max);
extern void Ind_Buffer(int volume);

unsigned int EncState,EncData;

int main(void)
{
//    Timer_Init();
    Shift_Init();
    Digits_Init();
    Encoder_init();
    sei();
//    TCCR2=BIT(CS21);// тактовую 1мег делем на 8
    // Insert code
   // int i=0;
    while(1){
            Encoder_Scan(0,99);
            Ind_Buffer(EncData);
       //     if (++i>999) i=0;
            // Send_Byte(249);
        //     _delay_ms(250);
    };
    return 0;
}



