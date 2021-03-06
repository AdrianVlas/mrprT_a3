#ifndef __CONST_MENU_CHOSE_EXTRA_SETTINGS__
#define __CONST_MENU_CHOSE_EXTRA_SETTINGS__

#define EKRAN_CHOSE_EXTRA_SETTINGS        (EKRAN_LEVEL_SET_NEW_PASSWORD1/*EKRAN_LEVEL_SET_NEW_PASSWORD2*/ + 1)

enum _index_ml_ctrlextra_settings_1
{
  INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU,
  INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB,
  INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION,
  
  MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS
};

#define CTR_EXTRA_SETTINGS_1_CTRL_READY_TU               (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU)   
#define CTR_EXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB          (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB)   
#define CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION          (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION)   

#define CTR_EXTRA_SETTINGS_1_MASKA                       (MASKA_FOR_BIT(MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS) - 1)

#endif
