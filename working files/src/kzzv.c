enum KZZV_BIT_POS { 

KZZV_DV_BLOCK_CMD_BIT  = 1,  
KZZV_DV_BLOCK_INVERSE_CMD_BIT  ,  
KZZV_MENU_P_3U0_STATE_BIT,
KZZV_PICKUP_3U0_STATE_BIT,
KZZV_TMR_3U0_STATE_BIT,
TOTAL_KZZV_BITS
//
};




//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Kz_zv_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name	-------------------------
register unsigned long u32_bit_holder = 0;  
register union { 
   struct {
      unsigned int previous_state_po_3U0_1 : 1;
	  unsigned int KZZV_1r_is_larger_than_3U0_1:1;
   } bool_vars;
  long lVl;
}wrp;
   long lV; 
   wrp.lVl = 0;
	UNUSED(p_active_functions);
	UNUSED(number_group_stp);
	
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
