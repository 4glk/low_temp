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
int main(void)
{
//    Timer_Init();
    Shift_Init();
    sei();
//    TCCR2=BIT(CS21);// тактовую 1мег делем на 8
    // Insert code
    char i=0;
    while(1){
             Send_Byte(i++);
           //  _delay_ms(700);
    };
    return 0;
}



