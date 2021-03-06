#ifndef __CONST_MENU_ZOP__
#define __CONST_MENU_ZOP__

#define EKRAN_SETPOINT_ZOP_GROUP1 (EKRAN_SETPOINT_UROV2_GROUP4 + 1)
#define EKRAN_SETPOINT_ZOP_GROUP2 (EKRAN_SETPOINT_ZOP_GROUP1 + 1)
#define EKRAN_SETPOINT_ZOP_GROUP3 (EKRAN_SETPOINT_ZOP_GROUP2 + 1)
#define EKRAN_SETPOINT_ZOP_GROUP4 (EKRAN_SETPOINT_ZOP_GROUP3 + 1)
#define EKRAN_TIMEOUT_ZOP_GROUP1  (EKRAN_TIMEOUT_UROV2_GROUP4  + 1)
#define EKRAN_TIMEOUT_ZOP_GROUP2  (EKRAN_TIMEOUT_ZOP_GROUP1  + 1)
#define EKRAN_TIMEOUT_ZOP_GROUP3  (EKRAN_TIMEOUT_ZOP_GROUP2  + 1)
#define EKRAN_TIMEOUT_ZOP_GROUP4  (EKRAN_TIMEOUT_ZOP_GROUP3  + 1)
#define EKRAN_CONTROL_ZOP         (EKRAN_CONTROL_UROV2  + 1)

#define MAX_ROW_FOR_SETPOINT_ZOP  2
#define MAX_ROW_FOR_TIMEOUT_ZOP   2

#define INDEX_ML_STPZOP1    0
#define INDEX_ML_STPZOP2    1

#define COL_SETPOINT_ZOP1_BEGIN    4
#define COL_SETPOINT_ZOP1_COMMA    5
#define COL_SETPOINT_ZOP1_END      8

#define COL_SETPOINT_ZOP2_BEGIN    4
#define COL_SETPOINT_ZOP2_COMMA    5
#define COL_SETPOINT_ZOP2_END      8

#define INDEX_ML_TMOZOP1   0
#define INDEX_ML_TMOZOP2   1

#define COL_TMO_ZOP1_BEGIN         4
#define COL_TMO_ZOP1_COMMA         6
#define COL_TMO_ZOP1_END           8

#define COL_TMO_ZOP2_BEGIN         4
#define COL_TMO_ZOP2_COMMA         6
#define COL_TMO_ZOP2_END           8

enum _index_ml_ctrl_ZOP
{
  INDEX_ML_CTRZOP_1_STATE = 0,
  INDEX_ML_CTRZOP_1_SEL_I,
  INDEX_ML_CTRZOP_2_STATE,
  INDEX_ML_CTRZOP_2_SEL_I,

  MAX_ROW_FOR_CONTROL_ZOP
};


#define CTRZOP_1_STATE            (1 << INDEX_ML_CTRZOP_1_STATE)
#define CTRZOP_1_SEL_I            (1 << INDEX_ML_CTRZOP_1_SEL_I)
#define CTRZOP_2_STATE            (1 << INDEX_ML_CTRZOP_2_STATE)
#define CTRZOP_2_SEL_I            (1 << INDEX_ML_CTRZOP_2_SEL_I)

#define CTR_ZOP_MASKA                   (                 \
                                         CTRZOP_1_STATE  |\
                                         CTRZOP_1_SEL_I  |\
                                         CTRZOP_2_STATE  |\
                                         CTRZOP_2_SEL_I   \
                                        )

#endif
