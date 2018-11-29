#ifndef __CONST_MENU_TRANSFORMATOR__
#define __CONST_MENU_TRANSFORMATOR__

#define EKRAN_TRANSFORMATOR_INFO            (EKRAN_LIST_LEDS_FOR_RANGUVANNJA + 1)
#define EKRAN_TRANSFORMATOR_INFO_SETPOINT   (EKRAN_TRANSFORMATOR_INFO          + 1)
#define EKRAN_TRANSFORMATOR_INFO_CONTROL    (EKRAN_TRANSFORMATOR_INFO_SETPOINT + 1)

enum _index_ml_stp_transformator
{
  INDEX_ML_TT_HV = 0,
  INDEX_ML_TT_LV,
  INDEX_ML_TN,
  INDEX_ML_D_VYR_HV,
  INDEX_ML_D_VYR_LV,
  
  MAX_ROW_FOR_TRANSFORMATOR_INFO_SETPOINT
};

#define COL_TT_HV_BEGIN                     6
#define COL_TT_HV_END                       9

#define COL_TT_LV_BEGIN                     6
#define COL_TT_LV_END                       9

#define COL_TN_BEGIN                        6
#define COL_TN_END                          9

#define COL_SETPOINT_D_VYR_HV_BEGIN                4
#define COL_SETPOINT_D_VYR_HV_COMMA                6
#define COL_SETPOINT_D_VYR_HV_END                  8

#define COL_SETPOINT_D_VYR_LV_BEGIN                4
#define COL_SETPOINT_D_VYR_LV_COMMA                6
#define COL_SETPOINT_D_VYR_LV_END                  8

enum _index_ml_ctrl_transformator
{
  INDEX_ML_CTR_TRANSFORMATOR_VH_VL = 0,
  INDEX_ML_CTR_TRANSFORMATOR_I_VH,
  INDEX_ML_CTR_TRANSFORMATOR_I_VL,
  INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE,
  
  MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL
};

#define CTR_TRANSFORMATOR_MASKA                         (MASKA_FOR_BIT(MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL) - 1)

#endif
