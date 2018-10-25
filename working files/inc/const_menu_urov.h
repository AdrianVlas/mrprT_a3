#ifndef __CONST_MENU_UROV__
#define __CONST_MENU_UROV__

#define EKRAN_SETPOINT_UROV1_GROUP1 (EKRAN_SETPOINT_TZNP_GROUP4  + 1)
#define EKRAN_SETPOINT_UROV1_GROUP2 (EKRAN_SETPOINT_UROV1_GROUP1 + 1)
#define EKRAN_SETPOINT_UROV1_GROUP3 (EKRAN_SETPOINT_UROV1_GROUP2 + 1)
#define EKRAN_SETPOINT_UROV1_GROUP4 (EKRAN_SETPOINT_UROV1_GROUP3 + 1)
#define EKRAN_TIMEOUT_UROV1_GROUP1  (EKRAN_TIMEOUT_TZNP_GROUP4   + 1)
#define EKRAN_TIMEOUT_UROV1_GROUP2  (EKRAN_TIMEOUT_UROV1_GROUP1  + 1)
#define EKRAN_TIMEOUT_UROV1_GROUP3  (EKRAN_TIMEOUT_UROV1_GROUP2  + 1)
#define EKRAN_TIMEOUT_UROV1_GROUP4  (EKRAN_TIMEOUT_UROV1_GROUP3  + 1)
#define EKRAN_CONTROL_UROV1         (EKRAN_CONTROL_TZNP          + 1)

#define EKRAN_SETPOINT_UROV2_GROUP1 (EKRAN_SETPOINT_UROV1_GROUP4 + 1)
#define EKRAN_SETPOINT_UROV2_GROUP2 (EKRAN_SETPOINT_UROV2_GROUP1 + 1)
#define EKRAN_SETPOINT_UROV2_GROUP3 (EKRAN_SETPOINT_UROV2_GROUP2 + 1)
#define EKRAN_SETPOINT_UROV2_GROUP4 (EKRAN_SETPOINT_UROV2_GROUP3 + 1)
#define EKRAN_TIMEOUT_UROV2_GROUP1  (EKRAN_TIMEOUT_UROV1_GROUP4  + 1)
#define EKRAN_TIMEOUT_UROV2_GROUP2  (EKRAN_TIMEOUT_UROV2_GROUP1  + 1)
#define EKRAN_TIMEOUT_UROV2_GROUP3  (EKRAN_TIMEOUT_UROV2_GROUP2  + 1)
#define EKRAN_TIMEOUT_UROV2_GROUP4  (EKRAN_TIMEOUT_UROV2_GROUP3  + 1)
#define EKRAN_CONTROL_UROV2         (EKRAN_CONTROL_UROV1         + 1)

#define MAX_ROW_FOR_SETPOINT_UROV  1
#define MAX_ROW_FOR_TIMEOUT_UROV   2

#define INDEX_ML_TMOUROV1          0
#define INDEX_ML_TMOUROV2          1

#define COL_SETPOINT_UROV_BEGIN    5
#define COL_SETPOINT_UROV_COMMA    6
#define COL_SETPOINT_UROV_END      8

#define COL_TMO_UROV_1_BEGIN       4
#define COL_TMO_UROV_1_COMMA       6
#define COL_TMO_UROV_1_END         8

#define COL_TMO_UROV_2_BEGIN       4
#define COL_TMO_UROV_2_COMMA       6
#define COL_TMO_UROV_2_END         8


enum _index_ml_ctrl_UROV
{
  INDEX_ML_CTRUROV_STATE = 0,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ1,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ2,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ3,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ4,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ04_1,
  INDEX_ML_CTRUROV_STARTED_FROM_MTZ04_2,
  INDEX_ML_CTRUROV_STARTED_FROM_ZDZ,
  INDEX_ML_CTRUROV_STARTED_FROM_3I0,
  INDEX_ML_CTRUROV_STARTED_FROM_3U0,
  INDEX_ML_CTRUROV_STARTED_FROM_NZZ,
  INDEX_ML_CTRUROV_STARTED_FROM_TZNP1,
  INDEX_ML_CTRUROV_STARTED_FROM_TZNP2,
  INDEX_ML_CTRUROV_STARTED_FROM_TZNP3,
  INDEX_ML_CTRUROV_STARTED_FROM_ZOP1,
  INDEX_ML_CTRUROV_STARTED_FROM_UMIN1,
  INDEX_ML_CTRUROV_STARTED_FROM_UMIN2,
  INDEX_ML_CTRUROV_STARTED_FROM_UMAX1,
  INDEX_ML_CTRUROV_STARTED_FROM_UMAX2,
  INDEX_ML_CTRUROV_STARTED_FROM_ACHR1,
  INDEX_ML_CTRUROV_STARTED_FROM_ACHR2,
  INDEX_ML_CTRUROV_STARTED_FROM_UP1,

  MAX_ROW_FOR_CONTROL_UROV = (INDEX_ML_CTRUROV_STARTED_FROM_UP1 + NUMBER_UP)
};

#define CTR_UROV_MASKA                    (MASKA_FOR_BIT(MAX_ROW_FOR_CONTROL_UROV) - 1)

#endif
