#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10300
//конечный регистр в карте памяти
#define END_ADR_REGISTER 11542

int privateUSTBigGetReg2(int adrReg);

int getUSTBigModbusRegister(int);//получить содержимое регистра
int getUSTBigModbusBit(int);//получить содержимое бита
int setUSTBigModbusRegister(int, int);//получить содержимое регистра
int setUSTBigModbusBit(int, int);//получить содержимое бита

void setUSTBigCountObject(void);//записать к-во обектов
void preUSTBigReadAction(void);//action до чтения
void preUSTBigWriteAction(void);//action до записи
int  postUSTBigWriteAction(void);//action после записи
int  ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **editValue);
int grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa);

COMPONENT_OBJ *ustbigcomponent;

int ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **editValue)
{
  int diapazon = 1;
  int actControl = 0;
  if(inOffset<0)
  {
    inOffset = -inOffset;
    actControl = 1;
  }//if(inOffset<0)
  (*multer) = 10;
  switch(inOffset)
  {
  case 0:
    (*editValue) = (uint32_t*)&edition_settings.grupa_ustavok;
    (*multer) = 1;
    if(regUst<1 || regUst>4) diapazon=0;
    break;
  case 1:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz1;
    (*multer) = 1;
    if(regUst<0 || regUst>2) diapazon=0;
    break;
  case 2:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz2;
    (*multer) = 1;
    if(regUst<0 || regUst>7) diapazon=0;
    break;
  case 3:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz3;
    (*multer) = 1;
    if(regUst<0 || regUst>7) diapazon=0;
    break;
  case 4:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz4;
    (*multer) = 1;
    if(regUst<0 || regUst>2) diapazon=0;
    break;

//IF ВСТАВКА 07-14

  case 15:
    (*editValue) = (uint32_t*)&edition_settings.type_con_ozt;
    (*multer) = 1;
    if(regUst<0 || regUst>2) diapazon=0;
    break;

  case 16:
    (*editValue) = &edition_settings.setpoint_mtz_1[gruppa];
    if(regUst<SETPOINT_MTZ1_MIN/10 || regUst>SETPOINT_MTZ1_MAX/10) diapazon=0;
    break;
  case 17:
    (*editValue) = &edition_settings.setpoint_mtz_1_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ1_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ1_N_VPERED_MAX/10) diapazon=0;
    break;
  case 18:
    (*editValue) = &edition_settings.setpoint_mtz_1_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ1_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ1_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 19:
    (*editValue) = &edition_settings.setpoint_mtz_1_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ1_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ1_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 20:
    (*editValue) = &edition_settings.setpoint_mtz_1_U[gruppa];
    if(regUst<SETPOINT_MTZ1_U_MIN/10 || regUst>SETPOINT_MTZ1_U_MAX/10) diapazon=0;
    break;
  case 21:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_1_angle[gruppa];
    if(regUst<SETPOINT_MTZ1_ANGLE_MIN || regUst>SETPOINT_MTZ1_ANGLE_MAX) diapazon=0;
    break;
  case 22:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1[gruppa];
    if(regUst<TIMEOUT_MTZ1_MIN/10 || regUst>TIMEOUT_MTZ1_MAX/10) diapazon=0;
    break;
  case 23:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ1_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ1_N_VPERED_MAX/10) diapazon=0;
    break;
  case 24:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ1_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ1_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 25:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ1_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ1_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 28:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_2[gruppa];
    if(regUst<SETPOINT_MTZ2_MIN/10 || regUst>SETPOINT_MTZ2_MAX/10) diapazon=0;
    break;
  case 29:
    (*editValue) = &edition_settings.setpoint_mtz_2_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ2_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ2_N_VPERED_MAX/10) diapazon=0;
    break;
  case 30:
    (*editValue) = &edition_settings.setpoint_mtz_2_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ2_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ2_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 31:
    (*editValue) = &edition_settings.setpoint_mtz_2_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ2_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ2_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 32:
    (*editValue) = &edition_settings.setpoint_mtz_2_U[gruppa];
    if(regUst<SETPOINT_MTZ2_U_MIN/10 || regUst>SETPOINT_MTZ2_U_MAX/10) diapazon=0;
    break;
  case 33:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_2_angle[gruppa];
    if(regUst<SETPOINT_MTZ2_ANGLE_MIN || regUst>SETPOINT_MTZ2_ANGLE_MAX) diapazon=0;
    break;
  case 34:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2[gruppa];
    if(regUst<TIMEOUT_MTZ2_MIN/10 || regUst>TIMEOUT_MTZ2_MAX/10) diapazon=0;
    break;
  case 35:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ2_N_VPERED_MAX/10) diapazon=0;
    break;
  case 36:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ2_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 37:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ2_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ2_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 38:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_vvid_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_VVID_PR_MIN/10 || regUst>TIMEOUT_MTZ2_VVID_PR_MAX/10) diapazon=0;
    break;
  case 39:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_PR_MIN/10 || regUst>TIMEOUT_MTZ2_PR_MAX/10) diapazon=0;
    break;
  case 40:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_vpered_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_VPERED_PR_MIN/10 || regUst>TIMEOUT_MTZ2_N_VPERED_PR_MAX/10) diapazon=0;
    break;
  case 41:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_nazad_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_NAZAD_PR_MIN/10 || regUst>TIMEOUT_MTZ2_N_NAZAD_PR_MAX/10) diapazon=0;
    break;
  case 42:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_po_napruzi_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_PO_NAPRUZI_PR_MIN/10 || regUst>TIMEOUT_MTZ2_PO_NAPRUZI_PR_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 46:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_3[gruppa];
    if(regUst<SETPOINT_MTZ3_MIN/10 || regUst>SETPOINT_MTZ3_MAX/10) diapazon=0;
    break;
  case 47:
    (*editValue) = &edition_settings.setpoint_mtz_3_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ3_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ3_N_VPERED_MAX/10) diapazon=0;
    break;
  case 48:
    (*editValue) = &edition_settings.setpoint_mtz_3_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ3_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ3_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 49:
    (*editValue) = &edition_settings.setpoint_mtz_3_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ3_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ3_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 50:
    (*editValue) = &edition_settings.setpoint_mtz_3_U[gruppa];
    if(regUst<SETPOINT_MTZ3_U_MIN/10 || regUst>SETPOINT_MTZ3_U_MAX/10) diapazon=0;
    break;
  case 51:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_3_angle[gruppa];
    if(regUst<SETPOINT_MTZ3_ANGLE_MIN || regUst>SETPOINT_MTZ3_ANGLE_MAX) diapazon=0;
    break;
  case 52:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3[gruppa];
    if(regUst<TIMEOUT_MTZ3_MIN/10 || regUst>TIMEOUT_MTZ3_MAX/10) diapazon=0;
    break;
  case 53:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ3_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ3_N_VPERED_MAX/10) diapazon=0;
    break;
  case 54:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ3_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ3_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 55:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ3_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ3_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 64:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_4[gruppa];
    if(regUst<SETPOINT_MTZ4_MIN/10 || regUst>SETPOINT_MTZ4_MAX/10) diapazon=0;
    break;
  case 65:
    (*editValue) = &edition_settings.setpoint_mtz_4_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ4_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ4_N_VPERED_MAX/10) diapazon=0;
    break;
  case 66:
    (*editValue) = &edition_settings.setpoint_mtz_4_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ4_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ4_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 67:
    (*editValue) = &edition_settings.setpoint_mtz_4_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ4_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ4_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 68:
    (*editValue) = &edition_settings.setpoint_mtz_4_U[gruppa];
    if(regUst<SETPOINT_MTZ4_U_MIN/10 || regUst>SETPOINT_MTZ4_U_MAX/10) diapazon=0;
    break;
  case 69:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_4_angle[gruppa];
    if(regUst<SETPOINT_MTZ4_ANGLE_MIN || regUst>SETPOINT_MTZ4_ANGLE_MAX) diapazon=0;
    break;
  case 70:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4[gruppa];
    if(regUst<TIMEOUT_MTZ4_MIN/10 || regUst>TIMEOUT_MTZ4_MAX/10) diapazon=0;
    break;
  case 71:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ4_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ4_N_VPERED_MAX/10) diapazon=0;
    break;
  case 72:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ4_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ4_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 73:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ4_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ4_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  count_bit = 2;
  case 93:
    (*editValue) = &edition_settings.setpoint_P_3U0[gruppa];
    if(regUst<SETPOINT_P_3U0_MIN/10 || regUst>SETPOINT_P_3U0_MAX/10) diapazon=0;
    break;
  case 94:
    (*editValue) = (uint32_t*)&edition_settings.timeout_P_3U0[gruppa];
    if(regUst<TIMEOUT_P_3U0_MIN/10 || regUst>TIMEOUT_P_3U0_MAX/10) diapazon=0;
    break;

//  count_bit = 1;
  case 95:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP1_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP1_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 96:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP1_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP1_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 97:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_1_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP1_VPERED_MIN/10 || regUst>TIMEOUT_TZNP1_VPERED_MAX/10) diapazon=0;
    break;
  case 98:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP1_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP1_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 99:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP1_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP1_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 100:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_1_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP1_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP1_NAZAD_MAX/10) diapazon=0;
    break;
  case 101:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_angle[gruppa];
    if(regUst<SETPOINT_TZNP1_ANGLE_MIN || regUst>SETPOINT_TZNP1_ANGLE_MAX) diapazon=0;
    break;
  case 102:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP2_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP2_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 103:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP2_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP2_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 104:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_2_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP2_VPERED_MIN/10 || regUst>TIMEOUT_TZNP2_VPERED_MAX/10) diapazon=0;
    break;
  case 105:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP2_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP2_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 106:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP2_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP2_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 107:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_2_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP2_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP2_NAZAD_MAX/10) diapazon=0;
    break;
  case 108:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_angle[gruppa];
    if(regUst<SETPOINT_TZNP2_ANGLE_MIN || regUst>SETPOINT_TZNP2_ANGLE_MAX) diapazon=0;
    break;
  case 109:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP3_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP3_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 110:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP3_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP3_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 111:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_3_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP3_VPERED_MIN/10 || regUst>TIMEOUT_TZNP3_VPERED_MAX/10) diapazon=0;
    break;
  case 112:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP3_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP3_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 113:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP3_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP3_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 114:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_3_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP3_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP3_NAZAD_MAX/10) diapazon=0;
    break;
  case 115:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_angle[gruppa];
    if(regUst<SETPOINT_TZNP3_ANGLE_MIN || regUst>SETPOINT_TZNP3_ANGLE_MAX) diapazon=0;
    break;
  case 116:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_4_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP4_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP4_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 117:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_4_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP4_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP4_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 118:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_4_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP4_VPERED_MIN/10 || regUst>TIMEOUT_TZNP4_VPERED_MAX/10) diapazon=0;
    break;
  case 119:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_4_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP4_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP4_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 120:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_4_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP4_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP4_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 121:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_4_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP4_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP4_NAZAD_MAX/10) diapazon=0;
    break;
  case 122:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_4_angle[gruppa];
    if(regUst<SETPOINT_TZNP4_ANGLE_MIN || regUst>SETPOINT_TZNP4_ANGLE_MAX) diapazon=0;
    break;

  case 123:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_zop1[gruppa];
    if(regUst<SETPOINT_ZOP1_MIN || regUst>SETPOINT_ZOP1_MAX) diapazon=0;
    break;
  case 124:
    (*editValue) = (uint32_t*)&edition_settings.timeout_zop1[gruppa];
    if(regUst<TIMEOUT_ZOP1_MIN/10 || regUst>TIMEOUT_ZOP1_MAX/10) diapazon=0;
    break;
  case 125:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_zop2[gruppa];
    if(regUst<SETPOINT_ZOP2_MIN || regUst>SETPOINT_ZOP2_MAX) diapazon=0;
    break;
  case 126:
    (*editValue) = (uint32_t*)&edition_settings.timeout_zop2[gruppa];
    if(regUst<TIMEOUT_ZOP2_MIN/10 || regUst>TIMEOUT_ZOP2_MAX/10) diapazon=0;
    break;

//  count_bit = 10;
  case 130:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin1[gruppa];
    if(regUst<SETPOINT_UMIN1_MIN/100 || regUst>SETPOINT_UMIN1_MAX/100) diapazon=0;
    break;
  case 131:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umin1[gruppa];
    if(regUst<TIMEOUT_UMIN1_MIN/10 || regUst>TIMEOUT_UMIN1_MAX/10) diapazon=0;
    break;
  case 132:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin2[gruppa];
    if(regUst<SETPOINT_UMIN2_MIN/100 || regUst>SETPOINT_UMIN2_MAX/100) diapazon=0;
    break;
  case 133:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umin2[gruppa];
    if(regUst<TIMEOUT_UMIN2_MIN/10 || regUst>TIMEOUT_UMIN2_MAX/10) diapazon=0;
    break;
  case 134:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin1_Iblk[gruppa];
    if(regUst<SETPOINT_UMIN1_IBLK_MIN/10 || regUst>SETPOINT_UMIN1_IBLK_MAX/10) diapazon=0;
    break;
  case 135:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin2_Iblk[gruppa];
    if(regUst<SETPOINT_UMIN2_IBLK_MIN/10 || regUst>SETPOINT_UMIN2_IBLK_MAX/10) diapazon=0;
    break;

  case 136:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umax1[gruppa];
    if(regUst<SETPOINT_UMAX1_MIN/100 || regUst>SETPOINT_UMAX1_MAX/100) diapazon=0;
    break;
  case 137:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umax1[gruppa];
    if(regUst<TIMEOUT_UMAX1_MIN/10 || regUst>TIMEOUT_UMAX1_MAX/10) diapazon=0;
    break;
  case 138:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umax2[gruppa];
    if(regUst<SETPOINT_UMAX2_MIN/100 || regUst>SETPOINT_UMAX2_MAX/100) diapazon=0;
    break;
  case 139:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umax2[gruppa];
    if(regUst<TIMEOUT_UMAX2_MIN/10 || regUst>TIMEOUT_UMAX2_MAX/10) diapazon=0;
    break;
  case 140:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_kp_Umax[gruppa];
    if(regUst<SETPOINT_KP_UMAX_MIN || regUst>SETPOINT_KP_UMAX_MAX) diapazon=0;
    break;

//  count_bit = 4;
  case 156:
    (*editValue) = &edition_settings.setpoint_urov[0][gruppa];
    if(regUst<SETPOINT_UROV_MIN/10 || regUst>SETPOINT_UROV_MAX/10) diapazon=0;
    break;
  case 157:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_1[0][gruppa];
    if(regUst<TIMEOUT_UROV1_MIN/10 || regUst>TIMEOUT_UROV1_MAX/10) diapazon=0;
    break;
  case 158:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_2[0][gruppa];
    if(regUst<TIMEOUT_UROV2_MIN/10 || regUst>TIMEOUT_UROV2_MAX/10) diapazon=0;
    break;

//  count_bit = 4;
  case 160:
    (*editValue) = &edition_settings.setpoint_urov[1][gruppa];
    if(regUst<SETPOINT_UROV_MIN/10 || regUst>SETPOINT_UROV_MAX/10) diapazon=0;
    break;
  case 161:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_1[1][gruppa];
    if(regUst<TIMEOUT_UROV1_MIN/10 || regUst>TIMEOUT_UROV1_MAX/10) diapazon=0;
    break;
  case 162:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_2[1][gruppa];
    if(regUst<TIMEOUT_UROV2_MIN/10 || regUst>TIMEOUT_UROV2_MAX/10) diapazon=0;
    break;


//IF ВСТАВКА 227-258

  case 259:
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_Id0[gruppa];
    if(regUst<PICKUP_OZT_Id0_MIN/10 || regUst>PICKUP_OZT_Id0_MAX/10) diapazon=0;
    break;
  case 260:
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_delta_Id[gruppa];
    if(regUst<PICKUP_OZT_DELTA_Id_MIN/10 || regUst>PICKUP_OZT_DELTA_Id_MAX/10) diapazon=0;
    break;
  case 261:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_Kg1[gruppa];
    if(regUst<PICKUP_OZT_Kg1_MIN || regUst>PICKUP_OZT_Kg1_MAX) diapazon=0;
    break;
  case 262:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_Kg2[gruppa];
    if(regUst<PICKUP_OZT_Kg2_MIN || regUst>PICKUP_OZT_Kg2_MAX) diapazon=0;
    break;
  case 263:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_k[gruppa];
    if(regUst<PICKUP_OZT_K_MIN || regUst>PICKUP_OZT_K_MAX) diapazon=0;
    break;
  case 264:
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_Ig0[gruppa];
    if(regUst<PICKUP_OZT_Ig0_MIN/10 || regUst>PICKUP_OZT_Ig0_MAX/10) diapazon=0;
    break;
  case 265:
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_Ig_obm[gruppa];
    if(regUst<PICKUP_OZT_Ig_OBM_MIN/10 || regUst>PICKUP_OZT_Ig_OBM_MAX/10) diapazon=0;
    break;
  case 266:
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_K_aI[gruppa];
    if(regUst<PICKUP_OZT_K_AI_MIN/10 || regUst>PICKUP_OZT_K_AI_MAX/10) diapazon=0;
    break;
  case 267:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_K_2I[gruppa];
    if(regUst<PICKUP_OZT_K_2I_MIN || regUst>PICKUP_OZT_K_2I_MAX) diapazon=0;
    break;
  case 268:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_K_5I[gruppa];
    if(regUst<PICKUP_OZT_K_5I_MIN || regUst>PICKUP_OZT_K_5I_MAX) diapazon=0;
    break;
  case 269:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_kp[gruppa];
    if(regUst<PICKUP_OZT_KP_MIN || regUst>PICKUP_OZT_KP_MAX) diapazon=0;
    break;
  case 270:
    (*editValue) = (uint32_t*)&edition_settings.timeout_ozt1[gruppa];
    if(regUst<TIMEOUT_OZT1_MIN/10 || regUst>TIMEOUT_OZT1_MAX/10) diapazon=0;
    break;
  case 271:
    (*editValue) = (uint32_t*)&edition_settings.timeout_ozt2[gruppa];
    if(regUst<TIMEOUT_OZT2_MIN/10 || regUst>TIMEOUT_OZT2_MAX/10) diapazon=0;
    break;
  case 272:
    (*editValue) = (uint32_t*)&edition_settings.timeout_ozt2_a_blk[gruppa];
    if(regUst<TIMEOUT_OZT2_A_BLK_MIN/10 || regUst>TIMEOUT_OZT2_A_BLK_MAX/10) diapazon=0;
    break;

  case 273:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP1[gruppa];
    if(regUst<TIMEOUT_GP1_MIN/10 || regUst>TIMEOUT_GP1_MAX/10) diapazon=0;
    break;
  case 274:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP2[gruppa];
    if(regUst<TIMEOUT_GP2_MIN/10 || regUst>TIMEOUT_GP2_MAX/10) diapazon=0;
    break;
  case 275:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP_RPN[gruppa];
    if(regUst<TIMEOUT_GP_RPN_MIN/10 || regUst>TIMEOUT_GP_RPN_MAX/10) diapazon=0;
    break;

  case 276:
    (*editValue) = (uint32_t*)&edition_settings.timeout_TP[gruppa];
    if(regUst<TIMEOUT_TP_MIN/10 || regUst>TIMEOUT_TP_MAX/10) diapazon=0;
    break;

  case 277:
    (*editValue) = (uint32_t*)&edition_settings.pickup_kz_zv[gruppa];
    if(regUst<SETPOINT_KZ_ZV_MIN/10 || regUst>SETPOINT_KZ_ZV_MAX/10) diapazon=0;
    break;
  case 278:
    (*editValue) = (uint32_t*)&edition_settings.pickup_kz_zv_angle[gruppa];
    if(regUst<SETPOINT_KZ_ZV_ANGLE_MIN/10 || regUst>SETPOINT_KZ_ZV_ANGLE_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1154:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TVoltage;
    if(regUst<KOEF_TN_MIN || regUst>KOEF_TN_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1156:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TCurrent_H;
    if(regUst<KOEF_TT_H_MIN || regUst>KOEF_TT_H_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1159:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TCurrent_L;
    if(regUst<KOEF_TT_L_MIN || regUst>KOEF_TT_L_MAX) diapazon=0;
    break;
  case 1160:
    (*editValue) = (uint32_t*)&edition_settings.pickup_vyr_H;
    if(regUst<PICKUP_VYR_H_MIN/10 || regUst>PICKUP_VYR_H_MAX/10) diapazon=0;
    break;
  case 1161:
    (*editValue) = (uint32_t*)&edition_settings.pickup_vyr_L;
    if(regUst<PICKUP_VYR_L_MIN/10 || regUst>PICKUP_VYR_L_MAX/10) diapazon=0;
    break;

  case 1162:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_udl_blk_on[0];
    if(regUst<TIMEOUT_SWCH_UDL_BLK_ON_MIN/10 || regUst>TIMEOUT_SWCH_UDL_BLK_ON_MAX/10) diapazon=0;
    break;
  case 1163:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_on[0];
    if(regUst<TIMEOUT_SWCH_ON_MIN/10 || regUst>TIMEOUT_SWCH_ON_MAX/10) diapazon=0;
    break;
  case 1164:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_off[0];
    if(regUst<TIMEOUT_SWCH_OFF_MIN/10 || regUst>TIMEOUT_SWCH_OFF_MAX/10) diapazon=0;
    break;
  case 1165:
    (*editValue) = (uint32_t*)&edition_settings.timeout_pryvoda_VV[0];
    if(regUst<TIMEOUT_PRYVODA_VV_MIN/10 || regUst>TIMEOUT_PRYVODA_VV_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1178:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_udl_blk_on[1];
    if(regUst<TIMEOUT_SWCH_UDL_BLK_ON_MIN/10 || regUst>TIMEOUT_SWCH_UDL_BLK_ON_MAX/10) diapazon=0;
    break;
  case 1179:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_on[1];
    if(regUst<TIMEOUT_SWCH_ON_MIN/10 || regUst>TIMEOUT_SWCH_ON_MAX/10) diapazon=0;
    break;
  case 1180:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_off[1];
    if(regUst<TIMEOUT_SWCH_OFF_MIN/10 || regUst>TIMEOUT_SWCH_OFF_MAX/10) diapazon=0;
    break;
  case 1181:
    (*editValue) = (uint32_t*)&edition_settings.timeout_pryvoda_VV[1];
    if(regUst<TIMEOUT_PRYVODA_VV_MIN/10 || regUst>TIMEOUT_PRYVODA_VV_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1198:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input_signal;
    break;

//  count_bit = 9;
  case 1200:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input;
    break;

//  count_bit = 9;
  case 1202:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output;
    break;
  case 1203:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output_modif;
    break;
  case 1204:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_df;
    if(regUst&(~(0xFF))) diapazon=0;
    break;
#define MARKER1205  1205
  case MARKER1205:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    break;
  case 1206:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    if(regUst&(~(0x1))) diapazon=0;
    break;
  case 1207:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.buttons_mode;
    if(regUst&(~(0xFFF))) diapazon=0;
    for(int bit=0; bit<NUMBER_DEFINED_BUTTONS; bit++)
    {
      if((regUst&(3<<(bit*2)))==(0x2<<(bit*2))) diapazon=0;
      if((regUst&(3<<(bit*2)))==(0x3<<(bit*2))) diapazon=0;
    }//for
    //Зміна режиму відбудеться у цій функції рахом з можливими змінами у ранжуванні ФК
    if(actControl)
    {
      action_during_changing_button_mode(&current_settings_interfaces, &edition_settings);
      //Перебираємо всі ФК
      for (size_t number = 0; number < NUMBER_DEFINED_BUTTONS; number++)
      {
        for (unsigned int i = 0; i < N_SMALL; i++)
        {
          edition_settings.ranguvannja_buttons[N_SMALL*number + i] =
            current_settings_interfaces.ranguvannja_buttons[N_SMALL*number + i];
        }//for
      }//for
    }//if
    break;

//IF ВСТАВКА 1208-1223
//IF ВСТАВКА 1228-1235
//IF ВСТАВКА 1238-1245

  }//switch

  if(inOffset>=7 && inOffset<15)
  {
    //УЗ
    int item = inOffset-7;
    (*editValue) = (uint32_t*)&edition_settings.ctrl_UP_input[item];
    (*multer) = 1;
    if(actControl)
      if(regUst!=current_settings_interfaces.ctrl_UP_input[item])
      {
        uint32_t tmp = edition_settings.ctrl_UP_input[item];
        edition_settings.ctrl_UP_input[item] = -1;
        action_after_changing_input_UP(&edition_settings, item, tmp);
      }//if(actControl)
  }//if(inOffset>=7 && inOffset<15)

//IF ВСТАВКА 227-258
  if(inOffset>=227 && inOffset<259)
  {
    //УЗ
    int item = inOffset-227;
    switch(item%4)
    {
    case 0:
    case 1:
      (*editValue) = (uint32_t*)&edition_settings.setpoint_UP[item/4][0][gruppa];
      break;
    case 2:
      (*editValue) = (uint32_t*)&edition_settings.timeout_UP[item/4][0][gruppa];
      break;
    case 3:
      (*multer) = 1;
      (*editValue) = (uint32_t*)&edition_settings.setpoint_UP_KP[item/4][0][gruppa];
      break;
    }//switch

    if((item%4)==0 || (item%4)==1)
      switch(edition_settings.ctrl_UP_input[item/4])
      {
      case UP_CTRL_Ia_Ib_Ic_H:
      case UP_CTRL_Ia_H:
      case UP_CTRL_Ib_H:
      case UP_CTRL_Ic_H:
      case UP_CTRL_I1_H:
      case UP_CTRL_I2_H:
      case UP_CTRL_3I0_r_H:
      case UP_CTRL_Ia_Ib_Ic_L:
      case UP_CTRL_Ia_L:
      case UP_CTRL_Ib_L:
      case UP_CTRL_Ic_L:
      case UP_CTRL_I1_L:
      case UP_CTRL_I2_L:
      case UP_CTRL_3I0_r_L:
        if((item%4)==1)
        {
          if(regUst!=0) diapazon=0;//нет старшего регистра
        }//if
        else if(regUst<SETPOINT_UP_I_MIN/10 || regUst>SETPOINT_UP_I_MAX/10) diapazon=0;
        break;
      case UP_CTRL_Ua_Ub_Uc:
      case UP_CTRL_Ua:
      case UP_CTRL_Ub:
      case UP_CTRL_Uc:
      case UP_CTRL_Uab_Ubc_Uca:
      case UP_CTRL_Uab:
      case UP_CTRL_Ubc:
      case UP_CTRL_Uca:
      case UP_CTRL_U1:
      case UP_CTRL_U2:
      case UP_CTRL_3U0:
        (*multer) = 100;
        if((item%4)==1)
        {
          if(regUst!=0) diapazon=0;//нет старшего регистра
        }//if
        else if(regUst<SETPOINT_UP_U_MIN/100 || regUst>SETPOINT_UP_U_MAX/100) diapazon=0;
        break;
      case UP_CTRL_P:
      case UP_CTRL_Q:
      case UP_CTRL_S:
        (*multer) = 1;
        break;
      }//switch

    if((item%4)==2)
      if(regUst<TIMEOUT_UP_MIN/10 || regUst>TIMEOUT_UP_MAX/10) diapazon=0;
    if((item%4)==3)
    {
      if(edition_settings.control_UP& (1<<(2+3*(item/4))))
      {
        if(regUst<SETPOINT_UP_KP_LESS_MIN || regUst>SETPOINT_UP_KP_LESS_MAX) diapazon=0;
      }//if(edition_settings.control_UP& (1<<(2+3*item/4)))
      else  if(regUst<SETPOINT_UP_KP_MORE_MIN || regUst>SETPOINT_UP_KP_MORE_MAX) diapazon=0;
    }//if((item%4)==3)
  }//if(inOffset>=213 && inOffset<245)

//IF ВСТАВКА 1208-1223
    if(inOffset>=1208 && inOffset<1224)
      {
        int item = inOffset-1208;
        (*editValue) = (uint32_t*)&edition_settings.dopusk_dv[item];
        (*multer) = 1;
        if(regUst<0 || regUst>60) diapazon=0;
      }//if(inOffset>=1205 && inOffset<1220)

//IF ВСТАВКА 1228-1235
  if(inOffset>=1228 && inOffset<1236)
  {
    int item = inOffset-1228;
    (*editValue) = (uint32_t*)&edition_settings.timeout_pause_df[item];
    if(regUst<TIMEOUT_DF_PAUSE_MIN/10 || regUst>TIMEOUT_DF_PAUSE_MAX/10) diapazon=0;
  }//if(inOffset>=1225 && inOffset<1233)

//IF ВСТАВКА 1238-1245
  if(inOffset>=1238 && inOffset<1246)
  {
    int item = inOffset-1238;
    (*editValue) = (uint32_t*)&edition_settings.timeout_work_df[item];
    if(regUst<TIMEOUT_DF_WORK_MIN/10 || regUst>TIMEOUT_DF_WORK_MAX/10) diapazon=0;
  }//if(inOffset>=1235 && inOffset<1243)

  return diapazon;
} //ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **ustValue, uint32_t **editValue)

/**************************************/
//подготовка компонента UST
/**************************************/
void constructorUSTBigComponent(COMPONENT_OBJ *ustbigcomp)
{
  ustbigcomponent = ustbigcomp;

  ustbigcomponent->getModbusRegister = getUSTBigModbusRegister;//получить содержимое регистра
  ustbigcomponent->getModbusBit      = getUSTBigModbusBit;//получить содержимое бита
  ustbigcomponent->setModbusRegister = setUSTBigModbusRegister;//получить содержимое регистра
  ustbigcomponent->setModbusBit      = setUSTBigModbusBit;//получить содержимое бита

  ustbigcomponent->preReadAction   = preUSTBigReadAction;//action до чтения
  ustbigcomponent->preWriteAction  = preUSTBigWriteAction;//action до записи
  ustbigcomponent->postWriteAction = postUSTBigWriteAction;//action после записи

  ustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getUSTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//делаем копию
  }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  uint32_t *editValue=NULL;
  int  multer = 1;
  int  adresGruppa=0;
  int  grupa_ustavok=0;
  int  offset = adrReg-BEGIN_ADR_REGISTER;
  grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);

  ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, 0, &editValue);
  if(editValue==NULL) return 0;

  for(int gruppa=0; gruppa<4; gruppa++)
  {
    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][gruppa])
      {
        if((offset-adresGruppa)&1)
          return (((uint32_t)(*editValue))/multer)&0xFFFF;
        else
          return (((*editValue)/multer)>>16)&0xFFFF;
      }//if
    }//for(int item=0; item<NUMBER_UP; item++)
  }//for(int gruppa=0; gruppa<NUMBER_UP; gruppa++)
  for(int item=0; item<NUMBER_UP; item++)
  {
   if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
   {
     if((*editValue)>13) *editValue += 3;
   }//if
  }//for(int item=0; item<NUMBER_UP; item++)
  if(editValue == (uint32_t*)&edition_settings.buttons_mode)
  {
    uint32_t buttonsmode = 0;
    for(int key=0; key<NUMBER_DEFINED_BUTTONS; key++)
    {
      if((*editValue) & (1<<key)) buttonsmode |= (1<<(2*key));
    }//for
    return (buttonsmode) &0xFFFF;
  }//if(editValue == (uint32_t*)&edition_settings.buttons_mode)
  if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
  {
      return (*editValue) & (uint32_t)0xffff;
  }//if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
  if(editValue == (uint32_t*)&edition_settings.type_of_input)
  {
      return (*editValue) & (uint32_t)0xffff;
  }//if(editValue == (uint32_t*)&edition_settings.type_of_input)
  if(editValue == (uint32_t*)&edition_settings.type_of_led)
  {
    if(offset==MARKER1205)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
  }//if(editValue == (uint32_t*)&edition_settings.type_of_led)

  return ((*editValue)/multer)&0xFFFF;
}//getDOUTBigModbusRegister(int adrReg)
int getUSTBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setUSTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//делаем копию
  }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(ustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int  adresGruppa=0;
  int  grupa_ustavok=0;
  int  offset = adrReg-BEGIN_ADR_REGISTER;
  grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);

  uint32_t *editValue=NULL;
  int  multer = 1;
  if(!ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, dataReg, &editValue)) return MARKER_ERRORDIAPAZON;
#ifdef TESTZBIRKA_VERSII_PZ
  if(editValue==NULL) return MARKER_ERRORDIAPAZON;
#else
  if(editValue==NULL) return 0;
#endif

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setUSTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preUSTBigReadAction(void)
{
//action до чтения
  ustbigcomponent->isActiveActualData = 1;
}//
void preUSTBigWriteAction(void)
{
//action до записи
  ustbigcomponent->operativMarker[0] = -1;
  ustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  ustbigcomponent->isActiveActualData = 1;
}//
int postUSTBigWriteAction(void)
{
  extern int upravlSetting;//флаг Setting
//action после записи
  int beginAdr = ustbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//не было записи
  int endAdr   = ustbigcomponent->operativMarker[1];
  int flag=0;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  int  grupa_ustavok=0;
  for(int i=0; i<countAdr; i++)
  {
    int  adresGruppa=0;
    int offset = i+beginAdr-BEGIN_ADR_REGISTER;
    uint32_t *editValue=NULL;
    int  multer = 1;
    int grupa_offset = grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);
    ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, 0, &editValue);
    if(editValue==NULL) continue;

    flag=1;

    uint32_t value = (unsigned short) tempWriteArray[offsetTempWriteArray+i];

//ОСОБАЯ СБОРКА
    for(int item=0; item<NUMBER_UP; item++)
    {
     if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
     {
      if(value>30) return ERROR_VALID2;//ошибка валидации
       switch(value)
       {
        case 14: case 15: case 16:
        return ERROR_VALID2;//ошибка валидации
       }//switch

      if(value>16) value -= 3;
     }//if
    }//for(int item=0; item<NUMBER_UP; item++)
    if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
    {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
    }//if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
    if(editValue == (uint32_t*)&edition_settings.type_of_input)
    {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
    }//if(editValue == (uint32_t*)&edition_settings.type_of_input)
    if(editValue == (uint32_t*)&edition_settings.type_of_led)
    {
      if(offset==MARKER1205)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.type_of_led)

    if(editValue == (uint32_t*)&edition_settings.buttons_mode)
    {
      for(int key=0; key<NUMBER_DEFINED_BUTTONS; key++)
      {
        if(value&(3<<(2*key))) (*editValue) |= (1<<key);
        else (*editValue) &= ~(1<<key);
      }//for
      goto m1;
    }//if(editValue == (uint32_t*)&edition_settings.buttons_mode)

    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.timeout_UP[item][0][grupa_ustavok])
      {
        (*editValue) = multer*value;
        goto m1;
      }//if(editValue == (uint32_t*)&edition_settings.timeout_UP[item][0][grupa_ustavok])
    }//for(int item=0; item<NUMBER_UP; item++)

    if(editValue == (uint32_t*)&edition_settings.pickup_kz_zv_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
//      edition_settings.pickup_kz_zv_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
//      edition_settings.pickup_kz_zv_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));

      edition_settings.pickup_kz_zv_angle_cos_1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*arm_cos_f32((PI*temp_value_f/180.0f)));
      edition_settings.pickup_kz_zv_angle_sin_1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*arm_sin_f32((PI*temp_value_f/180.0f)));
      edition_settings.pickup_kz_zv_angle_cos_2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*arm_cos_f32((PI*(temp_value_f + ANGLE_HYS)/180.0f)));
      edition_settings.pickup_kz_zv_angle_sin_2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*arm_sin_f32((PI*(temp_value_f + ANGLE_HYS)/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.pickup_kz_zv_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_1_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_1_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_2_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_2_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_2_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_3_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_3_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_3_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])

    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_1_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_1_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_1_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_2_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_2_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_2_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_2_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_3_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_3_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_3_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_3_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_4_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_4_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_4_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_4_angle[grupa_ustavok])

    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][grupa_ustavok])
      {
        if((offset-grupa_offset*grupa_ustavok)&1)
        {
          //мл регистр
          (*editValue) = value*multer;
          goto m1;
        }//if(offset&1)
        else
        {
          //ст регистр
          switch(edition_settings.ctrl_UP_input[item])
          {
          case UP_CTRL_P:
          case UP_CTRL_Q:
          case UP_CTRL_S:
            (*editValue)  &= 0xffff;
            (*editValue)  |= ((value & 0xffff)<<16);//
            goto m1;
          default:
            goto m1;
          }//switch
        }//else
      }//if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][grupa_ustavok])
    }//for(int item=0; item<NUMBER_UP; item++)

    (*editValue) = value*multer;

m1:
    grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);
    ustFunc000(-offset +adresGruppa, grupa_ustavok, &multer, value*multer, &editValue);
  }//for


//ОСОБАЯ ПРОВЕРКА
  int item=0;
  int temp1=0;

  for(; item<NUMBER_UP; item++)
  {
    temp1=edition_settings.setpoint_UP[item][0][grupa_ustavok];
    switch(edition_settings.ctrl_UP_input[item])
    {
    case UP_CTRL_P:
    case UP_CTRL_Q:
      if(temp1<0) temp1 = -temp1;//модуль
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//ошибка валидации
      break;

    case UP_CTRL_S:
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//ошибка валидации
      break;
    }//switch
  }//for(int item=0; item<NUMBER_UP; item++)


  if(flag) upravlSetting = 1;//флаг Setting

  return 0;
}//

int privateUSTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa)
{
  int  grupa_offset=276;
  int  ust_offset=16;
  if(offset>=(ust_offset+grupa_offset*0) && offset<=(ust_offset-1+grupa_offset*1))
  {
    *grupa_ustavok=0;
    *adresGruppa=0;
  }//if
  else if(offset>=(ust_offset+grupa_offset*1) && offset<=(ust_offset-1+grupa_offset*2))
  {
    *grupa_ustavok=1;
    *adresGruppa=grupa_offset*1;
  }//if
  else if(offset>=(ust_offset+grupa_offset*2) && offset<=(ust_offset-1+grupa_offset*3))
  {
    *grupa_ustavok=2;
    *adresGruppa=grupa_offset*2;
  }//if
  else if(offset>=(ust_offset+grupa_offset*3) && offset<=(ust_offset-1+grupa_offset*4))
  {
    *grupa_ustavok=3;
    *adresGruppa=grupa_offset*3;
  }//if
  return grupa_offset;
}//grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa)


