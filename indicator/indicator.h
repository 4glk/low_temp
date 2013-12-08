//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru
//
//  Target(s)...: AVR
//
//  Compiler....: �����
//
//  Description.: ������� 7-�� ����������� 4-�� ���������� ����������
//
//  Data........: 15.04.10  ������
//  Data........: 8.03.13  ������� ��������� SPI � ������������ ���������
//
//***************************************************************************
#ifndef INDICATOR_H
#define INDICATOR_H

#include <string.h>
#include "compilers.h"
#include "spi.h"

/********************** ��������� ***************************/

/*���������� ���� ����������*/
#define IND_AMOUNT_NUM 8

/*����������������, ���� �� ������������ ����������� �� SPI*/
//#define IND_SPI_CONNECTION

/*����������������, ���� ������������ ����������� ���������*/
#define IND_SCAN_SEGMENT

/*�������� ������� �������� 0 ��� 1*/
#define IND_ACTIVE_LEVEL_SEG   0    //�������

/*�������� ������� ������� 0 ��� 1*/
#define IND_ACTIVE_LEVEL_DIG   1

/*���� ���������� �������� ����������*/
#define IND_PORT_SEG PORTD
#define IND_DDR_SEG DDRD

/*���� ��������� ������� ����������*/
#define IND_PORT_DIG PORTB
#define IND_DDR_DIG DDRB

/*� ������ �������� ���������� �������� � �������
���� ������������ ��� ��������,
������ ������� ����� ����������������*/
#define IND_SHIFT_REG_SEG  2
#define IND_SHIFT_REG_DIG1 1
#define IND_SHIFT_REG_DIG2 0

/*� ����� ������� ���������� �������*/
#define IND_NUM1 7
#define IND_NUM2 6
#define IND_NUM3 5
#define IND_NUM4 4
#define IND_NUM5 3
#define IND_NUM6 2
#define IND_NUM7 1
#define IND_NUM8 0

/*���� ������������ ��� ��������� ��������
����� ���������� ������ ������ �������� */
#define IND_NUM9  8
#define IND_NUM10 9
#define IND_NUM11 10
#define IND_NUM12 11
#define IND_NUM13 12
#define IND_NUM14 13
#define IND_NUM15 14
#define IND_NUM16 15

/*� ����� ������� ���������� ��������*/
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
*   Returns :         ���
*   Parameters :      ���
*   Purpose :         ������������� ������ �����-������, ������� ������ ����������
************************************************************************************/
void IND_Init(void);

/***********************************************************************************
*   Function name :   IND_Output
*   Returns :         ���
*   Parameters :      value - ����� ��� ��������������, comma - ������� ����� �� ����������
*   Purpose :         ����������� 16-�� ��������� �����, ���������� ��� � ����� ����������
***********************************************************************************/
void IND_Output(uint16_t value, uint8_t comma);

/***********************************************************************************
*   Function name :   IND_OutputFormat
*   Returns :         ���
*   Parameters :      value - ����� ��� ��������������,
*                     comma - ������� ����� �� ����������
*                     position - �� ����� ������� �������� �����
*                     amount - ������� ���� ��������
*   Purpose :         ����������� 16-�� ��������� �����, ���������� ��� � ����� ����������
***********************************************************************************/
void IND_OutputFormat(uint16_t value, uint8_t comma, uint8_t position, uint8_t amount);

/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         ���
*   Parameters :      ���
*   Purpose :         ������� �� ��������� ����� �� ������.
*                     ��� ������� ����� �������� �� ���������� �������
***********************************************************************************/
void IND_Update(void);



/***********************************************************************************
*   Function name :   IND_Update
*   Returns :         ���
*   Parameters :      char_string - ������ ��������
                      position - �������
                      comma - �����
*   Purpose :         ������� ������ �������� � ������ ����������
***********************************************************************************/
void IND_OutputFormatChar(char char_string[],uint8_t comma, uint8_t position);

/***********************************************************************************
*   Function name :   ascii2int
*   Returns :         ��� �������
*   Parameters :      ������� ������ �������
*   Purpose :         ����������� ������
***********************************************************************************/
uint8_t ascii2int(uint8_t symbol);
//enum {one=1,two=2,three=3,zero=0,five=5,}tralala;


/***********************************************************************************
*   Function name :   IND_RunString
*   Returns :         ----------
*   Parameters :      ��������
                      ������
                      ���������� ����
                      �����
                      ���������
*   Purpose :         ������� ������
***********************************************************************************/
void IND_RunString(char ch_string,uint8_t speed,uint8_t field,uint8_t amount,uint8_t comma);

// ����� �����, ������ �� �������
/**
    ����� �� ��������� ����� � ������.
   @param ���� ���-�� ������ � ���
   @param argument2 explanation
   . . .
   @return ���������� ������� ����������
*/
void IND_Time(uint16_t CurrentTime,uint8_t position);


extern void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
#endif //INDICATOR_H
