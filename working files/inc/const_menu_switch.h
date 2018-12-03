#ifndef __CONST_MENU_SWITCH__
#define __CONST_MENU_SWITCH__

#define EKRAN_TIMEOUT_SWITCH_H           (EKRAN_CHOOSE_SETTINGS_SWITCHER_L  + 1)
#define EKRAN_TIMEOUT_SWITCH_L           (EKRAN_TIMEOUT_SWITCH_H  + 1)
#define EKRAN_CONTROL_SWITCH_H           (EKRAN_TIMEOUT_SWITCH_L  + 1)
#define EKRAN_CONTROL_SWITCH_L           (EKRAN_CONTROL_SWITCH_H  + 1)
#define EKRAN_CHOOSE_RANG_SWITCH_H       (EKRAN_CONTROL_SWITCH_L  + 1)
#define EKRAN_CHOOSE_RANG_SWITCH_L       (EKRAN_CHOOSE_RANG_SWITCH_H  + 1)
#define EKRAN_RANGUVANNJA_OFF_CB_H       (EKRAN_CHOOSE_RANG_SWITCH_L + 1) 
#define EKRAN_RANGUVANNJA_OFF_CB_L       (EKRAN_RANGUVANNJA_OFF_CB_H + 1) 
#define EKRAN_RANGUVANNJA_ON_CB_H        (EKRAN_RANGUVANNJA_OFF_CB_L + 1) 
#define EKRAN_RANGUVANNJA_ON_CB_L        (EKRAN_RANGUVANNJA_ON_CB_H + 1) 

#define MAX_ROW_FOR_TIMEOUT_SWITCH        4
#define MAX_ROW_FOR_CONTROL_SWITCH        1
#define MAX_ROW_FOR_RANG_SWITCH           2
#define MAX_ROW_RANGUVANNJA_OFF_CB        NUMBER_TOTAL_SIGNAL_FOR_RANG
#define MAX_ROW_RANGUVANNJA_ON_CB         NUMBER_TOTAL_SIGNAL_FOR_RANG

#define INDEX_ML_TMOON                    0
#define INDEX_ML_TMOOFF                   1
#define INDEX_ML_TMOUDL_BLK_ON            2
#define INDEX_ML_TMOPRYVODA_VV            3

#define COL_TMO_SWCH_ON_BEGIN             5
#define COL_TMO_SWCH_ON_COMMA             6
#define COL_TMO_SWCH_ON_END               8

#define COL_TMO_SWCH_OFF_BEGIN            5
#define COL_TMO_SWCH_OFF_COMMA            6
#define COL_TMO_SWCH_OFF_END              8

#define COL_TMO_SWCH_UDL_BLK_ON_BEGIN     4
#define COL_TMO_SWCH_UDL_BLK_ON_COMMA     6
#define COL_TMO_SWCH_UDL_BLK_ON_END       8

#define COL_TMO_PRYVODA_VV_BEGIN          5
#define COL_TMO_PRYVODA_VV_COMMA          6
#define COL_TMO_PRYVODA_VV_END            8

#define INDEX_ML_CTRPRYVOD_VV             0
#define CTR_PRYVOD_VV                     (1 << INDEX_ML_CTRPRYVOD_VV)          

#define CTR_SWITCH_MASKA                  (                     \
                                            CTR_PRYVOD_VV       \
                                          )

#define INDEX_ML_RANG_OFF_CB              0
#define INDEX_ML_RANG_ON_CB               1

#endif
