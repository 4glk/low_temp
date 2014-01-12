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
//#include "HAL.h"
#include <util/delay.h>
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
extern void Ind_Buffer(int volume);

int main(void)
{
//    Timer_Init();
    Shift_Init();
    Digits_Init();
    sei();
//    TCCR2=BIT(CS21);// тактовую 1мег делем на 8
    // Insert code
    char i=0;
    while(1){
            Ind_Buffer(67);
           // if (i>21) i=0;
            // Send_Byte(249);
           //  _delay_ms(700);
    };
    return 0;
}



