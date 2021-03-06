#ifndef __CONST_MENU_P_3U0__
#define __CONST_MENU_P_3U0__

#define EKRAN_SETPOINT_P_3U0_GROUP1    (EKRAN_SETPOINT_MTZ_GROUP4 + 1)
#define EKRAN_SETPOINT_P_3U0_GROUP2    (EKRAN_SETPOINT_P_3U0_GROUP1 + 1)
#define EKRAN_SETPOINT_P_3U0_GROUP3    (EKRAN_SETPOINT_P_3U0_GROUP2 + 1)
#define EKRAN_SETPOINT_P_3U0_GROUP4    (EKRAN_SETPOINT_P_3U0_GROUP3 + 1)
#define EKRAN_TIMEOUT_P_3U0_GROUP1     (EKRAN_TIMEOUT_MTZ_GROUP4 + 1)
#define EKRAN_TIMEOUT_P_3U0_GROUP2     (EKRAN_TIMEOUT_P_3U0_GROUP1 + 1)
#define EKRAN_TIMEOUT_P_3U0_GROUP3     (EKRAN_TIMEOUT_P_3U0_GROUP2 + 1)
#define EKRAN_TIMEOUT_P_3U0_GROUP4     (EKRAN_TIMEOUT_P_3U0_GROUP3 + 1)
#define EKRAN_CONTROL_P_3U0            (EKRAN_CONTROL_MTZ + 1)


#define MAX_ROW_FOR_SETPOINT_P_3U0    1
#define MAX_ROW_FOR_TIMEOUT_P_3U0     1
#define MAX_ROW_FOR_CONTROL_P_3U0     1

#define INDEX_ML_STP_P_3U0        0

#define INDEX_ML_TMO_P_3U0        0

#define COL_SETPOINT_P_3U0_BEGIN 3
#define COL_SETPOINT_P_3U0_COMMA 6
#define COL_SETPOINT_P_3U0_END   8

#define COL_TMO_P_3U0_BEGIN      4
#define COL_TMO_P_3U0_COMMA      6
#define COL_TMO_P_3U0_END        8

#define INDEX_ML_CTR_P_3U0_STATE      0
#define CTR_P_3U0_STATE               (1 << INDEX_ML_CTR_P_3U0_STATE)   

#define CTR_P_3U0_MASKA              (CTR_P_3U0_STATE)


#endif
