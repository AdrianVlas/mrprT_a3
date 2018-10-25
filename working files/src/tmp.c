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

UMIN_DV_BLOCK_CMD_BIT  = 1,  
UMIN_DV_BLOCK_INVERSE_CMD_BIT,
UMIN_MCTR_TRANSFORMATOR_PHASE_LINE_BIT,
UMIN_MCTR_UMIN1_BIT,
UMIN_MCTRLR_PO_UMIN1_OR_AND_BIT,  
UMIN_MCTRLR_UMIN1_UBLK_BIT,  
UMIN_MCTRLR_UMIN1_IBLK_BIT,
  
UMIN_MENU_P_3U0_STATE_BIT,
UMIN_PICKUP_3U0_STATE_BIT,
UMIN_TMR_3U0_STATE_BIT,
TOTAL_UMIN_BITS
//LU_GEN_OP_EV_FIX_IBUS
};
  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_P_3U0) != 0);
  u32_bit_holder |= lV << G3U0_DV_BLOCK_CMD_BIT;
  
IA_AND_IC_IS_SMALLER_THAN_IUST_STATE_BIT,
  UA_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UB_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UC_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UA_OR_UB_OR_UC_IS_SMALLER_THAN_250MV_STATE_BIT, 
  UAB_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UBC_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UCA_IS_SMALLER_THAN_UMIN1_STATE_BIT,      
  UAB_OR_UBC_OR_UCA_IS_SMALLER_THAN_250MV_STATE_BIT,  
  
  