void dp1(unsigned int *p_active_functions, unsigned int number_group_stp);
void dp2(unsigned int *p_active_functions, unsigned int number_group_stp);

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void ozt_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ---------------- dz      -------------------------
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
char ozt1_po_Id = 0;
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dp1(unsigned int *p_active_functions, unsigned int number_group_stp){
// ---------------- dz      -------------------------
 

register long lV; 
struct{
long lSP_a,lSP_2g,lSP_5g, lgdI;
long lgdI_hysteresis;
long conter_and;
__SETTINGS *p_current_settings_prt;
}sLV; 
  unsigned long u32_bit_holder = 0;
   sLV.conter_and = 0;
  sLV.p_current_settings_prt = &current_settings_prt;
     //ДВ
  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_OZT1);
  register long lAnd = 0;
  if(lV == 0)
    lAnd |= 1;
   lV = (sLV.p_current_settings_prt->control_ozt & CTR_OZT_1) ;
  if(lV != 0)
  lAnd |= 2;
  if(lAnd == 3){
    sLV.conter_and++;
    }
    if((sLV.p_current_settings_prt->control_ozt) & (CTR_OZT_1_G) != 0){
        //-----------Calc PickUP         --------------
        //Select Max Value
        if( measurement[IM_gdIA] > measurement[IM_gdIB] )
            lV = measurement[IM_gdIA];
        else
            lV = measurement[IM_gdIB];
        if (lV < (long)measurement[IM_gdIC] )
            lV = measurement[IM_gdIC];
        sLV.lgdI = lV;  
        //............................. 
        //Select diapason
        //--
		
        if((unsigned long)lV <= sLV.p_current_settings_prt->pickup_ozt_Ig0[number_group_stp]){
            //Check Stp
            if(ozt1_po_Id){
                lV = sLV.lgdI_hysteresis = sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp]
				+ sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
				lV *= (sLV.p_current_settings_prt->pickup_ozt_kp[number_group_stp]);
				lV /=100;
            }else{
                lV = sLV.lgdI_hysteresis = sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp];
				lV += sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
            }
            if(     (measurement[IM_dIA] >= (unsigned long) lV)
                ||  (measurement[IM_dIB] >= (unsigned long) lV)
                ||  (measurement[IM_dIC] >= (unsigned long) lV) )
                ozt1_po_Id = 1;
            else
                ozt1_po_Id = 0;
            
        }else
        if((unsigned long)lV <= sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp]){
            //Ід спр = Ідо+kг 2×(Ігальм – Іго );
            sLV.lgdI_hysteresis =  sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp]
			+ sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
			
            lV = (sLV.lgdI - sLV.p_current_settings_prt->pickup_ozt_Ig0[number_group_stp])
			*sLV.p_current_settings_prt->pickup_ozt_Kg1[number_group_stp];
            lV /= 1000;
            sLV.lgdI_hysteresis += lV;
            ;//Check Stp
            if(ozt1_po_Id){
            lV = sLV.p_current_settings_prt->pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
            lV = sLV.lgdI_hysteresis;
            if(     (measurement[IM_dIA] >= (unsigned long)lV)
                ||  (measurement[IM_dIB] >= (unsigned long)lV)
                ||  (measurement[IM_dIC] >= (unsigned long)lV) )
                ozt1_po_Id = 1;
            else
                ozt1_po_Id = 0;
        }else{
            ;////Ід спр = Ідо+kг 2×(Ігальм – Іго обм);
            sLV.lgdI_hysteresis =  sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp]
			+ sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
            lV = (sLV.lgdI - sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp])
			*sLV.p_current_settings_prt->pickup_ozt_Kg2[number_group_stp];
            lV /= 1000;
            sLV.lgdI_hysteresis += lV;
            ;//Check Stp
            if(ozt1_po_Id){
            lV = sLV.p_current_settings_prt->pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
            lV = sLV.lgdI_hysteresis;
            if(     (measurement[IM_dIA] >= (unsigned long) lV)
                ||  (measurement[IM_dIB] >= (unsigned long) lV)
                ||  (measurement[IM_dIC] >= (unsigned long) lV) )
                ozt1_po_Id = 1;
            else
                ozt1_po_Id = 0;   
        }
    }else{
        //Check Clipping Stp
        sLV.lgdI_hysteresis =  sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp]
		+ sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
        if(ozt1_po_Id){
        //Ід спр = Ідо
            lV = current_settings_prt.pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
        lV = sLV.lgdI_hysteresis;
        if(     (measurement[IM_dIA] >= (unsigned long) lV)
            ||  (measurement[IM_dIB] >= (unsigned long) lV)
            ||  (measurement[IM_dIC] >= (unsigned long) lV) )
            ozt1_po_Id = 1;
        else
            ozt1_po_Id = 0;
    }   
 
  //
  lV = ozt1_po_Id;
  lV += sLV.conter_and;
  //ПО 
  if (lV == 2){
    _SET_BIT(p_active_functions, RANG_PO_OZT1);
    u32_bit_holder |= 1 << OZT1_PICKUP_STATE_BIT;
   }   
  else{
    _CLEAR_BIT(p_active_functions, RANG_PO_OZT1);
    
}
     //ДВ
//  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_OZT1) != 0);
//  u32_bit_holder |= lV << OZT1_DV_BLOCK_CMD_BIT;
//  u32_bit_holder |= (!lV)<< OZT1_DV_BLOCK_INVERSE_CMD_BIT;//_INVERTOR(tmp_value, 6, tmp_value, 6);
//  lV = ((current_settings_prt.control_ozt & CTR_OZT_1) != 0);
//  u32_bit_holder |= lV << OZT1_MENU_STATE_BIT; 
//  
//  lV = wrp.bool_vars.dfrp1_is_larger_than_dI&&
//  (u32_bit_holder&( (1<< OZT1_MENU_STATE_BIT) | (1<< OZT1_DV_BLOCK_INVERSE_CMD_BIT) ) );
//  u32_bit_holder |= lV << OZT1_PICKUP_STATE_BIT;
  //ПО 
//  if (lV)
//    _SET_BIT(p_active_functions, RANG_PO_OZT1);
//  else
//    _CLEAR_BIT(p_active_functions, RANG_PO_OZT1);
  
  _TIMER_T_0(INDEX_TIMER_OZT1, current_settings_prt.timeout_ozt1[number_group_stp],
  u32_bit_holder, OZT1_PICKUP_STATE_BIT, u32_bit_holder, OZT1_TMR_STATE_BIT);
  
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
OZT2_PICKUP_ID,
OZT2__TIMER_0_T_IN,
OZT2__TIMER_0_T_OUT,


OZT2_PICKUP_IDA_BIT,

OZT2_PICKUP_STATE_BIT,
OZT2_TMR_STATE_BIT,
TOTAL_OZT2_BITS
//LU_GEN_OP_EV_FIX_IBUS
};

union { 
   struct {
      unsigned int po_Id_a  : 1;  //1
      unsigned int po_Id_2g : 1;  //2
      unsigned int po_Id_5g : 1;  //3
      unsigned int po_Id : 1; //4
//      unsigned int po_Id : 1; //5
//      unsigned int po_Id : 1; //6
//      unsigned int po_ : 1; //7
//      unsigned int po_ : 1; //8
//      unsigned int po_ : 1; //9
    } bool_val;
    long lVl;
} ozt_stp_state;
//ozt_stp_state.bool_vars.po_Id_aA  = ;po_Id_aA 

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dp2(unsigned int *p_active_functions, unsigned int number_group_stp){

// ---------------- dz      -------------------------
 
  
//register union { 
//   struct {
//    unsigned int po_Id_a  : 1;  //
//    unsigned int po_Id_2g : 1;  //
//    unsigned int po_Id_5g : 1;  //
//    unsigned int po_Id_a__inv : 1;  //
//    unsigned int po_Id_2g_inv : 1;  //
//    unsigned int po_Id_5g_inv : 1;  //
//    unsigned int state_po_dfrp2 : 1;
//  unsigned int dfrp2_is_larger_than_dI:1;
//   } bool_vars;
//  long lVl;
//}wrp;
register    long lV;
//register void* pv;
struct{
long lSP_a,lSP_2g,lSP_5g, lgdI;
long lgdI_hysteresis;
long conter_and;
__SETTINGS *p_current_settings_prt;
}sLV; 
  unsigned long u32_bit_holder = 0;
   sLV.conter_and = 0;//wrp.lVl = 0;
//   pv = (void*)&current_settings_prt;
    sLV.p_current_settings_prt = &current_settings_prt;
  //Check pickUP Id_a
    //lV = _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_OZT2) );
    // wrp.bool_vars.po_Id_a = lV;
    //if((lV == 0 ){
    if(ozt_stp_state.bool_val.po_Id_a == 0 ){
      lV = sLV.lSP_a = sLV.p_current_settings_prt->pickup_ozt_K_aI[number_group_stp];
    }else{
      lV = sLV.lSP_a = sLV.p_current_settings_prt->pickup_ozt_K_aI[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    ozt_stp_state.bool_val.po_Id_a = 
       (measurement[IM_adIA] >= (unsigned long)lV)
    || (measurement[IM_adIB] >= (unsigned long)lV)
    || (measurement[IM_adIC] >= (unsigned long)lV);
    lV = ozt_stp_state.bool_val.po_Id_a;
    u32_bit_holder |= lV << OZT2__TIMER_0_T_IN;
    //_index_timer,_max_count,_input, _input_bit,  _output, _output_bit
    _TIMER_0_T( INDEX_TIMER_OZT_AB, current_settings_prt.timeout_ozt2_a_blk[number_group_stp],
    u32_bit_holder,OZT2__TIMER_0_T_IN,u32_bit_holder,OZT2__TIMER_0_T_OUT);
    
    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_A_OZT2);
    long lAnd = 0;
    if(lV != 0)
        lAnd |= 1;
    lV = current_settings_prt.control_ozt&CTR_OZT_2_BLK_A;
    if(lV != 0)
        lAnd |= 2;
    if(u32_bit_holder&(1<<OZT2__TIMER_0_T_OUT))
        lAnd |= 4;
    if(lAnd == 7){
        //wrp.bool_vars.po_Id_a = 1;
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_OZT2);
        
    }   
    else {//wrp.bool_vars.po_Id_a = 0;
        //wrp.bool_vars.po_Id_a__inv = 1;
         _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_OZT2);
         sLV.conter_and++;
    }
  //Check pickUP Id_2g
    //lV =   previous_state_po_ = _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_2G_OZT2);
    // wrp.bool_vars.lSP_2g = lV;
    //  if(lV == 0 ){
    if(ozt_stp_state.bool_val.po_Id_2g == 0 ){
       sLV.lSP_2g = current_settings_prt.pickup_ozt_K_2I[number_group_stp];
    }else{
      sLV.lSP_2g  = current_settings_prt.pickup_ozt_K_2I[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    ozt_stp_state.bool_val.po_Id_2g = 
       (measurement[IM_2dIA] >= (unsigned long)lV)
    || (measurement[IM_2dIB] >= (unsigned long)lV)
    || (measurement[IM_2dIC] >= (unsigned long)lV);
    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_2G_OZT2);
    lAnd = 0;
    if(lV != 0)
        lAnd |= 1;
    lV = current_settings_prt.control_ozt&CTR_OZT_2_BLK_2G;
    if(lV != 0)
        lAnd |= 2;
    if(ozt_stp_state.bool_val.po_Id_2g)
        lAnd |= 4;
    if(lAnd == 7){
        //wrp.bool_vars.po_Id_2g = 1;
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_2G_OZT2);
        
    }   
    else {//wrp.bool_vars.po_Id_a = 0;
        //wrp.bool_vars.po_Id_2g_inv = 1;
        sLV.conter_and++;
         _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_2G_OZT2);
    }
    
  //Check pickUP Id_5g
    //lV = _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_5G_OZT2) ;
    // wrp.bool_vars.po_Id_5g = lV; 
    //if(lV == 0 ){
    if(ozt_stp_state.bool_val.po_Id_5g == 0 ){
      sLV.lSP_5g = current_settings_prt.pickup_ozt_K_5I[number_group_stp];
    }else{
      sLV.lSP_5g = current_settings_prt.pickup_ozt_K_5I[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    ozt_stp_state.bool_val.po_Id_5g = 
       (measurement[IM_5dIA] >= (unsigned long)lV)
    || (measurement[IM_5dIB] >= (unsigned long)lV)
    || (measurement[IM_5dIC] >= (unsigned long)lV);
    
    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_5G_OZT2);
    lAnd = 0;
    if(lV != 0)
        lAnd |= 1;
    lV = current_settings_prt.control_ozt&CTR_OZT_2_BLK_5G;
    if(lV != 0)
        lAnd |= 2;
    if(ozt_stp_state.bool_val.po_Id_5g)
        lAnd |= 4;
    if(lAnd == 7){
        //wrp.bool_vars.po_Id_5g = 1;
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_5G_OZT2);
        
    }   
    else {//wrp.bool_vars.po_Id_a = 0;
        //wrp.bool_vars.po_Id_5g_inv = 1;
        sLV.conter_and++;
         _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_5G_OZT2);
    }
  
     //ДВ
  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_OZT2);
  lAnd = 0;
  if(lV == 0)
        lAnd |= 1;
   lV = (current_settings_prt.control_ozt & CTR_OZT_2) ;
  if(lV != 0)
  lAnd |= 2;
  if(lAnd == 3){
    sLV.conter_and++;
    }
    if((current_settings_prt.control_ozt & CTR_OZT_2_G) != 0){
        //-----------Calc PickUP         --------------
        //Select Max Value
        if( measurement[IM_gdIA] > measurement[IM_gdIB] )
            lV = measurement[IM_gdIA];
        else
            lV = measurement[IM_gdIB];
        if (lV < (long)measurement[IM_gdIC] )
            lV = measurement[IM_gdIC];
        sLV.lgdI = lV;  
        //............................. 
        //Select diapason
        //--
        if((unsigned long)lV <= sLV.p_current_settings_prt->pickup_ozt_Ig0[number_group_stp]){
            //Check Stp
            if(ozt_stp_state.bool_val.po_Id){
                lV = sLV.lgdI_hysteresis = current_settings_prt.pickup_ozt_Id0[number_group_stp]*current_settings_prt.pickup_ozt_kp[number_group_stp]/100;
            }else{
                lV = sLV.lgdI_hysteresis = current_settings_prt.pickup_ozt_Id0[number_group_stp];
            }
            if(     (measurement[IM_dIA] >= (unsigned long) lV)
                ||  (measurement[IM_dIB] >= (unsigned long) lV)
                ||  (measurement[IM_dIC] >= (unsigned long) lV) )
                ozt_stp_state.bool_val.po_Id = 1;
            else
                ozt_stp_state.bool_val.po_Id = 0;
            
        }else
        if((unsigned long)lV <= sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp]){
            //Ід спр = Ідо+kг 2×(Ігальм – Іго );
            sLV.lgdI_hysteresis =  current_settings_prt.pickup_ozt_Id0[number_group_stp];
            lV = (sLV.lgdI - sLV.p_current_settings_prt->pickup_ozt_Ig0[number_group_stp])*current_settings_prt.pickup_ozt_Kg1[number_group_stp];
            lV /= 1000;
            sLV.lgdI_hysteresis += lV;
            ;//Check Stp
            if(ozt_stp_state.bool_val.po_Id){
            lV = current_settings_prt.pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
            lV = sLV.lgdI_hysteresis;
            if(     (measurement[IM_dIA] >= (unsigned long)lV)
                ||  (measurement[IM_dIB] >= (unsigned long)lV)
                ||  (measurement[IM_dIC] >= (unsigned long)lV) )
                ozt_stp_state.bool_val.po_Id = 1;
            else
                ozt_stp_state.bool_val.po_Id = 0;
        }else{
            ;////Ід спр = Ідо+kг 2×(Ігальм – Іго обм);
            sLV.lgdI_hysteresis =  current_settings_prt.pickup_ozt_Id0[number_group_stp];
            lV = (sLV.lgdI - sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp])*current_settings_prt.pickup_ozt_Kg2[number_group_stp];
            lV /= 1000;
            sLV.lgdI_hysteresis += lV;
            ;//Check Stp
            if(ozt_stp_state.bool_val.po_Id){
            lV = current_settings_prt.pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
            lV = sLV.lgdI_hysteresis;
            if(     (measurement[IM_dIA] >= (unsigned long) lV)
                ||  (measurement[IM_dIB] >= (unsigned long) lV)
                ||  (measurement[IM_dIC] >= (unsigned long) lV) )
                ozt_stp_state.bool_val.po_Id = 1;
            else
                ozt_stp_state.bool_val.po_Id = 0;   
        }
    }else{
        //Check Clipping Stp
        sLV.lgdI_hysteresis =  current_settings_prt.pickup_ozt_Id0[number_group_stp];
        if(ozt_stp_state.bool_val.po_Id){
        //Ід спр = Ідо
            lV = current_settings_prt.pickup_ozt_kp[number_group_stp]*sLV.lgdI_hysteresis;
                sLV.lgdI_hysteresis = lV/100;
            }
            lV = sLV.lgdI_hysteresis;
            if(     (measurement[IM_dIA] >= (unsigned long) lV)
                ||  (measurement[IM_dIB] >= (unsigned long) lV)
                ||  (measurement[IM_dIC] >= (unsigned long) lV) )
                ozt_stp_state.bool_val.po_Id = 1;
            else
                ozt_stp_state.bool_val.po_Id = 0;
    }   
 
  //
  lV = ozt_stp_state.bool_val.po_Id;
  lV += sLV.conter_and;
  //ПО 
  if (lV == 5){
    _SET_BIT(p_active_functions, RANG_PO_OZT2);
    u32_bit_holder |= 1 << OZT2_PICKUP_STATE_BIT;
   }   
  else{
    _CLEAR_BIT(p_active_functions, RANG_PO_OZT2);
    
}
  
  _TIMER_T_0(INDEX_TIMER_OZT2, current_settings_prt.timeout_ozt2[number_group_stp],
  u32_bit_holder, OZT2_PICKUP_STATE_BIT, u32_bit_holder, OZT2_TMR_STATE_BIT);
  
  //Сраб. 
  if ( u32_bit_holder&(1<<OZT2_TMR_STATE_BIT ) )
    _SET_BIT(p_active_functions, RANG_OZT2);
  else
    _CLEAR_BIT(p_active_functions, RANG_OZT2);

}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Bvhs_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Bvls_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````


