#include <avr/io.h>
#include <avr/interrupt.h>
#include "../macros.h"
//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include "../HAL.h"
#pragma once

typedef struct task{
    void (*pfunc) (void);    // указатель на функцию

    uint16_t countdown;           // обратный отсчет
}task;                      // флаг запуска можно вынести за структуру

uint16_t delay_time;   // задержка до старта , штоб счетчик не ушел в минус
uint16_t dt;
//extern void USART0_write(unsigned char data);
// максимальное количество задач
#define MAXnTASKS       8
#define StartFrom 0xD3
//Константа для UART`a
//скорость обмена 9600 при частоте 8 МГц
#define UBRRvalue 0x0033
/// Массив задач ///////////
volatile task TaskArray[MAXnTASKS];
/// Прототипы фукнций ////////
//void InitScheduler (void);      //инициализация диспетчера
void DispatchTask (void);       //собсна сам диспетчер и запуск задачи по флагу
void Idle();
void DeleteTask (uint8_t index);     //удаление задачи
//TODO:нужно научить эту функцию брать указатель на функцию с любыми аргументами и без них
void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
void InitScheduler();

