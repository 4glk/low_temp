//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru
//
//  Target(s)...: AVR
//
//  Compiler....: любой
//
//  Description.: Драйвер 7-ми сегментного 4-ех разрядного индикатора
//
//  Data........: 15.04.10  Создан
//  Data........: 8.03.13  Добавил поддержку SPI и посегментную развертку
//
//***************************************************************************
#ifndef INDICATOR_H
#define INDICATOR_H

#include <string.h>
#include "compilers.h"
#include "spi.h"

/********************** настройки ***************************/

/*количество цифр индикатора*/
#define IND_AMOUNT_NUM 8

/*закомментировать, если не используется подключение по SPI*/
//#define IND_SPI_CONNECTION

/*закомментировать, если используется поразрядная развертка*/
#define IND_SCAN_SEGMENT

/*активный уровень сегмента 0 или 1*/
#define IND_ACTIVE_LEVEL_SEG   0    //негатив

/*активный уровень разряда 0 или 1*/
#define IND_ACTIVE_LEVEL_DIG   1

/*куда подключены сегменты индикатора*/
#define IND_PORT_SEG PORTD
#define IND_DDR_SEG DDRD

/*куда подклчены разряды индикатора*/
#define IND_PORT_DIG PORTB
#define IND_DDR_DIG DDRB

/*к какому регистру подключены сегменты и разряды
если используется два регистра,
третью строчку нужно закомментировать*/
#define IND_SHIFT_REG_SEG  2
#define IND_SHIFT_REG_DIG1 1
#define IND_SHIFT_REG_DIG2 0

/*к каким выводам подключены разряды*/
#define IND_NUM1 7
#define IND_NUM2 6
#define IND_NUM3 5
#define IND_NUM4 4
#define IND_NUM5 3
#define IND_NUM6 2
#define IND_NUM7 1
#define IND_NUM8 0

/*если используется три сдвиговых регистра
нужно определить вторую группу разрядов */
#define IND_NUM9  8
#define IND_NUM10 9
#define IND_NUM11 10
#define IND_NUM12 11
#define IND_NUM13 12
#define IND_NUM14 13
#define IND_NUM15 14
#define IND_NUM16 15

/*к каким выводам подключены сегменты*/
#define IND_A    0
#define IND_B    1
#define IND_C    2
#define IND_D    3
#define IND_E    4
#define IND_F    5
#define IND_G    6
#define IND_COM  7

/***********************************************************************************
*   Function name :   IND_Init
*   Returns :         нет
*   Parameters :      нет
*   Purpose :         инициализация портов ввода-вывода, очистка буфера индикатора
************************************************************************************/
void IND_Init(void);

/***********************************************************************************
*   Function name :   IND_Output
*   Returns :         нет
*   Parameters :      value - число для преобразования, comma - позиция точки на индикаторе
*   Purpose :         преобразует 16-ти разрядное число, записывает его в буфер индикатора
***********************************************************************************/
void IND_Output(uint16_t value, uint8_t comma);

/***********************************************************************************
*   Function name :   IND_OutputFormat
*   Returns :         нет
*   Parameters :      value - число для преобразования,
*                     comma - позиция точки на индикаторе
*                     position - на какую позицию выводить число
*                     amount - сколько цифр выводить
*   Purpose :         преобразует 16-ти разрядное число, записывает его в буфер индикатора
***********************************************************************************/
void IND_OutputFormat(uint16_t value, uint8_t comma, uint8_t position, uint8_t amount);

/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         нет
*   Parameters :      нет
*   Purpose :         Выводит на индикатор число из буфера.
*                     Эту функцию нужно вызывать из прерывания таймера
***********************************************************************************/
void IND_Update(void);



/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         нет
*   Parameters :      char_string - строка символов
                      position - позиция
                      comma - точка
*   Purpose :         выводит строку символов в буффер индикатора
***********************************************************************************/
void IND_OutputFormatChar(char char_string[],uint8_t comma, uint8_t position);

/***********************************************************************************
*   Function name :   ascii2int
*   Returns :         код символа
*   Parameters :      входной символ таблицы
*   Purpose :         преобразует символ
***********************************************************************************/
uint8_t ascii2int(uint8_t symbol);
//enum {one=1,two=2,three=3,zero=0,five=5,}tralala;


/***********************************************************************************
*   Function name :   IND_RunString
*   Returns :         ----------
*   Parameters :      скорость
                      строка
                      количество цифр
                      точка
                      положение
*   Purpose :         бегущая строка
***********************************************************************************/
void IND_RunString(char ch_string,uint8_t speed,uint8_t field,uint8_t amount,uint8_t comma);

// вывод минут, секунд на дисплей
/**
    вывод на индикатор минут и секунд.
   @param вход кол-во секунд с ацп
   @param argument2 explanation
   . . .
   @return обновление буффера индикатора
*/
void IND_Time(uint16_t CurrentTime,uint8_t position);


extern void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
#endif //INDICATOR_H
