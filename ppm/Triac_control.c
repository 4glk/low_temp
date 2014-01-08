#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#define ZERO_CROSS PD2 //���� ��������� ZERO-CROSS (INT0)
#define Sw1 PC0        //������ ��������� � ���������� ������� 
#define Sw2 PC1        //������ ���������� � ���������� ������� 
 
#define control_triac PD6      //����� �� ����������� �������� ���������
#define v_change_brightness 10 //��� ����������� �������� ��������� ������� 
#define t_pulse_triac 20       //������������ ����������� �������� ��������� 20 ��� (�������� �� �� ��� ����������� ���������)
#define BR_hi 9600	           // ������������ �������
#define BR_lo 400	           // ������������ ������� 
#define BR_m 4500	           // ������� �������

volatile unsigned int brightness;

ISR (INT0_vect)                           //�� ���������/������� ������� �������� ZERO-CROSS
{
    OCR1A = brightness;                   //�������� ��������� ����������� �������� �������
	TCCR1B |= _BV(WGM12) | _BV(CS10);    //��������� ������ 1 � ������ ��� � �������� ����� 1 ���
}

ISR (TIMER0_OVF_vect)            //����� ������ ��� � 65 ��
{
    if(bit_is_clear(PINC, Sw1))  //���� ������ ������ +
	{
	    brightness += v_change_brightness;//����������� ������� � �������� �����
		if(brightness > BR_hi) brightness = BR_hi;//�� ������ �� �������
	}
	else if(bit_is_clear(PINC, Sw2)) //���� ������ ������ -
	{
	    brightness -= v_change_brightness;//��������� ������� �������� �����
		if(brightness <= BR_lo) brightness = BR_lo;//�� ������ �� �������
	}
}

ISR (TIMER1_COMPA_vect)           //���������� ��� ������������ ������������ �������� ���������
{
    PORTD |= _BV(control_triac);  //�������� ����� ����������� �������� ���������
    _delay_us (t_pulse_triac);    //������������ ����������� �������� 
    PORTD &= ~_BV(control_triac); //������ ����� ����������� �������� ���������
	TCCR1B = TCNT1 = 0;           //��������� � ��������� ������� 0
}

int main (void)
{
    PORTC |= _BV(Sw1) | _BV(Sw2);//������ � �������������� �����������
	DDRD |= _BV(control_triac);  //����� ������������ ���������
	DDRD &= ~_BV(ZERO_CROSS);    //���� ��������� ����
	PORTD |= _BV(ZERO_CROSS);    //� ������������� ���������� ��� ������� ����������� �������
	MCUCR |= _BV(ISC00);         //������� ���������� 0 �� ������ ��������� ������
    GICR |= _BV(INT0);           //��������� ������� ���������� 0
	TIMSK |= _BV(OCIE1A) | _BV(TOIE0);//��������� ���������� �������� 0 � 1
	TCCR0 |= _BV(CS02);          //��������� ������ 0 � ������������� �� 256 ��� ������ ������ ����������� �������
	brightness = BR_m;           //������� �� ������� ���������
    sei();                       //����� ���������� ����������
	for(;;);                     //����������� ���� 
}


