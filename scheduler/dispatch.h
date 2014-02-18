#include <avr/io.h>
#include <avr/interrupt.h>
#include "../macros.h"
//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include "../HAL.h"
#pragma once

typedef struct task{
    void (*pfunc) (void);    // ��������� �� �������

    uint16_t countdown;           // �������� ������
}task;                      // ���� ������� ����� ������� �� ���������

uint16_t delay_time;   // �������� �� ������ , ���� ������� �� ���� � �����
uint16_t dt;
//extern void USART0_write(unsigned char data);
// ������������ ���������� �����
#define MAXnTASKS       8
#define StartFrom 0xD3
//��������� ��� UART`a
//�������� ������ 9600 ��� ������� 8 ���
#define UBRRvalue 0x0033
/// ������ ����� ///////////
volatile task TaskArray[MAXnTASKS];
/// ��������� ������� ////////
//void InitScheduler (void);      //������������� ����������
void DispatchTask (void);       //������ ��� ��������� � ������ ������ �� �����
void Idle();
void DeleteTask (uint8_t index);     //�������� ������
//TODO:����� ������� ��� ������� ����� ��������� �� ������� � ������ ����������� � ��� ���
void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
void InitScheduler();

