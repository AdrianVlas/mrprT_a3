
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10000
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 55000

//конечный регистр в карте памяти
#define END_ADR_REGISTER 10035
//конечный bit в карте памяти
#define END_ADR_BIT 55560

#define CLRVALID_DATA  0

int privateUPRBigGetReg2(int adrReg);
int privateUPRBigGetBit2(int adrReg);

int getUPRBigModbusRegister(int);//получить содержимое регистра
int getUPRBigModbusBit(int);//получить содержимое бита
int setUPRBigModbusRegister(int, int);//получить содержимое регистра
int setUPRBigModbusBit(int, int);//получить содержимое бита

void setUPRBigCountObject(void);//записать к-во обектов
void preUPRBigReadAction(void);//action до чтения
void preUPRBigWriteAction(void);//action до записи
int  postUPRBigWriteAction(void);//action после записи

int  uprFunc000(int action, int inOffset, uint32_t *uprMaska, int validData, uint32_t **editControl);
void uprFuncRead000(int inOffset, uint32_t *uprMaska, uint32_t **editControl);
int  uprFuncValidWrite000(int action, int inOffset, uint32_t *uprMaska, uint32_t **editControl);
int  uprFuncValid000(int inOffset, int validData);
int isValidCONFCondition(unsigned int confMaska);
int isValidEXTRACondition(unsigned int extraMaska);
int isValidMTZSELCondition(uint32_t uprMaska);

void loadUPRBigActualDataBit(int beginOffset, int endOffset);

COMPONENT_OBJ *uprbigcomponent;

void uprFuncRead000(int inOffset, uint32_t *uprMaska, uint32_t **editControl)
{
  uprFunc000(0, inOffset, uprMaska, CLRVALID_DATA, editControl);
}//uprFuncRead000(int inOffset, uint32_t *uprMaska)
int uprFuncValidWrite000(int action, int inOffset, uint32_t *uprMaska, uint32_t **editControl)
{
  return uprFunc000(action, inOffset, uprMaska, CLRVALID_DATA, editControl);
}//uprFuncRead000(int inOffset, uint32_t *uprMaska)
int uprFuncValid000(int inOffset, int validData)
{
  uint32_t uprMaska=0;
  uint32_t *editControl=NULL;
  return uprFunc000(0, inOffset, &uprMaska, validData, &editControl);
}//uprFuncRead000(int inOffset, uint32_t *uprMaska)

int uprFunc000(int actControl, int inOffset, uint32_t *uprMaska, int validData, uint32_t **editControl)
{
  UNUSED(validData);
  int isValid = 1;
  (*uprMaska) = 0xFFFFFFFF;
  switch(inOffset)
    {
//  int count_bit = 2;
    case 0:
      (*uprMaska)   = MTZ_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define MTZ_CONFIGURATION_BEGIN 1
    case MTZ_CONFIGURATION_BEGIN:
      (*uprMaska)   = N_BIT_CTRMTZ_1;
      break;
    case 2:
      (*uprMaska)   = N_BIT_CTRMTZ_1_VPERED;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_1_SEL_I)) isValid = 0;
      break;
    case 3:
      (*uprMaska)   = N_BIT_CTRMTZ_1_NAZAD;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_1_SEL_I)) isValid = 0;
      break;

//  count_bit = 3;
    case 6:
      (*uprMaska)   = N_BIT_CTRMTZ_1_SEL_I;
      break;
    case 7:
      (*uprMaska)   = N_BIT_CTRMTZ_2;
      break;
    case 8:
      (*uprMaska)   = N_BIT_CTRMTZ_2_VPERED;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_2_SEL_I)) isValid = 0;
      break;
    case 9:
      (*uprMaska)   = N_BIT_CTRMTZ_2_NAZAD;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_2_SEL_I)) isValid = 0;
      break;
    case 10:
      (*uprMaska)   = N_BIT_CTRMTZ_2_PRYSKORENNJA;
      break;
    case 11:
      (*uprMaska)   = N_BIT_CTRMTZ_2_PRYSKORENA;
      break;

//  count_bit = 3;
    case 14:
      (*uprMaska)   = N_BIT_CTRMTZ_2_SEL_I;
      break;
    case 15:
      (*uprMaska)   = N_BIT_CTRMTZ_3;
      break;
    case 16:
      (*uprMaska)   = N_BIT_CTRMTZ_3_VPERED;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_3_SEL_I)) isValid = 0;
      break;
    case 17:
      (*uprMaska)   = N_BIT_CTRMTZ_3_NAZAD;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_3_SEL_I)) isValid = 0;
      break;

//  count_bit = 3;
    case 22:
      (*uprMaska)   = N_BIT_CTRMTZ_3_SEL_I;
      break;
    case 23:
      (*uprMaska)   = N_BIT_CTRMTZ_4;
      break;
    case 24:
      (*uprMaska)   = N_BIT_CTRMTZ_4_VPERED;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_4_SEL_I)) isValid = 0;
      break;
    case 25:
      (*uprMaska)   = N_BIT_CTRMTZ_4_NAZAD;
      if(isValidMTZSELCondition(N_BIT_CTRMTZ_4_SEL_I)) isValid = 0;
      break;

//  count_bit = 3;
    case 28:
      (*uprMaska)   = N_BIT_CTRMTZ_4_SEL_I;
      break;
#define MTZ_CONFIGURATION_END 29
    case MTZ_CONFIGURATION_END:
      (*uprMaska)   = N_BIT_CTRMTZ_NESPR_KIL_NAPR;
      break;

//  count_bit = 3;
    case 48:
      (*uprMaska)   = UP_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;

//IF ВСТАВКА 49-72

//  int count_bit = 2;
    case 80:
      (*uprMaska)   = OZT_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define OZT_CONFIGURATION_BEGIN 81
    case OZT_CONFIGURATION_BEGIN:
      (*uprMaska)   = N_BIT_CTROZT_1;
      break;
    case 82:
      (*uprMaska)   = N_BIT_CTROZT_1_G;
      break;
    case 83:
      (*uprMaska)   = N_BIT_CTROZT_2;
      break;
    case 84:
      (*uprMaska)   = N_BIT_CTROZT_2_G;
      break;
    case 85:
      (*uprMaska)   = N_BIT_CTROZT_2_BLK_A;
      break;
    case 86:
      (*uprMaska)   = N_BIT_CTROZT_2_BLK_2G;
      break;
#define OZT_CONFIGURATION_END 87
    case OZT_CONFIGURATION_END:
      (*uprMaska)   = N_BIT_CTROZT_2_BLK_5G;
      break;

//  int count_bit = 2;
    case 96:
      (*uprMaska)    = GP_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 97:
      (*uprMaska)   = 0;
      (*editControl) = &edition_settings.control_GP;
      if(isValidCONFCondition(GP_BIT_CONFIGURATION)) isValid = 0;
      break;

//  int count_bit = 2;
    case 112:
      (*uprMaska)   = TP_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 113:
      (*uprMaska)   = 0;
      (*editControl) = &edition_settings.control_TP;
      if(isValidCONFCondition(TP_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 3;
    case 176:
      (*uprMaska)   = P_3U0_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
          //Функція обновлення змінних при зміні конфігурації
          if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 177:
      (*uprMaska)   = 0;
      (*editControl) = &edition_settings.control_P_3U0;
      if(isValidCONFCondition(P_3U0_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 3;
    case 192:
      (*uprMaska)   = TZNP_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
          //Функція обновлення змінних при зміні конфігурації
          if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define TZNP_CONFIGURATION_BEGIN 193
    case TZNP_CONFIGURATION_BEGIN:
      (*uprMaska)   = INDEX_ML_CTR_TZNP1;
      break;
    case 194:
      (*uprMaska)   = INDEX_ML_CTR_TZNP1_VPERED;
      break;
    case 195:
      (*uprMaska)   = INDEX_ML_CTR_TZNP1_NAZAD;
      break;
    case 196:
      (*uprMaska)   = INDEX_ML_CTR_TZNP2;
      break;
    case 197:
      (*uprMaska)   = INDEX_ML_CTR_TZNP2_VPERED;
      break;
    case 198:
      (*uprMaska)   = INDEX_ML_CTR_TZNP2_NAZAD;
      break;
    case 199:
      (*uprMaska)   = INDEX_ML_CTR_TZNP3;
      break;
    case 200:
      (*uprMaska)   = INDEX_ML_CTR_TZNP3_VPERED;
      break;
    case 201:
      (*uprMaska)   = INDEX_ML_CTR_TZNP3_NAZAD;
      break;
    case 202:
      (*uprMaska)   = INDEX_ML_CTR_TZNP4;
      break;
    case 203:
      (*uprMaska)   = INDEX_ML_CTR_TZNP4_VPERED;
      break;
#define TZNP_CONFIGURATION_END 204
    case TZNP_CONFIGURATION_END:
      (*uprMaska)   = INDEX_ML_CTR_TZNP4_NAZAD;
      break;

//  count_bit = 3;
    case 208:
      (*uprMaska)   = ZOP_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 209:
      (*uprMaska)   = INDEX_ML_CTRZOP_1_STATE;
      (*editControl) = &edition_settings.control_zop;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 210:
      (*uprMaska)   = INDEX_ML_CTRZOP_1_SEL_I;
      (*editControl) = &edition_settings.control_zop;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 211:
      (*uprMaska)   = INDEX_ML_CTRZOP_2_STATE;
      (*editControl) = &edition_settings.control_zop;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 212:
      (*uprMaska)   = INDEX_ML_CTRZOP_2_SEL_I;
      (*editControl) = &edition_settings.control_zop;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 3;
    case 240:
      (*uprMaska)   = UMIN_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define UMIN_CONFIGURATION_BEGIN 241
    case UMIN_CONFIGURATION_BEGIN:
      (*uprMaska)   = INDEX_CTR_UMIN1;
      break;
    case 242:
      (*uprMaska)   = INDEX_CTR_UMIN2;
      break;
    case 243:
      (*uprMaska)   = INDEX_CTR_PO_UMIN1_OR_AND;
      break;
    case 244:
      (*uprMaska)   = INDEX_CTR_PO_UMIN2_OR_AND;
      break;
    case 245:
      (*uprMaska)   = INDEX_CTR_UMIN1_UBLK;
      break;
    case 246:
      (*uprMaska)   = INDEX_CTR_UMIN2_UBLK;
      break;
    case 247:
      (*uprMaska)   = INDEX_CTR_UMIN1_IBLK;
      break;
#define UMIN_CONFIGURATION_END 248
    case UMIN_CONFIGURATION_END:
      (*uprMaska)   = INDEX_CTR_UMIN2_IBLK;
      break;

//  count_bit = 3;
    case 256:
      (*uprMaska)   = UMAX_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define UMAX_CONFIGURATION_BEGIN 257
    case UMAX_CONFIGURATION_BEGIN:
      (*uprMaska)   = INDEX_CTR_UMAX1;
      break;
    case 258:
      (*uprMaska)   = INDEX_CTR_UMAX2;
      break;
    case 259:
      (*uprMaska)   = INDEX_CTR_PO_UMAX1_OR_AND;
      break;
#define UMAX_CONFIGURATION_END 260
    case UMAX_CONFIGURATION_END:
      (*uprMaska)   = INDEX_CTR_PO_UMAX2_OR_AND;
      break;

    case 292:
      (*uprMaska)   = INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE;
      (*editControl) = &edition_settings.control_transformator;
      break;

//  count_bit = 6;
    case 296:
      (*uprMaska)   = INDEX_ML_CTR_TRANSFORMATOR_VH_VL;
      (*editControl) = &edition_settings.control_transformator;
      break;
    case 297:
      (*uprMaska)   = INDEX_ML_CTR_TRANSFORMATOR_I_VH;
      (*editControl) = &edition_settings.control_transformator;
      break;
    case 298:
      (*uprMaska)   = INDEX_ML_CTR_TRANSFORMATOR_I_VL;
      (*editControl) = &edition_settings.control_transformator;
      break;

//  count_bit = 6;
    case 368:
      (*uprMaska)   = UROV_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
#define UROV1_CONFIGURATION_BEGIN 369
#define UROV2_CONFIGURATION_BEGIN 417
    case UROV1_CONFIGURATION_BEGIN:
    case UROV2_CONFIGURATION_BEGIN:
      (*uprMaska)   = INDEX_ML_CTRUROV_STATE;
      break;
    case 370:
    case 418:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_MTZ1;
      if(isValidCONFCondition(MTZ_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 371:
    case 419:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_MTZ2;
      if(isValidCONFCondition(MTZ_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 372:
    case 420:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_MTZ3;
      if(isValidCONFCondition(MTZ_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 373:
    case 421:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_MTZ4;
      if(isValidCONFCondition(MTZ_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 6;
    case 376:
    case 424:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_UMAX1;
      if(isValidCONFCondition(UMAX_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 377:
    case 425:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_UMAX2;
      if(isValidCONFCondition(UMAX_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 378:
    case 426:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_UMIN1;
      if(isValidCONFCondition(UMIN_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 379:
    case 427:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_UMIN2;
      if(isValidCONFCondition(UMIN_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 380:
    case 428:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_ZOP1;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 381:
    case 429:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_ZOP2;
      if(isValidCONFCondition(ZOP_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 6;
    case 386:
    case 434:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_P_3U0;
      if(isValidCONFCondition(P_3U0_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 387:
    case 435:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_TZNP1;
      if(isValidCONFCondition(TZNP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 388:
    case 436:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_TZNP2;
      if(isValidCONFCondition(TZNP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 389:
    case 437:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_TZNP3;
      if(isValidCONFCondition(TZNP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 390:
    case 438:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_TZNP4;
      if(isValidCONFCondition(TZNP_BIT_CONFIGURATION)) isValid = 0;
      break;

//IF ВСТАВКА 395-402
//IF ВСТАВКА 443-450

    case 403:
    case 451:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_OZT1;
      if(isValidCONFCondition(OZT_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 404:
    case 452:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_OZT2;
      if(isValidCONFCondition(OZT_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 405:
    case 453:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_GP1;
      if(isValidCONFCondition(GP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 406:
    case 454:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_GP2;
      if(isValidCONFCondition(GP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 407:
    case 455:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_GP_RPN;
      if(isValidCONFCondition(GP_BIT_CONFIGURATION)) isValid = 0;
      break;
    case 408:
    case 456:
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_TP;
      if(isValidCONFCondition(TP_BIT_CONFIGURATION)) isValid = 0;
      break;

#define UROV1_CONFIGURATION_END 409
#define UROV2_CONFIGURATION_END 457
    case UROV1_CONFIGURATION_END:
    case UROV2_CONFIGURATION_END:
      (*uprMaska)   = INDEX_ML_CTRUROV_SEL_I;
      break;

//  count_bit = 6;
    case 480:
      (*uprMaska)   = OFF_ON_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 481://Блокировка Вкл. ВВ от ДВ
      (*uprMaska)   = INDEX_ML_CTREXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE;
      (*editControl) = &edition_settings.control_extra_settings_1;
      break;
    case 482://Блокировка Откл. ВВ от ДВ
      (*uprMaska)   = INDEX_ML_CTREXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
      (*editControl) = &edition_settings.control_extra_settings_1;
      break;
    case 483://Контроль ФК
      (*uprMaska)   = INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION;
      (*editControl) = &edition_settings.control_extra_settings_1;
      break;
    case 484://Разрешение блокировки готовности к ТУ от защит
      (*uprMaska)   = INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU;
      (*editControl) = &edition_settings.control_extra_settings_1;
      break;
    case 485://Окно информации об отключении ВВ
      (*uprMaska)   = INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB;
      (*editControl) = &edition_settings.control_extra_settings_1;
      break;
    case 486://Контроль ВВ ВН
      (*uprMaska)   = INDEX_ML_CTRPRYVOD_VV;
      (*editControl) = &edition_settings.control_switch[0];
      if(isValidCONFCondition(OFF_ON_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 1;
    case 492://Контроль ВВ НН
      (*uprMaska)   = INDEX_ML_CTRPRYVOD_VV;
      (*editControl) = &edition_settings.control_switch[1];
      if(isValidCONFCondition(OFF_ON_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 6;
    case 512:
      (*uprMaska)   = KZ_ZV_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         //Функція обновлення змінних при зміні конфігурації
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;
    case 513:
      (*uprMaska)   = INDEX_ML_CTR_KZ_ZV_STATE;
      (*editControl) = &edition_settings.control_kz_zv;
      if(isValidCONFCondition(KZ_ZV_BIT_CONFIGURATION)) isValid = 0;
      break;

//  count_bit = 1;
    case 560:
      (*uprMaska)   = EL_BIT_CONFIGURATION;
      (*editControl) = &edition_settings.configuration;
      if(actControl)
        {
         if(action_after_changing_of_configuration(edition_settings.configuration, &edition_settings)) isValid = 0;
        }//if(actControl)
      break;

    }//switch

  if((*uprMaska)!=0xFFFFFFFF)
    {
      if(inOffset>=MTZ_CONFIGURATION_BEGIN && inOffset<=MTZ_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_mtz;
          if(isValidCONFCondition(MTZ_BIT_CONFIGURATION)) isValid = 0;
        }//if
      if(inOffset>=OZT_CONFIGURATION_BEGIN && inOffset<=OZT_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_ozt;
          if(isValidCONFCondition(OZT_BIT_CONFIGURATION)) isValid = 0;
        }//if

      if(inOffset>=TZNP_CONFIGURATION_BEGIN && inOffset<=TZNP_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_tznp;
          if(isValidCONFCondition(TZNP_BIT_CONFIGURATION)) isValid = 0;
        }//if

      if(inOffset>=UMIN_CONFIGURATION_BEGIN && inOffset<=UMIN_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_Umin;
          if(isValidCONFCondition(UMIN_BIT_CONFIGURATION)) isValid = 0;
        }//if

      if(inOffset>=UMAX_CONFIGURATION_BEGIN && inOffset<=UMAX_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_Umax;
          if(isValidCONFCondition(UMAX_BIT_CONFIGURATION)) isValid = 0;
        }//if

      if(inOffset>=UROV1_CONFIGURATION_BEGIN && inOffset<=UROV1_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_urov[0];
          if(isValidCONFCondition(UROV_BIT_CONFIGURATION)) isValid = 0;
        }//if
      if(inOffset>=UROV2_CONFIGURATION_BEGIN && inOffset<=UROV2_CONFIGURATION_END)
        {
          (*editControl) = &edition_settings.control_urov[1];
          if(isValidCONFCondition(UROV_BIT_CONFIGURATION)) isValid = 0;
        }//if

    }//if((*uprMaska)!=-1)

  if(inOffset>=49 && inOffset<73)
    {
      (*uprMaska)   = inOffset-49;//maska;
      (*editControl) = &edition_settings.control_UP;
      if(isValidCONFCondition(UP_BIT_CONFIGURATION)) isValid = 0;
      if(actControl)
        {
          //Функція обновлення коефіцієнта повернення після зміни налаштувань УЗ
          action_after_changing_ctrl_UP(&edition_settings, edition_settings.control_UP);

        }//if(actControl)
    }//if

  if((inOffset>=395 && inOffset<403) || (inOffset>=443 && inOffset<451))
    {
      int inupOffset = inOffset-395;
      (*editControl) = &edition_settings.control_urov[0];
      if(inOffset>=443)
      {
        inupOffset = inOffset-443;
        (*editControl) = &edition_settings.control_urov[1];
      }//if
      (*uprMaska)   = INDEX_ML_CTRUROV_STARTED_FROM_UP1+inupOffset;
      if(isValidCONFCondition(UROV_BIT_CONFIGURATION)) isValid = 0;
      if(isValidCONFCondition(UP_BIT_CONFIGURATION)) isValid = 0;
    }//if

  return isValid;
}//uprFunc000(int inOffset, uint32_t *uprMaska, uint32_t **editControl);

void loadUPRBigActualDataBit(int beginOffset, int endOffset)
{
  //ActualData
  for(int ii=0; ii<(1+(END_ADR_BIT-BEGIN_ADR_BIT+1)/16); ii++) tempReadArray[ii] = 0;
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
    {
      int value =0;
      if(item>=beginOffset && item<endOffset)
        {
          uint32_t uprMaska=0;
          uint32_t *editControl=NULL;
          uprFuncRead000(item, &uprMaska, &editControl);
          if(editControl==NULL) value=0;
          else
            {
              //читать значение
              value = (*editControl)&(1<<uprMaska);
            }//else
        }//if(item>=beginOffset && item<endOffset)

      int tsdata = 0;
      if(value) tsdata=1;
      tempReadArray[item/16] |= tsdata<<(item%16);
    }//for(int item=0; item<568; item++)
}//loadUPRBigActualDataBit(int beginOffset, int endOffset)

/**************************************/
//подготовка компонента UPR
/**************************************/
void constructorUPRBigComponent(COMPONENT_OBJ *uprbigcomp)
{
  uprbigcomponent = uprbigcomp;

  uprbigcomponent->getModbusRegister = getUPRBigModbusRegister;//получить содержимое регистра
  uprbigcomponent->getModbusBit      = getUPRBigModbusBit;//получить содержимое бита
  uprbigcomponent->setModbusRegister = setUPRBigModbusRegister;//получить содержимое регистра
  uprbigcomponent->setModbusBit      = setUPRBigModbusBit;//получить содержимое бита

  uprbigcomponent->preReadAction   = preUPRBigReadAction;//action до чтения
  uprbigcomponent->preWriteAction  = preUPRBigWriteAction;//action до записи
  uprbigcomponent->postWriteAction = postUPRBigWriteAction;//action после записи

  uprbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getUPRBigModbusRegister(int adrReg)
{
  extern int globalcntReg;//к-во  для чтения
  extern int globalbeginAdrReg;//адрес нач
//получить содержимое регистра
  if(privateUPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  if(uprbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//делаем копию
      int begin = globalbeginAdrReg-BEGIN_ADR_REGISTER;
      if(begin<0) globalcntReg += begin;

      int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
      int endOffset   = beginOffset +globalcntReg*16;

      loadUPRBigActualDataBit(beginOffset, endOffset); //ActualData
    }//if(acmdsmallcomponent->isActiveActualData)
  uprbigcomponent->isActiveActualData = 0;

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTBigModbusRegister(int adrReg)
int getUPRBigModbusBit(int adrBit)
{
  //получить содержимое bit
  extern int globalcntBit;//к-во бит для чтения
  extern int globalbeginAdrBit;//адрес нач бит
  //получить содержимое bit
  if(privateUPRBigGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(uprbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//делаем копию
      int begin = globalbeginAdrBit-BEGIN_ADR_BIT;
      if(begin<0) globalcntBit += begin;

      int beginOffset = adrBit-BEGIN_ADR_BIT;
      int endOffset   = adrBit-BEGIN_ADR_BIT +globalcntBit;
      loadUPRBigActualDataBit(beginOffset, endOffset); //ActualData
    }//if(acmdsmallcomponent->isActiveActualData)
  uprbigcomponent->isActiveActualData = 0;

  short tmp   = tempReadArray[(adrBit-BEGIN_ADR_BIT)/16];
  short maska = 1<<((adrBit-BEGIN_ADR_BIT)%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setUPRBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateUPRBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(uprbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//делаем копию
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(uprbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
  for(int item=beginOffset; item<(beginOffset+16); item++)
    {
      int temp = 0;
      if(dataReg&(1<<(item-beginOffset))) temp=1;//валидация на включение
      if(temp)
        if(!uprFuncValid000(item, temp)) return MARKER_ERRORDIAPAZON;
    }//for

  return 0;
}//setUPRBigModbusRegister(int adrReg, int dataReg)
int setUPRBigModbusBit(int adrBit, int dataBit)
{
  //записать содержимое bit
  if(privateUPRBigGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(uprbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//делаем копию
    }//if(uprbigcomponent->isActiveActualData)
  uprbigcomponent->isActiveActualData = 0;

  superSetOperativMarker(uprbigcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер

  int offset = adrBit-BEGIN_ADR_BIT;
  if(dataBit)//валидация на включение
    if(!uprFuncValid000(offset, dataBit)) return MARKER_ERRORDIAPAZON;

  return 0;
}//getDOUTBigModbusRegister(int adrReg)

void preUPRBigReadAction(void)
{
//action до чтения
  uprbigcomponent->isActiveActualData = 1;
}//
void preUPRBigWriteAction(void)
{
//action до записи
  uprbigcomponent->operativMarker[0] = -1;
  uprbigcomponent->operativMarker[1] = -1;//оперативный маркер
  uprbigcomponent->isActiveActualData = 1;
}//

int postUPRBigWriteAction(void)
{
  extern int upravlSetting;//флаг Setting
  extern int upravlSchematic;//флаг Rang
//action после записи
  int beginAdr = uprbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//не было записи
  int endAdr   = uprbigcomponent->operativMarker[1];
  int flag=0;
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;
  if(beginAdr>=BEGIN_ADR_BIT)
    {
      //работа с битами
      int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_BIT);//найти смещение TempWriteArray
      for(int i=0; i<countAdr; i++)
        {
          uint32_t uprMaska=0;
          uint32_t *editControl=NULL;
          int offset = i+beginAdr-BEGIN_ADR_BIT;
          uprFuncValidWrite000(0, offset, &uprMaska, &editControl);
          if(editControl==NULL) continue;
          uint32_t value = tempWriteArray[offsetTempWriteArray+i];

          //установка изменений
          (*editControl) &= ~(1<<uprMaska);
          (*editControl) |= (value<<uprMaska);

          //actControl
          if(value)//валидация на включение
                if(!uprFunc000(1, offset, &uprMaska, 1, &editControl)) return ERROR_VALID3;//ошибка валидации
          //ОСОБАЯ СБОРКА
          if((editControl == (uint32_t*)&edition_settings.control_extra_settings_1) ||
              (editControl == (uint32_t*)&edition_settings.configuration)
            )
            {
             if(!value)//валидация на отключение
                if(!uprFunc000(1, offset, &uprMaska, 0, &editControl)) return ERROR_VALID3;//ошибка валидации
              upravlSchematic = 1;//флаг Rang
            }//if
          //утверждение изменений
          flag=1;
        }//for
    }//if(beginAdr>=BEGIN_ADR_BIT)
  else
    {
      //работа с регистрами
      int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
      for(int i=0; i<countAdr; i++)
        {
          int offset = i+beginAdr-BEGIN_ADR_REGISTER;
          for(int bit=0; bit<16; bit++)
            {
              uint32_t uprMaska=0;
              uint32_t *editControl=NULL;
              uprFuncValidWrite000(0, offset*16+bit, &uprMaska, &editControl);
              if(editControl==NULL) continue;
              uint32_t value = tempWriteArray[offsetTempWriteArray+i];
              int temp = 0;
              if(value&(1<<bit)) temp = 1;

              //установка изменений
              (*editControl) &= ~(1<<uprMaska);
              (*editControl) |= (temp<<uprMaska);

              if(temp)//валидация на включение
                if(!uprFunc000(1, offset*16+bit, &uprMaska, 1, &editControl)) return ERROR_VALID3;//ошибка валидации
              //ОСОБАЯ СБОРКА
              if((editControl == (uint32_t*)&edition_settings.control_extra_settings_1) ||
                  (editControl == (uint32_t*)&edition_settings.configuration)
                )
                {
                 if(!temp)//валидация на отключение
                if(!uprFunc000(1, offset*16+bit, &uprMaska, 0, &editControl)) return ERROR_VALID3;//ошибка валидации
                  upravlSchematic = 1;//флаг Rang
                }//if
              //утверждение изменений
              flag=1;
            }//for
        }//for
    }//else
  if(flag) upravlSetting = 1;//флаг Setting

  return 0;
}//

int isValidCONFCondition(unsigned int confMaska)
{
  if(!(edition_settings.configuration&(1<<confMaska))) return 1;
  return 0;
}//isValidCONFCondition(unsigned int confControl, unsigned int confMaska, uint32_t uprMaska, int validData)
int isValidEXTRACondition(unsigned int extraMaska)
{
  if(edition_settings.control_extra_settings_1&(1<<extraMaska)) return 1;
  return 0;
}//isValidEXTRACondition(unsigned int extraControl, unsigned int extraMaska, uint32_t uprMaska, int validData)
int isValidMTZSELCondition(unsigned int extraMaska)
{
  if(edition_settings.control_mtz&(1<<extraMaska)) return 1;
  return 0;
}//isValidMTZSELCondition(unsigned int extraControl, unsigned int extraMaska, uint32_t uprMaska, int validData)

int privateUPRBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int privateUPRBigGetBit2(int adrBit)
{
  //проверить внешний периметр
  return controlPerimetr(adrBit, BEGIN_ADR_BIT, END_ADR_BIT);
}//privateGetReg2(int adrReg)

