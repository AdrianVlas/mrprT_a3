
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 256
//начальный bit в карте памяти
#define BEGIN_ADR_BIT 50000

//конечный регистр в карте памяти
#define END_ADR_REGISTER 302
//конечный bit в карте памяти
#define END_ADR_BIT 50743

int privateACMDSmallGetReg2(int adrReg);
int privateACMDSmallGetBit2(int adrBit);

int getACMDSmallModbusRegister(int);//получить содержимое регистра
int getACMDSmallModbusBit(int);//получить содержимое бита
int setACMDSmallModbusRegister(int, int);//записать регистр
int setACMDSmallModbusBit(int, int);//записать бит

void preACMDSmallReadAction(void);//action до чтения
void preACMDSmallWriteAction(void);//action до записи
int  postACMDSmallWriteAction(void);//action после записи

int  cmdFunc000(int inOffset, int *outMaska, int *dvMaska, int actControl);
void loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset);
unsigned int encoderValidN_BIGACMD(int offsetCMD, int *validCMD, int actControl);
unsigned int encoderValidN_SMALLACMD(int offsetCMD, int *validCMD);
int validBazaN_BIGACMD(unsigned short dataReg, int actControl);
int writeACMDSmallActualDataBit(int offset, int dataBit);
int passwordImunitetBitACMDSmallComponent(int adrReg);

int decoderN_BIGACMDArrayLoader(int idxBit);
int decoderN_SMALLACMDArrayLoader(int idxBit);

unsigned short decoderN_BIGACMDArray[N_BIG*32];//массив декодирования битов N_BIG
unsigned short decoderN_SMALLACMDArray[N_SMALL*32];//массив декодирования битов N_SMALL

#define CLRACT_CONTROL  0

COMPONENT_OBJ *acmdsmallcomponent;
int cmdFunc000(int inOffset, int *outMaska, int *dvMaska, int actControl)
{
  int isValid = 1;
  (*outMaska) = -1;
  switch(inOffset)//адр команд карты памяти modbus
  {
  case 0:
    (*outMaska) = RANG_1_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_1_GRUPA_USTAVOK;
    break;
  case 1:
    (*outMaska) = RANG_2_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_2_GRUPA_USTAVOK;
    break;
  case 2:
    (*outMaska) = RANG_3_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_3_GRUPA_USTAVOK;
    break;
  case 3:
    (*outMaska) = RANG_4_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_4_GRUPA_USTAVOK;
    break;

//  int count_bit = 3;
#define MTZ_CONFIGURATION_BEGIN 16
  case MTZ_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_MTZ1;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ1;
    break;
  case 17:
    (*outMaska) = RANG_MTZ1;
//        (*dvMaska) =
    break;
  case 18:
    (*outMaska) = RANG_PO_MTZ1;
//        (*dvMaska) =
    break;
  case 19:
    (*outMaska) = RANG_PO_MTZPN1;
//        (*dvMaska) =
    break;
  case 20:
    (*outMaska) = RANG_PO_MTZN1_VPERED;
//        (*dvMaska) =
    break;
  case 21:
    (*outMaska) = RANG_PO_MTZN1_NAZAD;
//        (*dvMaska) =
    break;
  case 22:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN1;
//        (*dvMaska) =
    break;
  case 23:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN1;
//        (*dvMaska) =
    break;
  case 24:
    (*outMaska) = RANG_PO_U_MTZPN1;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 32:
    (*outMaska) = RANG_BLOCK_MTZ2;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ2;
    break;
  case 33:
    (*outMaska) = RANG_MTZ2;
//        (*dvMaska) =
    break;
  case 34:
    (*outMaska) = RANG_PO_MTZ2;
//        (*dvMaska) =
    break;
  case 35:
    (*outMaska) = RANG_PO_MTZPN2;
//        (*dvMaska) =
    break;
  case 36:
    (*outMaska) = RANG_PO_MTZN2_VPERED;
//        (*dvMaska) =
    break;
  case 37:
    (*outMaska) = RANG_PO_MTZN2_NAZAD;
//        (*dvMaska) =
    break;
  case 38:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN2;
//        (*dvMaska) =
    break;
  case 39:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN2;
//        (*dvMaska) =
    break;
  case 40:
    (*outMaska) = RANG_PO_U_MTZPN2;
//        (*dvMaska) =
    break;
  case 41:
    (*outMaska) = RANG_BLOCK_USK_MTZ2;
    (*dvMaska) = RANG_SMALL_BLOCK_USK_MTZ2;
    break;

//  count_bit = 3;
  case 48:
    (*outMaska) = RANG_BLOCK_MTZ3;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ3;
    break;
  case 49:
    (*outMaska) = RANG_MTZ3;
//        (*dvMaska) =
    break;
  case 50:
    (*outMaska) = RANG_PO_MTZ3;
//        (*dvMaska) =
    break;
  case 51:
    (*outMaska) = RANG_PO_MTZPN3;
//        (*dvMaska) =
    break;
  case 52:
    (*outMaska) = RANG_PO_MTZN3_VPERED;
//        (*dvMaska) =
    break;
  case 53:
    (*outMaska) = RANG_PO_MTZN3_NAZAD;
//        (*dvMaska) =
    break;
  case 54:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN3;
//        (*dvMaska) =
    break;
  case 55:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN3;
//        (*dvMaska) =
    break;
  case 56:
    (*outMaska) = RANG_PO_U_MTZPN3;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 64:
    (*outMaska) = RANG_BLOCK_MTZ4;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ4;
    break;
  case 65:
    (*outMaska) = RANG_MTZ4;
//        (*dvMaska) =
    break;
  case 66:
    (*outMaska) = RANG_PO_MTZ4;
//        (*dvMaska) =
    break;
  case 67:
    (*outMaska) = RANG_PO_MTZPN4;
//        (*dvMaska) =
    break;
  case 68:
    (*outMaska) = RANG_PO_MTZN4_VPERED;
//        (*dvMaska) =
    break;
  case 69:
    (*outMaska) = RANG_PO_MTZN4_NAZAD;
//        (*dvMaska) =
    break;
  case 70:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN4;
//        (*dvMaska) =
    break;
  case 71:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN4;
//        (*dvMaska) =
    break;
#define MTZ_CONFIGURATION_END 72
  case MTZ_CONFIGURATION_END:
    (*outMaska) = RANG_PO_U_MTZPN4;
//        (*dvMaska) =
    break;


  case 88:
    (*outMaska) = RANG_NCN_MTZ;
//        (*dvMaska) =
    if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) isValid = 0;
    break;
  case 89:
    (*outMaska) = RANG_PO_BLOCK_U_MTZN;
//        (*dvMaska) =
    if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) isValid = 0;
    break;

//  count_bit = 3;
#define P_3U0_BIT_CONFIGURATION_BEGIN 144
  case P_3U0_BIT_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_P_3U0;
    (*dvMaska) = RANG_SMALL_BLOCK_P_3U0;
    break;
  case 145:
    (*outMaska) = RANG_PO_P_3U0;
//        (*dvMaska) =
    break;
#define P_3U0_BIT_CONFIGURATION_END 146
  case P_3U0_BIT_CONFIGURATION_END:
    (*outMaska) = RANG_P_3U0;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define TZNP_CONFIGURATION_BEGIN 160
  case TZNP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_TZNP1;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP1;
    break;
  case 161:
    (*outMaska) = RANG_PO_3I0_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 162:
    (*outMaska) = RANG_PO_3I0_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 163:
    (*outMaska) = RANG_PO_3U0_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 164:
    (*outMaska) = RANG_PO_3U0_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 165:
    (*outMaska) = RANG_PO_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 166:
    (*outMaska) = RANG_PO_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 167:
    (*outMaska) = RANG_SECTOR_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 168:
    (*outMaska) = RANG_SECTOR_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 169:
    (*outMaska) = RANG_TZNP1;
//        (*dvMaska) =
    break;
  case 170:
    (*outMaska) = RANG_BLOCK_TZNP2;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP2;
    break;
  case 171:
    (*outMaska) = RANG_PO_3I0_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 172:
    (*outMaska) = RANG_PO_3I0_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 173:
    (*outMaska) = RANG_PO_3U0_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 174:
    (*outMaska) = RANG_PO_3U0_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 175:
    (*outMaska) = RANG_PO_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 176:
    (*outMaska) = RANG_PO_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 177:
    (*outMaska) = RANG_SECTOR_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 178:
    (*outMaska) = RANG_SECTOR_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 179:
    (*outMaska) = RANG_TZNP2;
//        (*dvMaska) =
    break;
  case 180:
    (*outMaska) = RANG_BLOCK_TZNP3;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP3;
    break;
  case 181:
    (*outMaska) = RANG_PO_3I0_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 182:
    (*outMaska) = RANG_PO_3I0_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 183:
    (*outMaska) = RANG_PO_3U0_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 184:
    (*outMaska) = RANG_PO_3U0_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 185:
    (*outMaska) = RANG_PO_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 186:
    (*outMaska) = RANG_PO_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 187:
    (*outMaska) = RANG_SECTOR_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 188:
    (*outMaska) = RANG_SECTOR_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 189:
    (*outMaska) = RANG_TZNP3;
//        (*dvMaska) =
    break;
  case 190:
    (*outMaska) = RANG_BLOCK_TZNP4;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP4;
    break;
  case 191:
    (*outMaska) = RANG_PO_3I0_TZNP4_VPERED;
//        (*dvMaska) =
    break;
  case 192:
    (*outMaska) = RANG_PO_3I0_TZNP4_NAZAD;
//        (*dvMaska) =
    break;
  case 193:
    (*outMaska) = RANG_PO_3U0_TZNP4_VPERED;
//        (*dvMaska) =
    break;
  case 194:
    (*outMaska) = RANG_PO_3U0_TZNP4_NAZAD;
//        (*dvMaska) =
    break;
  case 195:
    (*outMaska) = RANG_PO_TZNP4_VPERED;
//        (*dvMaska) =
    break;
  case 196:
    (*outMaska) = RANG_PO_TZNP4_NAZAD;
//        (*dvMaska) =
    break;
  case 197:
    (*outMaska) = RANG_SECTOR_TZNP4_VPERED;
//        (*dvMaska) =
    break;
  case 198:
    (*outMaska) = RANG_SECTOR_TZNP4_NAZAD;
//        (*dvMaska) =
    break;
#define TZNP_CONFIGURATION_END 199
  case TZNP_CONFIGURATION_END:
    (*outMaska) = RANG_TZNP4;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define ZOP_CONFIGURATION_BEGIN 208
  case ZOP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_ZOP1;
    (*dvMaska) = RANG_SMALL_BLOCK_ZOP1;
    break;
  case 209:
    (*outMaska) = RANG_ZOP1;
//        (*dvMaska) =
    break;
  case 210:
    (*outMaska) = RANG_PO_ZOP1;
//        (*dvMaska) =
    break;
  case 211:
    (*outMaska) = RANG_BLOCK_ZOP2;
    (*dvMaska) = RANG_SMALL_BLOCK_ZOP2;
    break;
  case 212:
    (*outMaska) = RANG_ZOP2;
//        (*dvMaska) =
    break;
#define ZOP_CONFIGURATION_END 213
  case ZOP_CONFIGURATION_END:
    (*outMaska) = RANG_PO_ZOP2;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define UMIN_CONFIGURATION_BEGIN 224
  case UMIN_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_UMIN1;
    (*dvMaska) = RANG_SMALL_BLOCK_UMIN1;
    break;
  case 225:
    (*outMaska) = RANG_PO_UBLK_UMIN1;
//        (*dvMaska) =
    break;
  case 226:
    (*outMaska) = RANG_PO_IBLK_UMIN1;
//        (*dvMaska) =
    break;
  case 227:
    (*outMaska) = RANG_UMIN1;
//        (*dvMaska) =
    break;
  case 228:
    (*outMaska) = RANG_PO_UMIN1;
//        (*dvMaska) =
    break;
  case 229:
    (*outMaska) = RANG_BLOCK_UMIN2;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMIN2;
    break;
  case 230:
    (*outMaska) = RANG_PO_UBLK_UMIN2;
//        (*dvMaska) =
    break;
  case 231:
    (*outMaska) = RANG_PO_IBLK_UMIN2;
//        (*dvMaska) =
    break;
  case 232:
    (*outMaska) = RANG_UMIN2;
//        (*dvMaska) =
    break;
  case 233:
    (*outMaska) = RANG_PO_UMIN2;
//        (*dvMaska) =
    break;
  case 234:
    (*outMaska) = RANG_START_UMIN1;
    (*dvMaska)  = RANG_SMALL_START_UMIN1;
    break;
#define UMIN_CONFIGURATION_END 235
  case UMIN_CONFIGURATION_END:
    (*outMaska) = RANG_START_UMIN2;
    (*dvMaska) = RANG_SMALL_START_UMIN2;
    break;

//  count_bit = 3;
#define UMAX_CONFIGURATION_BEGIN 240
  case UMAX_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_UMAX1;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMAX1;
    break;
  case 241:
    (*outMaska) = RANG_UMAX1;
//        (*dvMaska) =
    break;
  case 242:
    (*outMaska) = RANG_PO_UMAX1;
//        (*dvMaska) =
    break;
  case 243:
    (*outMaska) = RANG_BLOCK_UMAX2;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMAX2;
    break;
  case 244:
    (*outMaska) = RANG_UMAX2;
//        (*dvMaska) =
    break;
#define UMAX_CONFIGURATION_END 245
  case UMAX_CONFIGURATION_END:
    (*outMaska) = RANG_PO_UMAX2;
//        (*dvMaska) =
    break;

//  count_bit = 5;
#define UROV_CONFIGURATION_BEGIN 336
    case UROV_CONFIGURATION_BEGIN:
      (*outMaska) = RANG_PUSK_UROV1_VID_DV;
      (*dvMaska) = RANG_SMALL_PUSK_UROV1_VID_DV;
      break;
    case 337:
      (*outMaska) = RANG_UROV1_1;
//        (*dvMaska) =
      break;
    case 338:
      (*outMaska) = RANG_UROV1_2;
//        (*dvMaska) =
      break;
    case 339:
      (*outMaska) = RANG_PO_UROV1;
//        (*dvMaska) =
      break;

//  count_bit = 5;
    case 352:
      (*outMaska) = RANG_PUSK_UROV2_VID_DV;
      (*dvMaska) = RANG_SMALL_PUSK_UROV2_VID_DV;
      break;
    case 353:
      (*outMaska) = RANG_UROV2_1;
//        (*dvMaska) =
      break;
    case 354:
      (*outMaska) = RANG_UROV2_2;
//        (*dvMaska) =
      break;
#define UROV_CONFIGURATION_END 355
    case UROV_CONFIGURATION_END:
      (*outMaska) = RANG_PO_UROV2;
//        (*dvMaska) =
      break;

//IF ВСТАВКА 432-455

//  count_bit = 3;
#define OZT_CONFIGURATION_BEGIN 464
  case OZT_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_OZT1;
    (*dvMaska)  = RANG_SMALL_BLOCK_OZT1;
    break;
  case 465:
    (*outMaska) = RANG_PO_OZT1;
//        (*dvMaska) =
    break;
  case 466:
    (*outMaska) = RANG_OZT1;
//        (*dvMaska) =
    break;
  case 467:
    (*outMaska) = RANG_BLOCK_OZT2;
    (*dvMaska)  = RANG_SMALL_BLOCK_OZT2;
    break;
  case 468:
    (*outMaska) = RANG_BLOCK_A_OZT2;
    (*dvMaska)  = RANG_SMALL_BLOCK_A_OZT2;
    break;
  case 469:
    (*outMaska) = RANG_PO_BLOCK_A_OZT2;
//        (*dvMaska) =
    break;
  case 470:
    (*outMaska) = RANG_BLOCK_2G_OZT2;
    (*dvMaska)  = RANG_SMALL_BLOCK_2G_OZT2;
    break;
  case 471:
    (*outMaska) = RANG_PO_BLOCK_2G_OZT2;
//        (*dvMaska) =
    break;
  case 472:
    (*outMaska) = RANG_BLOCK_5G_OZT2;
    (*dvMaska)  = RANG_SMALL_BLOCK_5G_OZT2;
    break;
  case 473:
    (*outMaska) = RANG_PO_BLOCK_5G_OZT2;
//        (*dvMaska) =
    break;
  case 474:
    (*outMaska) = RANG_PO_OZT2;
//        (*dvMaska) =
    break;
#define OZT_CONFIGURATION_END 475
  case OZT_CONFIGURATION_END:
    (*outMaska) = RANG_OZT2;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define GP_CONFIGURATION_BEGIN 480
  case GP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_GP;
    (*dvMaska)  = RANG_SMALL_BLOCK_GP;
    break;
  case 481:
    (*outMaska) = RANG_IN_GP1;
    (*dvMaska)  = RANG_SMALL_IN_GP1;
    break;
  case 482:
    (*outMaska) = RANG_PO_GP1;
//        (*dvMaska) =
    break;
  case 483:
    (*outMaska) = RANG_GP1;
//        (*dvMaska) =
    break;
  case 484:
    (*outMaska) = RANG_IN_GP2;
    (*dvMaska)  = RANG_SMALL_IN_GP2;
    break;
  case 485:
    (*outMaska) = RANG_PO_GP2;
//        (*dvMaska) =
    break;
  case 486:
    (*outMaska) = RANG_GP2;
//        (*dvMaska) =
    break;
  case 487:
    (*outMaska) = RANG_IN_GP_RPN;
    (*dvMaska)  = RANG_SMALL_IN_GP_RPN;
    break;
  case 488:
    (*outMaska) = RANG_PO_GP_RPN;
//        (*dvMaska) =
    break;
#define GP_CONFIGURATION_END 489
  case GP_CONFIGURATION_END:
    (*outMaska) = RANG_GP_RPN;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define TP_CONFIGURATION_BEGIN 496
  case TP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_TP;
    (*dvMaska)  = RANG_SMALL_BLOCK_TP;
    break;
  case 497:
    (*outMaska) = RANG_IN_TP;
    (*dvMaska)  = RANG_SMALL_IN_TP;
    break;
  case 498:
    (*outMaska) = RANG_PO_TP;
//        (*dvMaska) =
    break;
#define TP_CONFIGURATION_END 499
  case TP_CONFIGURATION_END:
    (*outMaska) = RANG_TP;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define KZZV_CONFIGURATION_BEGIN 528
  case KZZV_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_KZ_ZV;
    (*dvMaska)  = RANG_SMALL_BLOCK_KZ_ZV;
    break;
  case 529:
    (*outMaska) = RANG_KZ_V;
//        (*dvMaska) =
    break;
  case 530:
    (*outMaska) = RANG_KZ_Z;
//        (*dvMaska) =
    break;
  case 531:
    (*outMaska) = RANG_SECTOR_KZ_V;
//        (*dvMaska) =
    break;
#define KZZV_CONFIGURATION_END 532
  case KZZV_CONFIGURATION_END:
    (*outMaska) = RANG_SECTOR_KZ_Z;
//        (*dvMaska) =
    break;

//  count_bit = 8;
#define EL_CONFIGURATION_BEGIN 544
  case EL_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_DF1_IN;
    (*dvMaska) = RANG_SMALL_DF1_IN;
    if(actControl==1) isValid = 0;
    break;
  case 545:
    (*outMaska) = RANG_DF2_IN;
    (*dvMaska) = RANG_SMALL_DF2_IN;
    if(actControl==2) isValid = 0;
    break;
  case 546:
    (*outMaska) = RANG_DF3_IN;
    (*dvMaska) = RANG_SMALL_DF3_IN;
    if(actControl==3) isValid = 0;
    break;
  case 547:
    (*outMaska) = RANG_DF4_IN;
    (*dvMaska) = RANG_SMALL_DF4_IN;
    if(actControl==4) isValid = 0;
    break;
  case 548:
    (*outMaska) = RANG_DF5_IN;
    (*dvMaska) = RANG_SMALL_DF5_IN;
    if(actControl==5) isValid = 0;
    break;
  case 549:
    (*outMaska) = RANG_DF6_IN;
    (*dvMaska) = RANG_SMALL_DF6_IN;
    if(actControl==6) isValid = 0;
    break;
  case 550:
    (*outMaska) = RANG_DF7_IN;
    (*dvMaska) = RANG_SMALL_DF7_IN;
    if(actControl==7) isValid = 0;
    break;
  case 551:
    (*outMaska) = RANG_DF8_IN;
    (*dvMaska) = RANG_SMALL_DF8_IN;
    if(actControl==8) isValid = 0;
    break;

//  count_bit = 8;
  case 560:
    (*outMaska) = RANG_DF1_OUT;
//        (*dvMaska) =
    if(actControl==1) isValid = 0;
    break;
  case 561:
    (*outMaska) = RANG_DF2_OUT;
//        (*dvMaska) =
    if(actControl==2) isValid = 0;
    break;
  case 562:
    (*outMaska) = RANG_DF3_OUT;
//        (*dvMaska) =
    if(actControl==3) isValid = 0;
    break;
  case 563:
    (*outMaska) = RANG_DF4_OUT;
//        (*dvMaska) =
    if(actControl==4) isValid = 0;
    break;
  case 564:
    (*outMaska) = RANG_DF5_OUT;
//        (*dvMaska) =
    if(actControl==5) isValid = 0;
    break;
  case 565:
    (*outMaska) = RANG_DF6_OUT;
//        (*dvMaska) =
    if(actControl==6) isValid = 0;
    break;
  case 566:
    (*outMaska) = RANG_DF7_OUT;
//        (*dvMaska) =
    if(actControl==7) isValid = 0;
    break;
  case 567:
    (*outMaska) = RANG_DF8_OUT;
//        (*dvMaska) =
    if(actControl==8) isValid = 0;
    break;

//  count_bit = 12;
  case 576:
    (*outMaska) = RANG_DT1_SET;
    (*dvMaska) = RANG_SMALL_DT1_SET;
    if(actControl==1) isValid = 0;
    break;
  case 577:
    (*outMaska) = RANG_DT1_RESET;
    (*dvMaska) = RANG_SMALL_DT1_RESET;
    if(actControl==1) isValid = 0;
    break;
  case 578:
    (*outMaska) = RANG_DT2_SET;
    (*dvMaska) = RANG_SMALL_DT2_SET;
    if(actControl==2) isValid = 0;
    break;
  case 579:
    (*outMaska) = RANG_DT2_RESET;
    (*dvMaska) = RANG_SMALL_DT2_RESET;
    if(actControl==2) isValid = 0;
    break;
  case 580:
    (*outMaska) = RANG_DT3_SET;
    (*dvMaska) = RANG_SMALL_DT3_SET;
    if(actControl==3) isValid = 0;
    break;
  case 581:
    (*outMaska) = RANG_DT3_RESET;
    (*dvMaska) = RANG_SMALL_DT3_RESET;
    if(actControl==3) isValid = 0;
    break;
  case 582:
    (*outMaska) = RANG_DT4_SET;
    (*dvMaska) = RANG_SMALL_DT4_SET;
    if(actControl==4) isValid = 0;
    break;
  case 583:
    (*outMaska) = RANG_DT4_RESET;
    (*dvMaska) = RANG_SMALL_DT4_RESET;
    if(actControl==4) isValid = 0;
    break;
  case 584:
    (*outMaska) = RANG_DT1_OUT;
//        (*dvMaska) =
    if(actControl==1) isValid = 0;
    break;
  case 585:
    (*outMaska) = RANG_DT2_OUT;
//        (*dvMaska) =
    if(actControl==2) isValid = 0;
    break;
  case 586:
    (*outMaska) = RANG_DT3_OUT;
//        (*dvMaska) =
    if(actControl==3) isValid = 0;
    break;
  case 587:
    (*outMaska) = RANG_DT4_OUT;
//        (*dvMaska) =
    if(actControl==4) isValid = 0;
    break;

//  count_bit = 40;
  case 592:
    (*outMaska) = RANG_D_AND1;
//        (*dvMaska) =
    break;
  case 593:
    (*outMaska) = RANG_D_AND2;
//        (*dvMaska) =
    break;
  case 594:
    (*outMaska) = RANG_D_AND3;
//        (*dvMaska) =
    break;
  case 595:
    (*outMaska) = RANG_D_AND4;
//        (*dvMaska) =
    break;
  case 596:
    (*outMaska) = RANG_D_AND5;
//        (*dvMaska) =
    break;
  case 597:
    (*outMaska) = RANG_D_AND6;
//        (*dvMaska) =
    break;
  case 598:
    (*outMaska) = RANG_D_AND7;
//        (*dvMaska) =
    break;
  case 599:
    (*outMaska) = RANG_D_AND8;
//        (*dvMaska) =
    break;
  case 600:
    (*outMaska) = RANG_D_OR1;
//        (*dvMaska) =
    break;
  case 601:
    (*outMaska) = RANG_D_OR2;
//        (*dvMaska) =
    break;
  case 602:
    (*outMaska) = RANG_D_OR3;
//        (*dvMaska) =
    break;
  case 603:
    (*outMaska) = RANG_D_OR4;
//        (*dvMaska) =
    break;
  case 604:
    (*outMaska) = RANG_D_OR5;
//        (*dvMaska) =
    break;
  case 605:
    (*outMaska) = RANG_D_OR6;
//        (*dvMaska) =
    break;
  case 606:
    (*outMaska) = RANG_D_OR7;
//        (*dvMaska) =
    break;
  case 607:
    (*outMaska) = RANG_D_OR8;
//        (*dvMaska) =
    break;
  case 608:
    (*outMaska) = RANG_D_NOT1;
//        (*dvMaska) =
    break;
  case 609:
    (*outMaska) = RANG_D_NOT2;
//        (*dvMaska) =
    break;
  case 610:
    (*outMaska) = RANG_D_NOT3;
//        (*dvMaska) =
    break;
  case 611:
    (*outMaska) = RANG_D_NOT4;
//        (*dvMaska) =
    break;
  case 612:
    (*outMaska) = RANG_D_NOT5;
//        (*dvMaska) =
    break;
  case 613:
    (*outMaska) = RANG_D_NOT6;
//        (*dvMaska) =
    break;
  case 614:
    (*outMaska) = RANG_D_NOT7;
//        (*dvMaska) =
    break;
  case 615:
    (*outMaska) = RANG_D_NOT8;
//        (*dvMaska) =
    break;
  case 616:
    (*outMaska) = RANG_D_NOT9;
//        (*dvMaska) =
    break;
  case 617:
    (*outMaska) = RANG_D_NOT10;
//        (*dvMaska) =
    break;
  case 618:
    (*outMaska) = RANG_D_NOT11;
//        (*dvMaska) =
    break;
  case 619:
    (*outMaska) = RANG_D_NOT12;
//        (*dvMaska) =
    break;
  case 620:
    (*outMaska) = RANG_D_NOT13;
//        (*dvMaska) =
    break;
  case 621:
    (*outMaska) = RANG_D_NOT14;
//        (*dvMaska) =
    break;
  case 622:
    (*outMaska) = RANG_D_NOT15;
//        (*dvMaska) =
    break;
  case 623:
    (*outMaska) = RANG_D_NOT16;
//        (*dvMaska) =
    break;
  case 624:
    (*outMaska) = RANG_D_XOR1;
//        (*dvMaska) =
    break;
  case 625:
    (*outMaska) = RANG_D_XOR2;
//        (*dvMaska) =
    break;
  case 626:
    (*outMaska) = RANG_D_XOR3;
//        (*dvMaska) =
    break;
  case 627:
    (*outMaska) = RANG_D_XOR4;
//        (*dvMaska) =
    break;
  case 628:
    (*outMaska) = RANG_D_XOR5;
//        (*dvMaska) =
    break;
  case 629:
    (*outMaska) = RANG_D_XOR6;
//        (*dvMaska) =
    break;
  case 630:
    (*outMaska) = RANG_D_XOR7;
//        (*dvMaska) =
    break;
#define EL_CONFIGURATION_END 631
  case EL_CONFIGURATION_END:
    (*outMaska) = RANG_D_XOR8;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define  IMUNITET_BITACMD640 640
  case IMUNITET_BITACMD640:
    (*outMaska) = RANG_VKL_VV_H;
    (*dvMaska) = RANG_SMALL_VKL_VV_H;
    break;
#define  IMUNITET_BITACMD641 641
  case IMUNITET_BITACMD641:
    (*outMaska) = RANG_OTKL_VV_H;
    (*dvMaska) = RANG_SMALL_OTKL_VV_H;
    break;
  case 642:
    (*outMaska) = RANG_BLOCK_VKL_VV_H;
    (*dvMaska) = RANG_SMALL_BLOCK_VKL_VV_H;
    break;

//  count_bit = 15;
  case 644:
    (*outMaska) = RANG_WORK_BO_H;
//        (*dvMaska) =
    break;
  case 645:
    (*outMaska) = RANG_WORK_BV_H;
//        (*dvMaska) =
    break;
  case 646:
    (*outMaska) = RANG_STATE_VV_H;
    (*dvMaska) = RANG_SMALL_STATE_VV_H;
    break;
  case 647:
    (*outMaska) = RANG_PRYVID_VV_H;
//        (*dvMaska) =
    break;
  case 648:
    (*outMaska) = RANG_CTRL_VKL_H;
    (*dvMaska) = RANG_SMALL_CTRL_VKL_H;
    break;
  case 649:
    (*outMaska) = RANG_CTRL_OTKL_H;
    (*dvMaska) = RANG_SMALL_CTRL_OTKL_H;
    break;

//  count_bit = 3;
#define  IMUNITET_BITACMD672 672
  case IMUNITET_BITACMD672:
    (*outMaska) = RANG_VKL_VV_L;
    (*dvMaska) = RANG_SMALL_VKL_VV_L;
    break;
#define  IMUNITET_BITACMD673 673
  case IMUNITET_BITACMD673:
    (*outMaska) = RANG_OTKL_VV_L;
    (*dvMaska) = RANG_SMALL_OTKL_VV_L;
    break;
  case 674:
    (*outMaska) = RANG_BLOCK_VKL_VV_L;
    (*dvMaska) = RANG_SMALL_BLOCK_VKL_VV_L;
    break;

//  count_bit = 15;
  case 676:
    (*outMaska) = RANG_WORK_BO_L;
//        (*dvMaska) =
    break;
  case 677:
    (*outMaska) = RANG_WORK_BV_L;
//        (*dvMaska) =
    break;
  case 678:
    (*outMaska) = RANG_STATE_VV_L;
    (*dvMaska) = RANG_SMALL_STATE_VV_L;
    break;
  case 679:
    (*outMaska) = RANG_PRYVID_VV_L;
//        (*dvMaska) =
    break;
  case 680:
    (*outMaska) = RANG_CTRL_VKL_L;
    (*dvMaska) = RANG_SMALL_CTRL_VKL_L;
    break;
  case 681:
    (*outMaska) = RANG_CTRL_OTKL_L;
    (*dvMaska) = RANG_SMALL_CTRL_OTKL_L;
    break;

//  count_bit = 12;
  case 704:
    (*outMaska) = RANG_DEFECT;
//        (*dvMaska) =
    break;
  case 705:
    (*outMaska) = RANG_AVAR_DEFECT;
//        (*dvMaska) =
    break;
#define  IMUNITET_BITACMD706 706
  case IMUNITET_BITACMD706:
    (*outMaska) = RANG_RESET_LEDS;
    (*dvMaska) = RANG_SMALL_RESET_LEDS;
    break;
#define  IMUNITET_BITACMD707 707
  case IMUNITET_BITACMD707:
    (*outMaska) = RANG_RESET_RELES;
    (*dvMaska) = RANG_SMALL_RESET_RELES;
    break;

#define  IMUNITET_BITACMD708 708

  case 710:
    (*outMaska) = RANG_SETTINGS_CHANGED;
//        (*dvMaska) =
    break;

#define  BITACMD711 711

#define PASSWORD_SETCMD 712

  case 713:
    (*outMaska) = RANG_MISCEVE_DYSTANCIJNE;
    (*dvMaska) = RANG_SMALL_MISCEVE_DYSTANCIJNE;
    break;
  case 714:
    (*outMaska) = RANG_WORK_A_REJESTRATOR;
//        (*dvMaska) =
    break;
  case 715:
    (*outMaska) = RANG_WORK_D_REJESTRATOR;
//        (*dvMaska) =
    break;

//  count_bit = 1;
  case 721:
    (*outMaska) = RANG_ERROR_CONF_EL;
//        (*dvMaska) =
    break;

//  count_bit = 5;
  case 739:
    (*outMaska) = RANG_VIDKL_VID_ZAKHYSTIV;
//        (*dvMaska) =
    break;
  case 740:
    (*outMaska) = RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV;
//        (*dvMaska) =
    break;

  case 741:
    (*outMaska) = RANG_INVERS_DV_GRUPA_USTAVOK;
//        (*dvMaska) =
    break;
  case 742:
    (*outMaska) = RANG_READY_TU;
//        (*dvMaska) =
    break;
#define  IMUNITET_BITACMD743 743
  case IMUNITET_BITACMD743:
    (*outMaska) = RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
    (*dvMaska) = RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
    break;
  }//switch
  if((*outMaska)!=-1)
  {
    if(inOffset>=MTZ_CONFIGURATION_BEGIN && inOffset<=MTZ_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=P_3U0_BIT_CONFIGURATION_BEGIN && inOffset<=P_3U0_BIT_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<P_3U0_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=GP_CONFIGURATION_BEGIN && inOffset<=GP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<GP_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=TP_CONFIGURATION_BEGIN && inOffset<=TP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<TP_BIT_CONFIGURATION))) isValid = 0;
 
    if(inOffset>=KZZV_CONFIGURATION_BEGIN && inOffset<=KZZV_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<KZ_ZV_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=TZNP_CONFIGURATION_BEGIN && inOffset<=TZNP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<TZNP_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=ZOP_CONFIGURATION_BEGIN && inOffset<=ZOP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<ZOP_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UMIN_CONFIGURATION_BEGIN && inOffset<=UMIN_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UMIN_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UMAX_CONFIGURATION_BEGIN && inOffset<=UMAX_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UMAX_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UROV_CONFIGURATION_BEGIN && inOffset<=UROV_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UROV_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=OZT_CONFIGURATION_BEGIN && inOffset<=OZT_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<OZT_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=EL_CONFIGURATION_BEGIN && inOffset<=EL_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) isValid = 0;

  }//if((*outMaska)!=-1)

  if(inOffset>=432 && inOffset<456)
  {
    if(!(edition_settings.configuration&(1<<UP_BIT_CONFIGURATION))) isValid = 0;
    int inupOffset = inOffset-432;
    int subObj = inupOffset/3;
    int offsetObj = inupOffset%3;
    
    switch(offsetObj)
    {
    case 0:
      (*outMaska) = RANG_BLOCK_UP1 + 3*subObj;
      (*dvMaska)  = RANG_SMALL_BLOCK_UP1 + 1*subObj;
      break;
    case 1:
      (*outMaska) = RANG_PO_UP1 + 3*subObj;
//        (*dvMaska) =
      break;
    case 2:
      (*outMaska) = RANG_UP1 + 3*subObj;
//        (*dvMaska) =
      break;
    }//switch
  }//if

  return isValid;
}//cmdFunc000(int inOffset, int *outMaska, int *dvMaska)

int getACMDSmallBeginAdr(void)
{
  return BEGIN_ADR_BIT;
}//getACMDSmallBeginAdr(void)
/**************************************/
//компонент Текущие активные и сработавшие функции
/**************************************/
void constructorACMDSmallComponent(COMPONENT_OBJ *acmdcomp)
{
  acmdsmallcomponent = acmdcomp;

  acmdsmallcomponent->getModbusRegister = getACMDSmallModbusRegister;//получить содержимое регистра
  acmdsmallcomponent->getModbusBit      = getACMDSmallModbusBit;//получить содержимое бита
  acmdsmallcomponent->setModbusRegister = setACMDSmallModbusRegister;// регистра
  acmdsmallcomponent->setModbusBit      = setACMDSmallModbusBit;// бита

  acmdsmallcomponent->preReadAction   = preACMDSmallReadAction;//action до чтения
  acmdsmallcomponent->preWriteAction  = preACMDSmallWriteAction;//action до записи
  acmdsmallcomponent->postWriteAction = postACMDSmallWriteAction;//action после записи

  acmdsmallcomponent->isActiveActualData = 0;

  for(int i=0; i<N_BIG*32; i++)   decoderN_BIGACMDArray[i] = (unsigned short)decoderN_BIGACMDArrayLoader(i);//декодировщик индекса бита в адрес modbus  для реле
  for(int i=0; i<N_SMALL*32; i++) decoderN_SMALLACMDArray[i] = (unsigned short)decoderN_SMALLACMDArrayLoader(i);//декодировщик индекса бита в адрес modbus  для DV
}//constructorDOUTSmallComponent(COMPONENT_OBJ *doutcomp)

void loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset)
{
  //ActualData
  for(int ii=0; ii<(1+(END_ADR_BIT-BEGIN_ADR_BIT+1)/16); ii++) tempReadArray[ii] = 0;
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int value =0;
    int tsdata = 0;
    if(item>=beginOffset && item<endOffset)
    {
     switch(item)
     {
      case PASSWORD_SETCMD://Пароль установлен
      {
      if(pointInterface==USB_RECUEST)//метка интерфейса 0-USB 1-RS485
            value = password_set_USB;//Пароль установлен
      else  value = password_set_RS485;//Пароль установлен
      goto m1;
      }//if
     }//switch
      value = encoderN_BIGACMD(item);//кодировщик адреса modbus в индекс бита для реле
      if(value==-1) value=0;
      else {
        //читать значение команд
        if(cmdSwitch==0) {
          //ACMD
          value = active_functions[value/32] & (1<<(value%32));
        }//if(cmdSwitch==0)
        if(cmdSwitch==1) {
          //GCMD
          if(pointInterface==USB_RECUEST)//метка интерфейса 0-USB 1-RS485
          {
             value = trigger_functions_USB[value/32] & (1<<(value%32));
          }//if
          else
          {
             value = trigger_functions_RS485[value/32] & (1<<(value%32));
          }//else
        }//if(cmdSwitch==0)
      }
    }//if(item>=beginOffset && item<endOffset)
m1:
    if(value) tsdata=1;
    tempReadArray[item/16] |= tsdata<<(item%16);
  }//for(int item=0; item<568; item++)
}//loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset)

int validN_BIGACMD(unsigned short dataReg)
{
  return validBazaN_BIGACMD(dataReg, CLRACT_CONTROL);
}//validN_BIGACMD(unsigned short dataReg)
int validBazaN_BIGACMD(unsigned short dataReg, int actControl)
{
//расширенная проверка адреса команды for rele
  if(dataReg!=0)
  {
    int validCMD=0;
    if(((int)encoderValidN_BIGACMD(dataReg-getACMDSmallBeginAdr(), &validCMD, actControl))<0) return MARKER_ERRORPERIMETR; //кодировщик адреса modbus в индекс бита для реле
    if(!validCMD) return MARKER_ERRORPERIMETR; //не прошла валидация
  }//if(dataReg!=0)

  return 0;
}//validBazaN_BIGACMD(unsigned short dataReg, int actControl)
int validN_SMALLACMD(unsigned short dataReg)
{
//расширенная проверка адреса команды for dv
  if(dataReg!=0)
  {
    int validCMD=0;
    if(((int)encoderValidN_SMALLACMD(dataReg-getACMDSmallBeginAdr(), &validCMD))<0) return MARKER_ERRORPERIMETR; //кодировщик адреса modbus в индекс бита для реле
    if(!validCMD) return MARKER_ERRORPERIMETR; //не прошла валидация
  }//if(dataReg!=0)

  return 0;
}//validN_SMALLACMD(int dataReg)
unsigned int encoderN_BIGACMD(int offsetCMD)
{
  int validCMD=0;
  return encoderValidN_BIGACMD(offsetCMD, &validCMD, CLRACT_CONTROL);
}//encoderN_BIGACMD(int adrCMD)
unsigned int encoderValidN_BIGACMD(int offsetCMD, int *validCMD, int actControl)
{
//кодировщик адреса modbus в индекс бита для реле
  int outMaska=-1;
  int dvMaska=-1;
  (*validCMD) = cmdFunc000(offsetCMD, &outMaska, &dvMaska, actControl);
  return outMaska;
}//encoderValidN_BIGACMD(int offsetCMD, int *validCMD)
unsigned int encoderN_SMALLACMD(int offsetCMD)
{
  int validCMD=0;
  return encoderValidN_SMALLACMD(offsetCMD, &validCMD);
}//encoderN_SMALLACMD(int adrCMD)
unsigned int encoderValidN_SMALLACMD(int offsetCMD, int *validCMD)
{
//кодировщик адреса modbus в индекс бита для ДВ
  int outMaska=-1;
  int dvMaska=-1;
  (*validCMD) = cmdFunc000(offsetCMD, &outMaska, &dvMaska, CLRACT_CONTROL);
  return dvMaska;
}//encoderValidN_SMALLACMD(int offsetCMD, int *validCMD)

int decoderN_BIGACMD(int idxBit)
{
//декодировщик индекса бита в адрес modbus  для реле
  unsigned short result = decoderN_BIGACMDArray[idxBit];
  if(result==0xFFFF) return -1;
  return result;
/*
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(outMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
*/
}//decoderN_BIGACMD(int idxBit)
int decoderN_BIGACMDArrayLoader(int idxBit)
{
//декодировщик индекса бита в адрес modbus  для реле
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(outMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
}//decoderN_BIGACMD(int idxBit)
int decoderN_SMALLACMD(int idxBit)
{
//декодировщик индекса бита в адрес modbus  для ДВ
  unsigned short result = decoderN_SMALLACMDArray[idxBit];
  if(result==0xFFFF) return -1;
  return result;

/*
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(dvMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
*/
}//decoderN_SMALLACMD(int idxBit)
int decoderN_SMALLACMDArrayLoader(int idxBit)
{
//декодировщик индекса бита в адрес modbus  для ДВ
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(dvMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
}//decoderN_SMALLACMD(int idxBit)
int getSequenceN_BIGIndexActiveBit(int pps, unsigned int *array)
{
//индекс активного бита N_BIG
  int bit=0;
  unsigned int arrayData = 0;
  int propusk = pps;
  for(; bit<N_BIG*32; bit++)
  {
    arrayData = array[bit/32];
    if(arrayData==0) {
      bit+=31;
      continue;
    }
    unsigned int data = arrayData&(1<<(bit%32));
    if(data!=0&&propusk==0) break;
    if(data!=0&&propusk!=0) propusk--;
  }//for
  if(bit!=N_BIG*32) return bit;
  return -1;
}//getSequenceN_BIGIndexActiveBit(int propusk, unsigned int *array)

int getSequenceN_SMALLIndexActiveBit(int pps, unsigned int *array)
{
//индекс активного бита N_SMALL
  int bit=0;
  unsigned int arrayData = 0;
  int propusk = pps;
  for(; bit<N_SMALL*32; bit++)
  {
    arrayData = array[bit/32];
    if(arrayData==0) {
      bit+=31;
      continue;
    }
    unsigned int data = arrayData&(1<<(bit%32));
    if(data!=0&&propusk==0) break;
    if(data!=0&&propusk!=0) propusk--;
  }//for
  if(bit!=N_SMALL*32) return bit;
  return -1;
}//getSequenceN_SMALLIndexActiveBit(int propusk, unsigned int *array)
int getRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
{
//поиск активного бита
  int subObj = offset/countItem;
  int bit = getSequenceN_BIGIndexActiveBit(offset%countItem, &ranguvannja[N_BIG*subObj]);//индекс активного бита
  if(bit!=-1)
  {
    int adr = decoderN_BIGACMD(bit);
    return adr<0? 0: adr+getACMDSmallBeginAdr();//декодировщик индекса бита в адрес modbus  для rele
  }//if(bit!=-1)
  return 0;
}//getRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
int getRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
{
//поиск активного бита
  int subObj = offset/countItem;
  int bit = getSequenceN_SMALLIndexActiveBit(offset%countItem, &ranguvannja[N_SMALL*subObj]);//индекс активного бита
  if(bit!=-1)
  {
    int adr = decoderN_SMALLACMD(bit);
    return adr<0? 0: adr+getACMDSmallBeginAdr();//декодировщик индекса бита в адрес modbus  для rele
  }//if(bit!=-1)
  return 0;
}//getRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
void writeRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr,
                                  int countAdr, int begin_adr_register)
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(begin_adr_register);//найти смещение TempWriteArray
  unsigned int tmp[N_BIG];//для сохр ранжирования
  int idxObjOld=-1;//индекс суб обекта old
  //убрать старое
  for(int i=0; i<countAdr; i++)
  {
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//индекс суб обекта
    unsigned int *ranguvannja_d = &ranguvannja[N_BIG*idxObj]; //Ранжування
    if(idxObj!=idxObjOld) {
      idxObjOld = idxObj;
      for(int dx=0; dx<N_BIG; dx++) tmp[dx]=ranguvannja_d[dx];//сохр старое ранж
    }//if

    int bitOld = getSequenceN_BIGIndexActiveBit(offset%countItem, tmp);//индекс активного бита
    if(bitOld!=-1) {
      ranguvannja_d[bitOld/32] &= ~(1<<(bitOld%32));
    }//if
  }//for
  //добавить новое
  for(int i=0; i<countAdr; i++)
  {
    unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//новое значение
    if(adr==0) continue;
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//индекс суб обекта
    unsigned int *ranguvannja_d = &ranguvannja[N_BIG*idxObj]; //Ранжування
    int bit = encoderN_BIGACMD(adr-getACMDSmallBeginAdr()); //кодировщик адреса modbus в индекс бита для реле
    if(bit!=-1) {
      ranguvannja_d[bit/32] |= (1<<(bit%32));
    }//if
  }//for
}//writeRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr, int countAdr,
void writeRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr,
                                    int countAdr, int begin_adr_register)
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(begin_adr_register);//найти смещение TempWriteArray
  unsigned int tmp[N_SMALL];//для сохр ранжирования
  int idxObjOld=-1;//индекс суб обекта old
  //убрать старое
  for(int i=0; i<countAdr; i++)
  {
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//индекс суб обекта
    unsigned int *ranguvannja_d = &ranguvannja[N_SMALL*idxObj]; //Ранжування
    if(idxObj!=idxObjOld) {
      idxObjOld = idxObj;
      for(int dx=0; dx<N_SMALL; dx++) tmp[dx]=ranguvannja_d[dx];//сохр старое ранж
    }//if

    int bitOld = getSequenceN_SMALLIndexActiveBit(offset%countItem, tmp);//индекс активного бита
    if(bitOld!=-1) {
      ranguvannja_d[bitOld/32] &= ~(1<<(bitOld%32));
    }//if
  }//for
  //добавить новое
  for(int i=0; i<countAdr; i++)
  {
    unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//новое значение
    if(adr==0) continue;
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//индекс суб обекта
    unsigned int *ranguvannja_d = &ranguvannja[N_SMALL*idxObj]; //Ранжування
    int bit = encoderN_SMALLACMD(adr-getACMDSmallBeginAdr()); //кодировщик адреса modbus в индекс бита для dv
    if(bit!=-1) {
      ranguvannja_d[bit/32] |= (1<<(bit%32));
    }//if
  }//for
}//writeRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr, int countAdr,

int getACMDSmallModbusRegister(int adrReg)
{
  extern int globalcntReg;//к-во reg для чтения
  extern int globalbeginAdrReg;//адрес нач reg
  //получить содержимое регистра
  if(privateACMDSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(acmdsmallcomponent->isActiveActualData)
  {
    int begin = globalbeginAdrReg-BEGIN_ADR_REGISTER;
    if(begin<0) globalcntReg += begin;

    int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
    int endOffset   = beginOffset +globalcntReg*16;

    loadACMDSmallActualDataBit(0, beginOffset, endOffset); //ActualData
  }//if(acmdsmallcomponent->isActiveActualData)
  acmdsmallcomponent->isActiveActualData = 0;

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getACMDSmallModbusBit(int adrBit)
{
  extern int globalcntBit;//к-во бит для чтения
  extern int globalbeginAdrBit;//адрес нач бит
  //получить содержимое bit

  if(privateACMDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int beginOffset = adrBit-BEGIN_ADR_BIT;
  if(acmdsmallcomponent->isActiveActualData)
  {
    int begin = globalbeginAdrBit-BEGIN_ADR_BIT;
    if(begin<0) globalcntBit += begin;

    int endOffset   = beginOffset +globalcntBit;

    loadACMDSmallActualDataBit(0, beginOffset, endOffset); //ActualData
  }//if(acmdsmallcomponent->isActiveActualData)
  acmdsmallcomponent->isActiveActualData = 0;

  short tmp   = tempReadArray[beginOffset/16];
  short maska = 1<<(beginOffset%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTModbusBit(int adrReg)
int setACMDSmallModbusRegister(int adrReg, int dataReg)
{
  if(privateACMDSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
  int endOffset   = beginOffset+16;// + beginOffset;
  for(int offset=beginOffset; offset<endOffset; offset++)
  {
    if(!(dataReg & (1<<(offset%16)))) continue;
    if(writeACMDSmallActualDataBit(offset, 0)!=0) return MARKER_ERRORPERIMETR;
  }//for

  return 0;
}//getDOUTModbusRegister(int adrReg)
int setACMDSmallModbusBit(int adrBit, int dataBit)
{
  //записать содержимое bit
  if(privateACMDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(acmdsmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//записать в буфер
  if(adrBit!=BEGIN_ADR_BIT+BITACMD711)//Активация конфигурации
  {
    if(dataBit==0) return MARKER_ERRORPERIMETR;
  }//if(adrBit!=50567)
  else return 0;
  if(writeACMDSmallActualDataBit(adrBit-BEGIN_ADR_BIT, 0)!=0) return MARKER_ERRORPERIMETR;

  return 0;
}//getDOUTModbusRegister(int adrReg)

int writeACMDSmallActualDataBit(int inOffset, int dataBit)
{
  int actControl = 0;
  if(inOffset<0)
  {
    inOffset = -inOffset;
    actControl = 1;
  }//if(offset<0)
  switch(inOffset)
  {
  case 544://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF1_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 545://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF2_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 546://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF3_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 547://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF4_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 548://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF5_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 549://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF6_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 550://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF7_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 551://OF
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF8_IN);
      mutex_interface = false;
    }//if(action)
    return 0;

  case 576://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT1_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 577://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT1_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 578://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT2_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 579://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT2_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 580://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT3_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 581://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT3_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 582://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT4_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 583://DTR
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT4_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;

  case IMUNITET_BITACMD640://Включение ВВ ВН
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_VKL_VV_H); //Вкл.  виключателя
      mutex_interface = false;
    }//if(action)
    return 0;
  case IMUNITET_BITACMD641://Отключение ВВ ВН
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_OTKL_VV_H); //Викл. виключателя
      mutex_interface = false;
    }//if(action)
    return 0;
  case IMUNITET_BITACMD672://Включение ВВ HН
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_VKL_VV_L); //Вкл.  виключателя
      mutex_interface = false;
    }//if(action)
    return 0;
  case IMUNITET_BITACMD673://Отключение ВВ HН
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_OTKL_VV_L); //Викл. виключателя
      mutex_interface = false;
    }//if(action)
    return 0;

  case IMUNITET_BITACMD706://Сброс индикации
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_LEDS);//Очищення індикації
      mutex_interface = false;
    }//if(action)
    return 0;
  case IMUNITET_BITACMD707://Сброс реле
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if (_CHECK_SET_BIT(active_functions, RANG_READY_TU) == 0)return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_RELES); //Скидання реле
      mutex_interface = false;
    }//if(action)
    return 0;
  case IMUNITET_BITACMD708://Сброс сработавших функций
    if(actControl&&dataBit)
    {
      //Скидання загальних функцій
  if(pointInterface==USB_RECUEST)//метка интерфейса 0-USB 1-RS485
      reset_trigger_function_from_interface |= (1 << USB_RECUEST);
  else 
      reset_trigger_function_from_interface |= (1 << RS485_RECUEST);
    }//if(action)
    return 0;

  case BITACMD711://Активизация конфигурации
    if(actControl)
    {
      if(dataBit)
      {
        //Активація внесекних змін
        int typI = 2;
        if(pointInterface==RS485_RECUEST) typI = 3;//метка интерфейса 0-USB 1-RS485
        if(set_new_settings_from_interface(typI))//2-USB
        {
        type_of_settings_changed = 0;
        _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
          return ERROR_VALID3;//ошибка
        }//if
      }//if
      else//деактивация
      {
        //Відміна внесекних змін
        current_settings_interfaces = current_settings;
      }
        type_of_settings_changed = 0;
        _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
    }//if(action)
    return 0;

  case IMUNITET_BITACMD743://Скидання блокування готорності ТУ від захистів
    if(_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE) != 0) return MARKER_ERRORPERIMETR;
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV); //Скидання блокування готорності ТУ від захистів
      mutex_interface = false;
    }//if(action)
    return 0;
  }//switch
  return MARKER_ERRORPERIMETR;
}//writeACMDSmallActualDataBit(int offset)

void preACMDSmallReadAction(void)
{
//action до чтения
  acmdsmallcomponent->isActiveActualData = 1;
}//
void preACMDSmallWriteAction(void)
{
//action до записи
  acmdsmallcomponent->operativMarker[0] = -1;
  acmdsmallcomponent->operativMarker[1] = -1;//оперативный маркер
  acmdsmallcomponent->isActiveActualData = 1;
}//
int postACMDSmallWriteAction(void)
{
//action после записи
  int beginAdr = acmdsmallcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//не было записи
  int endAdr   = acmdsmallcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  if(beginAdr>=BEGIN_ADR_BIT)
  {
    //работа с битами
    int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_BIT);//найти смещение TempWriteArray

    for(int i=0; i<countAdr; i++) {
      int offset = i+beginAdr-BEGIN_ADR_BIT;
      uint32_t value = tempWriteArray[offsetTempWriteArray+i];
      writeACMDSmallActualDataBit(-offset, value);//action
    }//for
  }//if(beginAdr>=BEGIN_ADR_BIT)
  else
  {
    //работа с регистрами
    int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
    for(int i=0; i<countAdr; i++) {
      int offset = i+beginAdr-BEGIN_ADR_REGISTER;
      for(int bit=0; bit<16; bit++)
      {
        uint32_t value = tempWriteArray[offsetTempWriteArray+i];
        int temp = 0;
        if(value&(1<<bit)) temp = 1;
        writeACMDSmallActualDataBit(-(offset*16+bit), temp);//action
      }//for
    }//for
  }//else

  return 0;
}//

int privateACMDSmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int privateACMDSmallGetBit2(int adrBit)
{
  //проверить внешний периметр
  return controlPerimetr(adrBit, BEGIN_ADR_BIT, END_ADR_BIT);
}//privateGetReg2(int adrReg)

int passwordImunitetBitACMDSmallComponent(int adrBit)
{
  //имунитетные к паролю адреса bit 0 - есть имунитет
  if(privateACMDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  switch(adrBit)
  {
    case BEGIN_ADR_BIT+IMUNITET_BITACMD640://Включение ВВ H
    case BEGIN_ADR_BIT+IMUNITET_BITACMD641://Отключение ВВ H
    case BEGIN_ADR_BIT+IMUNITET_BITACMD672://Включение ВВ L
    case BEGIN_ADR_BIT+IMUNITET_BITACMD673://Отключение ВВ L

    case BEGIN_ADR_BIT+IMUNITET_BITACMD706://Сброс индикации
    case BEGIN_ADR_BIT+IMUNITET_BITACMD707://Сброс реле
    case BEGIN_ADR_BIT+IMUNITET_BITACMD708://Сброс сработавших функций

    case BEGIN_ADR_BIT+IMUNITET_BITACMD743://Сброс блокировки готовности к ТУ от защит
    return 0;//есть имунитет
  }//switch
  return MARKER_OUTPERIMETR;
}//passwordImunitetBitACMDSmallComponent(int adrBit)
