
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
 ch_type_voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1; 
if(ch_type_voltage){//0-VH 1 - VL 

 if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){

struct{
long Ii,Ip;

}sLV;  
_Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);

GRZU8
git push  --repo 'https://github.com/AdrianVlas/mrprT_a3.git'
getmac
ipconfig /all
arp -g
register union { 
   struct {
    //  unsigned int previous_state_po_dfrp1 : 1;
      unsigned int state_po_dfrp1 : 1;
      unsigned int dfrp1_is_larger_than_dI:1;
   } bool_vars;
  long lVl;
}wrp;

//register unsigned long u32_bit_holder = 0;  
//register union { 
//   struct {
//      unsigned int previous_state_po_3U0_1 : 1;
//	  unsigned int KZZV_1r_is_larger_than_3U0_1:1;
//   } bool_vars;
//  long lVl;
//}wrp;wrp.lVl = 0;
struct{
unsigned long I1_lead_ls, I1_lead_hs, I2_lead_ls, I2_lead_hs;
unsigned long  meas_I1_lead_ls, meas_I1_lead_hs, meas_I2_lead_ls, meas_I2_lead_hs;
unsigned long setpoint_ls,setpoint_hs;
long lgI_hysteresis;
long conter_and;
__SETTINGS *p_current_settings_prt;
}sLV; 
   long lV; 
   unsigned long lCmpVl;
   Mcp_stp_state *p_bl;
 sLV.conter_and = 0;sLV.lgI_hysteresis = 0;
  sLV.p_current_settings_prt = &current_settings_prt;
     //ДВ
  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_KZ_ZV);
  register long lAnd = 0;
  if(lV == 0)
    lAnd |= 1;
   lV = (sLV.p_current_settings_prt->control_kz_zv & (1<<INDEX_ML_CTR_KZ_ZV_STATE)) ;
  if(lV != 0)
  lAnd |= 2;
  if(lAnd == 3){
    sLV.conter_and++;
    }
	lCmpVl = MIN_LIMIT_I1_I2_P;
    
		
//    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
//    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
//    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
//    
//    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
//    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
//    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);	
   sLV.meas_I1_lead_ls = measurement[IM_I1_P_L ];
   sLV.meas_I1_lead_hs = measurement[IM_I1_P_H ];
   sLV.meas_I2_lead_ls = measurement[IM_I2_P_L ];
   sLV.meas_I2_lead_hs = measurement[IM_I2_P_H ];
	p_bl = &mcp_stp_state;
	lV = p_bl->bool_val.po_I1_lead_low_side;
	if(lV) 
		sLV.I1_lead_ls = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
	else 
		sLV.I1_lead_ls = lCmpVl;
	if(sLV.meas_I1_lead_ls >= sLV.I1_lead_ls)
		lV = 1;	
	else 
		lV = 0;
	p_bl->bool_val.po_I1_lead_low_side = lV;
	
	lV = p_bl->bool_val.po_I1_lead_high_side ;
	if (lV)
		sLV.I1_lead_hs = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
	else 
		sLV.I1_lead_hs = lCmpVl;
	if(sLV.meas_I1_lead_hs >= sLV.I1_lead_hs)
		lV = 1;	
	else 
		lV = 0;	
	p_bl->bool_val.po_I1_lead_high_side = lV;
	
	lV = p_bl->bool_val.po_I2_lead_low_side;	
	if(lV) 
		sLV.I2_lead_ls = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
	else 
		sLV.I2_lead_ls = lCmpVl;
	if(sLV.meas_I2_lead_ls >= sLV.I2_lead_ls)
		lV = 1;	
	else 
		lV = 0;	
	p_bl->bool_val.po_I2_lead_low_side = lV;	
	
	lV = p_bl->bool_val.po_I2_lead_high_side;	
	if ( lV)
		sLV.I2_lead_hs = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
	else 
		sLV.I2_lead_hs = lCmpVl;
	if(sLV.meas_I2_lead_hs >= sLV.I2_lead_hs)
		lV = 1;	
	else 
		lV = 0;	
	p_bl->bool_val.po_I2_lead_high_side = lV;
	lV = p_bl->lVl;
	lV &= 0xf;
	if(lV == 0xf){
		lV =  p_bl->bool_val.po_I2_I1_ls_lead;
		if(lV){
			lV = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
			lV *= KOEF_POVERNENNJA_GENERAL_UP/100;
			sLV.setpoint_ls = lV;
			
		}
		else{
			sLV.setpoint_ls = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
			
		}
		lV =  p_bl->bool_val.po_I2_I1_hs_lead;
		if(lV){
			lV = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
			lV *= KOEF_POVERNENNJA_GENERAL_UP/100;
			sLV.setpoint_hs = lV;
			
		}
		else{
			sLV.setpoint_hs = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
			
		}
		//((i2_current*1000) >= (i1_current*setpoint)) 
		if(	(sLV.meas_I2_lead_ls*1000) >= (sLV.meas_I1_lead_ls*sLV.setpoint_ls) ){
			lV =  p_bl->bool_val.po_I2_I1_ls_lead;
			if(lV == 0)
				p_bl->bool_val.po_I2_I1_ls_lead = 1;
		}
		else{
			lV =  p_bl->bool_val.po_I2_I1_ls_lead;
			if(lV != 0)
				p_bl->bool_val.po_I2_I1_ls_lead = 0;
			
		}
		if(	(sLV.meas_I2_lead_hs*1000) >= (sLV.meas_I1_lead_hs*sLV.setpoint_hs) ){
			lV =  p_bl->bool_val.po_I2_I1_hs_lead;
			if(lV == 0)
				p_bl->bool_val.po_I2_I1_hs_lead = 1;
		}
		else{
			lV =  p_bl->bool_val.po_I2_I1_hs_lead;
			if(lV != 0)
				p_bl->bool_val.po_I2_I1_hs_lead = 0;
			
		}
		//---------------------------------------------
		//Phase sensetive element
		//0- Not
		//1-Internal
		//2-External
		//---------------------------------------------
		lV = sLV.lgI_hysteresis;//Temporarly emulate Phase Calculation
		if( lV == 2 ){
			//Put Cmd  Sector In\Ext
			lV = p_bl->lVl;
			lV &= 0x30;
			if(lV == 0x30)
			sLV.conter_and += 2;
		}else if( lV == 1 ){
			//Put Cmd  Sector In\Ext
			lV = p_bl->lVl;
			lV &= 0x30;
			if(lV == 0x30)
			sLV.conter_and += 1;
		}
		else{
			//Clear Cmd Sector In\Ext
		}
	}
	else{
		;//Clr Kz
	}
	if(sLV.conter_and == 5){
	
	}else if(sLV.conter_and == 4){
	
	}
	else{//Clr State

	}
 
CYCLECOUNTER	631174246	ReadOnly	
631174684
438
CYCLECOUNTER	1659503	ReadOnly	
CYCLECOUNTER	1659861	ReadOnly
358	



 
 


