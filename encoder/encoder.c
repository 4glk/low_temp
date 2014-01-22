//Набор функций для обслуживания инкрементального энкодера
//Автор s_black - www.embed.com.ua
//июль 2010 г.

#include "encoder.h"

void Encoder_init (void)//Функция инициализации энкодера
{
    DDR_encoder &= ~_BV(ENC_0);//инициализируем входы
	DDR_encoder &= ~_BV(ENC_1);//для подключения энкодера
	PORT_encoder |= _BV(ENC_0) | _BV(ENC_1);//подключаем внутренние резистры
}

void Encoder_Scan(unsigned int min, unsigned int max)//Функция обработки энкодера
{
    static unsigned char New, EncPlus, EncMinus;//Переменные нового значения энкодера, промежуточные переменные + и -

    New = PIN_encoder & (_BV(ENC_1) | _BV(ENC_0));// Считываем настоящее положение энкодера (маска пинов (1<<ENC_1)|(1<<ENC_0)

    if(New != EncState)//Если значение изменилось по отношению к прошлому
    {
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
