
typedef struct Setpoints_tag{

 
}Setpoints;


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

  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_P_3U0) != 0);
  u32_bit_holder |= lV << G3U0_DV_BLOCK_CMD_BIT;
  
unsigned long pick_up_dfrp1 = wrp.bool_vars.previous_state_po_dfrp1 ?
          current_settings_prt.setpoint_P_3U0[number_group_stp] * KOEF_POVERNENNJA_3U0 / 100 :
          current_settings_prt.setpoint_P_3U0[number_group_stp];
		  
measurement[IM_dIA]||
measurement[IM_dIB]||
measurement[IM_dIC]||

pickup_ozt_delta_Id
type_con_ozt
 pickup_ozt_kp



  
 
CYCLECOUNTER	631174246	ReadOnly	
631174684
438
CYCLECOUNTER	1659503	ReadOnly	
CYCLECOUNTER	1659861	ReadOnly
358	

 
5.1.  Функції контролю та вимірювання
Пристрій повинен забезпечувати контроль та вимірювання наступних величин:

po_Id_aA 
po_Id_aB 
po_Id_aC 
po_Id_2gA
po_Id_2gB
po_Id_2gC
po_Id_5gA
po_Id_5gB
po_Id_5gC