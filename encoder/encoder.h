#ifndef ENCODER_H
#define ENCODER_H

#include <avr/io.h>

//#define _BV(x)   (1 << x)  //чтобы десять раз его не искать
#define PORT_encoder PORTB /*регистр порта энкодера*/
#define PIN_encoder  PINB  /*регистр выводов порта энкодера*/
#define DDR_encoder  DDRB  /*регистр направления*/
#define ENC_0        PB0   /*вывод 0 энкодера*/
#define ENC_1        PB2   /*вывод 1 энкодера*/
#define num_of_st    4     /*количество состояний на один "щелчок"*/
#define state_0      0x00  /*состояние выводов 0 энкодера*/
#define state_1      _BV(ENC_0)             /*состояние выводов 1 энкодера*/
#define state_2      _BV(ENC_1)             /*состояние выводов 2 энкодера*/
#define state_3      _BV(ENC_1) + _BV(ENC_0)/*состояние выводов 3 энкодера*/

unsigned int EncState,EncData;      //глобальные переменные состояния и данных энкодера

void Encoder_init(void);                   //функция инициализации энкодера
void Encoder_Scan(unsigned int min, unsigned int max);//Функция обработки энкодера

#endif


