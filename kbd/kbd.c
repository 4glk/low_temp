#include "kbd.h"
//extern void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod);
//  обработчик нажатий

void InitControl(){
    KEY_PORT |= KEY_MASK;
	KEY_DDR &= ~ KEY_MASK;
}

void KeyState(){

    if (((flags.KeyPressed)&&(flags.KeyReleased))||((flags.KeyPressed)&&(flags.KeyPushLong))){
        flags.KeyPressed=0;
        if (flags.KeyPushLong){
            flags.KeyPin+=8;
            //flags.KeyPushLong=0;
        }
        flags.KeyPushLong=0;
        //flags.State_Automate=1;
    }
    flags.KeyReleased=1;
    KeyCurrentCode=flags.KeyPin;
    flags.KeyPin=0;
}

void KeyScan(){
    volatile static uint8_t k=0;
  if(KEY_CODE){ // обработчик нажатия
    flags.KeyReleased=0;
        if (++k >=2 ) {      //короткое нажатие 100-250 миллисекунд
            if (!flags.KeyPressed){flags.KeyPressed = 1;flags.KeyPin=(KEY_CODE);}
               if ( k > 100 ){  //длинное нажатие 1-3 секунды
                 if (!flags.KeyPushLong){
                    k=0;                // проблема с этой переменной , конфликтует с енумом кнопок (((
                    flags.KeyPushLong=1;
                    KeyState();
                 }
               }
        }
    }
    else {
        k=0;
        if (!flags.KeyReleased) {flags.KeyReleased=1;}
        KeyState();
    }
    AddTask(KeyScan,50);
}
