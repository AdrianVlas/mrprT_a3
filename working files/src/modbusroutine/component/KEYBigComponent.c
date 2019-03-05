#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2156
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2203

#define REGISTERS_KEY 8

int privateKEYBigGetReg2(int adrReg);

int getKEYBigModbusRegister(int);//�������� ���������� ��������
int getKEYBigModbusBit(int);//�������� ���������� ����
int setKEYBigModbusRegister(int, int);// ��������
int setKEYBigModbusBit(int, int);// ����

void setKEYBigCountObject(void);//�������� �-�� �������
void preKEYBigReadAction(void);//action �� ������
void preKEYBigWriteAction(void);//action �� ������
int  postKEYBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *keybigcomponent;

/**************************************/
//���������� ���������� KEY
/**************************************/
void constructorKEYBigComponent(COMPONENT_OBJ *keybigcomp)
{
  keybigcomponent = keybigcomp;

  keybigcomponent->getModbusRegister = getKEYBigModbusRegister;//�������� ���������� ��������
  keybigcomponent->getModbusBit      = getKEYBigModbusBit;//�������� ���������� ����
  keybigcomponent->setModbusRegister = setKEYBigModbusRegister;// ��������
  keybigcomponent->setModbusBit      = setKEYBigModbusBit;// ����

  keybigcomponent->preReadAction   = preKEYBigReadAction;//action �� ������
  keybigcomponent->preWriteAction  = preKEYBigWriteAction;//action �� ������
  keybigcomponent->postWriteAction = postKEYBigWriteAction;//action ����� ������

  keybigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getKEYBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_SMALLModbusRegister(&current_settings_interfaces.ranguvannja_buttons[0], REGISTERS_KEY, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getKEYBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(keybigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(keybigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����
  if(validN_SMALLACMD(dataReg)==MARKER_ERRORPERIMETR) return MARKER_ERRORPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
  uint32_t maska = ((uint32_t)edition_settings.buttons_mode)&(1<<((offset/REGISTERS_KEY)*1));
  //�������� �� ������������ ����� �������
  if(!maska)
  switch((unsigned short)dataReg)
  {
   case 50000://- 1-� ��.�������    *
   case 50001://- 2-� ��.�������     *
   case 50002://- 3-� ��.�������     *
   case 50003://- 4-� ��.�������     *
   case 50016://- ����.���1          *
   case 50032://- ����.���2          *
   case 50041://- ����.�����.���2    *
   case 50048://- ����.���3          *
   case 50064://- ����.���4    
   case 50144://- ���������� �� 3U0-1
   case 50160://- ����.TZNP1
   case 50170://- ����.TZNP2
   case 50180://- ����.TZNP3
   case 50190://- ����.TZNP4
   case 50208://- ����.���1(���)  
   case 50211://- ����.���2(���)  
   case 50224://- ���������� �����1
   case 50229://- ���������� �����1
   case 50234://- ���� �����1
   case 50235://- ���� �����2
   case 50240://- ���������� ������1
   case 50243://- ���������� ������2
   case 50336://  ���� ����1 �� ��
   case 50352://  ���� ����2 �� ��
   case 50432://- ����.��1
   case 50435://- ����.��2
   case 50438://- ����.��3
   case 50441://- ����.��4
   case 50444://- ����.��5
   case 50447://- ����.��6
   case 50450://- ����.��7
   case 50453://- ����.��8
   case 50464://- ���������� ��� 1
   case 50467://- ���������� ��� 2
   case 50468://- ���������� ��� 2 �� ��
   case 50470://- ���������� ��� 2 �� I�2
   case 50472://- ���������� ��� 2 �� I�5
   case 50480://- ���������� ��
   case 50481://- ���� �� 1
   case 50484://- ���� �� 2
   case 50487://- ���� �� ���
   case 50496://- ���������� ��
   case 50497://- ���� ��
   case 50528://- ���������� �� �/�
//   case 50640://- ��������� �� ��
//   case 50641://- ���������� �� ��
   case 50642://- ���������� ��������� �� ��
   case 50646://- ��������� �� ��
   case 50648://- �������� ��� ��
   case 50649://- �������� ���� ��
   case 50672://- ��������� �� ��
   case 50673://- ���������� �� ��
   case 50674://- ���������� ��������� �� ��
   case 50678://- ��������� �� ��
   case 50680://- �������� ��� ��
   case 50681://- �������� ���� ��
//   case 50706://- ����� ���������
//   case 50707://- ����� ����
   case 50713://- ̳��./�������. *
//   case 50743://- �.���.���.�� ��
      return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//switch
  else
  //�������� �� ������������ ����� �����
  switch((unsigned short)dataReg)
  {
//   case 50000://- 1-� ��.�������    *
//   case 50001://- 2-� ��.�������     *
//   case 50002://- 3-� ��.�������     *
//   case 50003://- 4-� ��.�������     *
//   case 50016://- ����.���1          *
//   case 50032://- ����.���2          *
//   case 50041://- ����.�����.���2    *
//   case 50048://- ����.���3          *
//   case 50064://- ����.���4    
//   case 50144://- ���������� �� 3U0-1
//   case 50160://- ����.TZNP1
//   case 50170://- ����.TZNP2
//   case 50180://- ����.TZNP3
//   case 50190://- ����.TZNP4
//   case 50208://- ����.���1(���)  
//   case 50211://- ����.���2(���)  
//   case 50224://- ���������� �����1
//   case 50229://- ���������� �����1
   case 50234://- ���� �����1
   case 50235://- ���� �����2
//   case 50240://- ���������� ������1
//   case 50243://- ���������� ������2
   case 50336://  ���� ����1 �� ��
   case 50352://  ���� ����2 �� ��
//   case 50432://- ����.��1
//   case 50435://- ����.��2
//   case 50438://- ����.��3
//   case 50441://- ����.��4
//   case 50444://- ����.��5
//   case 50447://- ����.��6
//   case 50450://- ����.��7
//   case 50453://- ����.��8
//   case 50464://- ���������� ��� 1
//   case 50467://- ���������� ��� 2
//   case 50468://- ���������� ��� 2 �� ��
//   case 50470://- ���������� ��� 2 �� I�2
//   case 50472://- ���������� ��� 2 �� I�5
//   case 50480://- ���������� ��
   case 50481://- ���� �� 1
   case 50484://- ���� �� 2
   case 50487://- ���� �� ���
//   case 50496://- ���������� ��
   case 50497://- ���� ��
//   case 50528://- ���������� �� �/�
   case 50640://- ��������� �� ��
   case 50641://- ���������� �� ��
//   case 50642://- ���������� ��������� �� ��
   case 50646://- ��������� �� ��
   case 50648://- �������� ��� ��
   case 50649://- �������� ���� ��
   case 50672://- ��������� �� ��
   case 50673://- ���������� �� ��
//   case 50674://- ���������� ��������� �� ��
   case 50678://- ��������� �� ��
   case 50680://- �������� ��� ��
   case 50681://- �������� ���� ��
   case 50706://- ����� ���������
   case 50707://- ����� ����
   case 50713://- ̳��./�������. *
   case 50743://- �.���.���.�� ��
      return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preKEYBigReadAction(void) {
//action �� ������
  keybigcomponent->isActiveActualData = 1;
}//
void preKEYBigWriteAction(void) {
//action �� ������
  keybigcomponent->operativMarker[0] = -1;
  keybigcomponent->operativMarker[1] = -1;//����������� ������
  keybigcomponent->isActiveActualData = 1;
}//
int postKEYBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = keybigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = keybigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_SMALLModbusRegister(&edition_settings.ranguvannja_buttons[0], REGISTERS_KEY, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateKEYBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
