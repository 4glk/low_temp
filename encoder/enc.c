#include "enc.h"

void Encoder_Init(){
    //*
    DRIVER (ENC_0,IN);
    DRIVER (ENC_0,PULLUP);
    DRIVER (ENC_1,IN);
    DRIVER (ENC_1,PULLUP);
    DRIVER (ENC_BTN,IN);
    DRIVER (ENC_BTN,PULLUP);//*/
}

void Encoder_Scan(unsigned int min, unsigned int max)//������� ��������� ��������
{
    static unsigned char New, EncPlus, EncMinus;//���������� ������ �������� ��������, ������������� ���������� + � -

 //   New = PIN_encoder & (_BV(ENC1) | _BV(ENC0));// ��������� ��������� ��������� ��������
        New = (ACTIVE(ENC_1)|ACTIVE(ENC_0));

    if(New != EncState)//���� �������� ���������� �� ��������� � ��������
    {
      /*//switch macros give error , then deploy in if else construction
        switch(EncState) //������� �������� �������� ��������
	    {
	    case state_2:if(New == state_3) EncPlus++;//� ����������� �� �������� �����������
		             if(New == state_0) EncMinus++;//��� ���������
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
    //*//trouble whith macros   // ���������������� �� ������ , �� �� ������� � �������� ������� , ������ �� ����� ����� �����������
        if(EncState == state_2){ //������� �������� �������� ��������
            if(New == state_3) EncPlus++;//� ����������� �� �������� �����������
            if(New == state_0) EncMinus++;//��� ���������
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
		if(EncPlus == num_of_st) //���� ������ ���� "������"
		{
		    if(EncData++ >= max) EncData = max;//����������� ��������, ������, ����� �� ����� �� ������� ��������
			EncPlus = 0;
		}

		if(EncMinus == num_of_st) //���� ������ ���� "������"
		{
		    if(EncData-- <= min) EncData = min;//��������� ��������, ������ ����� �� ����� �� ������� ������� ��������
			EncMinus = 0;
		}
        EncState = New;	// ���������� ����� �������� ����������� ���������
	}
}
