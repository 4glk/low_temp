#include "enc.h"

void Encoder_Init(){
    //*
    DRIVER (ENC0,IN);
    DRIVER (ENC0,PULLUP);
    DRIVER (ENC1,IN);
    DRIVER (ENC1,PULLUP);
    DRIVER (ENC_BTN,IN);
    DRIVER (ENC_BTN,PULLUP);//*/
}

void Encoder_Scan(unsigned int min, unsigned int max)//Функция обработки энкодера
{
    static unsigned char New, EncPlus, EncMinus;//Переменные нового значения энкодера, промежуточные переменные + и -

 //   New = PIN_encoder & (_BV(ENC1) | _BV(ENC0));// Считываем настоящее положение энкодера
        New = (ACTIVE(ENC1)|ACTIVE(ENC0));

    if(New != EncState)//Если значение изменилось по отношению к прошлому
    {
      //*//switch macros give error , then deploy in if else construction
        switch(EncState) //Перебор прошлого значения энкодера
	    {
	    case state_2:if(New == state_3) EncPlus++;//В зависимости от значения увеличиваем
		             if(New == state_0) EncMinus++;//Или уменьшаем
		       break;
	    case state_0:if(New == state_2) EncPlus++;
		             if(New == state_1) EncMinus++;
		       break;
	    case state_1:if(New == state_0) EncPlus++;
		             if(New == state_3) EncMinus++;
		       break;
	    case state_3:if(New == state_1) EncPlus++;
		             if(New == state_2) EncMinus++;
		       break;
        default:break;
	    }
    //*/
    /*//trouble whith macros
        if(EncState == state_2){ //Перебор прошлого значения энкодера
            if(New == state_3) EncPlus++;//В зависимости от значения увеличиваем
            if(New == state_0) EncMinus++;//Или уменьшаем
        }else if(EncState==state_0){
            if(New == state_2) EncPlus++;
		    if(New == state_1) EncMinus++;
        }else if(EncState==state_1){
            if(New == state_0) EncPlus++;
		    if(New == state_3) EncMinus++;
        }else if(EncState==state_3){
            if(New == state_1) EncPlus++;
		    if(New == state_2) EncMinus++;
        }
        //*/
		if(EncPlus == num_of_st) //если прошёл один "щелчок"
		{
		    if(EncData++ >= max) EncData = max;//увеличиваем значение, следим, чтобы не выйти за границы верхнего
			EncPlus = 0;
		}

		if(EncMinus == num_of_st) //если прошёл один "щелчок"
		{
		    if(EncData-- <= min) EncData = min;//уменьшаем значение, следим чтобы не выйти за границы нижнего пределов
			EncMinus = 0;
		}
        EncState = New;	// Записываем новое значение предыдущего состояния
	}
}
