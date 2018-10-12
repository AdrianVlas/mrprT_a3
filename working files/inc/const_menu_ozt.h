#ifndef __CONST_MENU_OZT__
#define __CONST_MENU_OZT__


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
