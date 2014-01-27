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
#include <util/delay.h>
//#include "pin_macros.h"
#include "scheduler/dispatch.h"
#include "onewire/onewire.h"
//#include "onewire/OWfunc.h"
///#include "onewire.h"
///#include "encoder.h"
///#include "7seg.h"
///#include "zero_cross.h"
///#include "ppm.h"

//#define BIT(bit)  	(1<<(bit))
void indicator_Buffer();
void enc_Scan();
void temperature_Measure();
extern void Send_Byte();

extern void Timer_Init();
extern void Shift_Init();
extern void Digits_Init();
extern void Encoder_init();
//extern void Encoder_Init();
extern void Encoder_Scan(unsigned int min, unsigned int max);
extern void Ind_Buffer(int volume);
extern void usartDebug();
extern void temperatureStartConvert();
extern void temperatureRead();
extern void USART_init();
extern void USART0_write(unsigned char data);
//extern void AddTask (void (*taskfunc)(void), uint16_t taskdelay);

unsigned int EncState,EncData;

int main(void)
{
//    Timer_Init();
    Shift_Init();
    Digits_Init();
    Encoder_init();
    USART_init();
    usartDebug();
    InitScheduler();
//    Encoder_Init();

//    TCCR2=BIT(CS21);// тактовую 1мег делем на 8
    // Insert code
   // int i=0;
   flags.RunFlag=0;
   AddTask(indicator_Buffer,5);
   AddTask(enc_Scan,10);
   AddTask(temperature_Measure,25000);
    sei();
    while(1){

                DispatchTask();
          //  Encoder_Scan(0,99);
          //  Ind_Buffer(EncData);
           // temperatureStartConvert();
           // _delay_ms(700);
          //  temperatureRead();

    };
    return 0;
}

void indicator_Buffer(){
    Ind_Buffer(EncData);
     AddTask(indicator_Buffer,5);
}

void enc_Scan(){
    Encoder_Scan(0,99);
     AddTask(enc_Scan,10);
}

void temperature_Measure(){
    AddTask(temperatureStartConvert,25);
    AddTask(temperatureRead,2500);
    AddTask(temperature_Measure,25000);
    USART0_write('K');
}
