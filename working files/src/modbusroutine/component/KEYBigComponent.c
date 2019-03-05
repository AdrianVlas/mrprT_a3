#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 2156
//конечный регистр в карте памяти
#define END_ADR_REGISTER 2203

#define REGISTERS_KEY 8

int privateKEYBigGetReg2(int adrReg);

int getKEYBigModbusRegister(int);//получить содержимое регистра
int getKEYBigModbusBit(int);//получить содержимое бита
int setKEYBigModbusRegister(int, int);// регистра
int setKEYBigModbusBit(int, int);// бита

void setKEYBigCountObject(void);//записать к-во обектов
void preKEYBigReadAction(void);//action до чтения
void preKEYBigWriteAction(void);//action до записи
int  postKEYBigWriteAction(void);//action после записи

COMPONENT_OBJ *keybigcomponent;

/**************************************/
//подготовка компонента KEY
/**************************************/
void constructorKEYBigComponent(COMPONENT_OBJ *keybigcomp)
{
  keybigcomponent = keybigcomp;

  keybigcomponent->getModbusRegister = getKEYBigModbusRegister;//получить содержимое регистра
  keybigcomponent->getModbusBit      = getKEYBigModbusBit;//получить содержимое бита
  keybigcomponent->setModbusRegister = setKEYBigModbusRegister;// регистра
  keybigcomponent->setModbusBit      = setKEYBigModbusBit;// бита

  keybigcomponent->preReadAction   = preKEYBigReadAction;//action до чтения
  keybigcomponent->preWriteAction  = preKEYBigWriteAction;//action до записи
  keybigcomponent->postWriteAction = postKEYBigWriteAction;//action после записи

  keybigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getKEYBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_SMALLModbusRegister(&current_settings_interfaces.ranguvannja_buttons[0], REGISTERS_KEY, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getKEYBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(keybigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//делаем копию
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(keybigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер
  if(validN_SMALLACMD(dataReg)==MARKER_ERRORPERIMETR) return MARKER_ERRORPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
  uint32_t maska = ((uint32_t)edition_settings.buttons_mode)&(1<<((offset/REGISTERS_KEY)*1));
  //проверка на допустимость Режим «Кнопка»
  if(!maska)
  switch((unsigned short)dataReg)
  {
   case 50000://- 1-а гр.уставок    *
   case 50001://- 2-а гр.уставок     *
   case 50002://- 3-а гр.уставок     *
   case 50003://- 4-а гр.уставок     *
   case 50016://- Блок.МСЗ1          *
   case 50032://- Блок.МСЗ2          *
   case 50041://- Блок.приск.МСЗ2    *
   case 50048://- Блок.МСЗ3          *
   case 50064://- Блок.МСЗ4    
   case 50144://- Блокировка ЗЗ 3U0-1
   case 50160://- Блок.TZNP1
   case 50170://- Блок.TZNP2
   case 50180://- Блок.TZNP3
   case 50190://- Блок.TZNP4
   case 50208://- Блок.ЗЗП1(КОФ)  
   case 50211://- Блок.ЗЗП2(КОФ)  
   case 50224://- Блокировка ЗНмин1
   case 50229://- Блокировка ЗНмин1
   case 50234://- Пуск ЗНмин1
   case 50235://- Пуск ЗНмин2
   case 50240://- Блокировка ЗНмакс1
   case 50243://- Блокировка ЗНмакс2
   case 50336://  Пуск ПРВВ1 від ДВ
   case 50352://  Пуск ПРВВ2 від ДВ
   case 50432://- Блок.УЗ1
   case 50435://- Блок.УЗ2
   case 50438://- Блок.УЗ3
   case 50441://- Блок.УЗ4
   case 50444://- Блок.УЗ5
   case 50447://- Блок.УЗ6
   case 50450://- Блок.УЗ7
   case 50453://- Блок.УЗ8
   case 50464://- Блокировка ОЗТ 1
   case 50467://- Блокировка ОЗТ 2
   case 50468://- Блокировка ОЗТ 2 от АП
   case 50470://- Блокировка ОЗТ 2 от Iг2
   case 50472://- Блокировка ОЗТ 2 от Iг5
   case 50480://- Блокировка ГЗ
   case 50481://- Пуск ГЗ 1
   case 50484://- Пуск ГЗ 2
   case 50487://- Пуск ГЗ РПН
   case 50496://- Блокировка ТЗ
   case 50497://- Пуск ТЗ
   case 50528://- Блокировка КЗ Н/В
//   case 50640://- Включение ВВ ВН
//   case 50641://- Отключение ВВ ВН
   case 50642://- Блокировка включения ВВ ВН
   case 50646://- Положение ВВ ВН
   case 50648://- Контроль Вкл ВН
   case 50649://- Контроль Откл ВН
   case 50672://- Включение ВВ НН
   case 50673://- Отключение ВВ НН
   case 50674://- Блокировка включения ВВ НН
   case 50678://- Положение ВВ НН
   case 50680://- Контроль Вкл НН
   case 50681://- Контроль Откл НН
//   case 50706://- Сброс индикации
//   case 50707://- Сброс реле
   case 50713://- Місц./Дистанц. *
//   case 50743://- С.блк.Гот.до ТУ
      return MARKER_ERRORPERIMETR; //не прошла валидация
  }//switch
  else
  //проверка на допустимость Режим «Ключ
  switch((unsigned short)dataReg)
  {
//   case 50000://- 1-а гр.уставок    *
//   case 50001://- 2-а гр.уставок     *
//   case 50002://- 3-а гр.уставок     *
//   case 50003://- 4-а гр.уставок     *
//   case 50016://- Блок.МСЗ1          *
//   case 50032://- Блок.МСЗ2          *
//   case 50041://- Блок.приск.МСЗ2    *
//   case 50048://- Блок.МСЗ3          *
//   case 50064://- Блок.МСЗ4    
//   case 50144://- Блокировка ЗЗ 3U0-1
//   case 50160://- Блок.TZNP1
//   case 50170://- Блок.TZNP2
//   case 50180://- Блок.TZNP3
//   case 50190://- Блок.TZNP4
//   case 50208://- Блок.ЗЗП1(КОФ)  
//   case 50211://- Блок.ЗЗП2(КОФ)  
//   case 50224://- Блокировка ЗНмин1
//   case 50229://- Блокировка ЗНмин1
   case 50234://- Пуск ЗНмин1
   case 50235://- Пуск ЗНмин2
//   case 50240://- Блокировка ЗНмакс1
//   case 50243://- Блокировка ЗНмакс2
   case 50336://  Пуск ПРВВ1 від ДВ
   case 50352://  Пуск ПРВВ2 від ДВ
//   case 50432://- Блок.УЗ1
//   case 50435://- Блок.УЗ2
//   case 50438://- Блок.УЗ3
//   case 50441://- Блок.УЗ4
//   case 50444://- Блок.УЗ5
//   case 50447://- Блок.УЗ6
//   case 50450://- Блок.УЗ7
//   case 50453://- Блок.УЗ8
//   case 50464://- Блокировка ОЗТ 1
//   case 50467://- Блокировка ОЗТ 2
//   case 50468://- Блокировка ОЗТ 2 от АП
//   case 50470://- Блокировка ОЗТ 2 от Iг2
//   case 50472://- Блокировка ОЗТ 2 от Iг5
//   case 50480://- Блокировка ГЗ
   case 50481://- Пуск ГЗ 1
   case 50484://- Пуск ГЗ 2
   case 50487://- Пуск ГЗ РПН
//   case 50496://- Блокировка ТЗ
   case 50497://- Пуск ТЗ
//   case 50528://- Блокировка КЗ Н/В
   case 50640://- Включение ВВ ВН
   case 50641://- Отключение ВВ ВН
//   case 50642://- Блокировка включения ВВ ВН
   case 50646://- Положение ВВ ВН
   case 50648://- Контроль Вкл ВН
   case 50649://- Контроль Откл ВН
   case 50672://- Включение ВВ НН
   case 50673://- Отключение ВВ НН
//   case 50674://- Блокировка включения ВВ НН
   case 50678://- Положение ВВ НН
   case 50680://- Контроль Вкл НН
   case 50681://- Контроль Откл НН
   case 50706://- Сброс индикации
   case 50707://- Сброс реле
   case 50713://- Місц./Дистанц. *
   case 50743://- С.блк.Гот.до ТУ
      return MARKER_ERRORPERIMETR; //не прошла валидация
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preKEYBigReadAction(void) {
//action до чтения
  keybigcomponent->isActiveActualData = 1;
}//
void preKEYBigWriteAction(void) {
//action до записи
  keybigcomponent->operativMarker[0] = -1;
  keybigcomponent->operativMarker[1] = -1;//оперативный маркер
  keybigcomponent->isActiveActualData = 1;
}//
int postKEYBigWriteAction(void) {
extern int upravlSchematic;//флаг Rang
//action после записи
  int beginAdr = keybigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//не было записи
  int endAdr   = keybigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_SMALLModbusRegister(&edition_settings.ranguvannja_buttons[0], REGISTERS_KEY, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //ВАЛИДАЦИЯ УСПЕШНА - УСТАНОВКА
     upravlSchematic = 1;//флаг Rang

  return 0;
}//

int privateKEYBigGetReg2(int adrReg)
{
  //проверить внешний периметр
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
