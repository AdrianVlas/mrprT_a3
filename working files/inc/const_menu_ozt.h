#ifndef __CONST_MENU_OZT__
#define __CONST_MENU_OZT__

#define EKRAN_SETPOINT_OZT_GROUP1   (EKRAN_CHOSE_SETTINGS + 1)
#define EKRAN_SETPOINT_OZT_GROUP2   (EKRAN_SETPOINT_OZT_GROUP1 + 1)
#define EKRAN_SETPOINT_OZT_GROUP3   (EKRAN_SETPOINT_OZT_GROUP2 + 1)
#define EKRAN_SETPOINT_OZT_GROUP4   (EKRAN_SETPOINT_OZT_GROUP3 + 1)
#define EKRAN_TIMEOUT_OZT_GROUP1    (EKRAN_SETPOINT_UP_GROUP4 + 1)
#define EKRAN_TIMEOUT_OZT_GROUP2    (EKRAN_TIMEOUT_OZT_GROUP1  + 1)
#define EKRAN_TIMEOUT_OZT_GROUP3    (EKRAN_TIMEOUT_OZT_GROUP2  + 1)
#define EKRAN_TIMEOUT_OZT_GROUP4    (EKRAN_TIMEOUT_OZT_GROUP3  + 1)
#define EKRAN_CONTROL_OZT           (EKRAN_TIMEOUT_UP_GROUP4 + 1)

#define MAX_ROW_FOR_SETPOINT_OZT        13
#define MAX_ROW_FOR_TIMEOUT_OZT         3

#define INDEX_ML_D_OZT_BB                0
#define INDEX_ML_D_OZT_BH                1
#define INDEX_ML_D_OZT_ID0               2
#define INDEX_ML_D_OZT_delta             3

#define INDEX_ML_T_OZT_T1                4
#define INDEX_ML_T_OZT_T2                5
#define INDEX_ML_T_OZT_TK                6
#define INDEX_ML_T_OZT_IT0               7
#define INDEX_ML_T_OZT_ITG1              8

#define INDEX_ML_A_OZT_AK               9

#define INDEX_ML_N_OZT_N2G              10
#define INDEX_ML_N_OZT_N5G              11

#define INDEX_ML_K_OZT_KP              12

#define COL_SETPOINT_D_OZT_BB_BEGIN                4
#define COL_SETPOINT_D_OZT_BB_COMMA                6
#define COL_SETPOINT_D_OZT_BB_END                  8

#define COL_SETPOINT_D_OZT_BH_BEGIN                4
#define COL_SETPOINT_D_OZT_BH_COMMA                6
#define COL_SETPOINT_D_OZT_BH_END                  8

#define COL_SETPOINT_D_OZT_ID0_BEGIN               4
#define COL_SETPOINT_D_OZT_ID0_COMMA               6
#define COL_SETPOINT_D_OZT_ID0_END                 8

#define COL_SETPOINT_D_OZT_delta_BEGIN             4
#define COL_SETPOINT_D_OZT_delta_COMMA             6
#define COL_SETPOINT_D_OZT_delta_END               8

#define COL_SETPOINT_T_OZT_T1_BEGIN                5
#define COL_SETPOINT_T_OZT_T1_COMMA                6
#define COL_SETPOINT_T_OZT_T1_END                  9

#define COL_SETPOINT_T_OZT_T2_BEGIN                5
#define COL_SETPOINT_T_OZT_T2_COMMA                6
#define COL_SETPOINT_T_OZT_T2_END                  9

#define COL_SETPOINT_T_OZT_TK_BEGIN                5
#define COL_SETPOINT_T_OZT_TK_COMMA                6
#define COL_SETPOINT_T_OZT_TK_END                  9

#define COL_SETPOINT_T_OZT_IT0_BEGIN               4
#define COL_SETPOINT_T_OZT_IT0_COMMA               6
#define COL_SETPOINT_T_OZT_IT0_END                 8

#define COL_SETPOINT_T_OZT_ITG1_BEGIN              4
#define COL_SETPOINT_T_OZT_ITG1_COMMA              6
#define COL_SETPOINT_T_OZT_ITG1_END                8

#define COL_SETPOINT_T_OZT_ITG2_BEGIN              4
#define COL_SETPOINT_T_OZT_ITG2_COMMA              6
#define COL_SETPOINT_T_OZT_ITG2_END                8

#define COL_SETPOINT_A_OZT_AK_BEGIN                5
#define COL_SETPOINT_A_OZT_AK_COMMA                7
#define COL_SETPOINT_A_OZT_AK_END                  9

#define COL_SETPOINT_N_OZT_N2G_BEGIN               5
#define COL_SETPOINT_N_OZT_N2G_COMMA               6
#define COL_SETPOINT_N_OZT_N2G_END                 8

#define COL_SETPOINT_N_OZT_N5G_BEGIN               5
#define COL_SETPOINT_N_OZT_N5G_COMMA               6
#define COL_SETPOINT_N_OZT_N5G_END                 8

#define COL_SETPOINT_K_OZT_KP_BEGIN                6
#define COL_SETPOINT_K_OZT_KP_COMMA                7
#define COL_SETPOINT_K_OZT_KP_END                  9

#define INDEX_ML_TMOOZT1                0
#define INDEX_ML_TMOOZT2                1
#define INDEX_ML_A_OZT_AB               11

#define COL_TMO_OZT_1_BEGIN                        4
#define COL_TMO_OZT_1_COMMA                        6
#define COL_TMO_OZT_1_END                          8

#define COL_TMO_OZT_2_BEGIN                        4
#define COL_TMO_OZT_2_COMMA                        6
#define COL_TMO_OZT_2_END                          8

#define COL_TMO_A_OZT_AB_BEGIN                     5
#define COL_TMO_A_OZT_AB_COMMA                     6
#define COL_TMO_A_OZT_AB_END                       8


enum _index_ml_ctrozt
{
//Група з'єднань
  INDEX_ML_CTROZT_TYPE_CON = 0,
//1 ступень ОЗТ   
  INDEX_ML_CTROZT_1,
//Торможение 1 ступени ОЗТ   
  INDEX_ML_CTROZT_1_G,
//2 ступень ОЗТ   
  INDEX_ML_CTROZT_2,
//Торможение 2 ступени ОЗТ   
  INDEX_ML_CTROZT_2_G,
//Блокировка апериод   
  INDEX_ML_CTROZT_2_BLK_A,
//Блокировка 2-й гарм
  INDEX_ML_CTROZT_2_BLK_2G,
//Блокировка 5-й гарм
  INDEX_ML_CTROZT_2_BLK_5G,
  
  MAX_ROW_FOR_CONTROL_OZT
};

#define N_BIT_CTROZT_1                          (INDEX_ML_CTROZT_1 - 1)          
#define CTR_OZT_1                               (1 << N_BIT_CTROZT_1)          
#define N_BIT_CTROZT_1_G                        (INDEX_ML_CTROZT_1_G - 1)          
#define CTR_OZT_1_G                             (1 << N_BIT_CTROZT_1_G)          
#define N_BIT_CTROZT_2                          (INDEX_ML_CTROZT_2 - 1)          
#define CTR_OZT_2                               (1 << N_BIT_CTROZT_2)          
#define N_BIT_CTROZT_2_G                        (INDEX_ML_CTROZT_2_G - 1)          
#define CTR_OZT_2_G                             (1 << N_BIT_CTROZT_2_G)          
#define N_BIT_CTROZT_2_BLK_A                    (INDEX_ML_CTROZT_2_BLK_A - 1)          
#define CTR_OZT_2_BLK_A                         (1 << N_BIT_CTROZT_2_BLK_A)          
#define N_BIT_CTROZT_2_BLK_2G                   (INDEX_ML_CTROZT_2_BLK_2G - 1)          
#define CTR_OZT_2_BLK_2G                        (1 << N_BIT_CTROZT_2_BLK_2G)          
#define N_BIT_CTROZT_2_BLK_5G                   (INDEX_ML_CTROZT_2_BLK_5G - 1)          
#define CTR_OZT_2_BLK_5G                        (1 << N_BIT_CTROZT_2_BLK_5G)          


#define CTR_OZT_MASKA                   (                          \
                                         CTR_OZT_1                |\
                                         CTR_OZT_1_G              |\
                                         CTR_OZT_2                |\
                                         CTR_OZT_2_G              |\
                                         CTR_OZT_2_BLK_A          |\
                                         CTR_OZT_2_BLK_2G         |\
                                         CTR_OZT_2_BLK_5G         |\
                                        )

#endif
