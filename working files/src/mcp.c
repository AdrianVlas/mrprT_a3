enum MCP_BIT_POS { 

MCP_DV_BLOCK_CMD_BIT  = 1,  
MCP_DV_BLOCK_INVERSE_CMD_BIT  ,  
MCP_MENU_P_3U0_STATE_BIT,
MCP_PICKUP_3U0_STATE_BIT,
MCP_TMR_3U0_STATE_BIT,
TOTAL_MCP_BITS
//
};
void mcp_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
//const unsigned long MIN_LIMIT_I1_I2_P = MIN_LIMIT_FOR_I1_AND_I2;
typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int po_I1_lead_low_side  : 1; //1
      unsigned int po_I1_lead_high_side : 1; //2
      unsigned int po_I2_lead_low_side  : 1; //3
      unsigned int po_I2_lead_high_side : 1; //4
      unsigned int po_I2_I1_ls_lead     : 1; //5
      unsigned int po_I2_I1_hs_lead     : 1; //6
//      unsigned int po_ : 1; //7
//      unsigned int po_ : 1; //8
//      unsigned int po_ : 1; //9
    } bool_val;
    long lVl;
} Mcp_stp_state; 
Mcp_stp_state mcp_stp_state ;

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void mcp_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name	-------------------------
//Calc NCN for 4 stages

 
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
const unsigned long arL_ctrl_mcp_sel[NUMBER_LEVEL_MTZ] = {CTR_MTZ_1_SEL_I,CTR_MTZ_2_SEL_I,CTR_MTZ_3_SEL_I,CTR_MTZ_4_SEL_I};
inline int timeout_dependent_general(unsigned int i, unsigned int setpoint_mtz_2, int timeout_mtz_2, int type_mtz2_tmp);
inline void mtz_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int tmp_value;
  
  unsigned int po_mtz_x;
  unsigned int direction_ABC_tmp;
  unsigned int po_mtzn_x_vpered_setpoint;
  unsigned int po_mtzn_x_nazad_setpoint;
//  unsigned int po_block_u_mtzn_x_setpoint;
  unsigned int po_i_ncn_setpoint;
  unsigned int po_u_ncn_setpoint;
  unsigned int po_u_mtzpn_x_setpoint;
  unsigned int po_mtzpn_x_setpoint;
  
  /******Неисправность цепей напряжения для 4-х ступеней*******/
  _Bool ctr_mtz_nespr_kil_napr = (current_settings_prt.control_mtz & CTR_MTZ_NESPR_KIL_NAPR) != 0; //Неиспр. Напр. Вкл. (М)
  
  //ПО Iнцн
  po_i_ncn_setpoint = previous_state_mtz_po_incn ?
            i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 :
            i_nom_const;
  if(ch_type_voltage){//0-VH 1 - VL   
     previous_state_mtz_po_incn = ((measurement[IM_IA_L] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB_L] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC_L] <= po_i_ncn_setpoint));
	}
else{
     previous_state_mtz_po_incn = ((measurement[IM_IA_H] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB_H] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC_H] <= po_i_ncn_setpoint));
}  
  //ПО Uнцн
  po_u_ncn_setpoint = previous_state_mtz_po_uncn ?
            u_linear_nom_const * U_DOWN / 100 :
            u_linear_nom_const;
  
  previous_state_mtz_po_uncn = ((measurement[IM_UAB] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UBC] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UCA] <= po_u_ncn_setpoint));
  
  ctr_mtz_nespr_kil_napr = ctr_mtz_nespr_kil_napr && previous_state_mtz_po_incn && previous_state_mtz_po_uncn; //Неисправность цепей напряжения (_AND3)
  
  //Неисправность цепей напряжения
  if (ctr_mtz_nespr_kil_napr)
    _SET_BIT(p_active_functions, RANG_NCN_MTZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_NCN_MTZ);
  /******Неисправность цепей напряжения для 4-х ступеней*******/
  
  /******ПО U блок. МТЗНх***********************/
  //Уставка ПО U блок. МТЗНх з врахуванням гістерезису
  unsigned int po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) == 0) ? PORIG_CHUTLYVOSTI_VOLTAGE : PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
  
  //ПО U блок. МТЗНх
  if (
      (measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)
     )
  {
    _SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
  }
  /******ПО U блок. МТЗНх***********************/

  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //Для отладки
//    if (mtz_level == 0) {
//      mtz_level = 0;
//    } else if (mtz_level == 1) {
//      mtz_level = 1;
//    } else if (mtz_level == 2) {
//      mtz_level = 2;
//    } else if (mtz_level == 3) {
//      mtz_level = 3;
//    }
    
    //М
    /*Проверяем тип МТЗ*/
    tmp_value = (*type_mtz_arr[mtz_level] == 1)                                  << 0; //Направленная
    tmp_value |= (*type_mtz_arr[mtz_level] == 2)                                 << 1; //С пуском
    tmp_value |= (*type_mtz_arr[mtz_level] == 0)                                 << 2; //Простая
    tmp_value |= (
                  (mtz_level == 1)
                  && (*type_mtz_arr[mtz_level] >= TYPE_MTZ_DEPENDENT_A) //A, B, C (3-5)
                  && (*type_mtz_arr[mtz_level] <= TYPE_MTZ_DEPENDENT_RTV_I)
                 )                                                               << 3; //Зависимая (если mtz_level == 1 (2-я ступень МТЗ))
    
    /******ПО МТЗх***********************/
    //Уставка ПО МТЗх с учетом гистерезиса
    po_mtz_x = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) ?
            *(setpoint_mtz[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz[mtz_level] + number_group_stp);
    if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){
    tmp_value |= ((measurement[IM_IA_L] >= po_mtz_x) ||
          (measurement[IM_IB_L] >= po_mtz_x) ||
          (measurement[IM_IC_L] >= po_mtz_x)) << 4; //ПО МТЗх
	}else{
	    tmp_value |= ((measurement[IM_IA_H] >= po_mtz_x) ||
          (measurement[IM_IB_H] >= po_mtz_x) ||
          (measurement[IM_IC_H] >= po_mtz_x)) << 4; //ПО МТЗх
	}	
    /******ПО МТЗх***********************/
    
    //М
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ]) != 0) << 5; //МТЗх Вкл.
    //ДВ
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_MTZ]) == 0) << 6; //Блокировка МТЗх
    //М
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_VPERED]) != 0) << 7; //МТЗНх: Вкл. прям
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_NAZAD]) != 0) << 8; //МТЗНх: Вкл. обр
    
    /******Сектор МТЗНх Вперед/Назад**********/
    //Проверка направленности фаз А,В,С
    direction_ABC_tmp = (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_VPERED) << 0; //Проверка направленности фазы А вперед
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_VPERED) << 1; //Проверка направленности фазы B вперед
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_VPERED) << 2; //Проверка направленности фазы C вперед
    
    _OR3(direction_ABC_tmp, 0, direction_ABC_tmp, 1, direction_ABC_tmp, 2, direction_ABC_tmp, 3);
    
    //Сектор МТЗНх Вперед
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 3))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_NAZAD) << 4; //Проверка направленности фазы А назад
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_NAZAD) << 5; //Проверка направленности фазы B назад
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_NAZAD) << 6; //Проверка направленности фазы C назад
    
    _OR3(direction_ABC_tmp, 4, direction_ABC_tmp, 5, direction_ABC_tmp, 6, direction_ABC_tmp, 7);
    
    //Сектор МТЗНх Назад
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 7))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    
    //Уставка ПО МТЗН1 прям. с учетом гистерезиса
    po_mtzn_x_vpered_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0) ?
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp);
    if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){
    direction_ABC_tmp |= (measurement[IM_IA_L] >= po_mtzn_x_vpered_setpoint) << 8; //Сравниваем с уставкой тока по фазе А (вперед)
    direction_ABC_tmp |= (measurement[IM_IB_L] >= po_mtzn_x_vpered_setpoint) << 9; //Сравниваем с уставкой тока по фазе B (вперед)
    direction_ABC_tmp |= (measurement[IM_IC_L] >= po_mtzn_x_vpered_setpoint) << 10; //Сравниваем с уставкой тока по фазе C (вперед)
    }else{
	direction_ABC_tmp |= (measurement[IM_IA_H] >= po_mtzn_x_vpered_setpoint) << 8; //Сравниваем с уставкой тока по фазе А (вперед)
    direction_ABC_tmp |= (measurement[IM_IB_H] >= po_mtzn_x_vpered_setpoint) << 9; //Сравниваем с уставкой тока по фазе B (вперед)
    direction_ABC_tmp |= (measurement[IM_IC_H] >= po_mtzn_x_vpered_setpoint) << 10; //Сравниваем с уставкой тока по фазе C (вперед)
    }
    //Уставка ПО МТЗН1 прям. с учетом гистерезиса
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
     if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){
    direction_ABC_tmp |= (measurement[IM_IA_L] >= po_mtzn_x_nazad_setpoint) << 11; //Сравниваем с уставкой тока по фазе А (назад)
    direction_ABC_tmp |= (measurement[IM_IB_L] >= po_mtzn_x_nazad_setpoint) << 12; //Сравниваем с уставкой тока по фазе B (назад)
    direction_ABC_tmp |= (measurement[IM_IC_L] >= po_mtzn_x_nazad_setpoint) << 13; //Сравниваем с уставкой тока по фазе C (назад)
    }else{
	direction_ABC_tmp |= (measurement[IM_IA_H] >= po_mtzn_x_nazad_setpoint) << 11; //Сравниваем с уставкой тока по фазе А (назад)
    direction_ABC_tmp |= (measurement[IM_IB_H] >= po_mtzn_x_nazad_setpoint) << 12; //Сравниваем с уставкой тока по фазе B (назад)
    direction_ABC_tmp |= (measurement[IM_IC_H] >= po_mtzn_x_nazad_setpoint) << 13; //Сравниваем с уставкой тока по фазе C (назад)
    }
    _AND2(direction_ABC_tmp, 8, direction_ABC_tmp, 0, direction_ABC_tmp, 14);
    _AND2(direction_ABC_tmp, 9, direction_ABC_tmp, 1, direction_ABC_tmp, 15);
    _AND2(direction_ABC_tmp, 10, direction_ABC_tmp, 2, direction_ABC_tmp, 16);
    
    _AND2(direction_ABC_tmp, 11, direction_ABC_tmp, 4, direction_ABC_tmp, 17);
    _AND2(direction_ABC_tmp, 12, direction_ABC_tmp, 5, direction_ABC_tmp, 18);
    _AND2(direction_ABC_tmp, 13, direction_ABC_tmp, 6, direction_ABC_tmp, 19);
    
    _OR3(direction_ABC_tmp, 14, direction_ABC_tmp, 15, direction_ABC_tmp, 16, tmp_value, 12);
    _OR3(direction_ABC_tmp, 17, direction_ABC_tmp, 18, direction_ABC_tmp, 19, tmp_value, 13);
    /******Сектор МТЗНх Вперед/Назад**********/
    
//    /******ПО U блок. МТЗНх***********************/
//    //Уставка ПО U блок. МТЗНх с учетом гистерезиса
//    po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) != 0) ?
//           PORIG_CHUTLYVOSTI_VOLTAGE :
//           PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
//    
//    tmp_value |= ((measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)) << 14; //ПО U блок. МТЗНх
//    
//    //ПО U блок. МТЗНх
//    if (_GET_OUTPUT_STATE(tmp_value, 14))
//      _SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
//    else
//      _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
//    /******ПО U блок. МТЗНх***********************/
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) != 0) << 14;
    
    //Неисправность цепей напряжения для ступени МТЗх
    tmp_value |= (
                   !(_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD])  != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN])     != 0)
                   &&
                   ctr_mtz_nespr_kil_napr
                 ) << 15;
    
    /******ПО U МТЗПНх***********************/
    po_u_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]) != 0) ?
            *(setpoint_mtz_U[mtz_level] + number_group_stp) * U_DOWN / 100:
            *(setpoint_mtz_U[mtz_level] + number_group_stp) ;
    
    tmp_value |= ((measurement[IM_UAB] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UBC] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UCA] <= po_u_mtzpn_x_setpoint)) << 16; //ПО U МТЗПНх
    
    //ПО U МТЗПНх
    if (_GET_OUTPUT_STATE(tmp_value, 16))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    /******ПО U МТЗПНх***********************/
    
    /******ПО МТЗПНх***********************/
    po_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]) != 0) ?
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100:
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp);
	 if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){	
    tmp_value |= ((measurement[IM_IA_L] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB_L] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC_L] >= po_mtzpn_x_setpoint)) << 17; //ПО МТЗПНх
	}else{
				  tmp_value |= ((measurement[IM_IA_H] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB_H] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC_H] >= po_mtzpn_x_setpoint)) << 17; //ПО МТЗПНх
	}			  
    /******ПО МТЗПНх***********************/
    
    if (mtz_level == 1) { //только для 2-ой ступени
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_USK_MTZ]) == 0) << 9; //Блокировка ускорения МТЗ 2
      //М
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENA) != 0) << 10; //МТЗ2 Ускоренная
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV_L) != 0) << 18; //Положение ВВ
      //M
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENNJA) != 0) << 11; //Ускорение МТЗ2 вкл.
    }
    
    if (_GET_OUTPUT_STATE(tmp_value, 15)) { //Если зафиксирована неисправность цепей напряжения для ступени МТЗх
      _CLEAR_STATE(tmp_value, 16); //Очистка ПО U МТЗПНх
    }
    
    _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 14);
    
    if (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) 
    {
      _SET_STATE(tmp_value, 19);
    } 
    else 
    {
      if (mtz_level == 1)
      {
        //только для 2-ой ступени при формировании 19-го сигнала будет учитываться
        //сигнал "Зависимая" (tmp_value 3)
        if (_GET_OUTPUT_STATE(tmp_value, 14)) 
        {
          _OR3(tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
        else 
        {
          _OR4(tmp_value, 0, tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
      }
      else 
      {
        if (_GET_OUTPUT_STATE(tmp_value, 14))
        {
          _OR2(tmp_value, 2, tmp_value, 15, tmp_value, 19);
        } 
        else
        {
          _OR3(tmp_value, 0, tmp_value, 2, tmp_value, 15, tmp_value, 19);
        }
      }
    }
    
    _AND2(tmp_value, 5, tmp_value, 6, tmp_value, 20);
    
    //ПО МТЗх
    _AND3(tmp_value, 19, tmp_value, 4, tmp_value, 20, tmp_value, 21);
    if (_GET_OUTPUT_STATE(tmp_value, 21))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    
    //ПО МТЗНх вперед
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 7, tmp_value, 12, tmp_value, 14, tmp_value, 22);
    if (_GET_OUTPUT_STATE(tmp_value, 22))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    
    //ПО МТЗНх назад
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 8, tmp_value, 13, tmp_value, 14, tmp_value, 23);
    if (_GET_OUTPUT_STATE(tmp_value, 23)) 
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    
    //ПО МТЗПНх
    _AND4(tmp_value, 1, tmp_value, 20, tmp_value, 16, tmp_value, 17, tmp_value, 24);
    if (_GET_OUTPUT_STATE(tmp_value, 24))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    
    if (mtz_level != 1) { //для всех ступеней кроме 2-ой
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ], *(timeout_mtz[mtz_level] + number_group_stp), tmp_value, 21, tmp_value, 25);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_VPERED], *(timeout_mtz_n_vpered[mtz_level] + number_group_stp), tmp_value, 22, tmp_value, 26);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_NAZAD], *(timeout_mtz_n_nazad[mtz_level] + number_group_stp), tmp_value, 23, tmp_value, 27);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_PO_NAPRUZI], *(timeout_mtz_po_napruzi[mtz_level] + number_group_stp), tmp_value, 24, tmp_value, 28);
      _OR4(tmp_value, 25, tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 31);
    } else {
      unsigned int tmp = 0;
      _AND2(tmp_value, 18, tmp_value, 11, tmp, 0);
      _TIMER_IMPULSE(INDEX_TIMER_MTZ2_VVID_PR, current_settings_prt.timeout_mtz_2_vvid_pr[number_group_stp], temp_states_for_mtz, 0, tmp, 0, tmp, 1);
      _OR2(tmp, 1, tmp_value, 10, tmp, 2);
      _AND2(tmp_value, 9, tmp, 2, tmp, 3);
      _INVERTOR(tmp, 3, tmp, 4);
      _INVERTOR(tmp_value, 3, tmp, 23); /*Добавлено Тарасом у Богданову програму*/
      _AND3(tmp, 4, tmp_value, 3, tmp_value, 21, tmp, 5);
      _AND2(tmp, 3, tmp_value, 21, tmp, 6);
      _AND3(tmp, 4, tmp_value, 21, tmp, 23, tmp, 7); /*Модифіковано Тарасом у Богдановій програмі*/
      _AND2(tmp, 4, tmp_value, 22, tmp, 8);
      _AND2(tmp, 3, tmp_value, 22, tmp, 9);
      _AND2(tmp, 4, tmp_value, 23, tmp, 10);
      _AND2(tmp, 3, tmp_value, 23, tmp, 11);
      _AND2(tmp, 4, tmp_value, 24, tmp, 12);
      _AND2(tmp, 3, tmp_value, 24, tmp, 13);
      
      unsigned int i_max;
	   if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){
			i_max = measurement[IM_IA_L];
		if (i_max < measurement[IM_IB_L])
			i_max = measurement[IM_IB_L];
		if (i_max < measurement[IM_IC_L])
			i_max = measurement[IM_IC_L];
		}else{
			i_max = measurement[IM_IA_H];
		if (i_max < measurement[IM_IB_H])
			i_max = measurement[IM_IB_H];
		if (i_max < measurement[IM_IC_H])
			i_max = measurement[IM_IC_H];
		}
      _TIMER_T_0_LOCK(INDEX_TIMER_MTZ2_DEPENDENT, timeout_dependent_general(i_max, current_settings_prt.setpoint_mtz_2[number_group_stp], current_settings_prt.timeout_mtz_2[number_group_stp], current_settings_prt.type_mtz2), tmp, 5, p_global_trigger_state_mtz2, 0);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PR, current_settings_prt.timeout_mtz_2_pr[number_group_stp], tmp, 6, tmp, 15);
      _TIMER_T_0(INDEX_TIMER_MTZ2, current_settings_prt.timeout_mtz_2[number_group_stp], tmp, 7, tmp, 16);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED, current_settings_prt.timeout_mtz_2_n_vpered[number_group_stp], tmp, 8, tmp, 17);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED_PR, current_settings_prt.timeout_mtz_2_n_vpered_pr[number_group_stp], tmp, 9, tmp, 18);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD, current_settings_prt.timeout_mtz_2_n_nazad[number_group_stp], tmp, 10, tmp, 19);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD_PR, current_settings_prt.timeout_mtz_2_n_nazad_pr[number_group_stp], tmp, 11, tmp, 20);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI, current_settings_prt.timeout_mtz_2_po_napruzi[number_group_stp], tmp, 12, tmp, 21);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI_PR, current_settings_prt.timeout_mtz_2_po_napruzi_pr[number_group_stp], tmp, 13, tmp, 22);
      
      _OR6(p_global_trigger_state_mtz2, 0, tmp, 15, tmp, 16, tmp, 17, tmp, 18, tmp, 19, tmp_value, 29);
      _OR3(tmp, 20, tmp, 21, tmp, 22, tmp_value, 30);
      _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    }
    
    //Сраб.МТЗх
    if (_GET_OUTPUT_STATE(tmp_value, 31))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
  }
} 
void GP_TP_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void GP_TP_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
register long lV; 
register union { 
   struct {
      unsigned int gz_on : 1;//0
      unsigned int blk_gz :1;//1
      unsigned int gz1    :1;//2
      unsigned int gz2    :1;//3
      unsigned int gzrpn  :1;//4
      unsigned int tz_on  :1;//5
      unsigned int tz_blk :1;//6
      unsigned int tz_dv  :1;//7
	  
   } bool_vars;
  long lVl;
}wrp;
unsigned long u32_bit_holder = 0;

	wrp.lVl = 0;
	lV = (current_settings.control_GP & (1<< INDEX_ML_CTR_GP_STATE)) ;
	if(lV != 0)
		wrp.bool_vars.gz_on = 1;

	lV = _CHECK_SET_BIT(p_active_functions,RANG_BLOCK_GP);
	if(lV != 0){
		wrp.bool_vars.blk_gz = 1;


	
	lV = _CHECK_SET_BIT(p_active_functions, RANG_IN_GP1);
	if(lV != 0){
		wrp.bool_vars.gz1 = 1;	
	
	lV = _CHECK_SET_BIT(p_active_functions, RANG_IN_GP2);
	if(lV != 0)
		wrp.bool_vars.gz2 = 1;	
	lV = _CHECK_SET_BIT(p_active_functions, RANG_IN_GP_RPN);
	if(lV != 0)
		wrp.bool_vars.gzrpn = 1;		
	lV = _CHECK_SET_BIT(p_active_functions, RANG_IN_TP);
	if(lV != 0)
		wrp.bool_vars.tz_dv = 1;	
	lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_TP);
	if(lV != 0)
		wrp.bool_vars.tz_blk = 1;	
		
	lV = (current_settings.control_TP & (1<< INDEX_ML_CTR_TP_STATE)) ;
	if(lV != 0)
		wrp.bool_vars.tz_on = 1;
		
	lV = wrp.lVl&7;	
	if(lV == 0B101){
		u32_bit_holder |= 2;
		_TIMER_0_T(INDEX_TIMER_GZ1_TMP_04, 400, u32_bit_holder, 1, u32_bit_holder, 2);
	}else{
		//u32_bit_holder ~= 2;
		_TIMER_0_T(INDEX_TIMER_GZ1_TMP_04, 400, u32_bit_holder, 0, u32_bit_holder, 2);
	}
	//
	if (_GET_OUTPUT_STATE(u32_bit_holder, 2))
    _SET_BIT(p_active_functions, RANG_PO_GP1);
    else
    _CLEAR_BIT(p_active_functions, RANG_PO_GP1); 
	
	_TIMER_T_0(INDEX_TIMER_GZ1, current_settings_prt.timeout_GP1[number_group_stp], u32_bit_holder, 2, u32_bit_holder, 3);
	if (_GET_OUTPUT_STATE(u32_bit_holder, 3))
    _SET_BIT(p_active_functions, RANG_GP1);
    else
    _CLEAR_BIT(p_active_functions, RANG_GP1); 
	
	lV = wrp.lVl&0B1011;	
	if(lV == 0B1001){
		u32_bit_holder |= 0x10;
		_TIMER_0_T(INDEX_TIMER_GZ2_TMP_04, 400, u32_bit_holder,4 , u32_bit_holder,5 );
	}else{
		//u32_bit_holder ~= 2;
		_TIMER_0_T(INDEX_TIMER_GZ2_TMP_04, 400, u32_bit_holder, 0, u32_bit_holder,5 );
	}
	//
	if (_GET_OUTPUT_STATE(u32_bit_holder, 5))
    _SET_BIT(p_active_functions, RANG_PO_GP2);
    else
    _CLEAR_BIT(p_active_functions, RANG_PO_GP2); 
	_TIMER_T_0(INDEX_TIMER_GZ2, current_settings_prt.timeout_GP2[number_group_stp], u32_bit_holder, 5, u32_bit_holder, 6);
	if (_GET_OUTPUT_STATE(u32_bit_holder, 6))
    _SET_BIT(p_active_functions, RANG_GP2);
    else
    _CLEAR_BIT(p_active_functions, RANG_GP2); 
	
	
	
	lV = wrp.lVl&0B10011;	
	if(lV == 0B10001){
		u32_bit_holder |= ;
		_TIMER_0_T(INDEX_TIMER_GZ_RPN_TMP_04, 400, u32_bit_holder, 7, u32_bit_holder, 8);
	}else{
		//u32_bit_holder ~= 2;
		_TIMER_0_T(INDEX_TIMER_GZ_RPN_TMP_04, 400, u32_bit_holder, 0, u32_bit_holder, 8);
	}
	//
	if (_GET_OUTPUT_STATE(u32_bit_holder, 8))
    _SET_BIT(p_active_functions, RANG_PO_GP_RPN);
    else
    _CLEAR_BIT(p_active_functions, RANG_PO_GP_RPN); 
	_TIMER_T_0(INDEX_TIMER_GZ_RPN, current_settings_prt.timeout_GP_RPN[number_group_stp], u32_bit_holder, 9, u32_bit_holder, 10);
	if (_GET_OUTPUT_STATE(u32_bit_holder, 10))
    _SET_BIT(p_active_functions, RANG_GP_RPN);
    else
    _CLEAR_BIT(p_active_functions, RANG_GP_RPN); 
	
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
 