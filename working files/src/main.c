/* Includes ------------------------------------------------------------------*/
#include "constants.h"
#include "libraries.h"
#include "variables_global.h"
#include "functions_global.h"
#include "variables_global_m.h"

/*******************************************************************************/
//������ � Wotchdog
/*******************************************************************************/
inline void watchdog_routine(void)
{
  time_1_watchdog_input = time_2_watchdog_input;
  time_2_watchdog_input = TIM4->CNT;
  unsigned int delta_time;
  if (time_2_watchdog_input >= time_1_watchdog_input) delta_time = time_2_watchdog_input - time_1_watchdog_input;
  else delta_time = time_2_watchdog_input + 0xffff - time_1_watchdog_input;
  time_delta_watchdog_input = delta_time* 10;
  
  //������ � watchdogs � ��������� ��� ����� ������
  if((control_word_of_watchdog & UNITED_BITS_WATCHDOG) == UNITED_BITS_WATCHDOG)
  {
    //������� ���� ��� ����������� Watchdog �� �����������
//    if (test_watchdogs != CMD_TEST_EXTERNAL_WATCHDOG)
//    {
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );

      time_1_watchdog_output = time_2_watchdog_output;
      time_2_watchdog_output = TIM4->CNT;
      if (time_2_watchdog_output >= time_1_watchdog_output) delta_time = time_2_watchdog_output - time_1_watchdog_output;
      else delta_time = time_2_watchdog_output + 0xffff - time_1_watchdog_output;
      time_delta_watchdog_output = delta_time* 10;
//    }

    control_word_of_watchdog =  0;
  }
#ifdef DEBUG_TEST
  else
  {
    unsigned int time_1_watchdog_output_tmp = time_2_watchdog_output;
    unsigned int time_2_watchdog_output_tmp = TIM4->CNT;
    if (time_2_watchdog_output_tmp >= time_1_watchdog_output_tmp) delta_time = time_2_watchdog_output_tmp - time_1_watchdog_output_tmp;
    else delta_time = time_2_watchdog_output_tmp + 0xffff - time_1_watchdog_output_tmp;
    unsigned int time_delta_watchdog_output_tmp = delta_time* 10;
    
    if (time_delta_watchdog_output_tmp > 100000)
    {
      while(time_delta_watchdog_output_tmp != 0);
    }
  }
#endif

  if (restart_timing_watchdog == 0)
  {
    if (time_delta_watchdog_input < time_delta_watchdog_input_min) time_delta_watchdog_input_min = time_delta_watchdog_input;
    if (time_delta_watchdog_input > time_delta_watchdog_input_max) time_delta_watchdog_input_max = time_delta_watchdog_input;

    if (time_delta_watchdog_output < time_delta_watchdog_output_min) time_delta_watchdog_output_min = time_delta_watchdog_output;
    if (time_delta_watchdog_output > time_delta_watchdog_output_max) time_delta_watchdog_output_max = time_delta_watchdog_output;
  }
  else
  {
    restart_timing_watchdog = 0;
        
    time_delta_watchdog_input = 0;
    time_delta_watchdog_input_min = 0xffff*10;
    time_delta_watchdog_input_max = 0;
        
    time_delta_watchdog_output = 0;
    time_delta_watchdog_output_min = 0xffff*10;
    time_delta_watchdog_output_max = 0;
  }
}
/*******************************************************************************/

/*************************************************************************
��������� ���������������� ������
*************************************************************************/
inline void periodical_operations(void)
{
  //���� ����� SPI_1
  if (  
      (control_spi1_taskes[0] != 0) || 
      (control_spi1_taskes[1] != 0) || 
      (state_execution_spi1 > 0)
     )
  {
    mutex_spi1 = true;
    if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
    {
      main_routines_for_spi1();
    }
    mutex_spi1 = false;
  }

  //����� ����� I2C
  if (
      (control_i2c_taskes[0]     != 0) || 
      (driver_i2c.state_execution > 0)
     )
    main_routines_for_i2c();

  //������� �� ������� ����
  if (reinit_LCD)
  {
    reinit_LCD = false;
    lcd_init();
    new_state_keyboard |= (1<<BIT_REWRITE);
  }
  main_manu_function();
  //���������� ���������� �� ������
  view_whole_ekran();
    
  //������ � Watchdog
  watchdog_routine();

  //������ � �������� ���������� ����� ��� �����������
  if ((timeout_idle_new_settings >= current_settings.timeout_idle_new_settings) && (restart_timeout_idle_new_settings == 0))
  {
    if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) != 0) 
    {
      current_settings_interfaces = current_settings;
      type_of_settings_changed = 0;
      _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
    }
  }
  
  //���� �� USB
  if (current_settings.password_interface_USB)
  {
    unsigned int timeout = current_settings.timeout_deactivation_password_interface_USB;
    if ((timeout != 0) && (timeout_idle_USB >= timeout) && ((restart_timeout_interface & (1 << USB_RECUEST)) == 0)) password_set_USB = 1;
  }
  Usb_routines();

  //���� �� RS-485
  if (current_settings.password_interface_RS485)
  {
    unsigned int timeout = current_settings.timeout_deactivation_password_interface_RS485;
    if ((timeout != 0) && (timeout_idle_RS485 >= timeout) && ((restart_timeout_interface & (1 << RS485_RECUEST)) == 0)) password_set_RS485 = 1;
  }
  if(
     (RxBuffer_RS485_count != 0) &&
     (make_reconfiguration_RS_485 == 0) &&
     ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) == 0)
    )
  {
    //�� � ������, �� ���� ������ � ����  �� �������
      
    //������ � Watchdog
    watchdog_routine();

    //���������� �����
    inputPacketParserRS485();
    
    //�����������, �� ������� ��������� ���� ���� 0
    RxBuffer_RS485_count = 0;
  }
  else if (make_reconfiguration_RS_485 != 0)
  {
    //����� ����� ����������������� RS-485
      
    //���������� �� �� ����� ����� �� ��� �������� ����� �� ������� �����
    if (GPIO_ReadOutputDataBit(GPIO_485DE, GPIO_PIN_485DE) == Bit_RESET)
    {

      //����������������� USART ��� RS-485
      USART_RS485_Configure();

      //³��������� ���������� ������ RS-485
      restart_monitoring_RS485();
      
      //������� �������� ��� �������� ���������������� ���������� RS-485
      make_reconfiguration_RS_485 = 0;
    }
  }

  /*******************/
  //�������� ����������� �������� �����
  /*******************/
  /*
  � �������� ���������� ������ �����
  if ()
  else if()
  else if()
  ...
  else if ()
  ��� �� ���� ����� ������������ ����� ���� ��������, ����� ��� � ������ �����
  �� ���� ����� ����� �������� �� ������ ��������, ��� � �������.
  */
  if (periodical_tasks_CALC_POWER_DATA != 0)
  {
    //����� � ���� ������� ������ ���������� ��������� � ������
      
    calc_power_total();

    //������� ������� ������ ���������� ��������� � ������
    periodical_tasks_CALC_POWER_DATA = false;
  }
  else if (periodical_tasks_CALCULATION_ANGLE != 0)
  {
    //����� � ���� ������� ������ ���������� ����
      
    calc_angle();

    //������� ������� ������ ���������� ����
    periodical_tasks_CALCULATION_ANGLE = false;
  }
  else if (periodical_tasks_TEST_SETTINGS != 0)
  {
    //����� � ���� ������� ������ ������������ ������� ���������
    if ((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) != 0)
    {
      //�������� ��������� ����� ���, ���� ������� ��������� ���� ������ ���������
      if (
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT    ) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT ) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT    ) == 0) &&
          (changed_settings == CHANGED_ETAP_NONE)  
         ) 
      {
        //�� ����� ������� �� ��� �������-����� ������� ���������, ���� ����� �������� �������� �����������
        control_settings();

        //������� ������� ������ ������������ ������� ���������
        periodical_tasks_TEST_SETTINGS = false;
      }
    }
    else
    {
      //������� ������� ������ ������������ ������� ���������, �� �� ���� �� ������ ����������
      periodical_tasks_TEST_SETTINGS = false;
    }
  }
  else if (periodical_tasks_TEST_USTUVANNJA != 0)
  {
    //����� � ���� ������� ������ ������������ ��������� (� ��� �� ������������ ������ � �������� ������ ��������)
    if ((state_spi1_task & STATE_USTUVANNJA_EEPROM_GOOD) != 0)
    {
      //�������� ��������� ����� ���, ���� ��������� ���� ������ ���������
      if (
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT    ) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT ) == 0) &&
          (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT    ) == 0) &&
          (changed_ustuvannja == CHANGED_ETAP_NONE)  
         ) 
      {
        //�� ����� ������� �� ��� �������-����� ���������, ���� ����� �������� �������� �����������
        control_ustuvannja();

        //������� ������� ������ ������������ ���������
        periodical_tasks_TEST_USTUVANNJA = false;
      }
    }
    else
    {
      //������� ������� ������ ������������ ������� ���������, �� �� ���� �� ������ ����������
      periodical_tasks_TEST_USTUVANNJA = false;
    }
  }
  else if (periodical_tasks_TEST_TRG_FUNC_LOCK != 0)
  {
    //����� � ���� ������� ������ ������������ �� ��������� ��ﳿ ��� ������� ����������
    //�������� ��
    control_trg_func();
      
    //������� ������� ������ ������������ �� ��������� ��ﳿ ��� ������� ����������
    periodical_tasks_TEST_TRG_FUNC_LOCK = false;
  }
  else if (periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK != 0)
  {
    //����� � ���� ������� ������ ������������ �� ��������� ��ﳿ ��� ����������� ����������
    //�������� ��
    unsigned int result;
    result = control_info_rejestrator(&info_rejestrator_ar_ctrl, crc_info_rejestrator_ar_ctrl);
      
    if (result == 1)
    {
      //�������� ����������� ���������� ������� ������
    
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_AR_CONTROL_BIT);
    }
    else
    {
      //�������� ����������� ���������� �� �������

      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_AR_CONTROL_BIT);
    }

    //������� ������� ������ ������������ �� ��������� ��ﳿ ��� ����������� ����������
    periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = false;
  }
  else if (periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK != 0)
  {
    //����� � ���� ������� ������ ������������ �� ��������� ��ﳿ ��� ����������� ����������
    //�������� ��
    unsigned int result;
    result = control_info_rejestrator(&info_rejestrator_dr_ctrl, crc_info_rejestrator_dr_ctrl);
      
    if (result == 1)
    {
      //�������� ����������� ���������� ������� ������
    
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT);
    }
    else
    {
      //�������� ����������� ���������� �� �������

      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT);
    }

    //������� ������� ������ ������������ �� ��������� ��ﳿ ��� ����������� ����������
    periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = false;
  }
  else if (periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK != 0)
  {
    //����� � ���� ������� ������ ������������ �� ��������� ��ﳿ ��� ���������� ���������� ����
    //�������� ��
    unsigned int result;
    result = control_info_rejestrator(&info_rejestrator_pr_err_ctrl, crc_info_rejestrator_pr_err_ctrl);
      
    if (result == 1)
    {
      //�������� ����������� ���������� ������� ������
    
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT);
    }
    else
    {
      //�������� ����������� ���������� �� �������

      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT);
    }

    //������� ������� ������ ������������ �� ��������� ��ﳿ ��� ����������� ����������
    periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = false;
  }
  /*******************/

  //ϳ�������� ������� ������ ��������-��������
  if(resurs_temp < 0xfffffffe) resurs_temp++;

  watchdog_routine();
}
/*************************************************************************/

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
//  /************************************************************/
//  //�������� ���������� ���� ��������
//  /************************************************************/
//  {
//    unsigned short sum = 0;
//    unsigned char *point = ((unsigned char *)&__checksum_begin);
//    for (unsigned int i = ((unsigned int)&__checksum_end -(unsigned int)&__checksum_begin +1); i > 0; i--)
//      sum += *point++;
//    if (sum != (unsigned short)__checksum)
//    {
//      while(1);
//    }
//  }
//  /************************************************************/
  
  /************************************************************/
  //�������� ������������
  /************************************************************/
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_Conf();            /* Configure and initialize SystemView  */
#endif
  
  //����������� ���� ��� ������� �������� � ������������ ����� ������, � ��� ������������ ������, RTC ����'����� ��� ���������� ��������
  _SET_BIT(set_diagnostyka, EVENT_STOP_SYSTEM_BIT);
  changing_diagnostyka_state();//ϳ����������� ����� ����� ��� ���������� ���������� ����
  
  //����������, �� ��������: ������ �������, �� ���������� (���������� ������ ������� ��� ������ ������������ ��������) 
  if (RCC_GetFlagStatus(RCC_FLAG_SFTRST) == SET)
  {
    //����������� ���� ��� ���������� ���������� ��������
    _SET_BIT(set_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT);
  }
  else if (RCC_GetFlagStatus(RCC_FLAG_BORRST/*RCC_FLAG_PORRST*/) != SET)
  {
    //����������� ���� ��� ���������� �������� (�� �� ����������� ���� Power-on/Power-down)
    _SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT);
  }
  else
  {
    //����������� ���� ��� ������ �������� 
    _SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT);
  }
  //������� ��������
  RCC->CSR |= RCC_CSR_RMVF;
  changing_diagnostyka_state();//ϳ����������� ����� ����� ��� ���������� ���������� ����

  //�������� ��������� ������� ���������
  start_settings_peripherals();
  
  if(
     ((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) != 0) &&
     ((state_spi1_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
    )   
  {
    //�������, ���� ��������� ������ �������
          
    /*******************************************************/
    //���������� �������� ��� ����������� ������� � ������� �������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ���� �� ���������)*/
    {
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
        ustuvannja_meas[k] = ustuvannja[k];

        //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
        phi_ustuvannja_meas[k] = phi_ustuvannja[k];
        phi_ustuvannja_sin_cos_meas[2*k    ] = phi_ustuvannja_sin_cos[2*k    ];
        phi_ustuvannja_sin_cos_meas[2*k + 1] = phi_ustuvannja_sin_cos[2*k + 1];
      }
      
      //�������, �� ���� ������� ���� ���������
      changed_ustuvannja = CHANGED_ETAP_NONE;
    }

    if (changed_settings == CHANGED_ETAP_ENDED)  /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ �������� ������� (� ��� ����� ����� ���� �� ���������)*/
    {
      //������� ������� ��������� � ���� ���� ������� ��� � ���� ������ (���� � �����) ����� ������� �������
      current_settings_prt = current_settings;
      ch_type_voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;

      ctr_transformator_I_VH_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VH) & 0x1;
      ctr_transformator_I_VL_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VL) & 0x1;
      for (size_t n_g = 0; n_g < NUMBER_GROUP_USTAVOK; n_g++)pickup_ozt_k_meas[n_g] = current_settings_prt.pickup_ozt_k[n_g];
      KOEF_VH_VL(type_con_ozt_meas, koef_VH_meas, koef_VL_meas);
      
      //�������, �� ���� ������� ���� ���������
      changed_settings = CHANGED_ETAP_NONE;
    }
    /*******************************************************/
  
    //��������� ������ ������� ����������� �������
    TIM_Cmd(TIM5, ENABLE);
    // ��������� ������ ������� ������� �������
    TIM_Cmd(TIM2, ENABLE);

    //������������ LCD
    lcd_init();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  else
  {
    //�������, ���� ��������� ������ �� �������, ��� �� ������ ����
    
    //������������ LCD
    lcd_init();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  
    //���� ��������� �� ������� ������ � EEPROM, �� �������� �������� �� ����� ����������� ��� ��
    while (
           ((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) == 0) ||
           ((state_spi1_task & STATE_TRG_FUNC_EEPROM_GOOD) == 0)
          )   
    {
      error_reading_with_eeprom();
    }

    /*****/
    /*
    ������� ��������� ���������� �� ����������� ��������� ������� ��������� 
    ����������� � ��������� ������������, � �� �������, ��, �������, �������� 
    ����� ����������� � ������������� ������ �� ������ ��������� (�� ���� 
    �� ����� ���� �������� ���������� ��������� � ��� ���������� ������������)
    */
    /*****/
    //����������� ������� ������ ���� ��������� � EEPROM
    /*
    ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
    �� �� ����� ��������������� ������������ ����� ���������� �� �����������
    ���������� ���������� ��������� � ������� ������� ���������
    info_rejestrator_ar � �������� �����. �� ��������� ��������� � ������� 
    "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
    ������ ������� ���������.
    � ����� ������� �� �������, ��� ������� ����� �� �����������, 
    �� ����� ����������� �������� main_routines_for_spi1 - ��� ���������� �� ������ � ���� �
    ���� ������������, �� � ������� main.
    ����� �������� ����� ���� �� ������� ������� main_routines_for_spi1, � �� ��� �������
    ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
    �� ����� ����������� ������� (�� ������� ������� main_routines_for_spi1)
    */
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
    info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
    info_rejestrator_ar.saving_execution = 0;
    info_rejestrator_ar.number_records = 0;
    while(
          (control_spi1_taskes[0]     != 0) ||
          (control_spi1_taskes[1]     != 0) ||
          (state_execution_spi1 > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ����������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog =  0;
      }

      main_routines_for_spi1();
    }
    /*****/
          
    /*******************************************************/
    //���������� �������� ��� ����������� ������� � ������� �������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ���� �� ���������)*/
    {
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
        ustuvannja_meas[k] = ustuvannja[k];

        //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
        phi_ustuvannja_meas[k] = phi_ustuvannja[k];
        phi_ustuvannja_sin_cos_meas[2*k    ] = phi_ustuvannja_sin_cos[2*k    ];
        phi_ustuvannja_sin_cos_meas[2*k + 1] = phi_ustuvannja_sin_cos[2*k + 1];
      }
      
      //�������, �� ���� ������� ���� ���������
      changed_ustuvannja = CHANGED_ETAP_NONE;
    }

    if (changed_settings == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ �������� ������� (� ��� ����� ����� ���� �� ���������)*/
    {
      //������� ������� ��������� � ���� ���� ������� ��� � ���� ������ (���� � �����) ����� ������� �������
      current_settings_prt = current_settings;
      ch_type_voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;

      ctr_transformator_I_VH_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VH) & 0x1;
      ctr_transformator_I_VL_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VL) & 0x1;
      for (size_t n_g = 0; n_g < NUMBER_GROUP_USTAVOK; n_g++)pickup_ozt_k_meas[n_g] = current_settings_prt.pickup_ozt_k[n_g];
      KOEF_VH_VL(type_con_ozt_meas, koef_VH_meas, koef_VL_meas);
      
      //�������, �� ���� ������� ���� ���������
      changed_settings = CHANGED_ETAP_NONE;
    }
    /*******************************************************/
    
    //��������� ������ ������� ����������� �������
    TIM_Cmd(TIM5, ENABLE);
    //��������� ������ ������� ������� �������
    TIM_Cmd(TIM2, ENABLE);
  }
  changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����

  /**********************/
  //������������ USB
  /**********************/
  //������ � watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //������� ���� ��� ����������� Watchdog �� �����������
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
    control_word_of_watchdog =  0;
  }
  
  USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS 
            USB_OTG_HS_CORE_ID,
#else            
            USB_OTG_FS_CORE_ID,
#endif  
            &USR_desc, 
            &USBD_CDC_cb, 
            &USR_cb);
  
  //������ � watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //������� ���� ��� ����������� Watchdog �� �����������
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
    control_word_of_watchdog =  0;
  }
  /**********************/
    
  //���������, �� ����� ����� ������ ����� ���������� � �������
  if (current_settings.password_interface_RS485 == 0) password_set_RS485 = 0;
  else password_set_RS485 = 1;
  timeout_idle_RS485 = current_settings.timeout_deactivation_password_interface_RS485;
  
  if (current_settings.password_interface_USB   == 0) password_set_USB   = 0;
  else password_set_USB   = 1;
  timeout_idle_USB = current_settings.timeout_deactivation_password_interface_USB;

  timeout_idle_new_settings = current_settings.timeout_idle_new_settings;
  
  //�������� �������������� �������� DataFlash
  start_checking_dataflash();
  
  //��������� ��������� ���������� ����� ����� 1 �� �� ������ 2 ������� 4 ��� ��������� ���������� ����������������� �����
  start_tim4_canal2_for_interrupt_1mc();
  
  //ϳ��������� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
  calculate_namber_bit_waiting_for_rs_485();
  //��������� ��������� ���������� � ��������� ������� (��� ���������� ���������� �������) �� ������ 3 ������� 4 ��� RS-485
  start_tim4_canal3_for_interrupt_10mkc();
  //���������� USART �� ������ � RS-485
  USART_RS485_Configure();
  //�������� ���������� ������ RS-485
  restart_monitoring_RS485();
  /************************************************************/

  //����������� �������, �� �� ������ ����� �������� �������� ����������
  new_state_keyboard |= (1<<BIT_REWRITE);
  
  //������ � watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //������� ���� ��� ����������� Watchdog �� �����������
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
    control_word_of_watchdog =  0;
  }
  restart_resurs_count = 0xff;/*��������� �������� ����������� ���������*/

  /**********************/
  //����������� I2C
  /**********************/
//  low_speed_i2c = 0xff;
  Configure_I2C(I2C);
  /**********************/

  //����������� �������, �� ������ ��������� �� ������� RTC, � ����, ��� ������ ������������� ���� ����
  //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ������������������ � ������� ����������� �������
  _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
  _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
  
  
  time_2_watchdog_input = time_2_watchdog_output = TIM4->CNT;
  restart_timing_watchdog = 0xff;
  

  /* ��������� ������ */
  while (1)
  {
    if (periodical_tasks_TEST_FLASH_MEMORY != 0)
    {
      /************************************************************/
      //�������� ���������� ���� ��������
      /************************************************************/
      unsigned short sum = 0;
      unsigned char *point = ((unsigned char *)&__checksum_begin);
      for (unsigned int i = ((unsigned int)&__checksum_end -(unsigned int)&__checksum_begin +1); i > 0; i--)
      {
        sum += *point++;
        periodical_operations();
      }
      if (sum != (unsigned short)__checksum) _SET_BIT(set_diagnostyka, ERROR_INTERNAL_FLASH_BIT);
      else _SET_BIT(clear_diagnostyka, ERROR_INTERNAL_FLASH_BIT);
      /************************************************************/

      periodical_tasks_TEST_FLASH_MEMORY = false;
    }
    else periodical_operations();
  }
}
/*******************************************************************************/

/*******************************************************************************/
//��������� ������� ����������� ������������
/*******************************************************************************/
void total_error_sw_fixed(unsigned int number)
{
  total_error = number;
  while (1);
}
/*******************************************************************************/

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
