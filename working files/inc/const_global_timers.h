#ifndef __CONST_GLOBAL_TIMERS__
#define __CONST_GLOBAL_TIMERS__

enum _index_timer
{
  INDEX_TIMER_INPUT_START = 0,
  
  INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS),
  
  INDEX_TIMER_DF_PAUSE_START = (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + NUMBER_DEFINED_FUNCTIONS),
    
  INDEX_TIMER_DF_WORK_START = (INDEX_TIMER_DF_PAUSE_START + NUMBER_DEFINED_FUNCTIONS),
  
  INDEX_TIMER_VIDKL_VV_H = (INDEX_TIMER_DF_WORK_START + NUMBER_DEFINED_FUNCTIONS),
  INDEX_TIMER_BLK_VKL_VV_H,
  INDEX_TIMER_VKL_VV_H,
  INDEX_TIMER_PRYVOD_VV_H,
  INDEX_TIMER_VIDKL_VV_L,
  INDEX_TIMER_BLK_VKL_VV_L,
  INDEX_TIMER_VKL_VV_L,
  INDEX_TIMER_PRYVOD_VV_L,

  INDEX_TIMER_OZT1,
  INDEX_TIMER_OZT2,
  INDEX_TIMER_OZT_AB,
  
  INDEX_TIMER_MTZ1,
  INDEX_TIMER_MTZ1_N_VPERED,
  INDEX_TIMER_MTZ1_N_NAZAD,
  INDEX_TIMER_MTZ1_PO_NAPRUZI,
  INDEX_TIMER_MTZ2,
  INDEX_TIMER_MTZ2_DEPENDENT,
  INDEX_TIMER_MTZ2_PR,
  INDEX_TIMER_MTZ2_N_VPERED,
  INDEX_TIMER_MTZ2_N_VPERED_PR,
  INDEX_TIMER_MTZ2_N_NAZAD,
  INDEX_TIMER_MTZ2_N_NAZAD_PR,
  INDEX_TIMER_MTZ2_PO_NAPRUZI,
  INDEX_TIMER_MTZ2_PO_NAPRUZI_PR,
  INDEX_TIMER_MTZ2_VVID_PR,
  INDEX_TIMER_MTZ3,
  INDEX_TIMER_MTZ3_N_VPERED,
  INDEX_TIMER_MTZ3_N_NAZAD,
  INDEX_TIMER_MTZ3_PO_NAPRUZI,
  INDEX_TIMER_MTZ4,
  INDEX_TIMER_MTZ4_N_VPERED,
  INDEX_TIMER_MTZ4_N_NAZAD,
  INDEX_TIMER_MTZ4_PO_NAPRUZI,
  
  INDEX_TIMER_P_3U0,

  INDEX_TIMER_TZNP1_VPERED,
  INDEX_TIMER_TZNP1_NAZAD,
  INDEX_TIMER_TZNP2_VPERED,
  INDEX_TIMER_TZNP2_NAZAD,
  INDEX_TIMER_TZNP3_VPERED,
  INDEX_TIMER_TZNP3_NAZAD,
  INDEX_TIMER_TZNP4_VPERED,
  INDEX_TIMER_TZNP4_NAZAD,
  
  INDEX_TIMER_ZOP1,
  INDEX_TIMER_ZOP2,
  
  INDEX_TIMER_UROV1_1,
  INDEX_TIMER_UROV1_2,
  INDEX_TIMER_UROV2_1,
  INDEX_TIMER_UROV2_2,
  
  INDEX_TIMER_UMIN1,
  INDEX_TIMER_UMIN2,
  
  INDEX_TIMER_UMAX1,
  INDEX_TIMER_UMAX2,
  
  INDEX_TIMER_GZ1_TMP_04,
  INDEX_TIMER_GZ1,
  INDEX_TIMER_GZ2_TMP_04,
  INDEX_TIMER_GZ2,
  INDEX_TIMER_GZ_RPN_TMP_04,
  INDEX_TIMER_GZ_RPN,

  INDEX_TIMER_TZ_TMP_04,
  INDEX_TIMER_TZ,
  
  INDEX_TIMER_UP1,
  
  NEXT_TIMER = (INDEX_TIMER_UP1 + NUMBER_UP)
};

enum _mtz_tmr_const {
  INDEX_TIMER_MTZ = 0,
  INDEX_TIMER_MTZ_N_VPERED,
  INDEX_TIMER_MTZ_N_NAZAD,
  INDEX_TIMER_MTZ_PO_NAPRUZI,
  /*************************************/
  NUMBER_LEVEL_TMR_CONST
};

#define MAX_NUMBER_GLOBAL_TIMERS                               NEXT_TIMER   //����������� ������� �������

#endif
