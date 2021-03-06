#include "header.h"

/*****************************************************/
//����� ������ ������ ��� ���������
/*****************************************************/
inline void find_new_ADC_canal_to_read(unsigned int command_word_adc_diff, unsigned int *point_active_index_command_word_adc)
{
  unsigned int command_word_adc_diff_tmp = command_word_adc_diff;
  unsigned int command_word_adc_diff_fapch = command_word_adc_diff_tmp & maska_canaliv_fapch;
    
  if (
      ((status_adc_read_work & DATA_VAL_READ) != 0) &&
      (command_word_adc_diff_fapch != 0) 
     )  
  {
    command_word_adc_diff_tmp = command_word_adc_diff_fapch;
  }
  else
  {
    command_word_adc_diff_tmp &= (unsigned int)(~maska_canaliv_fapch);
  }
  
  while ((command_word_adc_diff_tmp & (1 << (*point_active_index_command_word_adc))) == 0)
  {
    /*
    �� �� �������� ������, ���� ����� ������������
    */
    *point_active_index_command_word_adc = (*point_active_index_command_word_adc + 1) % NUMBER_INPUTs_ADCs;
  }
}
/*****************************************************/

/*****************************************************/
//��������� �������� ����� � ���
/*****************************************************/
void control_reading_ADCs(void)
{
  //���������� ������ �������� ����� � �������� �� ������ ����� ������������
  if (adc_DATA_VAL_read != 0)
  {
    adc_DATA_VAL_read = false;
    status_adc_read_work |= DATA_VAL_READ;
      
    /*
    ������ �� ���� ���� ��������������� ������� ����� �������������� �� 
    ����� ������ �� ����������� ������� ������ ������� ���������
    */
    command_word_adc      &= (unsigned int)(~maska_canaliv_fapch);
    command_word_adc_work &= (unsigned int)(~maska_canaliv_fapch);
        
    command_word_adc |= READ_DATA_VAL;
  }

  if (adc_TEST_VAL_read != 0) 
  {
    adc_TEST_VAL_read = false;
    status_adc_read_work |= TEST_VAL_READ;
      
    command_word_adc |= READ_TEST_VAL;
  }
  
  unsigned int command_word_adc_diff = command_word_adc ^ command_word_adc_work;
  if (command_word_adc_diff != 0)
  {
    /*
    � ������, �� ������� �� ���������
    */
    find_new_ADC_canal_to_read(command_word_adc_diff, &active_index_command_word_adc);
      
    /*
    ����� active_index_command_word_adc ����� � ����� input_adc �� �����, 
    ���� ����� ����������
    */
      
    /*
    ���������, ���� ����� �������� ���
    */
    unsigned int active_adc_old = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 1 : 2;

    /*
    ���������, ���� ����� ����� ������������ ��� � �� ���� ����� ��������
    */
    unsigned int active_adc_new = input_adc[active_index_command_word_adc][0];
    unsigned int command_word = input_adc[active_index_command_word_adc][1];
    
    //��������� ��������� ����
    if (
        (state_reading_ADCs == STATE_READING_ADCs_NONE) ||
        (state_reading_ADCs == STATE_READING_READ     )
       )
    {
      state_reading_ADCs = STATE_READING_WRITE;
      /*
      ��������� ��������� ���
      */
      switch (active_adc_new)
      {
      case 1:
        {
          //���1
          GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
          break;
        }
        case 2:
        {
          //���2
          GPIO_SELECT_ADC->BSRRL = GPIO_SELECTPin_ADC;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(50);
        } 
      }
    }
    else
    {
      if (active_adc_old == active_adc_new)
      {
        state_reading_ADCs = STATE_READING_WRITE_READ;
      }
      else
      {
        state_reading_ADCs = STATE_READING_READ;
        command_word = 0;
      }
    }
    
    if (command_word != 0)
    {
      /*
      �������, �� ����� ������ ���� �������� ����� ����������
      */
      command_word_adc_work |= (1 << active_index_command_word_adc);
    }

    //�������� �������� �����
    while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
    GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
    SPI_ADC->DR = (uint16_t)command_word;                   //³���������� �������� �����
    
    channel_answer = channel_request;
    channel_request = (active_adc_new - 1)*NUMBER_CANALs_ADC + ((command_word >> 10) & 0xf);
  }
  else 
  {
    if (
        (state_reading_ADCs == STATE_READING_READ     ) ||
        (state_reading_ADCs == STATE_READING_ADCs_NONE)
       )
    {
      //�� ������ ��� ����������
      state_reading_ADCs = STATE_READING_ADCs_NONE;

      command_word_adc = 0;
      command_word_adc_work = 0;
      active_index_command_word_adc = 0;
    }
    else
    {
      /*
      ����� �� �������� �������� � ���������� ��������, ���� ����� �����
      ���� �������������
      */
      state_reading_ADCs = STATE_READING_READ;
      while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
      GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
      SPI_ADC->DR = 0;                                        //³���������� ����� (��� ���, ��� ���� ���������� ����� �� ������������)
    
      channel_answer = channel_request;
    }
  }
}
/*****************************************************/

/*************************************************************************
����������� ����������� ��������
 *************************************************************************/
void operate_test_ADCs(void)
{
  /*******************************************************
  ������������� ���������� �������� ����������� �����
  *******************************************************/
  unsigned int temp;

  //GND ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_COARSE_BIT);
  unsigned int gnd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_GND_ADC1; i++)
  {
    temp = output_adc[index_GND_ADC1[i]].value;
    gnd_adc1_averange_sum[i] += temp;
    gnd_adc1_averange_sum[i] -= gnd_adc1_moment_value[i][index_array_of_one_value];
    gnd_adc1_moment_value[i][index_array_of_one_value] = temp;
    gnd_tmp += gnd_adc1_averange[i] = gnd_adc1_averange_sum[i] >> VAGA_NUMBER_POINT;
    if (temp > 0xA1) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_COARSE_BIT);
  }
  gnd_adc1 = gnd_tmp / NUMBER_GND_ADC1;
  
  //GND ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_COARSE_BIT);
  gnd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_GND_ADC2; i++)
  {
    temp = output_adc[index_GND_ADC2[i]].value;
    gnd_adc2_averange_sum[i] += temp;
    gnd_adc2_averange_sum[i] -= gnd_adc2_moment_value[i][index_array_of_one_value];
    gnd_adc2_moment_value[i][index_array_of_one_value] = temp;
    gnd_tmp += gnd_adc2_averange[i] = gnd_adc2_averange_sum[i] >> VAGA_NUMBER_POINT;
    if (temp > 0xA1) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_COARSE_BIT);
  }
  gnd_adc2 = gnd_tmp / NUMBER_GND_ADC2;

  //VREF ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC1_TEST_COARSE_BIT);
  unsigned int vref_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_VREF_ADC1; i++)
  {
    temp = output_adc[index_VREF_ADC1[i]].value;
    vref_adc1_averange_sum[i] += temp;
    vref_adc1_averange_sum[i] -= vref_adc1_moment_value[i][index_array_of_one_value];
    vref_adc1_moment_value[i][index_array_of_one_value] = temp;
    vref_tmp += vref_adc1_averange[i] = vref_adc1_averange_sum[i] >> VAGA_NUMBER_POINT;
    if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_COARSE_BIT);
  }
  vref_adc1 = vref_tmp / NUMBER_VREF_ADC1;
  
  //VREF ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC2_TEST_COARSE_BIT);
  vref_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_VREF_ADC2; i++)
  {
    temp = output_adc[index_VREF_ADC2[i]].value;
    vref_adc2_averange_sum[i] += temp;
    vref_adc2_averange_sum[i] -= vref_adc2_moment_value[i][index_array_of_one_value];
    vref_adc2_moment_value[i][index_array_of_one_value] = temp;
    vref_tmp += vref_adc2_averange[i] = vref_adc2_averange_sum[i] >> VAGA_NUMBER_POINT;
    if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_COARSE_BIT);
  }
  vref_adc2 = vref_tmp / NUMBER_VREF_ADC2;

  //VDD ��� ���1
  _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_COARSE_BIT);
  unsigned int vdd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_VDD_ADC1; i++)
  {
    temp = output_adc[index_VDD_ADC1[i]].value;
    vdd_adc1_averange_sum[i] += temp;
    vdd_adc1_averange_sum[i] -= vdd_adc1_moment_value[i][index_array_of_one_value];
    vdd_adc1_moment_value[i][index_array_of_one_value] = temp;
    vdd_tmp += vdd_adc1_averange[i] = vdd_adc1_averange_sum[i] >> VAGA_NUMBER_POINT;
    if ((temp <0x6F2) || (temp > 0xF5B)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_COARSE_BIT);
  }
  vdd_adc1 = vdd_tmp / NUMBER_VDD_ADC1;
  
  //VDD ��� ���2
  _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_COARSE_BIT);
  vdd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_VDD_ADC2; i++)
  {
    temp = output_adc[index_VDD_ADC2[i]].value;
    vdd_adc2_averange_sum[i] += temp;
    vdd_adc2_averange_sum[i] -= vdd_adc2_moment_value[i][index_array_of_one_value];
    vdd_adc2_moment_value[i][index_array_of_one_value] = temp;
    vdd_tmp += vdd_adc2_averange[i] = vdd_adc2_averange_sum[i] >> VAGA_NUMBER_POINT;
    if ((temp <0x6F2) || (temp > 0xF5B)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_COARSE_BIT);
  }
  vdd_adc2 = vdd_tmp / NUMBER_VDD_ADC2;
  
  //�� ������ ���� �������� �� ��� ����������  
  if((++index_array_of_one_value) == NUMBER_POINT)
    index_array_of_one_value = 0;
  else if (index_array_of_one_value > NUMBER_POINT)
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(21);
  }
  /*******************************************************/
}
/*************************************************************************/

/*************************************************************************
����������� ���� ��� ������������ ���'�
 *************************************************************************/
void Fourier(void)
{
  unsigned int index_period_array_tmp = index_period_array;
  int *p_data_sin = data_sin[index_period_array_tmp];
  int *p_data_cos = data_cos[index_period_array_tmp];
  int *p_data_0   = data_0[index_period_array_tmp];

  unsigned int i_ort_tmp = 0;
  for (size_t i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    //������� ������ �������� ��� ����� ����������
    int temp_value_1 = ADCs_data[i];

    int temp_value_2;
    
    //������������ SIN
    ortogonal_irq[i_ort_tmp] -= *p_data_sin;
    temp_value_2 = (int)((float)temp_value_1*sin_data_f[index_period_array_tmp]);
    *p_data_sin = temp_value_2;
    p_data_sin++;
    ortogonal_irq[i_ort_tmp++] += temp_value_2;
    
    //������������ COS
    ortogonal_irq[i_ort_tmp] -= *p_data_cos;
    temp_value_2 = (int)((float)temp_value_1*sin_data_f[(index_period_array_tmp + (NUMBER_POINT >> 2)) & 0x1f]);
    *p_data_cos = temp_value_2;
    p_data_cos++;
    ortogonal_irq[i_ort_tmp++] += temp_value_2;
  }
  
  unsigned int i_ort_ap_tmp = 0;
  for (size_t i = NUMBER_ANALOG_CANALES; i < NUMBER_ANALOG_CANALES_WITH_CALC; i++)
  {
    //�������  ������� ���.������
    
    //������� ������ �������� ��� ����� ����������
    int temp_value_1 = ADCs_data[i];
    
    //����������� ��������
    aperiodic_irq[i_ort_ap_tmp] -= *p_data_0;
    *p_data_0 = temp_value_1;
    p_data_0++;
    aperiodic_irq[i_ort_ap_tmp++] += temp_value_1;

    const uint32_t garm[3] = {1, 2, 5};
    for (size_t j = 0; j < 3; j++)
    {
      int temp_value_2;
      
      //������������ SIN
      ortogonal_irq[i_ort_tmp] -= *p_data_sin;
      temp_value_2 = (int)((float)temp_value_1*sin_data_f[(garm[j]*index_period_array_tmp) & 0x1f]);
      *p_data_sin = temp_value_2;
      p_data_sin++;
      ortogonal_irq[i_ort_tmp++] += temp_value_2;
    
      //������������ COS
      ortogonal_irq[i_ort_tmp] -= *p_data_cos;
      temp_value_2 = (int)((float)temp_value_1*sin_data_f[(garm[j]*index_period_array_tmp + (NUMBER_POINT >> 2)) & 0x1f]);
      *p_data_cos = temp_value_2;
      *p_data_cos++;
      ortogonal_irq[i_ort_tmp++] += temp_value_2;
    
    }
  }
  
  if((++index_period_array_tmp) >= NUMBER_POINT) index_period_array_tmp = 0;
  index_period_array = index_period_array_tmp;

  //��������� ��� ����� ������
  unsigned int bank_ortogonal_tmp = bank_ortogonal;
  for(size_t i = 0; i < (2*(NUMBER_ANALOG_CANALES + 3*(NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES))); i++ ) ortogonal[bank_ortogonal_tmp][i] = ortogonal_irq[i];
  for(size_t i = 0; i < (NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES); i++ )aperiodic[bank_ortogonal_tmp][i] = aperiodic_irq[i];
}
/*************************************************************************/

/*************************************************************************
�������� ������� ��� ������ ����� 1
*************************************************************************/
void fapch(void)
{
  unsigned int bank_measurement_high_tmp = bank_measurement_high;
  int index_1 = -1;
  unsigned int maska_canaliv_fapch_tmp = 0;

  /*****
  ������ ������ �� ����� ������ ������������� �������
  *****/  
  if (measurement_high[bank_measurement_high_tmp][IM_UA] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UA;
    maska_canaliv_fapch_tmp = READ_Ua;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UB] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UB;
    maska_canaliv_fapch_tmp = READ_Ub;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UC] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UC;
    maska_canaliv_fapch_tmp = READ_Uc;
  }
  maska_canaliv_fapch = maska_canaliv_fapch_tmp;
  /*****/

  uint32_t step_timer_adc_tmp;
  /*****/
  //�������
  /*****/
  step_timer_adc_tmp = step_timer_adc;
  if (
      (index_1 >= 0) &&
      (fix_perechid_cherez_nul[index_1] != 0)
     )   
  {
    fix_perechid_cherez_nul[index_1] = 0;
    
    unsigned int delta_tick;
    long long tick_tmp;
    int delta_value;
    unsigned int tick_p, x1_tmp, x2_tmp;
      
    /*��������� ��� �������� ����� 0 ������������ ���� � ����������� ������ ������������*/
    delta_value = perechid_cherez_nul[index_1][0].y2 - perechid_cherez_nul[index_1][0].y1;
    x1_tmp = perechid_cherez_nul[index_1][0].x1;
    x2_tmp = perechid_cherez_nul[index_1][0].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][0].x1) - ((long long)perechid_cherez_nul[index_1][0].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_p = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_p = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_p = (unsigned int)tick_tmp;
      }
    }

    /*��������� ��� �������� ����� 0 ��������� ���� � ����������� ������ ������������*/
    delta_value = perechid_cherez_nul[index_1][1].y2 - perechid_cherez_nul[index_1][1].y1;
    x1_tmp = perechid_cherez_nul[index_1][1].x1;
    x2_tmp = perechid_cherez_nul[index_1][1].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][1].x1) - ((long long)perechid_cherez_nul[index_1][1].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_c = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_c = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_c = (unsigned int)tick_tmp;
      }
    }
    /***/
      
    if (tick_c > tick_p) delta_tick = tick_c - tick_p;
    else
    {
      long long delta_tick_64 = tick_c + 0x100000000 - tick_p;
      delta_tick = delta_tick_64;
    }
    tick_period = delta_tick;
    
    /*****
    ���������� �������
    *****/
    if (
        (tick_period <= MAX_TICK_PERIOD) &&
        (tick_period >= MIN_TICK_PERIOD)
       ) 
    {
      frequency = (float)MEASUREMENT_TIM_FREQUENCY/(float)tick_period;

      step_timer_adc_tmp = tick_period >> VAGA_NUMBER_POINT;
      if ((tick_period - (step_timer_adc_tmp << VAGA_NUMBER_POINT)) >= (1 << (VAGA_NUMBER_POINT - 1))) step_timer_adc_tmp++;
    }
    else
    {
      step_timer_adc_tmp = TIM5_CCR1_2_VAL;
      if (tick_period > MAX_TICK_PERIOD) frequency = -2; /*������� ����� ������ ����������� ���������� MIN_FREQUENCY*/
      else frequency = -3; /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
    }
    /****/
  }
  else
  {
    if (index_1 < 0)
    {
      step_timer_adc_tmp = TIM5_CCR1_2_VAL;
      frequency = -1; /*������� �� ���������*/
    }
  }
  /*****/

  /*****/
  //����
  /*****/
  if (step_timer_adc != step_timer_adc_tmp)
  {
    //����� ������ ������� �������������
    step_timer_adc = step_timer_adc_tmp;
  }
  
  if ((command_restart_monitoring_frequency & (1 << 0)) != 0)
  {
    frequency_min = 50;
    frequency_max = 50;
    
    command_restart_monitoring_frequency &= (unsigned int)(~(1 << 0));
  }
  else
  {
    if (frequency >= 0)
    {
      if (frequency > frequency_max) frequency_max = frequency;
      if (frequency < frequency_min) frequency_min = frequency;
    }
  }
  /*****/
}
/*****************************************************/

/*****************************************************/
//����������� �� ���������� ����� �� ������ SPI, ���� ��������� ����������� �������
/*****************************************************/
void SPI_ADC_IRQHandler(void)
{
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordEnterISR();
//#endif

  //Գ����� ���� � ����������� ������� ����� �� ���
  semaphore_adc_irq  = true;
  
  //Գ����� ��� ���������
  uint32_t tick_output_adc_tmp = TIM5->CNT;
  
  //�� ������ ������� ������� chip_select
  GPIO_SPI_ADC->BSRRL = GPIO_NSSPin_ADC;
  uint16_t read_value = SPI_ADC->DR;

  static uint32_t tick_output_adc_p;
  /*
  �������� ������� ����
  */
  if (
      (state_reading_ADCs == STATE_READING_WRITE_READ) ||
      (state_reading_ADCs == STATE_READING_READ)
     )
  {
    unsigned int shift = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 0 : NUMBER_CANALs_ADC;
    unsigned int number_canal = shift + ((read_value >> 12) & 0xf);
    
    output_adc[number_canal].tick = tick_output_adc_p;
    
    static uint32_t error_spi_adc;
    if(channel_answer != number_canal) 
    {
      if (error_spi_adc < 3 ) error_spi_adc++;
      if (error_spi_adc >= 3 )_SET_BIT(set_diagnostyka, ERROR_SPI_ADC_BIT);
    }
    else 
    {
      error_spi_adc = 0;
      
      _SET_BIT(clear_diagnostyka, ERROR_SPI_ADC_BIT);
      output_adc[number_canal].value = read_value & 0xfff;
    }
  }
  tick_output_adc_p = tick_output_adc_tmp;
  /***/
  
  //�������� �������� � ������� ���
  control_reading_ADCs();
  
  /*
  �������� �� �������� ����� ���, ���� �� ������ ��� ����������
  */
  if (state_reading_ADCs == STATE_READING_ADCs_NONE)
  {
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
    /*******************************************************/
    //����������, �� ���������� ���� ���������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ���� �� ���������)*/
    {
      //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        ustuvannja_meas[k] = ustuvannja[k];
      }
      
      //�������, �� ���� ������� ������������ ��������, ��� �� ����� �������� �������� �������
      changed_ustuvannja = CHANGED_ETAP_ENDED_EXTRA_ETAP;
    }
    /*****************************************************/

    /*******************************************************/
    //����������, �� ���������� ���� �����������
    /*******************************************************/
    if (changed_settings == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*�� � �����, �� ��� ���� ����������� ��� �������� �� � ������ �������� �������(� ��� ����� ����� ���� �� ���������)*/
    {
      //������� ������������, �� ������� ������������ ������
      ctr_transformator_I_VH_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VH) & 0x1;
      ctr_transformator_I_VL_meas = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_I_VL) & 0x1;
      for (size_t n_g = 0; n_g < NUMBER_GROUP_USTAVOK; n_g++)pickup_ozt_k_meas[n_g] = current_settings_prt.pickup_ozt_k[n_g];
      KOEF_VH_VL(type_con_ozt_meas, koef_VH_meas, koef_VL_meas);
      
      //�������, �� ���� ������� �������� �������
      changed_settings = CHANGED_ETAP_NONE;
    }
    /*****************************************************/

    /*
    ������� �������� ������������� ������
    */
    unsigned int command_word = 0;
    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      command_word |= (1 << I_Ia_H) | (1 << I_Ib_H) | (1 << I_Ic_H) |
                      (1 << I_Ia_L) | (1 << I_Ib_L) | (1 << I_Ic_L) |
                      (1 << I_Ua  ) | (1 << I_Ub  ) | (1 << I_Uc  );
    }
      
    uint32_t _x1, _x2, _DX, _dx;
    int _y1, _y2;
    long long _y;
      
    uint32_t _x = previous_tick_DATA_VAL;

    unsigned int gnd_adc  = gnd_adc1; 
    unsigned int vref_adc = vref_adc1; 

    /*****/
    //������� �������� Ua
    /*****/
    if ((command_word & (1 << I_Ua)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ua].tick;
      _y1 = ADCs_data_raw[I_Ua].value;
      
      _y2 = output_adc[C_Ua_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ua_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ua])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ua_16].value - gnd_adc - vref_adc;
      
        _x2 = output_adc[C_Ua_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ua])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
        {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
        }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);
      
      if ((_y >= 0) && (ADCs_data[I_Ua] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //���������� �������
        perechid_cherez_nul[INDEX_PhK_UA][0].x1 = poperednij_perechid.Ua_x1;
        perechid_cherez_nul[INDEX_PhK_UA][0].y1 = poperednij_perechid.Ua_y1;
        perechid_cherez_nul[INDEX_PhK_UA][0].x2 = poperednij_perechid.Ua_x2;
        perechid_cherez_nul[INDEX_PhK_UA][0].y2 = poperednij_perechid.Ua_y2;
          
        //�������� �������
        poperednij_perechid.Ua_x1 = perechid_cherez_nul[INDEX_PhK_UA][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Ua_y1 = perechid_cherez_nul[INDEX_PhK_UA][1].y1 = ADCs_data[I_Ua];
        poperednij_perechid.Ua_x2 = perechid_cherez_nul[INDEX_PhK_UA][1].x2 = _x;
        poperednij_perechid.Ua_y2 = perechid_cherez_nul[INDEX_PhK_UA][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UA] = 0xff;
      }
      ADCs_data[I_Ua] = _y;
        
      ADCs_data_raw[I_Ua].tick = _x2;
      ADCs_data_raw[I_Ua].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ub
    /*****/
    if ((command_word & (1 << I_Ub)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ub].tick;
      _y1 = ADCs_data_raw[I_Ub].value;
        
      _y2 = output_adc[C_Ub_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ub_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ub])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ub_16].value - gnd_adc - vref_adc;

        _x2 = output_adc[C_Ub_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ub])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Ub] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //���������� �������
        perechid_cherez_nul[INDEX_PhK_UB][0].x1 = poperednij_perechid.Ub_x1;
        perechid_cherez_nul[INDEX_PhK_UB][0].y1 = poperednij_perechid.Ub_y1;
        perechid_cherez_nul[INDEX_PhK_UB][0].x2 = poperednij_perechid.Ub_x2;
        perechid_cherez_nul[INDEX_PhK_UB][0].y2 = poperednij_perechid.Ub_y2;
          
        //�������� �������
        poperednij_perechid.Ub_x1 = perechid_cherez_nul[INDEX_PhK_UB][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Ub_y1 = perechid_cherez_nul[INDEX_PhK_UB][1].y1 = ADCs_data[I_Ub];
        poperednij_perechid.Ub_x2 = perechid_cherez_nul[INDEX_PhK_UB][1].x2 = _x;
        poperednij_perechid.Ub_y2 = perechid_cherez_nul[INDEX_PhK_UB][1].y2 = _y;
      
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UB] = 0xff;
      }
      ADCs_data[I_Ub] = _y;
      
      ADCs_data_raw[I_Ub].tick = _x2;
      ADCs_data_raw[I_Ub].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Uc
    /*****/
    if ((command_word & (1 << I_Uc)) != 0)
    {
      _x1 = ADCs_data_raw[I_Uc].tick;
      _y1 = ADCs_data_raw[I_Uc].value;
        
      _y2 = output_adc[C_Uc_1].value - gnd_adc - vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Uc_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Uc])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Uc_16].value - gnd_adc - vref_adc;
      
        _x2 = output_adc[C_Uc_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Uc])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
        {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
        }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Uc] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //���������� �������
        perechid_cherez_nul[INDEX_PhK_UC][0].x1 = poperednij_perechid.Uc_x1;
        perechid_cherez_nul[INDEX_PhK_UC][0].y1 = poperednij_perechid.Uc_y1;
        perechid_cherez_nul[INDEX_PhK_UC][0].x2 = poperednij_perechid.Uc_x2;
        perechid_cherez_nul[INDEX_PhK_UC][0].y2 = poperednij_perechid.Uc_y2;
          
        //�������� �������
        poperednij_perechid.Uc_x1 = perechid_cherez_nul[INDEX_PhK_UC][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Uc_y1 = perechid_cherez_nul[INDEX_PhK_UC][1].y1 = ADCs_data[I_Uc];
        poperednij_perechid.Uc_x2 = perechid_cherez_nul[INDEX_PhK_UC][1].x2 = _x;
        poperednij_perechid.Uc_y2 = perechid_cherez_nul[INDEX_PhK_UC][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UC] = 0xff;
      }
      ADCs_data[I_Uc] = _y;
      
      ADCs_data_raw[I_Uc].tick = _x2;
      ADCs_data_raw[I_Uc].value = _y2;
    }
    /*****/

    gnd_adc  = gnd_adc2; 
    vref_adc = vref_adc2; 
    
    int32_t multiplier = ((ctr_transformator_I_VH_meas == 0) ? (1) : (-1));

    /*****/
    //������� �������� Ia_H
    /*****/
    if ((command_word & (1 << I_Ia_H)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ia_H].tick;
      _y1 = ADCs_data_raw[I_Ia_H].value;
        
      _y2 = output_adc[C_Ia_H_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ia_H_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ia_H])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ia_H_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ia_H_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ia_H])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ia_H] = multiplier*_y;
      
      ADCs_data_raw[I_Ia_H].tick = _x2;
      ADCs_data_raw[I_Ia_H].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ib_H
    /*****/
    if ((command_word & (1 << I_Ib_H)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ib_H].tick;
      _y1 = ADCs_data_raw[I_Ib_H].value;
        
      _y2 = output_adc[C_Ib_H_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ib_H_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ib_H])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ib_H_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ib_H_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ib_H])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ib_H] = multiplier*_y;
      
      ADCs_data_raw[I_Ib_H].tick = _x2;
      ADCs_data_raw[I_Ib_H].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ic_H
    /*****/
    if ((command_word & (1 << I_Ic_H)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ic_H].tick;
      _y1 = ADCs_data_raw[I_Ic_H].value;
        
      _y2 = output_adc[C_Ic_H_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ic_H_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ic_H])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ic_H_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ic_H_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ic_H])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ic_H] = multiplier*_y;
      
      ADCs_data_raw[I_Ic_H].tick = _x2;
      ADCs_data_raw[I_Ic_H].value = _y2;
    }
    /*****/
    
    multiplier = ((ctr_transformator_I_VL_meas == 0) ? (1) : (-1));

    /*****/
    //������� �������� Ia_L
    /*****/
    if ((command_word & (1 << I_Ia_L)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ia_L].tick;
      _y1 = ADCs_data_raw[I_Ia_L].value;
        
      _y2 = output_adc[C_Ia_L_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ia_L_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ia_L])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ia_L_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ia_L_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ia_L])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ia_L] = multiplier*_y;
      
      ADCs_data_raw[I_Ia_L].tick = _x2;
      ADCs_data_raw[I_Ia_L].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ib_L
    /*****/
    if ((command_word & (1 << I_Ib_L)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ib_L].tick;
      _y1 = ADCs_data_raw[I_Ib_L].value;
        
      _y2 = output_adc[C_Ib_L_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ib_L_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ib_L])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ib_L_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ib_L_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ib_L])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ib_L] = multiplier*_y;
      
      ADCs_data_raw[I_Ib_L].tick = _x2;
      ADCs_data_raw[I_Ib_L].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ic_L
    /*****/
    if ((command_word & (1 << I_Ic_L)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ic_L].tick;
      _y1 = ADCs_data_raw[I_Ic_L].value;
        
      _y2 = output_adc[C_Ic_L_1].value - gnd_adc -  vref_adc;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ic_L_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ic_L])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ic_L_16].value - gnd_adc -  vref_adc;

        _x2 = output_adc[C_Ic_L_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ic_L])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ic_L] = multiplier*_y;
      
      ADCs_data_raw[I_Ic_L].tick = _x2;
      ADCs_data_raw[I_Ic_L].value = _y2;
    }
    /*****/
    
    /*****/
    //���.������
    /*****/
    double koef_VH_tmp = koef_VH_meas, koef_VL_tmp = koef_VL_meas;
    switch (type_con_ozt_meas)
    {
    case TYPE_CON_OZT_0:
      {
        ADCs_data[I_dIa] = (int)(round((double)ADCs_data[I_Ia_H]*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ia_L]*koef_VL_tmp));
        ADCs_data[I_dIb] = (int)(round((double)ADCs_data[I_Ib_H]*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ib_L]*koef_VL_tmp));
        ADCs_data[I_dIc] = (int)(round((double)ADCs_data[I_Ic_H]*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ic_L]*koef_VL_tmp));
        break;
      }
    case TYPE_CON_OZT_1:
      {
        ADCs_data[I_dIa] = (int)(round((double)(ADCs_data[I_Ia_H] - ADCs_data[I_Ic_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ia_L]*koef_VL_tmp));
        ADCs_data[I_dIb] = (int)(round((double)(ADCs_data[I_Ib_H] - ADCs_data[I_Ia_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ib_L]*koef_VL_tmp));
        ADCs_data[I_dIc] = (int)(round((double)(ADCs_data[I_Ic_H] - ADCs_data[I_Ib_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ic_L]*koef_VL_tmp));
        break;
      }
    case TYPE_CON_OZT_11:
      {
        ADCs_data[I_dIa] = (int)(round((double)(ADCs_data[I_Ia_H] - ADCs_data[I_Ib_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ia_L]*koef_VL_tmp));
        ADCs_data[I_dIb] = (int)(round((double)(ADCs_data[I_Ib_H] - ADCs_data[I_Ic_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ib_L]*koef_VL_tmp));
        ADCs_data[I_dIc] = (int)(round((double)(ADCs_data[I_Ic_H] - ADCs_data[I_Ia_H])*koef_VH_tmp)) + (int)(round((double)ADCs_data[I_Ic_L]*koef_VL_tmp));
        break;
      }
    default: total_error_sw_fixed(23);
    }
    
    /*****/
    
    unsigned int head_data_for_oscylograph_tmp = head_data_for_oscylograph;
    unsigned int x2, x1, delta_x; 

    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      /*
      ��������� ���������� ���������� ���� ��� ������������ ���'�
      */
      Fourier();
      
      //������� ���� ��� ��������� �������
      x1 = rozshyrena_vyborka.time_p = penultimate_tick_DATA_VAL;
      x2 = rozshyrena_vyborka.time_c = previous_tick_DATA_VAL;
      for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_WITH_CALC; i++) 
      {
        rozshyrena_vyborka.data_p[i] = rozshyrena_vyborka.data_c[i];
        rozshyrena_vyborka.data_c[i] = ADCs_data[i];
      }

      /*******************************************************
      ���������� �������������� �������
      *******************************************************/
      if (head_data_for_oscylograph_tmp != DATA_VAL_tail_data_for_oscylograph)
      {
        if (x2 > x1) delta_x = x2 - x1;
        else
        {
          long long delta_x_64 = x2 + 0x100000000 - x1;
          delta_x = delta_x_64;
        }

        while (head_data_for_oscylograph_tmp != DATA_VAL_tail_data_for_oscylograph)
        {
          unsigned int DATA_VAL_tail_data_for_oscylograph_tmp = DATA_VAL_tail_data_for_oscylograph;
    
          unsigned int x = data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].time_stemp;
        
          unsigned int dx;
          if (x >= x1) dx = x - x1;
          else
          {
            long long dx_64 = x + 0x100000000 - x1;
            dx = dx_64;
          }
          
          if (dx > delta_x) 
          {
            break;
          }

          for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_WITH_CALC; i++)
          {
            int y1 = rozshyrena_vyborka.data_p[i], y2 = rozshyrena_vyborka.data_c[i];
            long long y;
            if (dx <= delta_x)
            {
              y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
            }
            else
            {
              y = 0;
            }
            data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].data[I_Ia_H + i] = y;
          }
          data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].DATA_fix = 0xff;

          if (++DATA_VAL_tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) DATA_VAL_tail_data_for_oscylograph = 0;
        }
      }
      /******************************************************/
      
      /*
      �������� �������� �� ���������� ������� � ��������� �������
      */
      fapch();
    
      status_adc_read_work &= (unsigned int)(~DATA_VAL_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� ������ ����� ����� ������������ �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_DATA_VAL;
      /**************************************************/
    }
    
    /********************************************************
    ������� ����� ������� ������� � �������� �������� ��� ����������� ����������
    ********************************************************/
    unsigned int number_postfault_slices = 0;
    if (head_data_for_oscylograph_tmp != tail_data_for_oscylograph)
    {
      while (
             (head_data_for_oscylograph_tmp != tail_data_for_oscylograph) &&
             (data_for_oscylograph[tail_data_for_oscylograph].DATA_fix != 0)
            )
      {
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES_WITH_CALC; i++)
        {
          int data_tmp = data_for_oscylograph[tail_data_for_oscylograph_tmp].data[i];
          
          if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) == 0)
          {
            //����� ������� ���������� ������� ��� ����������� ����������
//            array_ar[index_array_ar_current++] = data_tmp;
            AR_WRITE(index_array_ar_current, data_tmp);
          }
        }

        //����� ���������� ������� ��� ����������� ����������
        unsigned int *label_to_active_functions_source = data_for_oscylograph[tail_data_for_oscylograph_tmp].active_functions;
        if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) != 0)
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] = *(label_to_active_functions_source + i);
        }
        else
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] |= *(label_to_active_functions_source + i);

          unsigned short int *label_to_active_functions_trg = (unsigned short int*)active_functions_trg;
          for(unsigned int i = 0; i < number_word_digital_part_ar; i++) 
          {
//            array_ar[index_array_ar_current++] = *(label_to_active_functions_trg + i);
            AR_WRITE(index_array_ar_current, *(label_to_active_functions_trg + i));
          }
          //������ ������ ��'������� ������� ��� ����������� ����������
          if (index_array_ar_current >= SIZE_BUFFER_FOR_AR) index_array_ar_current = 0;/*����� ���� � ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
          
          //������������ ������� ���� ������� � ������ ����������� �� ������������� ������ ��'������� ������� ��� ����������� ����������
          if (
              (data_for_oscylograph[tail_data_for_oscylograph_tmp].state_ar_record == STATE_AR_START) ||
              (data_for_oscylograph[tail_data_for_oscylograph_tmp].state_ar_record == STATE_AR_SAVE_SRAM_AND_SAVE_FLASH)
             )
          {
            number_postfault_slices++;
          }
        }
        prescaler_ar++;
    
        data_for_oscylograph[tail_data_for_oscylograph_tmp].DATA_fix = 0;

        if (++tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph = 0;
      }
    }

    //��������� ���������� ������������
    if (
        ((state_ar_record == STATE_AR_START) && (number_postfault_slices != 0)) || 
        (state_ar_record == STATE_AR_SAVE_SRAM_AND_SAVE_FLASH)
       )
    {
      static unsigned int uncopied_postfault_time_sapmles;

      /*
      ��� ����� ��� ������������� ������ � ������� ������� � �����
      */
        
      if (state_ar_record == STATE_AR_START)
      {
        int difference;
        /*
        ������� number_postfault_slices ������������ ���� ������� � �����,
        �� ��� ���������� ����� ���� ������������� ������ �� index_array_ar_current
        ������ ������� ������� ������� � ������ ���
        */
        /*
        ������������ ���� ������� �������� �������� ������������ ������ � 
        ��������� �������� �� � ����� "��������" ��� ����, ��� ������ �������� 
        ���� "�������������", ����� �������, ������
        */
        difference = index_array_ar_current - number_postfault_slices*(NUMBER_ANALOG_CANALES_WITH_CALC + number_word_digital_part_ar);
        if (difference >= 0) index_array_ar_heat = difference;
        else index_array_ar_heat = difference + SIZE_BUFFER_FOR_AR;

        //������������ ���� "��������"
        difference = index_array_ar_heat - (current_settings_prt.prefault_number_periods << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES_WITH_CALC + number_word_digital_part_ar);
        if (difference >= 0) index_array_ar_tail = difference;
        else index_array_ar_tail = difference + SIZE_BUFFER_FOR_AR;
          
        //��������� ������ ����� ���� �������� ��� ������������� ������
        /*
        !!!� ������ ���� ������� ���� � �� ������� ������� �������, ��� �����
        ���� ������� � ����� ���� ��� �������� �� �������� � ������ � ������� ������,
        � ������� �� �������� �� �������!!!
        */
        uncopied_postfault_time_sapmles = (current_settings_prt.postfault_number_periods << VAGA_NUMBER_POINT_AR);

        /*
        ��� �� ���� ��������, �� ����������� �� ������� �� �� ������� ���� �����
        ����, �� �� ����� ������ �� ������������� ������ - �� ������� �� ����� ����, �� ���� ��� 
        ����� ���� �������� � ���������� ���������.
        */
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        while (head_data_for_oscylograph_tmp != tail_data_for_oscylograph_tmp)
        {
           data_for_oscylograph[tail_data_for_oscylograph_tmp++].state_ar_record = state_ar_record;
           if (tail_data_for_oscylograph_tmp >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph_tmp = 0;
        }

        //���������� � ���� ������ ����������� ���������� "�������� � ��������"
        state_ar_record = STATE_AR_SAVE_SRAM_AND_SAVE_FLASH;

      }
        
      /*
      ������������ ���� "��������" � ���������� ������������ ������ � ����� 
      ��������, �� ���� �������� ���������� �� �������, �� �� ����� ���� � 
      ������ index_array_ar_heat ����������� �������� ���� "��������" �� ��������� 
      number_postfault_slices ����. 
      ��� ������ ��� ������ number_postfault_slices ���� � �����
      index_array_ar_current ������� � ������� ���� "����������" ������ ������� 
      ������� ��� ����������� ����������.
      */

      /*
      �������� ��������� �������� ������������ ������ (����������� �� ������� ������ �
      �� ���� ��������, ���� � ��������� ������ ����� ������ � ������������ 
      ������������� �������� ����������� � ������������� ������ � ����������
      "��������" � "��������")
      */
      int difference_before, difference_after;
      unsigned int index_array_ar_tail_tmp = index_array_ar_tail;
      difference_before = (index_array_ar_heat - index_array_ar_tail_tmp);
      if (difference_before < 0) difference_before += SIZE_BUFFER_FOR_AR;
      difference_after = (index_array_ar_current - index_array_ar_tail_tmp);
      if (difference_after < 0) difference_after += SIZE_BUFFER_FOR_AR;
      if ((difference_after - difference_before) != number_postfault_slices*(NUMBER_ANALOG_CANALES_WITH_CALC + number_word_digital_part_ar))
      {
        //��������� ��������, ��� ��������� ������������� 
        _SET_BIT(set_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
      }
      else
      {
        //���� ��������� ��������, ��� ��������� �������������
        _SET_BIT(clear_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
      }

      //������������ ���� "��������" � ������� ����, �� �� ����� �������� �� ������������� ������
      if (uncopied_postfault_time_sapmles >= number_postfault_slices)
      {
        index_array_ar_heat = index_array_ar_current;
        uncopied_postfault_time_sapmles -= number_postfault_slices;
      }
      else
      {
        int difference = index_array_ar_current - (number_postfault_slices - uncopied_postfault_time_sapmles);
        if (difference >= 0) index_array_ar_heat = difference;
        else index_array_ar_heat = difference + SIZE_BUFFER_FOR_AR;

        uncopied_postfault_time_sapmles = 0;
      }

      if (uncopied_postfault_time_sapmles == 0)
      {
        /*
        �� ����������� ���� ��� ��������� � ���� ���������� ����� ������ 
        ����������� ���������� � ����� ����� ������ ��� ������� �� �� �� ��������
        */
        state_ar_record = STATE_AR_ONLY_SAVE_FLASH;

        /*
        ��� �� ���� ��������, �� ����������� �� ������� ��� ������� ��� �����
        ����, �� ����� ������ �� ������������� ������, ��� �� ���� �� ���������,
        �� �� ���� ��������� ��� - �� ������� �� ����� ����, �� ���� ��� 
        �������� �� ������������ �����.
        */
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        while (head_data_for_oscylograph_tmp != tail_data_for_oscylograph_tmp)
        {
           data_for_oscylograph[tail_data_for_oscylograph_tmp++].state_ar_record = state_ar_record;
           if (tail_data_for_oscylograph_tmp >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph_tmp = 0;
        }
      }
        
    }
    /*******************************************************/
    
    if ((status_adc_read_work & TEST_VAL_READ) != 0)
    {
      //����� ���������� ����������� ��������
      operate_test_ADCs();

      status_adc_read_work &= (unsigned int)(~TEST_VAL_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� �������� �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_TEST_VAL;
      /**************************************************/
      
      /**************************************************/
      //���� ����� ����� ���������� �� ���� �������
      /**************************************************/
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      /**************************************************/
    }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
  }

  if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)
  {
    //����� ���� �� ������� �������� control_reading_ADCs
    
    /*
    ������� � ���� ���������� ������� ������� control_reading_ADCs �� ������
    ������� ����������� �� ������� ��������� ��� ������ �� ���������
    */
    
    /*
    ����������� ��������� ����������, ��� ���� �� �������� ��� ���� ����� �����
    �� ��������� �� ����� �� ���������
    */
    __disable_interrupt();
    
    /*
    ��������, �� ���� ����� ����� �� ��������� � ���� �� ������ ������� �����
    ����� �� ���������, �� ������������ ��������� ������� ��������� � �����������
    ������� ( chip select ����������� � 1)
    */
    if (
        (adc_DATA_VAL_read == false) &&
        (adc_TEST_VAL_read == false)
       )
    {
      semaphore_adc_irq  = false;
    }
    
    /*
    ���������� ��������� ����������
    */
     __enable_interrupt();
  }
  else semaphore_adc_irq  = false;

  
  if (semaphore_adc_irq  != false)
  {
    /*
    �� ����� ���� ���� ������ � ������ �������: ���� ��� ����� �� ��� ���� �� ���������
    � ������� ��������� ������� ������� control_reading_ADCs �� �������� ����������
    �������� __disable_interrupt ���� ������� ���������.
    
    ������ � ���� ������� ������� control_reading_ADCs. �������� �� ����, ��
    chip_select ������ ����������� � ������� ���� (�� �� ������� �������� 
    if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)) � ����� semaphore_adc_irq ��
    �� ���� false, � ��� ����� ����� ������ ��������� � ����������� �������
    */
    
    control_reading_ADCs();
    
    /*
    ������� ���������. ���� �������� �� �� � ����������� ������� ����������� �����, �� ������� �� SPI
    ����������. ��� ��� ��������� ��� ������ �� �����, �� ������ ������� control_reading_ADCs
    ��� ������������ ����, �� ���� �� ��������� "������ � ����"  ������ ������
    ��������� - � �� ������� ����� ���, ���� chip_select ���� �������� ���� ������������ � ������� �����
    
    � ������������ chip_select ����� � ������� ����� ����� ���� ����� ����������� ����������� ��
    ����� SPI
    */
    semaphore_adc_irq  = false;
  }
  
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordExitISR();
//#endif
}
/*****************************************************/

/*****************************************************/
//����������� ����
/*****************************************************/
void calc_angle(void) 
{
  //������� ����������
  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < _NUMBER_IM; i++ ) 
  {
    measurement_low[i] = measurement_middle[i];
  }
  semaphore_measure_values_low1 = 0;
              
  int ortogonal_low_tmp[2*FULL_ORT_MAX];
  
  //����������� ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 1;
  for(unsigned int i = 0; i < (2*FULL_ORT_MAX); i++ )
  {
      ortogonal_low_tmp[i] = ortogonal_calc_low[i];
  } 
  //������� ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 0;
  
  //���������, ���� ������ ������ �� ������
  __index_meas index_base = IM_UA;

  /***
  ���������, ���� �������� ������ ����� ����� �� ������
  ***/
  __index_meas index_last = IM_UCA;
  /***/
  
  int base_index_for_angle_tmp = -1;
  __index_meas index = index_base;
  while( index <= index_last)
  {
    if (measurement_low[index] >= PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE)
    {
      base_index_for_angle_tmp = index;
      break; //����� �� ����� while
    }
    index++;
  }
  base_index_for_angle = base_index_for_angle_tmp;
  
  if (base_index_for_angle_tmp >= 0)
  {
    //���������� �������� �������, ������� ����� ������ ������ ����
    int ortogonal_base[2] = {ortogonal_low_tmp[2*base_index_for_angle_tmp], ortogonal_low_tmp[2*base_index_for_angle_tmp + 1]};
    
#define SIN_BASE   ortogonal_base[0]
#define COS_BASE   ortogonal_base[1]

    unsigned int amplituda_base = sqrt_64((unsigned long long)((long long)SIN_BASE*(long long)SIN_BASE) + (unsigned long long)((long long)COS_BASE*(long long)COS_BASE));
    if (amplituda_base != 0)
    {
      for (__index_meas index_tmp = index_base; index_tmp < FULL_ORT_MAX; index_tmp++)
      {
        if (index_tmp == index)
        {
          phi_angle[index_tmp] = 0;
          continue;
        }
        else
        {
          unsigned int porig_chutlyvosti;
          if (index_tmp <= _IM_U_END) porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
          else porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
          
          if (measurement_low[index_tmp] >= porig_chutlyvosti)
          {
            //����������� ���
#define SIN_TARGET ortogonal_low_tmp[2*index_tmp]
#define COS_TARGET ortogonal_low_tmp[2*index_tmp + 1]

            unsigned int amplituda_target = sqrt_64((unsigned long long)((long long)SIN_TARGET*(long long)SIN_TARGET) + (unsigned long long)((long long)COS_TARGET*(long long)COS_TARGET));
      
            if (amplituda_target != 0)
            {
              //���������� COS � SIN ���� ������ �� ���������
              long long cos_fi = COS_TARGET*COS_BASE + SIN_TARGET*SIN_BASE;
              long long sin_fi = -(SIN_TARGET*COS_BASE - COS_TARGET*SIN_BASE);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_TARGET
#undef COS_TARGET
      
              float sin_fi_f = ( ((float)sin_fi) / ((float)amplituda_target) ) / ((float)amplituda_base);
              if (sin_fi_f > 1) sin_fi_f = 1;
              else if (sin_fi_f < -1) sin_fi_f = -1;
      
              float angle_f = asin(sin_fi_f)*180 / PI;
              int angle_int = (int)(angle_f*10); //������ �������� �� �������
              if (angle_int < 0) angle_int = -angle_int;
      
              if ((sin_fi >= 0) && (cos_fi >= 0))
              {
                //1-�� ��������
                //angle_int ���������� ��� ����
              }
              else if ((sin_fi >= 0) && (cos_fi <  0))
              {
                //2-�� ��������
                angle_int = 1800 - angle_int;
              }
              else if ((sin_fi <  0) && (cos_fi <  0))
              {
                //3-�� ��������
                angle_int = 1800 + angle_int;
              }
              else
              {
                //4-�� ��������
                angle_int = 3600 - angle_int;
              }
    
              if (angle_int >= 3600) angle_int -= 3600;
              else if (angle_int < 0) angle_int += 3600;
      
              phi_angle[index_tmp] = angle_int;
      
            }
            else
            {
              phi_angle[index_tmp] = -1;
            }

          }
          else
          {
            //������ ������������� ������� ����� ������ - ��� ������������
            phi_angle[index_tmp] = -1;
          }
        }
      }
    }
    else
    {
      //�������� �������� ������� ���������� �� ���������� ��� ���� ������� ���� 0 (� �����, �� ���� �������� �� ���� � ������ ��������). �� �������������.
      for (__index_meas index_tmp = _IM_BEGIN; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[index_tmp] = -1;
    }

#undef SIN_BASE
#undef COS_BASE
    
  }
  else
  {
    //�� ����������� ������� ����������, ������� ����� ����� ������������� ����
    for (__index_meas index_tmp = _IM_BEGIN; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[index_tmp] = -1;
  }
}

/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
void calc_power_total(void) 
{
  //��������� ���� �� ������������� ������ ��� �������
  unsigned int bank_for_enegry_tmp = (bank_for_enegry + 1) & 0x1;
  
  int P_tmp = P_plus[bank_for_enegry_tmp] - P_minus[bank_for_enegry_tmp];
  int Q_tmp = Q_1q[bank_for_enegry_tmp] + Q_2q[bank_for_enegry_tmp] - Q_3q[bank_for_enegry_tmp] - Q_4q[bank_for_enegry_tmp];

  float P_float = ((float)P_tmp)/((float)MAIN_FREQUENCY);
  float Q_float = ((float)Q_tmp)/((float)MAIN_FREQUENCY);
  
  mutex_power = 0xff;
  P[0] = (int)P_float;
  Q[0] = (int)Q_float;
  mutex_power = 0;
  P[1] = P[0];
  Q[1] = Q[0];
  
  //����� ����������
  if ( (P[0] != 0) || (Q[0] != 0))
  {
    float in_square_root, S_float;
    in_square_root = P_float*P_float + Q_float*Q_float;
    
    if (arm_sqrt_f32(in_square_root, &S_float) == ARM_MATH_SUCCESS)
    {
      mutex_power = 0xff;
      S[0] = (unsigned int)S_float;
      mutex_power = 0;
      S[1] = S[0];
    }
    else
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(53);
    }
    
    cos_phi_x1000 = (int)(1000.0f*P_float/S_float);
  }
  else
  {
    mutex_power = 0xff;
    S[0] = 0;
    mutex_power = 0;
    S[1] = S[0];
    
    cos_phi_x1000 = 0;
  }
  
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
