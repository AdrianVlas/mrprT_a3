#ifndef __CONSTANTS_BUTTONS__
#define __CONSTANTS_BUTTONS__

#define EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA        (_NEXT_EKRAN_AFTER_ALL_TF_EKRANS)

#define EKRAN_RANGUVANNJA_BUTTON_1                (EKRAN_LIST_BUTTONS_FOR_RANGUVANNJA + 1)
#define EKRAN_RANGUVANNJA_BUTTON_2                (EKRAN_RANGUVANNJA_BUTTON_1 + 1)
#define EKRAN_RANGUVANNJA_BUTTON_3                (EKRAN_RANGUVANNJA_BUTTON_2 + 1)
#define EKRAN_RANGUVANNJA_BUTTON_4                (EKRAN_RANGUVANNJA_BUTTON_3 + 1)
#define EKRAN_RANGUVANNJA_BUTTON_5                (EKRAN_RANGUVANNJA_BUTTON_4 + 1)
#define EKRAN_RANGUVANNJA_BUTTON_6                (EKRAN_RANGUVANNJA_BUTTON_5 + 1)

#define MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA       NUMBER_DEFINED_BUTTONS
#define MAX_ROW_RANGUVANNJA_BUTTON                 NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL

enum __button_mode
{
  BUTTON_MODE_BUTTON = 0,
  BUTTON_MODE_SWITCHER,
  
  NUMBER_BUTTON_MODE
};

#endif 
