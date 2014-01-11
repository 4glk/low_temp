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
#include "HAL.h"
#include <avr/include.h>
//#include "pin_macros.h"
///#include "onewire.h"
///#include "encoder.h"
///#include "7seg.h"
///#include "zero_cross.h"
///#include "ppm.h"
#define BIT(bit)  	(1<<(bit))
extern void Send_Byte();
int main(void)
{
TCCR0=BIT(CS01);// тактовую 1мег делем на 8
    // Insert code
    char i=0;
    while(1){
            if ( TIFR & BIT(TOIE0) ){// Задержка 0,002048
                TIFR=BIT(TOV0);{
                Send_Byte(i);
                delay(200);
               	if (++i>8) i=0;//счетчик для последовательного перебора цифр
                }

    };


    return 0;
}

}

