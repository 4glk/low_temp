#ifndef ENC_H
#define ENC_H

#include <avr/io.h>
#include "../HAL.h"
#include "../pin_macros.h"

#define num_of_st    4     /*количество состояний на один "щелчок"*/
#define state_0      0x00  /*состояние выводов 0 энкодера*/
//old
//#define state_1      _BV(ENC0)             /*состояние выводов 1 энкодера*/
//#define state_2      _BV(ENC1)             /*состояние выводов 2 энкодера*/
//#define state_3      _BV(ENC1) + _BV(ENC0)/*состояние выводов 3 энкодера*/
//new
#define state_1      ACTIVE(ENC_0)             /*состояние выводов 1 энкодера*/ //_BV(ENC_0)  || (1<<ENC_0)
#define state_2      ACTIVE(ENC_1)             /*состояние выводов 2 энкодера*/
#define state_3      ACTIVE(ENC_1) + ACTIVE(ENC_0)/*состояние выводов 3 энкодера*/


unsigned int EncState,EncData;      //глобальные переменные состояния и данных энкодера

void Encoder_Init();                   //функция инициализации энкодера
void Encoder_Scan(unsigned int min, unsigned int max);//Функция обработки энкодера

#endif
