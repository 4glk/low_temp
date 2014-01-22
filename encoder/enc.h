#ifndef ENC_H
#define ENC_H

#include <avr/io.h>
#include "../HAL.h"
#include "../pin_macros.h"

#define num_of_st    4     /*���������� ��������� �� ���� "������"*/
#define state_0      0x00  /*��������� ������� 0 ��������*/
//old
//#define state_1      _BV(ENC0)             /*��������� ������� 1 ��������*/
//#define state_2      _BV(ENC1)             /*��������� ������� 2 ��������*/
//#define state_3      _BV(ENC1) + _BV(ENC0)/*��������� ������� 3 ��������*/
//new
#define state_1      ACTIVE(ENC_0)             /*��������� ������� 1 ��������*/ //_BV(ENC_0)  || (1<<ENC_0)
#define state_2      ACTIVE(ENC_1)             /*��������� ������� 2 ��������*/
#define state_3      ACTIVE(ENC_1) + ACTIVE(ENC_0)/*��������� ������� 3 ��������*/


unsigned int EncState,EncData;      //���������� ���������� ��������� � ������ ��������

void Encoder_Init();                   //������� ������������� ��������
void Encoder_Scan(unsigned int min, unsigned int max);//������� ��������� ��������

#endif
