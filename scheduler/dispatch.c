#include "dispatch.h"
//delay_time=50;

void AddTask (void (*taskfunc)(void), uint16_t taskdelay){
   uint8_t n=0;
   uint8_t position=0;
   // ������� ���� : �� ��������� ������� ��� ������ ������� ��� ������ ������  � ������ ������ ��������� � �� ������ ���������� �����
   while (((TaskArray[n].pfunc!=(*taskfunc))&&((TaskArray[n].pfunc!=0)||(TaskArray[n].countdown!=0)))&&(TaskArray[n].countdown<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n;
        if ((TaskArray[position].pfunc==(*taskfunc))){// ���� ���� ��� ����� ������� � ������ , �� ��������� �� �����
             TaskArray[position].countdown += taskdelay;  // ��������� ����� , ����� ��� ��� ����������� ���� �� �������
                                                        // ��� �� ��� ������� ��� goto � ������ �������
                                                        // ��� ���� ������ ������ �� ������� �.� �� ������ ��� �� �������
                                                        // ��� ������� ������� �� ������� , �� ��� � ��������� ����� ������� ???
                                                        // ���������� �� ����� ��� ���� �������� ������ ��������
        task tmp2;
        while ((TaskArray[n+1].pfunc!=0)&&(TaskArray[n+1].countdown<=TaskArray[n].countdown)){
                tmp2=TaskArray[n+1];
                TaskArray[n+1]=TaskArray[n];
                TaskArray[n]=tmp2;
                n++;
        }
        //while (((TaskArray[n].pfunc!=0)||(TaskArray[n].countdown!=0))&&(TaskArray[n].countdown<=(TaskArray[position].countdown))&&(n < MAXnTASKS)))n++;
        // � ������ ����� �������� ������� :) ������ �������� ����� ����� ������� , ����� ������ ������ ���������� �������������
        // ���� , ��� ���� ��������� ���������
        }else {
        while ((TaskArray[n].pfunc != 0) && (TaskArray[n].countdown!=0) && (n < MAXnTASKS))n++;   // ���� ���� ������ �� ����� �������
        for (/*.*/;n>position;n--){TaskArray[n]=TaskArray[n-1];} // ���� �������� � ����� �� �������
        TaskArray[position].pfunc = *taskfunc;                      // ���� ��������� ������  , �� �������� ����������??? ��!
        TaskArray[position].countdown = taskdelay;
        }
       if (n==0){ delay_time=TaskArray[0].countdown;dt=delay_time;} //���� � ������� ����� �����
// ��� ���������� ����� ��������� �������, �� ��� ������ ��������
}

void DispatchTask (void){
    uint8_t n=0;
    if (flags.RunFlag==1&&TaskArray[0].pfunc != 0){
        task tmp;
        tmp=TaskArray[0];
        //�������� ������� � �������� ������ �  ������� , �.�. ��� � ��� ��� �� �������
    while (((TaskArray[n].pfunc != 0) || (TaskArray[n].countdown!=0)) && (n < MAXnTASKS)){
        n++;
        TaskArray[n-1]=TaskArray[n];        //�������� ������� ������
        if (TaskArray[n-1].countdown) TaskArray[n-1].countdown-=dt;     //�������� ��������� ����� �� ������ ������
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
   TCCR2 |= (0<<CS02)|(1<<CS01)|(1<<CS00);   // ������������� ��������� - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // ������� ���� ���������� ������� �0
   TIMSK |= 1<<TOIE2;   // ��������� ���������� �� ������������
   TCNT2 = StartFrom;    // ��������� ��������� ��. � ������� �������
//   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // ������� ������ �����
}
