#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 10300
//�������� ������� � ����� ������
#define END_ADR_REGISTER 11559

int privateUSTBigGetReg2(int adrReg);

int getUSTBigModbusRegister(int);//�������� ���������� ��������
int getUSTBigModbusBit(int);//�������� ���������� ����
int setUSTBigModbusRegister(int, int);//�������� ���������� ��������
int setUSTBigModbusBit(int, int);//�������� ���������� ����

void setUSTBigCountObject(void);//�������� �-�� �������
void preUSTBigReadAction(void);//action �� ������
void preUSTBigWriteAction(void);//action �� ������
int  postUSTBigWriteAction(void);//action ����� ������
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

//IF ������� 07-14

  case 15:
    (*editValue) = (uint32_t*)&edition_settings.type_con_ozt;
    (*multer) = 1;
    if(!(regUst==0 || regUst==1 || regUst==11)) diapazon=0;
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


//IF ������� 227-258

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
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_aI_kp[gruppa];
    if(regUst<PICKUP_OZT_A_KP_MIN || regUst>PICKUP_OZT_A_KP_MAX) diapazon=0;
    break;
  case 274:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_2I_kp[gruppa];
    if(regUst<PICKUP_OZT_2I_KP_MIN || regUst>PICKUP_OZT_2I_KP_MAX) diapazon=0;
    break;
  case 275:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_ozt_5I_kp[gruppa];
    if(regUst<PICKUP_OZT_5I_KP_MIN || regUst>PICKUP_OZT_5I_KP_MAX) diapazon=0;
    break;

  case 276:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP1[gruppa];
    if(regUst<TIMEOUT_GP1_MIN/10 || regUst>TIMEOUT_GP1_MAX/10) diapazon=0;
    break;
  case 277:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP2[gruppa];
    if(regUst<TIMEOUT_GP2_MIN/10 || regUst>TIMEOUT_GP2_MAX/10) diapazon=0;
    break;
  case 278:
    (*editValue) = (uint32_t*)&edition_settings.timeout_GP_RPN[gruppa];
    if(regUst<TIMEOUT_GP_RPN_MIN/10 || regUst>TIMEOUT_GP_RPN_MAX/10) diapazon=0;
    break;

  case 279:
    (*editValue) = (uint32_t*)&edition_settings.timeout_TP[gruppa];
    if(regUst<TIMEOUT_TP_MIN/10 || regUst>TIMEOUT_TP_MAX/10) diapazon=0;
    break;

  case 280:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_kz_zv[gruppa];
    if(regUst<SETPOINT_KZ_ZV_MIN || regUst>SETPOINT_KZ_ZV_MAX) diapazon=0;
    break;
  case 281:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_kz_zv_angle[gruppa];
    if(regUst<SETPOINT_KZ_ZV_ANGLE_MIN || regUst>SETPOINT_KZ_ZV_ANGLE_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1166:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TVoltage;
    if(regUst<KOEF_TN_MIN || regUst>KOEF_TN_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1168:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TCurrent_H;
    if(regUst<KOEF_TT_H_MIN || regUst>KOEF_TT_H_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1171:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TCurrent_L;
    if(regUst<KOEF_TT_L_MIN || regUst>KOEF_TT_L_MAX) diapazon=0;
    break;
  case 1172:
    (*editValue) = (uint32_t*)&edition_settings.pickup_vyr_H;
    if(regUst<PICKUP_VYR_H_MIN/10 || regUst>PICKUP_VYR_H_MAX/10) diapazon=0;
    break;
  case 1173:
    (*editValue) = (uint32_t*)&edition_settings.pickup_vyr_L;
    if(regUst<PICKUP_VYR_L_MIN/10 || regUst>PICKUP_VYR_L_MAX/10) diapazon=0;
    break;

  case 1174:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_udl_blk_on[0];
    if(regUst<TIMEOUT_SWCH_UDL_BLK_ON_MIN/10 || regUst>TIMEOUT_SWCH_UDL_BLK_ON_MAX/10) diapazon=0;
    break;
  case 1175:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_on[0];
    if(regUst<TIMEOUT_SWCH_ON_MIN/10 || regUst>TIMEOUT_SWCH_ON_MAX/10) diapazon=0;
    break;
  case 1176:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_off[0];
    if(regUst<TIMEOUT_SWCH_OFF_MIN/10 || regUst>TIMEOUT_SWCH_OFF_MAX/10) diapazon=0;
    break;
  case 1177:
    (*editValue) = (uint32_t*)&edition_settings.timeout_pryvoda_VV[0];
    if(regUst<TIMEOUT_PRYVODA_VV_MIN/10 || regUst>TIMEOUT_PRYVODA_VV_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1190:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_udl_blk_on[1];
    if(regUst<TIMEOUT_SWCH_UDL_BLK_ON_MIN/10 || regUst>TIMEOUT_SWCH_UDL_BLK_ON_MAX/10) diapazon=0;
    break;
  case 1191:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_on[1];
    if(regUst<TIMEOUT_SWCH_ON_MIN/10 || regUst>TIMEOUT_SWCH_ON_MAX/10) diapazon=0;
    break;
  case 1192:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_off[1];
    if(regUst<TIMEOUT_SWCH_OFF_MIN/10 || regUst>TIMEOUT_SWCH_OFF_MAX/10) diapazon=0;
    break;
  case 1193:
    (*editValue) = (uint32_t*)&edition_settings.timeout_pryvoda_VV[1];
    if(regUst<TIMEOUT_PRYVODA_VV_MIN/10 || regUst>TIMEOUT_PRYVODA_VV_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1210:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input_signal;
    break;

//  count_bit = 9;
  case 1212:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input;
    break;

//  count_bit = 9;
  case 1214:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output;
    break;
  case 1215:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output_modif;
    break;
  case 1216:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_df;
    if(regUst&(~(0xFF))) diapazon=0;
    break;
#define MARKER1217  1217
  case MARKER1217:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    break;
  case 1218:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    if(regUst&(~(0x1))) diapazon=0;
    break;
  case 1219:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.buttons_mode;
    if(regUst&(~(0xFFF))) diapazon=0;
    for(int bit=0; bit<NUMBER_DEFINED_BUTTONS; bit++)
    {
      if((regUst&(3<<(bit*2)))==(0x2<<(bit*2))) diapazon=0;
      if((regUst&(3<<(bit*2)))==(0x3<<(bit*2))) diapazon=0;
    }//for
    //���� ������ ���������� � ��� ������� ����� � ��������� ������ � ���������� ��
    if(actControl)
    {
      action_during_changing_button_mode(&current_settings_interfaces, &edition_settings);
      //���������� �� ��
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

//IF ������� 1220-1235
//IF ������� 1240-1247
//IF ������� 1250-1257

  }//switch

  if(inOffset>=7 && inOffset<15)
  {
    //��
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

//IF ������� 227-258
  if(inOffset>=227 && inOffset<259)
  {
    //��
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
          if(regUst!=0) diapazon=0;//��� �������� ��������
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
          if(regUst!=0) diapazon=0;//��� �������� ��������
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

//IF ������� 1220-1235
    if(inOffset>=1220 && inOffset<1236)
      {
        int item = inOffset-1220;
        (*editValue) = (uint32_t*)&edition_settings.dopusk_dv[item];
        (*multer) = 1;
        if(regUst<KOEF_DOPUSK_DV_POST_MIN || regUst>KOEF_DOPUSK_DV_MAX) diapazon=0;
        if(!((edition_settings.type_of_input_signal)&(1<<item)))
        {
         //������ ��� ���������
         if((regUst%2)!=0) diapazon=0;//������ ������
        }//if
        else
        {
         //������ ��� ���������
         if(regUst<KOEF_DOPUSK_DV_ZMIN_MIN) diapazon=0;//�� ������ 20 ��
         if((regUst%10)!=0) diapazon=0;//������ ������
        }
      }//if(inOffset>=1220 && inOffset<1236)

//IF ������� 1240-1247
  if(inOffset>=1240 && inOffset<1248)
  {
    int item = inOffset-1240;
    (*editValue) = (uint32_t*)&edition_settings.timeout_pause_df[item];
    if(regUst<TIMEOUT_DF_PAUSE_MIN/10 || regUst>TIMEOUT_DF_PAUSE_MAX/10) diapazon=0;
  }//if(inOffset>=1240 && inOffset<1248)

//IF ������� 1250-1257
  if(inOffset>=1250 && inOffset<1258)
  {
    int item = inOffset-1250;
    (*editValue) = (uint32_t*)&edition_settings.timeout_work_df[item];
    if(regUst<TIMEOUT_DF_WORK_MIN/10 || regUst>TIMEOUT_DF_WORK_MAX/10) diapazon=0;
  }//if(inOffset>=1250 && inOffset<1258)

  return diapazon;
} //ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **ustValue, uint32_t **editValue)

/**************************************/
//���������� ���������� UST
/**************************************/
void constructorUSTBigComponent(COMPONENT_OBJ *ustbigcomp)
{
  ustbigcomponent = ustbigcomp;

  ustbigcomponent->getModbusRegister = getUSTBigModbusRegister;//�������� ���������� ��������
  ustbigcomponent->getModbusBit      = getUSTBigModbusBit;//�������� ���������� ����
  ustbigcomponent->setModbusRegister = setUSTBigModbusRegister;//�������� ���������� ��������
  ustbigcomponent->setModbusBit      = setUSTBigModbusBit;//�������� ���������� ����

  ustbigcomponent->preReadAction   = preUSTBigReadAction;//action �� ������
  ustbigcomponent->preWriteAction  = preUSTBigWriteAction;//action �� ������
  ustbigcomponent->postWriteAction = postUSTBigWriteAction;//action ����� ������

  ustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getUSTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//������ �����
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
//B�:0-(Ia+Ib+Ic);1-Ia;2-Ib;3-Ic;4-I1;5-I2;6-I04;7-3I0-1;8-3I0;9-3I0h;10-Ua+Ub+Uc;11-Ua;12-Ub;13-Uc;14-Uab+Ubc+Uca;15-Uab;16-Ubc;
//17-Uca;18-U1;19-U2;20-3U0;21-3U0-1;22-P;23-Q;24-S
//��: 25-(Ia+Ib+Ic);26-Ia;27-Ib;28-Ic;29-I1;30-I2;31-3I0-1
/*
  UP_CTRL_Ia_Ib_Ic_H = _UP_CTRL_MIN, 
  UP_CTRL_Ia_H,                      
  UP_CTRL_Ib_H,                      
  UP_CTRL_Ic_H,                      
  UP_CTRL_I1_H,                      
  UP_CTRL_I2_H,                      
  UP_CTRL_3I0_r_H,                   
  UP_CTRL_Ia_Ib_Ic_L,
  UP_CTRL_Ia_L,
  UP_CTRL_Ib_L,
  UP_CTRL_Ic_L,
  UP_CTRL_I1_L,
  UP_CTRL_I2_L,
  UP_CTRL_3I0_r_L,
  UP_CTRL_Ua_Ub_Uc,
  UP_CTRL_Uab_Ubc_Uca,
  UP_CTRL_Ua,
  UP_CTRL_Uab,
  UP_CTRL_Ub,
  UP_CTRL_Ubc,
  UP_CTRL_Uc,
  UP_CTRL_Uca,
  UP_CTRL_U1,
  UP_CTRL_U2,
  UP_CTRL_3U0,
  UP_CTRL_P,
  UP_CTRL_Q,
  UP_CTRL_S,
*/
  for(int item=0; item<NUMBER_UP; item++)
  {
   if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
   {
//     if((*editValue)>13) *editValue += 3;
     switch(*editValue)
     {
      case UP_CTRL_Ia_Ib_Ic_H:
       *editValue = 0;//(Ia+Ib+Ic)_H
      break;
      case UP_CTRL_Ia_H:
       *editValue = 1;//Ia_H;
      break;
      case UP_CTRL_Ib_H:
       *editValue = 2;//Ib_H;
      break;
      case UP_CTRL_Ic_H:
       *editValue = 3;//Ic_H;
      break;
      case UP_CTRL_I1_H:
       *editValue = 4;//I1_H;
      break;
      case UP_CTRL_I2_H:
       *editValue = 5;//I2_H;
      break;
      case UP_CTRL_3I0_r_H:
       *editValue = 7;//3I0-1_H
      break;

      case UP_CTRL_Ia_Ib_Ic_L:
       *editValue = 25;//(Ia+Ib+Ic)_L
      break;
      case UP_CTRL_Ia_L:
       *editValue = 26;//Ia_L;
      break;
      case UP_CTRL_Ib_L:
       *editValue = 27;//Ib_L;
      break;
      case UP_CTRL_Ic_L:
       *editValue = 28;//Ic_L;
      break;
      case UP_CTRL_I1_L:
       *editValue = 29;//I1_L;
      break;
      case UP_CTRL_I2_L:
       *editValue = 30;//I2_L;
      break;
      case UP_CTRL_3I0_r_L:
       *editValue = 31;//3I0-1_L
      break;

      case UP_CTRL_Ua_Ub_Uc:
       *editValue = 10;//Ua+Ub+Uc
      break;
      case UP_CTRL_Uab_Ubc_Uca:
       *editValue = 14;//Uab+Ubc+Uca
      break;
      case UP_CTRL_Ua:
       *editValue = 11;//Ua
      break;
      case UP_CTRL_Uab:
       *editValue = 15;//Uab
      break;
      case UP_CTRL_Ub:
       *editValue = 12;//Ub
      break;
      case UP_CTRL_Ubc:
       *editValue = 16;//Ubc
      break;
      case UP_CTRL_Uc:
       *editValue = 13;//Uc
      break;
      case UP_CTRL_Uca:
       *editValue = 17;//Uca
      break;
      case UP_CTRL_U1:
       *editValue = 18;//U1
      break;
      case UP_CTRL_U2:
       *editValue = 19;//U2
      break;
      case UP_CTRL_3U0:
       *editValue = 20;//3U0
      break;
      case UP_CTRL_P:
       *editValue = 22;//P
      break;
      case UP_CTRL_Q:
       *editValue = 23;//Q
      break;
      case UP_CTRL_S:
       *editValue = 24;//S
      break;
    }//switch
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
    if(offset==MARKER1217)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
  }//if(editValue == (uint32_t*)&edition_settings.type_of_led)
  if(editValue == (uint32_t*)&edition_settings.type_con_ozt)
  {
   if((*editValue)==2) return 11;
   return (*editValue);
  }

  return ((*editValue)/multer)&0xFFFF;
}//getDOUTBigModbusRegister(int adrReg)
int getUSTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setUSTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//������ �����
  }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(ustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

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
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preUSTBigReadAction(void)
{
//action �� ������
  ustbigcomponent->isActiveActualData = 1;
}//
void preUSTBigWriteAction(void)
{
//action �� ������
  ustbigcomponent->operativMarker[0] = -1;
  ustbigcomponent->operativMarker[1] = -1;//����������� ������
  ustbigcomponent->isActiveActualData = 1;
}//
int postUSTBigWriteAction(void)
{
  extern int upravlSetting;//���� Setting
//action ����� ������
  int beginAdr = ustbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = ustbigcomponent->operativMarker[1];
  int flag=0;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
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

//������ ������
    for(int item=0; item<NUMBER_UP; item++)
    {
     if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
     {
//B�:0-(Ia+Ib+Ic);1-Ia;2-Ib;3-Ic;4-I1;5-I2;6-I04;7-3I0-1;8-3I0;9-3I0h;10-Ua+Ub+Uc;11-Ua;12-Ub;13-Uc;14-Uab+Ubc+Uca;15-Uab;16-Ubc;
//17-Uca;18-U1;19-U2;20-3U0;21-3U0-1;22-P;23-Q;24-S
//��: 25-(Ia+Ib+Ic);26-Ia;27-Ib;28-Ic;29-I1;30-I2;31-3I0-1
/*
  UP_CTRL_Ia_Ib_Ic_H = _UP_CTRL_MIN, 
  UP_CTRL_Ia_H,                      
  UP_CTRL_Ib_H,                      
  UP_CTRL_Ic_H,                      
  UP_CTRL_I1_H,                      
  UP_CTRL_I2_H,                      
  UP_CTRL_3I0_r_H,                   
  UP_CTRL_Ia_Ib_Ic_L,
  UP_CTRL_Ia_L,
  UP_CTRL_Ib_L,
  UP_CTRL_Ic_L,
  UP_CTRL_I1_L,
  UP_CTRL_I2_L,
  UP_CTRL_3I0_r_L,
  UP_CTRL_Ua_Ub_Uc,
  UP_CTRL_Uab_Ubc_Uca,
  UP_CTRL_Ua,
  UP_CTRL_Uab,
  UP_CTRL_Ub,
  UP_CTRL_Ubc,
  UP_CTRL_Uc,
  UP_CTRL_Uca,
  UP_CTRL_U1,
  UP_CTRL_U2,
  UP_CTRL_3U0,
  UP_CTRL_P,
  UP_CTRL_Q,
  UP_CTRL_S,
*/
      if(value>31) return ERROR_VALID2;//������ ���������
     switch(value)
     {
      case 0:
       value = UP_CTRL_Ia_Ib_Ic_H;//(Ia+Ib+Ic)_H
      break;
      case 1:
       value = UP_CTRL_Ia_H;//Ia_H;
      break;
      case 2:
       value = UP_CTRL_Ib_H;//Ib_H;
      break;
      case 3:
       value = UP_CTRL_Ic_H;//Ic_H;
      break;
      case 4:
       value = UP_CTRL_I1_H;//I1_H;
      break;
      case 5:
       value = UP_CTRL_I2_H;//I2_H;
      break;
      case 6:return ERROR_VALID2;//������ ���������
      case 7:
       value = UP_CTRL_3I0_r_H;//3I0-1
      break;
      case 8:
      case 9:
       return ERROR_VALID2;//������ ���������
      case 10:
       value = UP_CTRL_Ua_Ub_Uc;//Ua+Ub+Uc
      break;
      case 11:
       value = UP_CTRL_Ua;//Ua
      break;
      case 12:
       value = UP_CTRL_Ub;//Ub
      break;
      case 13:
       value = UP_CTRL_Uc;//Uc
      break;
      case 14:
       value = UP_CTRL_Uab_Ubc_Uca;//Uab+Ubc+Uca
      break;
      case 15:
       value = UP_CTRL_Uab;//Uab
      break;
      case 16:
       value = UP_CTRL_Ubc;//Ubc
      break;
      case 17:
       value = UP_CTRL_Uca;//Uca
      break;
      case 18:
       value = UP_CTRL_U1;//U1
      break;
      case 19:
       value = UP_CTRL_U2;//U2
      break;
      case 20:return ERROR_VALID2;//������ ���������
      case 21:
       value = UP_CTRL_3U0;//3U0
      break;
      case 22:
       value = UP_CTRL_P;//P
      break;
      case 23:
       value = UP_CTRL_Q;//Q
      break;
      case 24:
       value = UP_CTRL_S;//S
      break;

      case 25:
       value = UP_CTRL_Ia_Ib_Ic_L;//(Ia+Ib+Ic)_L
      break;
      case 26:
       value = UP_CTRL_Ia_L;//Ia_L
      break;
      case 27:
       value = UP_CTRL_Ib_L;//Ib_L
      break;
      case 28:
       value = UP_CTRL_Ic_L;//Ic_L
      break;
      case 29:
       value = UP_CTRL_I1_L;//I1_L
      break;
      case 30:
       value = UP_CTRL_I2_L;//I2_L
      break;
      case 31:
       value = UP_CTRL_3I0_r_L;//3I0_1
      break;
     }//switch
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
      if(offset==MARKER1217)
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
    if(editValue == (uint32_t*)&edition_settings.type_con_ozt)
    {
      (*editValue) = value;
      if(value==11) (*editValue) = 2;
      goto m1;
    }
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
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_4_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_4_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_4_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
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
          //�� �������
          (*editValue) = value*multer;
          goto m1;
        }//if(offset&1)
        else
        {
          //�� �������
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


//������ ��������
  int item=0;
  int temp1=0;

  for(; item<NUMBER_UP; item++)
  {
    temp1=edition_settings.setpoint_UP[item][0][grupa_ustavok];
    switch(edition_settings.ctrl_UP_input[item])
    {
    case UP_CTRL_P:
    case UP_CTRL_Q:
      if(temp1<0) temp1 = -temp1;//������
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//������ ���������
      break;

    case UP_CTRL_S:
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//������ ���������
      break;
    }//switch
  }//for(int item=0; item<NUMBER_UP; item++)


  if(flag) upravlSetting = 1;//���� Setting

  return 0;
}//

int privateUSTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa)
{
  int  grupa_offset=279;
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


