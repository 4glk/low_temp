#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#define ZERO_CROSS PD2 //¬ход импульсов ZERO-CROSS (INT0)
#define Sw1 PC0        // нопка включени€ и увеличени€ €ркости 
#define Sw2 PC1        // нопка выключени€ и уменьшени€ €ркости 
 
#define control_triac PD6      //¬ывод на управл€ющий электрод симистора
#define v_change_brightness 10 //Ўаг регулировки скорости изменени€ €ркости 
#define t_pulse_triac 20       //ƒлительность отпирающего импульса симистора 20 мкс (смотреть по “” дл€ конкретного симистора)
#define BR_hi 9600	           // максимальна€ €ркость
#define BR_lo 400	           // миниимальна€ €ркость 
#define BR_m 4500	           // средн€€ €ркость

volatile unsigned int brightness;

ISR (INT0_vect)                           //ѕо переднему/заднему фронтам импульса ZERO-CROSS
{
    OCR1A = brightness;                   //–егистру сравнени€ присваиваем значение €ркости
	TCCR1B |= _BV(WGM12) | _BV(CS10);    //«апускаем таймер 1 в режиме —“— с периодом счЄта 1 мкс
}

ISR (TIMER0_OVF_vect)            //ќпрос кнопок раз в 65 мс
{
    if(bit_is_clear(PINC, Sw1))  //если нажата кнопка +
	{
	    brightness += v_change_brightness;//увеличиваем €ркость с заданным шагом
		if(brightness > BR_hi) brightness = BR_hi;//не выход€ за пределы
	}
	else if(bit_is_clear(PINC, Sw2)) //если нажата кнопка -
	{
	    brightness -= v_change_brightness;//уменьшаем €ркость заданным шагом
		if(brightness <= BR_lo) brightness = BR_lo;//не выход€ за пределы
	}
}

ISR (TIMER1_COMPA_vect)           //прерывание дл€ формировани€ открывающего импульса симистора
{
    PORTD |= _BV(control_triac);  //ѕередний фронт отпирающего импульса симистора
    _delay_us (t_pulse_triac);    //ƒлительность отпирающего импульса 
    PORTD &= ~_BV(control_triac); //«адний фронт отпирающего импульса симистора
	TCCR1B = TCNT1 = 0;           //остановка и обнуление таймера 0
}

int main (void)
{
    PORTC |= _BV(Sw1) | _BV(Sw2);//кнопки с подт€гивающими резисторами
	DDRD |= _BV(control_triac);  //выход управл€ющего электрода
	DDRD &= ~_BV(ZERO_CROSS);    //вход детектора нул€
	PORTD |= _BV(ZERO_CROSS);    //с подт€гивающим резистором дл€ питани€ транзистора оптрона
	MCUCR |= _BV(ISC00);         //внешнее прерывание 0 по любому изменению уровн€
    GICR |= _BV(INT0);           //разрешаем внешнее прерывание 0
	TIMSK |= _BV(OCIE1A) | _BV(TOIE0);//разрешаем прерывани€ таймеров 0 и 1
	TCCR0 |= _BV(CS02);          //запускаем таймер 0 с предделителем на 256 дл€ опроса кнопок регулировки €ркости
	brightness = BR_m;           //€ркость на средину диапазона
    sei();                       //общее разрешение прерываний
	for(;;);                     //бесконечный цикл 
}


