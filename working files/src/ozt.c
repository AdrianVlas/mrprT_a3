void dp1(unsigned int *p_active_functions, unsigned int number_group_stp);
void dp2(unsigned int *p_active_functions, unsigned int number_group_stp);
#ifdef DBGMODE 
#include <stdio.h> 

#endif












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
long lgdI_hysteresis,lIdObm;
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
    if(((sLV.p_current_settings_prt->control_ozt) & (CTR_OZT_1_G)) != 0){
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
            ;////Ідоbm = Ідо+kг 1×(Ігальм – Іго обм);
            lV = (sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp] - current_settings_prt.pickup_ozt_Ig0[number_group_stp])*current_settings_prt.pickup_ozt_Kg1[number_group_stp];
            lV /= 1000;
            sLV.lIdObm = current_settings_prt.pickup_ozt_delta_Id[number_group_stp]+current_settings_prt.pickup_ozt_Id0[number_group_stp] + lV;
            ;////Ід спр = Ідоbm+kг 2×(Ігальм – Іго обм);
            sLV.lgdI_hysteresis =  sLV.lIdObm;//sLV.p_current_settings_prt->pickup_ozt_Id0[number_group_stp]
            //+ sLV.p_current_settings_prt->pickup_ozt_delta_Id[number_group_stp];
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
char chGlbDbgFlg = 0;
 char chGlbDbgCtr1a = 0;char chGlbDbgCtr2g = 0;char chGlbDbgCtr5g = 0; 
 char chGlbDbgCmpV1a = 2;char chGlbDbgCmpV2g = 2;char chGlbDbgCmpV5g = 2; 
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
long lgdI_hysteresis,lIdObm;
long conter_and, lCtrStp,lCtrBlock;
char chBlkPhaseA,chBlkPhaseB,chBlkPhaseC;
__SETTINGS *p_current_settings_prt;
}sLV; 
  unsigned long u32_bit_holder = 0;
   sLV.conter_and = 0;//wrp.lVl = 0;
//   
    sLV.p_current_settings_prt = &current_settings_prt;
  //Check pickUP Id_a
    //lV = _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_OZT2) );
    // 
    //if((lV == 0 ){
    sLV.lSP_a = (sLV.p_current_settings_prt)->pickup_ozt_K_aI[number_group_stp];
    if(ozt_stp_state.bool_val.po_Id_a == 0 ){
      lV = 100*10;
      
    }else{
      lV = 1000;//lV = (sLV.p_current_settings_prt->pickup_ozt_aI_kp[number_group_stp])*10;//
      sLV.lSP_a *= (sLV.p_current_settings_prt->pickup_ozt_aI_kp[number_group_stp]);
      sLV.lSP_a /= 100;
    }
    sLV.lCtrStp = 0;sLV.lCtrBlock = 1;//Special case forrr 
    sLV.chBlkPhaseA = sLV.chBlkPhaseB = sLV.chBlkPhaseC = 0;

    if(   measurement[IM_dIA] < 0.05*I_NOM){
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_A);sLV.chBlkPhaseA = 1;
    }
    else{
        if( _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_A) != 0){
            if((measurement[IM_dIA] < 0.0525*I_NOM) ){
            _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_A);sLV.chBlkPhaseA = 1;
            }else{
                _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_A);//sLV.lCtrBlock = 0;
            }
        }else{
            _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_A);//sLV.lCtrBlock = 0;
            }   
    }

    if(   measurement[IM_dIB] < 0.05*I_NOM){
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_B);sLV.chBlkPhaseB = 1;
    }
    else{
        if( _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_B) != 0){
            if((measurement[IM_dIB] < 0.0525*I_NOM) ){
            _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_B);sLV.chBlkPhaseB = 1;
            }else{
                _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_B);//sLV.lCtrBlock = 0;
            }
        }else{
            _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_B);//sLV.lCtrBlock = 0;
            }   
    }

    if(   measurement[IM_dIC] < 0.05*I_NOM){
        _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_C);sLV.chBlkPhaseC = 1;
    }
    else{
        if( _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_C) != 0){
            if((measurement[IM_dIC] < 0.0525*I_NOM) ){
            _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_C);sLV.chBlkPhaseC = 1;
            }else{
                _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_C);//sLV.lCtrBlock = 0;
            }
        }else{
            _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2_C);//sLV.lCtrBlock = 0;
            }   
    }

    if( sLV.chBlkPhaseA == 0){//(measurement[IM_dIA] >= 0.05*I_NOM)
        if( ((measurement[IM_adIA]*lV)/measurement[IM_dIA]) >=  ((unsigned long)sLV.lSP_a))
            sLV.lCtrStp++;//
    }
    
    if( sLV.chBlkPhaseB == 0){//(measurement[IM_dIB] >= 0.05*I_NOM)
        if( ((measurement[IM_adIB]*lV)/measurement[IM_dIB]) >=  ((unsigned long)sLV.lSP_a) )
            sLV.lCtrStp++;//
    }
    if( sLV.chBlkPhaseC == 0){//(measurement[IM_dIC] >= 0.05*I_NOM)
        if( ((measurement[IM_adIC]*lV)/measurement[IM_dIC]) >=  ((unsigned long)sLV.lSP_a))
            sLV.lCtrStp++;//
    }
    //}
    if(sLV.lCtrStp > 0){//<-OR if(sLV.lCtrStp >= 3){<-AND
        ozt_stp_state.bool_val.po_Id_a = 1;
    }
    else{
        if(ozt_stp_state.bool_val.po_Id_a == 1){//dbg Code for find error
            chGlbDbgCtr1a++;                    //dbg Code for find error
            if(chGlbDbgCtr1a>chGlbDbgCmpV1a){   //dbg Code for find error
                chGlbDbgCtr1a = 0;              //dbg Code for find error
            }                                   //dbg Code for find error
        }                                       //dbg Code for find error
        ozt_stp_state.bool_val.po_Id_a = 0;
    }
    //else  ozt_stp_state.bool_val.po_Id_a = 0;
//    ozt_stp_state.bool_val.po_Id_a = 
//       ( (measurement[IM_adIA]*lV) >=  (measurement[IM_dIA]*sLV.lSP_a) )
//    || ( (measurement[IM_adIB]*lV) >=  (measurement[IM_dIB]*sLV.lSP_a) )
//    || ( (measurement[IM_adIC]*lV) >=  (measurement[IM_dIC]*sLV.lSP_a) );
    lV = ozt_stp_state.bool_val.po_Id_a; chGlbDbgFlg |= lV<<0;
    u32_bit_holder |= lV << OZT2__TIMER_0_T_IN;
    //_index_timer,_max_count,_input, _input_bit,  _output, _output_bit
    _TIMER_0_T( INDEX_TIMER_OZT_AB, current_settings_prt.timeout_ozt2_a_blk[number_group_stp],
    u32_bit_holder,OZT2__TIMER_0_T_IN,u32_bit_holder,OZT2__TIMER_0_T_OUT);
    //chGlbDbgFlg |= lV<<1;
    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_A_OZT2);
    long lAnd = 0;
    if(lV == 0)
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
    
    sLV.lSP_2g = sLV.p_current_settings_prt->pickup_ozt_K_2I[number_group_stp];
    if(ozt_stp_state.bool_val.po_Id_2g == 0 ){
       lV = 1000;
    }else{
      lV = 1000;//lV = 10*(sLV.p_current_settings_prt->pickup_ozt_2I_kp[number_group_stp]);//
      sLV.lSP_2g *= (sLV.p_current_settings_prt->pickup_ozt_2I_kp[number_group_stp]);
      sLV.lSP_2g /= 100;
    }
    sLV.lCtrStp = 0;
//       (measurement[IM_2dIA]*lV >= (measurement[IM_dIA]*sLV.lSP_2g) )ozt_stp_state.bool_val.po_Id_2g = 0;
//    || (measurement[IM_2dIB]*lV >= (measurement[IM_dIB]*sLV.lSP_2g) )
//    || (measurement[IM_2dIC]*lV >= (measurement[IM_dIC]*sLV.lSP_2g) );
//    if(sLV.lCtrBlock == 0){
    if(sLV.chBlkPhaseA == 0){//(measurement[IM_2dIA]>= (0.05*I_NOM)) && (measurement[IM_dIA] > 0.05*I_NOM)
        if( ((measurement[IM_2dIA]*lV)/measurement[IM_dIA]) >=  ((unsigned long)sLV.lSP_2g) )
            sLV.lCtrStp++;//
    }
    if(sLV.chBlkPhaseB == 0){//(measurement[IM_2dIB]>= (0.05*I_NOM)) && (measurement[IM_dIB] > 0.05*I_NOM)
        if( ((measurement[IM_2dIB]*lV)/measurement[IM_dIB]) >=  ((unsigned long)sLV.lSP_2g) )
            sLV.lCtrStp++;//
    }
    if(sLV.chBlkPhaseC == 0){//(measurement[IM_2dIC]>= (0.05*I_NOM) ) && (measurement[IM_dIC] > 0.05*I_NOM)
        if( ((measurement[IM_2dIC]*lV)/measurement[IM_dIC]) >=  ((unsigned long)sLV.lSP_2g) )
            sLV.lCtrStp++;//
    }   
//    }
    if(sLV.lCtrStp > 0 ){//<-OR    if(sLV.lCtrStp >=3 ){<-And
        ozt_stp_state.bool_val.po_Id_2g = 1; 
    }
    else{
        if(ozt_stp_state.bool_val.po_Id_2g == 1){//dbg Code for find error
            chGlbDbgCtr2g++;                     //dbg Code for find error
            if(chGlbDbgCtr2g > chGlbDbgCmpV2g){  //dbg Code for find error
                chGlbDbgCtr2g = 0;               //dbg Code for find error
            }                                    //dbg Code for find error
        }                                        //dbg Code for find error
        ozt_stp_state.bool_val.po_Id_2g = 0; 
    }
    
    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_2G_OZT2);
    lAnd = 0;
    if(lV == 0)
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
    sLV.lSP_5g = sLV.p_current_settings_prt->pickup_ozt_K_5I[number_group_stp];
    if(ozt_stp_state.bool_val.po_Id_5g == 0 ){
      lV = 1000;
    }else{
      lV = 1000;//lV = 10*(sLV.p_current_settings_prt->pickup_ozt_5I_kp[number_group_stp]);//
      sLV.lSP_5g *= (sLV.p_current_settings_prt->pickup_ozt_5I_kp[number_group_stp]);
      sLV.lSP_5g /= 100;
    }
    sLV.lCtrStp = 0;
//       (measurement[IM_5dIA]*lV >=  (measurement[IM_dIA]*sLV.lSP_5g))ozt_stp_state.bool_val.po_Id_5g = 0;
//    || (measurement[IM_5dIB]*lV >=  (measurement[IM_dIB]*sLV.lSP_5g))
//    || (measurement[IM_5dIC]*lV >=  (measurement[IM_dIC]*sLV.lSP_5g));
    //if(sLV.lCtrBlock == 0){
    if(sLV.chBlkPhaseA == 0){//(measurement[IM_5dIA] >= (0.05*I_NOM)) && (measurement[IM_dIA] > 0.05*I_NOM)
        if( ((measurement[IM_5dIA]*lV)/measurement[IM_dIA]) >=  ((unsigned long)sLV.lSP_5g) )
            sLV.lCtrStp++;//
    }
    if(sLV.chBlkPhaseB == 0){//(measurement[IM_5dIB] >= (0.05*I_NOM)) && (measurement[IM_dIB] > 0.05*I_NOM)
        if( ((measurement[IM_5dIB]*lV)/measurement[IM_dIB]) >=  ((unsigned long)sLV.lSP_5g) )
            sLV.lCtrStp++;//
    }
    if(sLV.chBlkPhaseC == 0){//(measurement[IM_5dIC] >= (0.05*I_NOM)) && (measurement[IM_dIC] > 0.05*I_NOM)
        if( ((measurement[IM_5dIC]*lV)/measurement[IM_dIC]) >=  ((unsigned long)sLV.lSP_5g) )
            sLV.lCtrStp++;//
    } 
    //}   
    if(sLV.lCtrStp > 0){//<- OR if(sLV.lCtrStp >= 3){<-And
    ozt_stp_state.bool_val.po_Id_5g = 1; 
    }else{
        if(ozt_stp_state.bool_val.po_Id_5g == 1){//dbg Code for find error
            chGlbDbgCtr5g++;                     //dbg Code for find error
            if(chGlbDbgCtr5g>chGlbDbgCmpV5g){//  //dbg Code for find error
                chGlbDbgCtr5g = 0;               //dbg Code for find error
            }                                    //dbg Code for find error
        }                                        //dbg Code for find error
        ozt_stp_state.bool_val.po_Id_5g = 0;
    }


    lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_5G_OZT2);
    lAnd = 0;
    if(lV == 0)
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
            ;//// Ідоbm = Ідо +kг 1×(Ігальм – Іго обм);
            lV = (sLV.p_current_settings_prt->pickup_ozt_Ig_obm[number_group_stp] - current_settings_prt.pickup_ozt_Ig0[number_group_stp])*current_settings_prt.pickup_ozt_Kg1[number_group_stp];
            lV /= 1000;
            sLV.lIdObm = current_settings_prt.pickup_ozt_Id0[number_group_stp] + lV;
            ;////Ід спр = Ідоbm +kг 2×(Ігальм – Іго обм);
            sLV.lgdI_hysteresis = sLV.lIdObm; //current_settings_prt.pickup_ozt_Id0[number_group_stp];
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
#ifdef DBGMODE 
    //printf("Dbg Message %ld /n",sLV.conter_and);
//  puts("yuiyipuypip");
#endif 
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
static unsigned int previous_active_functions_bv[N_BIG];
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Bvhs_handler(unsigned int *p_active_functions);
void Bvhs_handler(unsigned int *p_active_functions){
// ----------------    -------------------------
  
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  /*********************/
  //Спочатку опрацьовуємо таймери
  /*********************/
  //Таймер  відключення
  if (global_timers[INDEX_TIMER_VIDKL_VV_H] >= 0)
  {
    //Таймер БО зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_VIDKL_VV_H] >= current_settings_prt.timeout_swch_off[0])//0-H
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_VIDKL_VV_H] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БО має бути деативованим
      _CLEAR_BIT(p_active_functions, RANG_WORK_BO_H);
    }
    //Незавершена робота блоку БО означає, що таймер блокування БВ має бути запущений і знаходитися у свому початковому значенні,
    //щоб як тільки блок БО відпрацює, щоб блокування включення почалося на весь час з моменту закінчення роботи блоку БО
    global_timers[INDEX_TIMER_BLK_VKL_VV_H] = 0;
  }
    
  //Таймер  блокування включення
  if (global_timers[INDEX_TIMER_BLK_VKL_VV_H] >= 0)
  {
    //Таймер блокування включення БВ зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_BLK_VKL_VV_H] >= current_settings_prt.timeout_swch_udl_blk_on[0])//H-
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_BLK_VKL_VV_H] = -1;
    }
  }

  //Таймер  включення
  if (global_timers[INDEX_TIMER_VKL_VV_H] >= 0)
  {
    //Таймер БВ зараз активний і як мінімум тільки зараз завершить свою роботу

    //Якщо по якійсь причині таймер включення працює, при умові, що таймери БО і блокування включення ще не скинуті, то таймер включення треба скинути
    if ((global_timers[INDEX_TIMER_VIDKL_VV_H] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV_H] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV_H] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
      _CLEAR_BIT(p_active_functions, RANG_WORK_BV_H);
    }
    else
    {
      //Перевіряємо, чи таймер включення не досягнув свого масимального значення
      if (global_timers[INDEX_TIMER_VKL_VV_H] >= current_settings_prt.timeout_swch_on[0])//0-H
      {
        //Таймер досягнув свого максимального значення
        global_timers[INDEX_TIMER_VKL_VV_H] = -1;
        //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
        _CLEAR_BIT(p_active_functions, RANG_WORK_BV_H);
      }
    }
  }
  /*********************/
  /*********************/
  //Першим розглядається блок відключення, бо він може блокувати включення вимикача
  /*********************/
  /*
  Цей сигнал встановлюється тільки у певних випадках, тому по замовчуванню його треба скинута,
  а коли буде потрібно - він встановиться
  */
  _CLEAR_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
  for (unsigned int i = 0; i < N_BIG; i++ )
    maska[i] = p_active_functions[i];
    //_CLEAR_BIT(maska, RANG_BLOCK_VKL_VV_L);
    //_CLEAR_BIT(maska, RANG_STATE_VV_L);
    //_CLEAR_BIT(maska, RANG_VKL_VV_L);
    //_CLEAR_BIT(maska, RANG_CTRL_VKL_L);
    //_CLEAR_BIT(maska, RANG_OTKL_VV_L);
    //_CLEAR_BIT(maska, RANG_CTRL_OTKL_L);
    //_CLEAR_BIT(maska, RANG_PRYVID_VV_L);
    //_CLEAR_BIT(maska, RANG_WORK_BO_L);
    //_CLEAR_BIT(maska, RANG_WORK_BV_L);
  
  if (
      ((maska[0] & current_settings_prt.ranguvannja_off_cb[0][0]) != 0) ||
      ((maska[1] & current_settings_prt.ranguvannja_off_cb[0][1]) != 0) ||
      ((maska[2] & current_settings_prt.ranguvannja_off_cb[0][2]) != 0) ||
      ((maska[3] & current_settings_prt.ranguvannja_off_cb[0][3]) != 0) ||
      ((maska[4] & current_settings_prt.ranguvannja_off_cb[0][4]) != 0) ||
      ((maska[5] & current_settings_prt.ranguvannja_off_cb[0][5]) != 0) ||
      ((maska[6] & current_settings_prt.ranguvannja_off_cb[0][6]) != 0) ||
      ((maska[7] & current_settings_prt.ranguvannja_off_cb[0][7]) != 0) ||
      ((maska[8] & current_settings_prt.ranguvannja_off_cb[0][8]) != 0)
     )
  {
    //Є умова активації блку вимкнення
    _SET_BIT(p_active_functions, RANG_WORK_BO_H);

    //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БО) таймери: блоку БО, блокуванння БВ.
    global_timers[INDEX_TIMER_VIDKL_VV_H  ] = 0;
    global_timers[INDEX_TIMER_BLK_VKL_VV_H] = 0;
    
    //Скидаємо активацію блоку ввімкнення
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV_H);
    //Скидаємо таймер блку вимкнення
    global_timers[INDEX_TIMER_VKL_VV_H] = -1;  

    /*
    Формуємо сигнал "Відключення від захистів" (він рівний наявності умови команди
    активації команди "Робота БО" будь-якою командою за виключенняв "Вимкн. ВВ")
    */
    //Формуємо інвертовану маску для виключення команди "Вимк.ВВ"
    for (unsigned int i = 0; i < N_BIG; i++ )
        maska[i] = (unsigned int)(~0);
    _CLEAR_BIT(maska, RANG_OTKL_VV_H);
    //_CLEAR_BIT(maska, RANG_WORK_BO_H);
    //_CLEAR_BIT(maska,RANG_BLOCK_VKL_VV_L);
    //_CLEAR_BIT(maska,RANG_STATE_VV_L);
    //_CLEAR_BIT(maska,RANG_VKL_VV_L);
    //_CLEAR_BIT(maska,RANG_CTRL_VKL_L);
    //_CLEAR_BIT(maska,RANG_OTKL_VV_L);
    //_CLEAR_BIT(maska,RANG_CTRL_OTKL_L);
    //_CLEAR_BIT(maska,RANG_PRYVID_VV_L);
    //_CLEAR_BIT(maska,RANG_WORK_BO_L);
    //_CLEAR_BIT(maska,RANG_WORK_BV_L);
    if (
        ((p_active_functions[0] & maska[0]) != 0) ||
        ((p_active_functions[1] & maska[1]) != 0) ||
        ((p_active_functions[2] & maska[2]) != 0) ||
        ((p_active_functions[3] & maska[3]) != 0) ||
        ((p_active_functions[4] & maska[4]) != 0) ||
        ((p_active_functions[5] & maska[5]) != 0) ||
        ((p_active_functions[6] & maska[6]) != 0) ||
        ((p_active_functions[7] & maska[7]) != 0) ||
        ((p_active_functions[8] & maska[8]) != 0)
       )
    {
      //Вимкнення від захистів
      _SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
      
      unsigned int temp_array_of_outputs[N_BIG];
      for (unsigned int i = 0; i < N_BIG; i++ ) temp_array_of_outputs[i] = (p_active_functions[i] & maska[i]);
      _CLEAR_BIT(temp_array_of_outputs, RANG_VIDKL_VID_ZAKHYSTIV);
          
      /*****************************************************
      Формуванні інформації про причину відключення для меню
      *****************************************************/
      unsigned char *label_to_time_array;
      if (copying_time == 2) label_to_time_array = time_copy;
      else label_to_time_array = time;
          
      //ОЗТ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OZT1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_OZT1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT1);
      }
      
      //ОЗТ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OZT2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_OZT2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT2);
      }
      
      //МТЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ1);
      }
      
      //МТЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ2);
      }
      
      //МТЗ3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ3);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ3);
      }
      
      //МТЗ4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ4);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ4);
      }
          
      //3U0
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_P_3U0) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_P_3U0) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_P_3U0);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_P_3U0][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_P_3U0);
      }
          
      //ТЗНП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP1);
      }

      //ТЗНП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP2);
      }

      //ТЗНП3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP3);
      }

      //ТЗНП4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP4);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP4][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP4);
      }

      //ПРВВ1_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV1_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV1_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_2);
      }

      //ПРВВ2_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV2_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV2_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_2);
      }

      //ЗЗП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_ZOP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP1);
      }

      //ЗЗП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_ZOP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP2);
      }
      
      //Umin1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMIN1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN1);
      }
      
      //Umin2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMIN2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN2);
      }
      
      //Umax1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMAX1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX1);
      }
      
      //Umax2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMAX2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX2);
      }
      
      //ГЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP1);
      }
      
      //ГЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP2);
      }
      
      //ГЗ-РПН
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP_RPN) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP_RPN) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP_RPN);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP_RPN][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP_RPN);
      }
      
      //ТЗ
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TP) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TP) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TP);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TP][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TP);
      }
      
      //Універсальний захист
      for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
      {
        if(
           (_CHECK_SET_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP)) != 0) &&
           (_CHECK_SET_BIT(previous_active_functions_bv, (RANG_UP1 + 3*n_UP)) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
          )   
        {
          _SET_BIT(info_vidkluchennja_vymykacha, (VYMKNENNJA_VID_UP1 + n_UP));
          for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UP1 + n_UP][i] = *(label_to_time_array + i);

          _CLEAR_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP));
        }
      }
      
      //Відключення від інших сигналів (крім відключення від сигналу "Вимк.ВВ")
      if(
         (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0) ||
          (temp_array_of_outputs[7] != 0) ||
          (temp_array_of_outputs[8] != 0)
         )
         &&
         (
          ((previous_active_functions_bv[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
          ((previous_active_functions_bv[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
          ((previous_active_functions_bv[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
          ((previous_active_functions_bv[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
          ((previous_active_functions_bv[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
          ((previous_active_functions_bv[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5]) ||
          ((previous_active_functions_bv[6] & temp_array_of_outputs[6])!= temp_array_of_outputs[6]) ||
          ((previous_active_functions_bv[7] & temp_array_of_outputs[7])!= temp_array_of_outputs[7]) ||
          ((previous_active_functions_bv[8] & temp_array_of_outputs[8])!= temp_array_of_outputs[8])
         ) 
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_INSHYKH_SYGNALIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_INSHYKH_SYGNALIV][i] = *(label_to_time_array + i);
      }
      /*****************************************************/
    }
  }

  /*********************/
  //Потім розглядається блок включення
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV_H  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV_H] < 0) &&
      (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_VKL_VV_H) == 0)
     )
  {
    //Оскільки не працюють таймери БО і блокування включення БВ, а також немає сигналу блокування включення ВВ
    //тому перевіряємо, чи немає умови запуску БВ
//    if(_CHECK_SET_BIT(p_active_functions, RANG_VKL_VV_H) != 0){
//        long k = previous_active_functions_bv[0];
//    }
    for (unsigned int i = 0; i < N_BIG; i++ )
        maska[i] = p_active_functions[i];
        
    //_CLEAR_BIT(maska, RANG_OTKL_VV_H);
    //_CLEAR_BIT(maska, RANG_WORK_BO_H);
    //_CLEAR_BIT(maska,RANG_BLOCK_VKL_VV_L);
    //_CLEAR_BIT(maska,RANG_STATE_VV_L);
    //_CLEAR_BIT(maska,RANG_VKL_VV_L);
    //_CLEAR_BIT(maska,RANG_CTRL_VKL_L);
    //_CLEAR_BIT(maska,RANG_OTKL_VV_L);
    //_CLEAR_BIT(maska,RANG_CTRL_OTKL_L);
    //_CLEAR_BIT(maska,RANG_PRYVID_VV_L);
    //_CLEAR_BIT(maska,RANG_WORK_BO_L);
    //_CLEAR_BIT(maska,RANG_WORK_BV_L);
    
    if (
        ((maska[0] & current_settings_prt.ranguvannja_on_cb[0][0]) != 0) ||
        ((maska[1] & current_settings_prt.ranguvannja_on_cb[0][1]) != 0) ||
        ((maska[2] & current_settings_prt.ranguvannja_on_cb[0][2]) != 0) ||
        ((maska[3] & current_settings_prt.ranguvannja_on_cb[0][3]) != 0) ||
        ((maska[4] & current_settings_prt.ranguvannja_on_cb[0][4]) != 0) ||
        ((maska[5] & current_settings_prt.ranguvannja_on_cb[0][5]) != 0) ||
        ((maska[6] & current_settings_prt.ranguvannja_on_cb[0][6]) != 0) ||
        ((maska[7] & current_settings_prt.ranguvannja_on_cb[0][7]) != 0) ||
        ((maska[8] & current_settings_prt.ranguvannja_on_cb[0][8]) != 0)
      )
    {
      //Відмічаємо у масиві функцій, які зараз активуються, що ще треба активувати блок БВ (якщо він ще не активний)
      _SET_BIT(p_active_functions, RANG_WORK_BV_H);

      //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БВ) таймер роботи БВ
      global_timers[INDEX_TIMER_VKL_VV_H] = 0;
    }
  }
  else
  {
    //На даний момент існує одна або більше умов блокування БВ
    global_timers[INDEX_TIMER_VKL_VV_H] = -1;
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV_H);
  }
  /*********************/

  /*********************/
  //Формуємо попереденій стан сигналів для функції ввімкнення/вимкнення
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions_bv[i] = p_active_functions[i];
  /*********************/

}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Bvls_handler(unsigned int *p_active_functions);
void Bvls_handler(unsigned int *p_active_functions){
// ----------------    -------------------------
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  /*********************/
  //Спочатку опрацьовуємо таймери
  /*********************/
  //Таймер  відключення
  if (global_timers[INDEX_TIMER_VIDKL_VV_L] >= 0)
  {
    //Таймер БО зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_VIDKL_VV_L] >= current_settings_prt.timeout_swch_off[1])//1-L
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_VIDKL_VV_L] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БО має бути деативованим
      _CLEAR_BIT(p_active_functions, RANG_WORK_BO_L);
    }
    //Незавершена робота блоку БО означає, що таймер блокування БВ має бути запущений і знаходитися у свому початковому значенні,
    //щоб як тільки блок БО відпрацює, щоб блокування включення почалося на весь час з моменту закінчення роботи блоку БО
    global_timers[INDEX_TIMER_BLK_VKL_VV_L] = 0;
  }
    
  //Таймер  блокування включення
  if (global_timers[INDEX_TIMER_BLK_VKL_VV_L] >= 0)
  {
    //Таймер блокування включення БВ зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_BLK_VKL_VV_L] >= current_settings_prt.timeout_swch_udl_blk_on[1])
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_BLK_VKL_VV_L] = -1;
    }
  }

  //Таймер  включення
  if (global_timers[INDEX_TIMER_VKL_VV_L] >= 0)
  {
    //Таймер БВ зараз активний і як мінімум тільки зараз завершить свою роботу

    //Якщо по якійсь причині таймер включення працює, при умові, що таймери БО і блокування включення ще не скинуті, то таймер включення треба скинути
    if ((global_timers[INDEX_TIMER_VIDKL_VV_L] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV_L] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV_L] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
      _CLEAR_BIT(p_active_functions, RANG_WORK_BV_L);
    }
    else
    {
      //Перевіряємо, чи таймер включення не досягнув свого масимального значення
      if (global_timers[INDEX_TIMER_VKL_VV_L] >= current_settings_prt.timeout_swch_on[1])
      {
        //Таймер досягнув свого максимального значення
        global_timers[INDEX_TIMER_VKL_VV_L] = -1;
        //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
        _CLEAR_BIT(p_active_functions, RANG_WORK_BV_L);
      }
    }
  }
  /*********************/
  /*********************/
  //Першим розглядається блок відключення, бо він може блокувати включення вимикача
  /*********************/
  /*
  Цей сигнал встановлюється тільки у певних випадках, тому по замовчуванню його треба скинута,
  а коли буде потрібно - він встановиться
  */
  _CLEAR_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
  for (unsigned int i = 0; i < N_BIG; i++ )
    maska[i] = p_active_functions[i];
    //_CLEAR_BIT(maska, RANG_BLOCK_VKL_VV_H);
    //_CLEAR_BIT(maska, RANG_STATE_VV_H);
    //_CLEAR_BIT(maska, RANG_VKL_VV_H);
    //_CLEAR_BIT(maska, RANG_CTRL_VKL_H);
    //_CLEAR_BIT(maska, RANG_OTKL_VV_H);
    //_CLEAR_BIT(maska, RANG_CTRL_OTKL_H);
    //_CLEAR_BIT(maska, RANG_PRYVID_VV_H);
    //_CLEAR_BIT(maska, RANG_WORK_BO_H);
    //_CLEAR_BIT(maska, RANG_WORK_BV_H);
  if (
      ((maska[0] & current_settings_prt.ranguvannja_off_cb[1][0]) != 0) ||
      ((maska[1] & current_settings_prt.ranguvannja_off_cb[1][1]) != 0) ||
      ((maska[2] & current_settings_prt.ranguvannja_off_cb[1][2]) != 0) ||
      ((maska[3] & current_settings_prt.ranguvannja_off_cb[1][3]) != 0) ||
      ((maska[4] & current_settings_prt.ranguvannja_off_cb[1][4]) != 0) ||
      ((maska[5] & current_settings_prt.ranguvannja_off_cb[1][5]) != 0) ||
      ((maska[6] & current_settings_prt.ranguvannja_off_cb[1][6]) != 0) ||
      ((maska[7] & current_settings_prt.ranguvannja_off_cb[1][7]) != 0) ||
      ((maska[8] & current_settings_prt.ranguvannja_off_cb[1][8]) != 0)
     )
  {
    //Є умова активації блку вимкнення
    _SET_BIT(p_active_functions, RANG_WORK_BO_L);

    //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БО) таймери: блоку БО, блокуванння БВ.
    global_timers[INDEX_TIMER_VIDKL_VV_L  ] = 0;
    global_timers[INDEX_TIMER_BLK_VKL_VV_L] = 0;
    
    //Скидаємо активацію блоку ввімкнення
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV_L);
    //Скидаємо таймер блку вимкнення
    global_timers[INDEX_TIMER_VKL_VV_L] = -1;  

    /*
    Формуємо сигнал "Відключення від захистів" (він рівний наявності умови команди
    активації команди "Робота БО" будь-якою командою за виключенняв "Вимкн. ВВ")
    */
    //Формуємо інвертовану маску для виключення команди "Вимк.ВВ"
    for (unsigned int i = 0; i < N_BIG; i++ )  maska[i] = (unsigned int)(~0);
    _CLEAR_BIT(maska, RANG_OTKL_VV_L);
    //_CLEAR_BIT(maska, RANG_WORK_BO_L);
    //_CLEAR_BIT(maska,RANG_BLOCK_VKL_VV_H);
    //_CLEAR_BIT(maska,RANG_STATE_VV_H);
    //_CLEAR_BIT(maska,RANG_VKL_VV_H);
    //_CLEAR_BIT(maska,RANG_CTRL_VKL_H);
    //_CLEAR_BIT(maska,RANG_OTKL_VV_H);
    //_CLEAR_BIT(maska,RANG_CTRL_OTKL_H);
    //_CLEAR_BIT(maska,RANG_PRYVID_VV_H);
    //_CLEAR_BIT(maska,RANG_WORK_BO_H);
    //_CLEAR_BIT(maska,RANG_WORK_BV_H);
    
    if (
        ((p_active_functions[0] & maska[0]) != 0) ||
        ((p_active_functions[1] & maska[1]) != 0) ||
        ((p_active_functions[2] & maska[2]) != 0) ||
        ((p_active_functions[3] & maska[3]) != 0) ||
        ((p_active_functions[4] & maska[4]) != 0) ||
        ((p_active_functions[5] & maska[5]) != 0) ||
        ((p_active_functions[6] & maska[6]) != 0) ||
        ((p_active_functions[7] & maska[7]) != 0) ||
        ((p_active_functions[8] & maska[8]) != 0)
       )
    {
      //Вимкнення від захистів
      _SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
      
      unsigned int temp_array_of_outputs[N_BIG];
      for (unsigned int i = 0; i < N_BIG; i++ ) temp_array_of_outputs[i] = (p_active_functions[i] & maska[i]);
      _CLEAR_BIT(temp_array_of_outputs, RANG_VIDKL_VID_ZAKHYSTIV);
          
      /*****************************************************
      Формуванні інформації про причину відключення для меню
      *****************************************************/
      unsigned char *label_to_time_array;
      if (copying_time == 2) label_to_time_array = time_copy;
      else label_to_time_array = time;
          
      //ОЗТ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OZT1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_OZT1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT1);
      }
      
      //ОЗТ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OZT2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_OZT2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT2);
      }
      
      //МТЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ1);
      }
      
      //МТЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ2);
      }
      
      //МТЗ3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ3);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ3);
      }
      
      //МТЗ4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_MTZ4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ4);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ4);
      }
          
      //3U0
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_P_3U0) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_P_3U0) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_P_3U0);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_P_3U0][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_P_3U0);
      }
          
      //ТЗНП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP1);
      }

      //ТЗНП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP2);
      }

      //ТЗНП3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP3);
      }

      //ТЗНП4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TZNP4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP4);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP4][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP4);
      }

      //ПРВВ1_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV1_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV1_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_2);
      }

      //ПРВВ2_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV2_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UROV2_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_2);
      }

      //ЗЗП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_ZOP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP1);
      }

      //ЗЗП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_ZOP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP2);
      }
      
      //Umin1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMIN1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN1);
      }
      
      //Umin2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMIN2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN2);
      }
      
      //Umax1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMAX1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX1);
      }
      
      //Umax2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_UMAX2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX2);
      }
      
      //ГЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP1);
      }
      
      //ГЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP2);
      }
      
      //ГЗ-РПН
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP_RPN) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_GP_RPN) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP_RPN);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP_RPN][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP_RPN);
      }
      
      //ТЗ
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TP) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions_bv, RANG_TP) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TP);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TP][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TP);
      }
      
      //Універсальний захист
      for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
      {
        if(
           (_CHECK_SET_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP)) != 0) &&
           (_CHECK_SET_BIT(previous_active_functions_bv, (RANG_UP1 + 3*n_UP)) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
          )   
        {
          _SET_BIT(info_vidkluchennja_vymykacha, (VYMKNENNJA_VID_UP1 + n_UP));
          for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UP1 + n_UP][i] = *(label_to_time_array + i);

          _CLEAR_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP));
        }
      }
      
      //Відключення від інших сигналів (крім відключення від сигналу "Вимк.ВВ")
      if(
         (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0) ||
          (temp_array_of_outputs[7] != 0) ||
          (temp_array_of_outputs[8] != 0)
         )
         &&
         (
          ((previous_active_functions_bv[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
          ((previous_active_functions_bv[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
          ((previous_active_functions_bv[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
          ((previous_active_functions_bv[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
          ((previous_active_functions_bv[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
          ((previous_active_functions_bv[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5]) ||
          ((previous_active_functions_bv[6] & temp_array_of_outputs[6])!= temp_array_of_outputs[6]) ||
          ((previous_active_functions_bv[7] & temp_array_of_outputs[7])!= temp_array_of_outputs[7]) ||
          ((previous_active_functions_bv[8] & temp_array_of_outputs[8])!= temp_array_of_outputs[8])
         ) 
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_INSHYKH_SYGNALIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_INSHYKH_SYGNALIV][i] = *(label_to_time_array + i);
      }
      /*****************************************************/
    }
  }

  /*********************/
  //Потім розглядається блок включення
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV_L  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV_L] < 0) &&
      (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_VKL_VV_L) == 0)
     )
  {
    //Оскільки не працюють таймери БО і блокування включення БВ, а також немає сигналу блокування включення ВВ
    //тому перевіряємо, чи немає умови запуску БВ
//        if(_CHECK_SET_BIT(p_active_functions, RANG_VKL_VV_L) != 0){
//        long k = previous_active_functions_bv[0];
//        }
        for (unsigned int i = 0; i < N_BIG; i++ )
            maska[i] = p_active_functions[i];
    //_CLEAR_BIT(maska, RANG_OTKL_VV_L);
    //_CLEAR_BIT(maska, RANG_WORK_BO_L);
    //_CLEAR_BIT(maska,RANG_BLOCK_VKL_VV_H);
    //_CLEAR_BIT(maska,RANG_STATE_VV_H);
    //_CLEAR_BIT(maska,RANG_VKL_VV_H);
    //_CLEAR_BIT(maska,RANG_CTRL_VKL_H);
    //_CLEAR_BIT(maska,RANG_OTKL_VV_H);
    //_CLEAR_BIT(maska,RANG_CTRL_OTKL_H);
    //_CLEAR_BIT(maska,RANG_PRYVID_VV_H);
    //_CLEAR_BIT(maska,RANG_WORK_BO_H);
    //_CLEAR_BIT(maska,RANG_WORK_BV_H);

    if (
        ((maska[0] & current_settings_prt.ranguvannja_on_cb[1][0]) != 0) ||
        ((maska[1] & current_settings_prt.ranguvannja_on_cb[1][1]) != 0) ||
        ((maska[2] & current_settings_prt.ranguvannja_on_cb[1][2]) != 0) ||
        ((maska[3] & current_settings_prt.ranguvannja_on_cb[1][3]) != 0) ||
        ((maska[4] & current_settings_prt.ranguvannja_on_cb[1][4]) != 0) ||
        ((maska[5] & current_settings_prt.ranguvannja_on_cb[1][5]) != 0) ||
        ((maska[6] & current_settings_prt.ranguvannja_on_cb[1][6]) != 0) ||
        ((maska[7] & current_settings_prt.ranguvannja_on_cb[1][7]) != 0) ||
        ((maska[8] & current_settings_prt.ranguvannja_on_cb[1][8]) != 0)
      )
    {
      //Відмічаємо у масиві функцій, які зараз активуються, що ще треба активувати блок БВ (якщо він ще не активний)
      _SET_BIT(p_active_functions, RANG_WORK_BV_L);

      //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БВ) таймер роботи БВ
      global_timers[INDEX_TIMER_VKL_VV_L] = 0;
    }
  }
  else
  {
    //На даний момент існує одна або більше умов блокування БВ
    global_timers[INDEX_TIMER_VKL_VV_L] = -1;
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV_L);
  }
  /*********************/

  /*********************/
  //Формуємо попереденій стан сигналів для функції ввімкнення/вимкнення
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++)
    previous_active_functions_bv[i] = p_active_functions[i];
  /*********************/
  

    
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
void control_2VV(unsigned int *p_active_functions);
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void control_2VV(unsigned int *p_active_functions){
// ----------------    -------------------------

register long lV,rI; 
register union { 
   struct {
      unsigned int vv_vkl         :1;//0
      unsigned int vv_otkl        :1;//1
      unsigned int rl_vv_hs       :1;//2
      unsigned int rl_vv_ls       :1;//3
      unsigned int not_hs         :1;//4
      unsigned int not_ls         :1;//5
      unsigned int prvvh          :1;//6
      unsigned int prvvl          :1;//7
      
   } bool_vars;
  long lVl;
}wrp;
unsigned long u32_bit_holder = 0;
wrp.lVl = 0;
        
    lV = (current_settings_prt.control_switch[0] & CTR_PRYVOD_VV);
     if(lV != 0){
        //wrp.bool_vars.m_ctrl_vv_hs = 1;
        lV = _CHECK_SET_BIT(p_active_functions,RANG_CTRL_VKL_H );
        if(lV != 0){
            wrp.bool_vars.vv_vkl = 1;
            //u32_bit_holder = 1;
        }   
        lV = _CHECK_SET_BIT(p_active_functions,RANG_CTRL_OTKL_H );
        if(lV != 0)
            wrp.bool_vars.vv_otkl = 1;
        //lV = (wrp.lVl&2)^(wrp.lVl&1);
		rI = wrp.bool_vars.vv_vkl;
		lV = wrp.bool_vars.vv_otkl;
		lV ^= rI;
        if(lV == 0)
        u32_bit_holder = 1;
        _TIMER_T_0(INDEX_TIMER_PRYVOD_VV_H, current_settings_prt.timeout_pryvoda_VV[0], u32_bit_holder, 0, u32_bit_holder, 1);
        if (u32_bit_holder&2)//wrp.bool_vars.prvvh
            _SET_BIT(p_active_functions, RANG_PRYVID_VV_H);
        else
            _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV_H);
    }   
    else{   
         _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV_H);
         //return;
    }
    wrp.lVl = 0;
    lV = (current_settings_prt.control_switch[1] & CTR_PRYVOD_VV);
     if(lV != 0){
        lV = _CHECK_SET_BIT(p_active_functions,RANG_CTRL_VKL_L );
        if(lV != 0){
            wrp.bool_vars.vv_vkl = 1;
            //u32_bit_holder = 1;
        }   
        lV = _CHECK_SET_BIT(p_active_functions,RANG_CTRL_OTKL_L );
        if(lV != 0)
            wrp.bool_vars.vv_otkl = 1;
		//lV = (wrp.lVl&2)^(wrp.lVl&1);	
        rI = wrp.bool_vars.vv_vkl;
		lV = wrp.bool_vars.vv_otkl;
		lV ^= rI;
        if(lV == 0)
        u32_bit_holder |= 4;
        _TIMER_T_0(INDEX_TIMER_PRYVOD_VV_L, current_settings_prt.timeout_pryvoda_VV[1], u32_bit_holder, 2, u32_bit_holder, 3);
        if (u32_bit_holder&8)//wrp.bool_vars.prvvh
            _SET_BIT(p_active_functions, RANG_PRYVID_VV_L);
        else
            _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV_L);
    }   
    else{   
         _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV_L);
         //return;
    }
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
 
