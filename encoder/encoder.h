#ifndef ENCODER_H
#define ENCODER_H

#include <avr/io.h>

//#define _BV(x)   (1 << x)  //����� ������ ��� ��� �� ������
#define PORT_encoder PORTB /*������� ����� ��������*/
#define PIN_encoder  PINB  /*������� ������� ����� ��������*/
#define DDR_encoder  DDRB  /*������� �����������*/
#define ENC_0        PB0   /*����� 0 ��������*/
#define ENC_1        PB2   /*����� 1 ��������*/
#define num_of_st    4     /*���������� ��������� �� ���� "������"*/
#define state_0      0x00  /*��������� ������� 0 ��������*/
#define state_1      _BV(ENC_0)             /*��������� ������� 1 ��������*/
#define state_2      _BV(ENC_1)             /*��������� ������� 2 ��������*/
#define state_3      _BV(ENC_1) + _BV(ENC_0)/*��������� ������� 3 ��������*/

unsigned int EncState,EncData;      //���������� ���������� ��������� � ������ ��������

void Encoder_init(void);                   //������� ������������� ��������
void Encoder_Scan(unsigned int min, unsigned int max);//������� ��������� ��������

#endif


