void dp1(unsigned int *p_active_functions, unsigned int number_group_stp);
void dp2(unsigned int *p_active_functions, unsigned int number_group_stp);

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void ozt_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ---------------- dz   	-------------------------
dp1( p_active_functions,number_group_stp);
dp2( p_active_functions,number_group_stp);
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
enum OZT1_BIT_POS { 

OZT1_DV_BLOCK_CMD_BIT  = 1,  
OZT1_DV_BLOCK_INVERSE_CMD_BIT  ,  
OZT1_MENU_STATE_BIT,
OZT1_PICKUP_STATE_BIT,
OZT1_TMR_STATE_BIT,
TOTAL_OZT1_BITS
//LU_GEN_OP_EV_FIX_IBUS
};

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dp1(unsigned int *p_active_functions, unsigned int number_group_stp){
// ---------------- dz   	-------------------------
register unsigned long u32_bit_holder = 0;  
register union { 
   struct {
    //  unsigned int previous_state_po_dfrp1 : 1;
      unsigned int state_po_dfrp1 : 1;
	  unsigned int dfrp1_is_larger_than_dI:1;
   } bool_vars;
  long lVl;
}wrp;
   long lV; 
   wrp.lVl = 0;
  
uint32_t pickup_ozt_Id0;//Уставка Id0 (початкова горизонтальна ділянка)
  pickup_ozt_Id0 = current_settings_prt.pickup_ozt_delta_Id[number_group_stp]+
  current_settings_prt.pickup_ozt_Id0[number_group_stp];

  if((current_settings_prt.control_ozt & CTR_OZT_1_G )){
	//calc setting point
	
  }
  else{
	//direct compare
	
	if(CHECK_SET_BIT(p_active_functions,RANG_PO_OZT1 ) > 0){
		pickup_ozt_Id0 *= current_settings_prt.pickup_ozt_kp;
		pickup_ozt_Id0 /= 100;
	}
  	wrp.bool_vars.dfrp1_is_larger_than_dI = 
	(measurement[IM_dIA] >= pickup_ozt_Id0)
	|| (measurement[IM_dIB] >= pickup_ozt_Id0)
	|| (measurement[IM_dIC] >= pickup_ozt_Id0);

  } 
     //ДВ
  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_OZT1) != 0);
  u32_bit_holder |= lV << OZT1_DV_BLOCK_CMD_BIT;
  u32_bit_holder |= (!lV)<< OZT1_DV_BLOCK_INVERSE_CMD_BIT;//_INVERTOR(tmp_value, 6, tmp_value, 6);
  lV = ((current_settings_prt.control_ozt & CTR_OZT_1) != 0);
  u32_bit_holder |= lV << OZT1_MENU_OZT1_STATE_BIT; 
  
  lV = wrp.bool_vars.dfrp1_is_larger_than_dI&&
  (u32_bit_holder&( (1<< OZT1_MENU_OZT1_STATE_BIT) | (1<< OZT1_DV_BLOCK_INVERSE_CMD_BIT) ) );
  u32_bit_holder |= lV << OZT1_PICKUP_OZT1_STATE_BIT;
  //ПО 
  if (lV)
    _SET_BIT(p_active_functions, RANG_PO_OZT1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_OZT1);
  
  _TIMER_T_0(INDEX_TIMER_OZT1, current_settings_prt.timeout_ozt1[number_group_stp],
  u32_bit_holder, OZT1_PICKUP_OZT1_STATE_BIT, u32_bit_holder, OZT1_TMR_STATE_BIT);
  
  //Сраб. 
  if ( u32_bit_holder&(1<<OZT1_TMR_STATE_BIT ) )
    _SET_BIT(p_active_functions, RANG_OZT1);
  else
    _CLEAR_BIT(p_active_functions, RANG_OZT1);


}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
enum OZT2_BIT_POS { 

OZT2_DV_BLOCK_CMD_BIT  = 1,  
OZT2_DV_BLOCK_INVERSE_CMD_BIT  ,  
OZT2_MENU_STATE_BIT,
OZT2_PICKUP_ID1
OZT2_AND1
OZT2_AND2
OZT2_AND3
OZT2_PICKUP_STATE_BIT,
OZT2_TMR_STATE_BIT,
TOTAL_OZT2_BITS
//LU_GEN_OP_EV_FIX_IBUS
};
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dp2(unsigned int *p_active_functions, unsigned int number_group_stp){

// ---------------- dz   	-------------------------
register unsigned long u32_bit_holder = 0;  
register union { 
   struct {
      unsigned int po_Id_aA : 1;
      unsigned int po_Id_aB : 1;
      unsigned int po_Id_aC : 1;
      unsigned int po_Id_2gA : 1;
      unsigned int po_Id_2gB : 1;
      unsigned int po_Id_2gC : 1;
      unsigned int po_Id_5gA : 1;
      unsigned int po_Id_5gB : 1;
      unsigned int po_Id_5gC : 1;
	  
      unsigned int state_po_dfrp2 : 1;
	  unsigned int dfrp2_is_larger_than_dI:1;
   } bool_vars;
  long lVl;
}wrp;
   long lV; 
   wrp.lVl = 0;
  
uint32_t pickup_ozt_Id0;//Уставка Id0 (початкова горизонтальна ділянка)
  pickup_ozt_Id0 = current_settings_prt.pickup_ozt_delta_Id[number_group_stp];

  if((current_settings_prt.control_ozt & CTR_OZT_2_G )){
	//calc setting point
	
  }
  else{
	//direct compare
	
	if(CHECK_SET_BIT(p_active_functions,RANG_PO_OZT2 ) > 0){
		pickup_ozt_Id0 *= current_settings_prt.pickup_ozt_kp;
		pickup_ozt_Id0 /= 100;
	}
  	wrp.bool_vars.dfrp2_is_larger_than_dI = 
	(measurement[IM_dIA] >= pickup_ozt_Id0)
	|| (measurement[IM_dIB] >= pickup_ozt_Id0)
	|| (measurement[IM_dIC] >= pickup_ozt_Id0);

  }
wrp.bool_vars.po_Id_aA  = ;
wrp.bool_vars.po_Id_aB  = ;
wrp.bool_vars.po_Id_aC  = ;
wrp.bool_vars.po_Id_2gA = ;
wrp.bool_vars.po_Id_2gB = ;
wrp.bool_vars.po_Id_2gC = ;
wrp.bool_vars.po_Id_5gA = ;
wrp.bool_vars.po_Id_5gB = ;
wrp.bool_vars.po_Id_5gC = ;




  
     //ДВ
  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_OZT2) != 0);
  u32_bit_holder |= lV << OZT2_DV_BLOCK_CMD_BIT;
  u32_bit_holder |= (!lV)<< OZT2_DV_BLOCK_INVERSE_CMD_BIT;//_INVERTOR(tmp_value, 6, tmp_value, 6);
  lV = ((current_settings_prt.control_ozt & CTR_OZT_2) != 0);
  u32_bit_holder |= lV << OZT2_MENU_OZT1_STATE_BIT; 
  
  lV = wrp.bool_vars.dfrp2_is_larger_than_dI&&
  (u32_bit_holder&(1<< OZT2_MENU_STATE_BIT) );
  u32_bit_holder |= lV << 
  
  u32_bit_holder |= lV << OZT2_PICKUP_STATE_BIT;
  //ПО 
  if (lV)
    _SET_BIT(p_active_functions, RANG_PO_OZT1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_OZT1);
  
  _TIMER_T_0(INDEX_TIMER_OZT1, current_settings_prt.timeout_ozt1[number_group_stp],
  u32_bit_holder, OZT1_PICKUP_OZT1_STATE_BIT, u32_bit_holder, OZT1_TMR_STATE_BIT);
  
  //Сраб. 
  if ( u32_bit_holder&(1<<OZT1_TMR_STATE_BIT ) )
    _SET_BIT(p_active_functions, RANG_OZT1);
  else
    _CLEAR_BIT(p_active_functions, RANG_OZT1);

}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````


