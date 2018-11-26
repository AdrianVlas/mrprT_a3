
typedef struct Setpoints_tag{

 
}Setpoints;

INDEX_ML_CTR_TRANSFORMATOR_VH_VL //0-VH 1 - VL 
unsigned int voltage = (current_settings.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;

   unsigned int type_voltage = (current_settings.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;
//  CTR_EXTRA_SETTINGS_1_CTRL_VH_VL //0-VH 1 - VL 
	if(type_voltage != 0){
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void p_3U0_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````




struct{
long Ii,Ip;


}sLV;  

register union { 
   struct {
    //  unsigned int previous_state_po_dfrp1 : 1;
      unsigned int state_po_dfrp1 : 1;
      unsigned int dfrp1_is_larger_than_dI:1;
   } bool_vars;
  long lVl;
}wrp;

 
CYCLECOUNTER	631174246	ReadOnly	
631174684
438
CYCLECOUNTER	1659503	ReadOnly	
CYCLECOUNTER	1659861	ReadOnly
358	

 
5.1.  Функції контролю та вимірювання
Пристрій повинен забезпечувати контроль та вимірювання наступних величин:

measurement[IM_UAB] >= 
measurement[IM_UBC] >= 
measurement[IM_UCA] >= 


