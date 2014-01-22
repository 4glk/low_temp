#include "dispatch.h"
//delay_time=50;

void AddTask (void (*taskfunc)(void), uint16_t taskdelay){
   uint8_t n=0;
   uint8_t position=0;
   // крутить пока : не попадется функция или пустая функция или пустой отсчет  и отсчет больше следующих и не больше количества задач
   while (((TaskArray[n].pfunc!=(*taskfunc))&&((TaskArray[n].pfunc!=0)||(TaskArray[n].countdown!=0)))&&(TaskArray[n].countdown<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n;
        if ((TaskArray[position].pfunc==(*taskfunc))){// если есть уже такая функция в списке , то добавляем ей время
             TaskArray[position].countdown += taskdelay;  // прибавили время , нужно еще раз сортировать вниз по очереди
                                                        // как бы это сделать без goto и лишних функций
                                                        // еще один проход ничего не изменит т.к он найдет эту же функцию
                                                        // как вариант разбить на функции , но как с передачей имени функции ???
                                                        // перемотаем до конца или пока счетчики меньше текущего
        task tmp2;
        while ((TaskArray[n+1].pfunc!=0)&&(TaskArray[n+1].countdown<=TaskArray[n].countdown)){
                tmp2=TaskArray[n+1];
                TaskArray[n+1]=TaskArray[n];
                TaskArray[n]=tmp2;
                n++;
        }
        //while (((TaskArray[n].pfunc!=0)||(TaskArray[n].countdown!=0))&&(TaskArray[n].countdown<=(TaskArray[position].countdown))&&(n < MAXnTASKS)))n++;
        // а теперь нужно сдвинуть очередь :) теперь наверное нужна новая позиция , здесь скорее пойдет сортировка перестановкой
        // чтож , еще одна временная структура
        }else {
        while ((TaskArray[n].pfunc != 0) && (TaskArray[n].countdown!=0) && (n < MAXnTASKS))n++;   // этот цикл мотает до конца очереди
        for (/*.*/;n>position;n--){TaskArray[n]=TaskArray[n-1];} // этот сдвигает с конца до позиции
        TaskArray[position].pfunc = *taskfunc;                      // если присвоить раньше  , то значение потеряется??? да!
        TaskArray[position].countdown = taskdelay;
        }
       if (n==0){ delay_time=TaskArray[0].countdown;dt=delay_time;} //если в очереди пусто вроде
// при добавлении нужно обновлять счетчик, тк там старое значение
}

void DispatchTask (void){
    uint8_t n=0;
    if (flags.RunFlag==1&&TaskArray[0].pfunc != 0){
        task tmp;
        tmp=TaskArray[0];
        //сдвигаем очередь и затираем первое в  очереди , т.к. оно у нас уже на запуске
    while (((TaskArray[n].pfunc != 0) || (TaskArray[n].countdown!=0)) && (n < MAXnTASKS)){
        n++;
        TaskArray[n-1]=TaskArray[n];        //сдвигаем очередь вперед
        if (TaskArray[n-1].countdown) TaskArray[n-1].countdown-=dt;     //вычитаем прошедшее время из каждой задачи
   }

    if (TaskArray[0].pfunc != 0) {
            delay_time=TaskArray[0].countdown;
            dt=delay_time;
    }
    if (*tmp.pfunc!=0)(*tmp.pfunc)();
    flags.RunFlag=0;
   }
}

void DeleteTask (uint8_t j)
{
   TaskArray[j].pfunc = 0x0000;
   TaskArray[j].countdown=0;
//   TaskArray[j].delay = 0;
//    usartWrite('S');
}

ISR(TIMER2_OVF_vect){
  //  timer2++;
   TCNT2 = StartFrom;
   if (flags.RunFlag==0&&delay_time!=0)delay_time--;
   if (delay_time==0)flags.RunFlag=1;
}

void InitScheduler (void){
//   uint8_t i;
   TCCR2 |= (0<<CS02)|(1<<CS01)|(1<<CS00);   // устанавливаем прескалер - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // очищаем флаг прерывания таймера Т0
   TIMSK |= 1<<TOIE2;   // разрешаем прерывание по переполнению
   TCNT2 = StartFrom;    // загружаем начальное зн. в счетный регистр
//   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // очищаем массив задач
}
