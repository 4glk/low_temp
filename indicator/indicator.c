//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru
//
//  Target(s)...: AVR
//
//  Compiler....: любой
//
//  Description.: Драйвер 7-ми сегментного 4-ех разрядного индикатора
//
//  Data........: 15.04.10  Создан
//  Data........: 8.03.13  Добавил поддержку SPI и посегментную развертку
//
//***************************************************************************
#include "indicator.h"

#ifndef IND_SPI_CONNECTION
   #if (IND_AMOUNT_NUM > 8)
    #error "При данной конфигурации IND_AMOUNT_NUM должно быть меньше 8"
  #endif
#endif

#ifndef IND_SHIFT_REG_DIG2
  #if (IND_AMOUNT_NUM > 8)
    #error "При данной конфигурации IND_AMOUNT_NUM должно быть меньше 8"
  #endif

  #if ((IND_SHIFT_REG_SEG > 1)||(IND_SHIFT_REG_DIG1 > 1))
    #error "При данной конфигурации IND_SHIFT_REG_SEG и IND_SHIFT_REG_DIG1 должны быть меньше 2"
  #endif
#endif

#ifdef IND_SPI_CONNECTION
 #ifdef IND_SHIFT_REG_DIG2
   #define IND_AMOUNT_REG 3
 #else
   #define IND_AMOUNT_REG 2
 #endif
   uint8_t spi_buf[IND_AMOUNT_REG];
#endif

#define IND_LIGHT_OUT 0xff

#if (IND_ACTIVE_LEVEL_SEG == 0)
   #define IND_OutSeg(port, value) port &= ~(value)
   #define IND_LightOutSeg(port, value) port |= (value)
#else
   #define IND_OutSeg(port, value) port |= (value)
   #define IND_LightOutSeg(port, value) port &= ~(value)
#endif

#if (IND_ACTIVE_LEVEL_DIG == 0)
   #define IND_OutDig(port, value) port &= ~(value)
   #define IND_LightOutDig(port, value) port |= (value)
#else
   #define IND_OutDig(port, value) port |= (value)
   #define IND_LightOutDig(port, value) port &= ~(value)
#endif

#define IND_EMPTY_NUM 10

/*буфер 7-ми сегметного индикатора*/
uint8_t ind_buf[IND_AMOUNT_NUM];

// TODO: забить таблицу под завязку, транслит , добавляем все совпадающие символы
/*таблица перекодировки*/
//*
__flash uint8_t number[][2] =   // скоро она потолстеет , будет + 46 символов , с повторяющимися , а может и больше
{
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(0<<IND_G),0}, //0
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(0<<IND_D)|(0<<IND_E)|(0<<IND_F)|(0<<IND_G),1}, //1
  {(1<<IND_A)|(1<<IND_B)|(0<<IND_C)|(1<<IND_D)|(1<<IND_E)|(0<<IND_F)|(1<<IND_G),2},//2
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(0<<IND_E)|(0<<IND_F)|(1<<IND_G),3}, //3
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(0<<IND_D)|(0<<IND_E)|(1<<IND_F)|(1<<IND_G),4},//4
  {(1<<IND_A)|(0<<IND_B)|(1<<IND_C)|(1<<IND_D)|(0<<IND_E)|(1<<IND_F)|(1<<IND_G),5}, //5
  {(1<<IND_A)|(0<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),6}, //6
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(0<<IND_D)|(0<<IND_E)|(0<<IND_F)|(0<<IND_G),7}, //7
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),8}, //8
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(0<<IND_E)|(1<<IND_F)|(1<<IND_G),9}, //9
  {(0<<IND_A)|(0<<IND_B)|(0<<IND_C)|(0<<IND_D)|(0<<IND_E)|(0<<IND_F)|(0<<IND_G),10},  //IND_EMPTY_NUM
  {(0<<IND_A)|(0<<IND_B)|(0<<IND_C)|(0<<IND_D)|(0<<IND_E)|(0<<IND_F)|(1<<IND_G),11}, //MINUS , 11
  {(0<<IND_A)|(0<<IND_B)|(0<<IND_C)|(0<<IND_D)|(0<<IND_E)|(0<<IND_F)|(0<<IND_G),32}, //SPACE
  {(0<<IND_A)|(0<<IND_B)|(0<<IND_C)|(1<<IND_D)|(0<<IND_E)|(0<<IND_F)|(0<<IND_G),95}, //_
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(0<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),65}, //a
  {(0<<IND_A)|(0<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),66},//b
  {(1<<IND_A)|(0<<IND_B)|(0<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(0<<IND_G),67}, //c
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(0<<IND_F)|(1<<IND_G),68}, //d
  {(1<<IND_A)|(0<<IND_B)|(0<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),69}, //e
  {(1<<IND_A)|(0<<IND_B)|(0<<IND_C)|(0<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),70}, //f
  {(1<<IND_A)|(0<<IND_B)|(0<<IND_C)|(0<<IND_D)|(1<<IND_E)|(1<<IND_F)|(0<<IND_G),71}, //G Г
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(0<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),72}, //h
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(0<<IND_G),79}, //O
  {(1<<IND_A)|(1<<IND_B)|(0<<IND_C)|(0<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),80}, //P P
  {(0<<IND_A)|(0<<IND_B)|(0<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),84}, //T t
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(0<<IND_E)|(1<<IND_F)|(1<<IND_G),85}, //U Y
  {(1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G),86}, //V B
  {(0<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(0<<IND_E)|(1<<IND_F)|(1<<IND_G),89}, //Y Y

};

uint8_t ascii2int(uint8_t symbol){
    int tmp=(int)(symbol);
    return tmp;
}
/******************************************************************************/
void IND_OutputFormatChar(char char_string[], uint8_t comma, uint8_t position)
// TODO: реализовать бегущую строку с использованием количества элементов, а также мигание символов
{
    uint8_t i,j,amount;
    char tmp[strlen(char_string)];
    amount=strlen(char_string);
    for (i=0,j=strlen(char_string);i<strlen(char_string);i++,j--){ //зеркалирование строки
            tmp[j-1]=char_string[i];
    }

    for (j=0;j<amount;j++){
        for (i=11;i<=((int)tmp[j]);++i){    //добавлено стартовое значение , перескакиваем цифры
            if (read_byte_flash(number[i][1])==(int)tmp[j]) break; // вся трабла была с чтением с пзу
        }
      ind_buf[j+position-1] = read_byte_flash(number[i][0]); //это конечно не оптимально искать в пзу
                                                    // но не забивать же туда всю таблицу
    }
  if ((comma <= IND_AMOUNT_NUM) && (comma != 0)) {
    ind_buf[comma-1] |= 1<<IND_COM;
  }
}

void IND_Time(uint16_t CurrentTime,uint8_t position){
        uint8_t blk_dot;
    !(CurrentTime%2)?(blk_dot=1):(blk_dot=0);   // мигает по четности ...
	ind_buf[3+position-1] = read_byte_flash(number[CurrentTime % 6000/600]); // здесь раскладываем число на разряды
	ind_buf[2+position-1] = read_byte_flash(number[CurrentTime % 600 /60 ])|(blk_dot<<IND_COM);//(!(CurrentTime%2)?(1<<IND_COM):tralala()); // +точка
	ind_buf[1+position-1] = read_byte_flash(number[CurrentTime % 60 /10]);					// выделяем десятки секунд 5 максимальное значение
	ind_buf[0+position-1] = read_byte_flash(number[CurrentTime % 10]);

}



__flash uint8_t digit[] =
{
   IND_NUM1,
   IND_NUM2,
   IND_NUM3,
   IND_NUM4,
   IND_NUM5,
   IND_NUM6,
   IND_NUM7,
   IND_NUM8
#ifdef IND_SHIFT_REG_DIG2
   ,IND_NUM9,
   IND_NUM10,
   IND_NUM11,
   IND_NUM12,
   IND_NUM13,
   IND_NUM14,
   IND_NUM15,
   IND_NUM16
#endif
};


#ifdef IND_SCAN_SEGMENT
__flash uint8_t mask[] =
{
   (1<<IND_A),
   (1<<IND_B),
   (1<<IND_C),
   (1<<IND_D),
   (1<<IND_E),
   (1<<IND_F),
   (1<<IND_G),
   (1<<IND_COM)
};
#endif

/******************************************************************************/
void IND_Init(void)
{
  uint8_t i;
#ifndef IND_SPI_CONNECTION
  IND_PORT_SEG = (1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G)|(1<<IND_COM);
  IND_DDR_SEG = (1<<IND_A)|(1<<IND_B)|(1<<IND_C)|(1<<IND_D)|(1<<IND_E)|(1<<IND_F)|(1<<IND_G)|(1<<IND_COM);

  for(i = 0; i < IND_AMOUNT_NUM; i++){
     IND_PORT_DIG |= (1<<read_byte_flash(digit[i]));
     IND_DDR_DIG |= (1<<read_byte_flash(digit[i]));
  }
#else
    SPI_Init();
#endif

  for(i = 0; i < IND_AMOUNT_NUM; i++) {
     ind_buf[i] = 0;
  }
}

/******************************************************************************/
void IND_Output(uint16_t value, uint8_t comma)
{
  uint8_t tmp;
  uint8_t i;


  for(i = 0; i < IND_AMOUNT_NUM; i++){
    tmp = value % 10;
    if ((i == 0)||(value > 0)||(i <= comma)){
       ind_buf[i] = read_byte_flash(number[tmp]);
    }
    else{
       ind_buf[i] = read_byte_flash(number[IND_EMPTY_NUM]);
    }
    value = value/10;
  }

  if ((comma <= IND_AMOUNT_NUM) && (comma != 0)) {
    ind_buf[comma-1] |= 1<<IND_COM;
  }
}

/******************************************************************************/
void IND_OutputFormat(uint16_t value, uint8_t comma, uint8_t position, uint8_t amount)
{
  uint8_t tmp;
  uint8_t i;

  if ((position <= IND_AMOUNT_NUM)&&(position != 0)){
     for(i = 0; i < amount; i++){
        tmp = value % 10;
        if ((i == 0)||(value > 0)||(position <= comma)){
           ind_buf[position-1] = read_byte_flash(number[tmp]);
        }
        else{
           ind_buf[position-1] = read_byte_flash(number[IND_EMPTY_NUM]);
        }
        value = value/10;
        position++;
        if (position > IND_AMOUNT_NUM){
           break;
        }
     }
  }

  if ((comma <= IND_AMOUNT_NUM) && (comma != 0)) {
    ind_buf[comma-1] |= 1<<IND_COM;
  }
}

/******************************************************************************/
void IND_Update(void)
{
  static uint8_t count = 0;
  uint8_t i;

#ifdef IND_SPI_CONNECTION
  /*________________ подключение по SPI____________________________*/

 #ifdef IND_SHIFT_REG_DIG2
  uint16_t tmp;
 #else
  uint8_t tmp;
 #endif

  /*гасим индикатор*/
  IND_LightOutSeg(spi_buf[IND_SHIFT_REG_SEG],IND_LIGHT_OUT);

  tmp = 0;
  for (i = 0; i < IND_AMOUNT_NUM; i++){
     tmp |= (1<<read_byte_flash(digit[i]));
  }
  IND_LightOutDig(spi_buf[IND_SHIFT_REG_DIG1],((uint8_t)tmp));

 #ifdef IND_SHIFT_REG_DIG2
  IND_LightOutDig(spi_buf[IND_SHIFT_REG_DIG2],(tmp>>8));
 #endif

  SPI_WriteArray(IND_AMOUNT_REG, spi_buf);

 #ifdef IND_SCAN_SEGMENT
 /*___________реализация посегментной развертки___________*/

  tmp = 0;
  for (i = 0; i < IND_AMOUNT_NUM; i++){
    if (ind_buf[i]&read_byte_flash(mask[count])) {
       tmp |= (1<<read_byte_flash(digit[i]));
    }
  }
  IND_OutDig(spi_buf[IND_SHIFT_REG_DIG1], ((uint8_t)tmp));

 #ifdef IND_SHIFT_REG_DIG2
  IND_OutDig(spi_buf[IND_SHIFT_REG_DIG2],(tmp>>8));
 #endif

  IND_OutSeg(spi_buf[IND_SHIFT_REG_SEG], read_byte_flash(mask[count]));

  count++;
  count &= 0x07;

 #else
  /*___________реализация поразрядной развертки___________*/

  tmp = 1<<read_byte_flash(digit[count]);
  IND_OutDig(spi_buf[IND_SHIFT_REG_DIG1], ((uint8_t)tmp));

 #ifdef IND_SHIFT_REG_DIG2
  IND_OutDig(spi_buf[IND_SHIFT_REG_DIG2],(tmp>>8));
 #endif

  IND_OutSeg(spi_buf[IND_SHIFT_REG_SEG], ind_buf[count]);

  count++;
  if (count >= IND_AMOUNT_NUM){
     count = 0;
  }
 #endif

  /*вывод на индикатор*/
  SPI_WriteArray(IND_AMOUNT_REG, spi_buf);

#else
 /*____________________обычное подключение____________________________*/

 uint8_t tmp;

 /*гасим все индикаторы*/
 IND_LightOutSeg(IND_PORT_SEG, IND_LIGHT_OUT);

 tmp = 0;
 for (i = 0; i < IND_AMOUNT_NUM; i++){
    tmp |= (1<<read_byte_flash(digit[i]));
 }
 IND_LightOutDig(IND_PORT_DIG, tmp);

 #ifdef IND_SCAN_SEGMENT
 /*____________реализация посегментной развертки___________*/

  tmp = 0;

  for (i = 0; i < IND_AMOUNT_NUM; i++){
    if (ind_buf[i]&read_byte_flash(mask[count])) {
       tmp |= (1<<read_byte_flash(digit[i]));
    }
  }

  IND_OutDig(IND_PORT_DIG, tmp);
  IND_OutSeg(IND_PORT_SEG, read_byte_flash(mask[count]));

  count++;
  count &= 0x07;

 #else
 /*____________реализаци поразрядной развертки____________*/

  IND_OutDig(IND_PORT_DIG, (1<<read_byte_flash(digit[count])));
  IND_OutSeg(IND_PORT_SEG, ind_buf[count]);

  count++;
  if (count >= IND_AMOUNT_NUM){
     count = 0;
  }
 #endif
#endif
    AddTask(IND_Update,1);
}
