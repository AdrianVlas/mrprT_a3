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


enum _index_ml_ctrozt
{
  INDEX_ML_CTROZT_TYPE_CON = 0,
  
  INDEX_ML_CTROZT_1,
  INDEX_ML_CTROZT_1_G,
  
  INDEX_ML_CTROZT_2,
  INDEX_ML_CTROZT_2_G,
  INDEX_ML_CTROZT_2_BLK_A,
  INDEX_ML_CTROZT_2_BLK_2G,
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
