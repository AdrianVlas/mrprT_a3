
enum DREC_MEAS_INDEXES_NAMES{
BGS_IN_NAME__ANALOG_IN = 1,

TOTAL_MEAS_INDEXES 
};



inline void start_monitoring_max_phase_current(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального фазного струму
  number_max_phase_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_phase_max_dr[ 0] = measurement[IM_3I0];
//  measurements_phase_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_phase_max_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_phase_max_dr[ 3] = measurement[IM_IA_H];
  measurements_phase_max_dr[ 4] = measurement[IM_IB_H];
  measurements_phase_max_dr[ 5] = measurement[IM_IC_H];
  measurements_phase_max_dr [6] = measurement[IM_I2_H];
  measurements_phase_max_dr[ 7] = measurement[IM_I1_H];
//  measurements_phase_max_dr[ 8] = measurement[IM_I04];
  measurements_phase_max_dr[ 9] = measurement[IM_UA];
  measurements_phase_max_dr[10] = measurement[IM_UB];
  measurements_phase_max_dr[11] = measurement[IM_UC];
  measurements_phase_max_dr[12] = measurement[IM_3U0_r];
  measurements_phase_max_dr[13] = measurement[IM_U2];
  measurements_phase_max_dr[14] = measurement[IM_U1];
  measurements_phase_max_dr[15] = measurement[IM_UAB];
  measurements_phase_max_dr[16] = measurement[IM_UBC];
  measurements_phase_max_dr[17] = measurement[IM_UCA];
  measurements_phase_max_dr[18] = (unsigned int)frequency_int;
  
  //Визначаємо макисальний фазний струм між трьома фазами
  max_phase_current_dr = measurements_phase_max_dr[2];
  if (max_phase_current_dr < measurements_phase_max_dr[3]) max_phase_current_dr = measurements_phase_max_dr[3];
  if (max_phase_current_dr < measurements_phase_max_dr[4]) max_phase_current_dr = measurements_phase_max_dr[4];

  //Фіксуємо час з моменту початку аварійного запису
  measurements_phase_max_dr[19] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимального фазного струму
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE);
}
inline void continue_monitoring_max_phase_current(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза фазний струм більший, ніж той що помічений максимальним
  if (
      (max_phase_current_dr < measurement[IM_IA_H]) ||
      (max_phase_current_dr < measurement[IM_IB_H]) ||
      (max_phase_current_dr < measurement[IM_IC_H])
     )
  {
    //Зафіксовано зріз при найвищому фазовому струмі з моменту початку спостереження за ним
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_phase_max_dr[ 0] = measurement[IM_3I0];
//    measurements_phase_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_phase_max_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_phase_max_dr[ 3] = measurement[IM_IA_H];
    measurements_phase_max_dr[ 4] = measurement[IM_IB_H];
    measurements_phase_max_dr[ 5] = measurement[IM_IC_H];
    measurements_phase_max_dr [6] = measurement[IM_I2_H];
    measurements_phase_max_dr[ 7] = measurement[IM_I1_H];
//    measurements_phase_max_dr[ 8] = measurement[IM_I04];
    measurements_phase_max_dr[ 9] = measurement[IM_UA];
    measurements_phase_max_dr[10] = measurement[IM_UB];
    measurements_phase_max_dr[11] = measurement[IM_UC];
    measurements_phase_max_dr[12] = measurement[IM_3U0_r];
    measurements_phase_max_dr[13] = measurement[IM_U2];
    measurements_phase_max_dr[14] = measurement[IM_U1];
    measurements_phase_max_dr[15] = measurement[IM_UAB];
    measurements_phase_max_dr[16] = measurement[IM_UBC];
    measurements_phase_max_dr[17] = measurement[IM_UCA];
    measurements_phase_max_dr[18] = (unsigned int)frequency_int;

    max_phase_current_dr = measurements_phase_max_dr[2];
    if (max_phase_current_dr < measurements_phase_max_dr[3]) max_phase_current_dr = measurements_phase_max_dr[3];
    if (max_phase_current_dr < measurements_phase_max_dr[4]) max_phase_current_dr = measurements_phase_max_dr[4];

    //Фіксуємо час з моменту початку аварійного запису
    measurements_phase_max_dr[19] = time_tmp;
  }
}
inline void start_monitoring_max_3I0(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального 3I0
  number_max_3I0_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_3I0_max_dr[ 0] = measurement[IM_3I0];
//  measurements_3I0_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_3I0_max_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_3I0_max_dr[ 3] = measurement[IM_IA_H];
  measurements_3I0_max_dr[ 4] = measurement[IM_IB_H];
  measurements_3I0_max_dr[ 5] = measurement[IM_IC_H];
  measurements_3I0_max_dr [6] = measurement[IM_I2_H];
  measurements_3I0_max_dr[ 7] = measurement[IM_I1_H];
//  measurements_3I0_max_dr[ 8] = measurement[IM_I04];
  measurements_3I0_max_dr[ 9] = measurement[IM_UA];
  measurements_3I0_max_dr[10] = measurement[IM_UB];
  measurements_3I0_max_dr[11] = measurement[IM_UC];
  measurements_3I0_max_dr[12] = measurement[IM_3U0_r];
  measurements_3I0_max_dr[13] = measurement[IM_U2];
  measurements_3I0_max_dr[14] = measurement[IM_U1];
  measurements_3I0_max_dr[15] = measurement[IM_UAB];
  measurements_3I0_max_dr[16] = measurement[IM_UBC];
  measurements_3I0_max_dr[17] = measurement[IM_UCA];
  measurements_3I0_max_dr[18] = (unsigned int)frequency_int;
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_3I0_max_dr[19] = time_tmp;
  
  //Помічаємо, що ми на стадії моніторингу максимального струму 3I0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0);
}
inline void continue_monitoring_max_3I0(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза струм 3I0 більший, ніж той що помічений максимальним
  if(
     (
      ((current_settings_prt.configuration & (1<<TZNP_BIT_CONFIGURATION)) != 0) && 
      (                                                            (measurements_3I0_max_dr[2] < measurement[IM_3I0_r_H]))
     )   
    )
  {
    //Зафіксовано зріз при найвищому струмі 3I0 з моменту спостереження за ним
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_3I0_max_dr[ 0] = measurement[IM_3I0];
//    measurements_3I0_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_3I0_max_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_3I0_max_dr[ 3] = measurement[IM_IA_H];
    measurements_3I0_max_dr[ 4] = measurement[IM_IB_H];
    measurements_3I0_max_dr[ 5] = measurement[IM_IC_H];
    measurements_3I0_max_dr [6] = measurement[IM_I2_H];
    measurements_3I0_max_dr[ 7] = measurement[IM_I1_H];
//    measurements_3I0_max_dr[ 8] = measurement[IM_I04];
    measurements_3I0_max_dr[ 9] = measurement[IM_UA];
    measurements_3I0_max_dr[10] = measurement[IM_UB];
    measurements_3I0_max_dr[11] = measurement[IM_UC];
    measurements_3I0_max_dr[12] = measurement[IM_3U0_r];
    measurements_3I0_max_dr[13] = measurement[IM_U2];
    measurements_3I0_max_dr[14] = measurement[IM_U1];
    measurements_3I0_max_dr[15] = measurement[IM_UAB];
    measurements_3I0_max_dr[16] = measurement[IM_UBC];
    measurements_3I0_max_dr[17] = measurement[IM_UCA];
    measurements_3I0_max_dr[18] = (unsigned int)frequency_int;

    //Фіксуємо час з моменту початку аварійного запису
    measurements_3I0_max_dr[19] = time_tmp;
  }
}
inline void start_monitoring_max_3U0(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимальної 3U0
  number_max_3U0_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_3U0_max_dr[ 0] = measurement[IM_3I0];
//  measurements_3U0_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_3U0_max_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_3U0_max_dr[ 3] = measurement[IM_IA_H];
  measurements_3U0_max_dr[ 4] = measurement[IM_IB_H];
  measurements_3U0_max_dr[ 5] = measurement[IM_IC_H];
  measurements_3U0_max_dr[ 6] = measurement[IM_I2_H];
  measurements_3U0_max_dr[ 7] = measurement[IM_I1_H];
//  measurements_3U0_max_dr[ 8] = measurement[IM_I04];
  measurements_3U0_max_dr[ 9] = measurement[IM_UA];
  measurements_3U0_max_dr[10] = measurement[IM_UB];
  measurements_3U0_max_dr[11] = measurement[IM_UC];
  measurements_3U0_max_dr[12] = measurement[IM_3U0_r];
  measurements_3U0_max_dr[13] = measurement[IM_U2];
  measurements_3U0_max_dr[14] = measurement[IM_U1];
  measurements_3U0_max_dr[15] = measurement[IM_UAB];
  measurements_3U0_max_dr[16] = measurement[IM_UBC];
  measurements_3U0_max_dr[17] = measurement[IM_UCA];
  measurements_3U0_max_dr[18] = (unsigned int)frequency_int;
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_3U0_max_dr[19] = time_tmp;
  
  //Помічаємо, що ми на стадії моніторингу максимальної напруги 3U0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0);
}
inline void continue_monitoring_max_3U0(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза напруга 3U0 більша, ніж та що помічена максимальною
  if(measurements_3U0_max_dr[12] < measurement[IM_3U0_r])
  {
    //Зафіксовано зріз при найвищому струмі 3I0 з моменту спостереження за ним
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_3U0_max_dr[ 0] = measurement[IM_3I0];
//    measurements_3U0_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_3U0_max_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_3U0_max_dr[ 3] = measurement[IM_IA_H];
    measurements_3U0_max_dr[ 4] = measurement[IM_IB_H];
    measurements_3U0_max_dr[ 5] = measurement[IM_IC_H];
    measurements_3U0_max_dr[ 6] = measurement[IM_I2_H];
    measurements_3U0_max_dr[ 7] = measurement[IM_I1_H];
//    measurements_3U0_max_dr[ 8] = measurement[IM_I04];
    measurements_3U0_max_dr[ 9] = measurement[IM_UA];
    measurements_3U0_max_dr[10] = measurement[IM_UB];
    measurements_3U0_max_dr[11] = measurement[IM_UC];
    measurements_3U0_max_dr[12] = measurement[IM_3U0_r];
    measurements_3U0_max_dr[13] = measurement[IM_U2];
    measurements_3U0_max_dr[14] = measurement[IM_U1];
    measurements_3U0_max_dr[15] = measurement[IM_UAB];
    measurements_3U0_max_dr[16] = measurement[IM_UBC];
    measurements_3U0_max_dr[17] = measurement[IM_UCA];
    measurements_3U0_max_dr[18] = (unsigned int)frequency_int;

    //Фіксуємо час з моменту початку аварійного запису
    measurements_3U0_max_dr[19] = time_tmp;
  }
}
inline void start_monitoring_min_U(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень мінімальної фазної/лінійної напруги
  number_min_U_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найменші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_U_min_dr[ 0] = measurement[IM_3I0];
//  measurements_U_min_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_U_min_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_U_min_dr[ 3] = measurement[IM_IA_H];
  measurements_U_min_dr[ 4] = measurement[IM_IB_H];
  measurements_U_min_dr[ 5] = measurement[IM_IC_H];
  measurements_U_min_dr[ 6] = measurement[IM_I2_H];
  measurements_U_min_dr[ 7] = measurement[IM_I1_H];
//  measurements_U_min_dr[ 8] = measurement[IM_I04];
  measurements_U_min_dr[ 9] = measurement[IM_UA];
  measurements_U_min_dr[10] = measurement[IM_UB];
  measurements_U_min_dr[11] = measurement[IM_UC];
  measurements_U_min_dr[12] = measurement[IM_3U0_r];
  measurements_U_min_dr[13] = measurement[IM_U2];
  measurements_U_min_dr[14] = measurement[IM_U1];
  measurements_U_min_dr[15] = measurement[IM_UAB];
  measurements_U_min_dr[16] = measurement[IM_UBC];
  measurements_U_min_dr[17] = measurement[IM_UCA];
  measurements_U_min_dr[18] = (unsigned int)frequency_int;
  
  if ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0)
  {
    //Визначаємо мінімальної фазну напругу між трьома фазами
    min_voltage_dr = measurements_U_min_dr[9];
    if (min_voltage_dr > measurements_U_min_dr[10]) min_voltage_dr = measurements_U_min_dr[10];
    if (min_voltage_dr > measurements_U_min_dr[11]) min_voltage_dr = measurements_U_min_dr[11];
  }
  else
  {
    //Визначаємо мінімальної лінійну напругу між трьома фазами
    min_voltage_dr = measurements_U_min_dr[15];
    if (min_voltage_dr > measurements_U_min_dr[16]) min_voltage_dr = measurements_U_min_dr[16];
    if (min_voltage_dr > measurements_U_min_dr[17]) min_voltage_dr = measurements_U_min_dr[17];
  }

  //Фіксуємо час з моменту початку аварійного запису
  measurements_U_min_dr[19] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу мінімальної фазної/лінійної напруги
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE);
}
inline void continue_monitoring_min_U(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза досліджувана напуга менша, ніж та що помічена мінімальною
  if (
      (
       ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) &&
       (  
        (min_voltage_dr > measurement[IM_UA]) ||
        (min_voltage_dr > measurement[IM_UB]) ||
        (min_voltage_dr > measurement[IM_UC])
       )
      )   
      || 
      (
       ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) != 0) &&
       (  
        (min_voltage_dr > measurement[IM_UAB]) ||
        (min_voltage_dr > measurement[IM_UBC]) ||
        (min_voltage_dr > measurement[IM_UCA])
       )
     )
    )    
  {
    //Зафіксовано зріз при найнижчій досліджуваній напрузі з моменту початку спостереження за нею
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_U_min_dr[ 0] = measurement[IM_3I0];
//    measurements_U_min_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_U_min_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_U_min_dr[ 3] = measurement[IM_IA_H];
    measurements_U_min_dr[ 4] = measurement[IM_IB_H];
    measurements_U_min_dr[ 5] = measurement[IM_IC_H];
    measurements_U_min_dr[ 6] = measurement[IM_I2_H];
    measurements_U_min_dr[ 7] = measurement[IM_I1_H];
//    measurements_U_min_dr[ 8] = measurement[IM_I04];
    measurements_U_min_dr[ 9] = measurement[IM_UA];
    measurements_U_min_dr[10] = measurement[IM_UB];
    measurements_U_min_dr[11] = measurement[IM_UC];
    measurements_U_min_dr[12] = measurement[IM_3U0_r];
    measurements_U_min_dr[13] = measurement[IM_U2];
    measurements_U_min_dr[14] = measurement[IM_U1];
    measurements_U_min_dr[15] = measurement[IM_UAB];
    measurements_U_min_dr[16] = measurement[IM_UBC];
    measurements_U_min_dr[17] = measurement[IM_UCA];
    measurements_U_min_dr[18] = (unsigned int)frequency_int;

    if ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0)
    {
      //Визначаємо мінімальну фазну напругу між трьома фазами
      min_voltage_dr = measurements_U_min_dr[9];
      if (min_voltage_dr > measurements_U_min_dr[10]) min_voltage_dr = measurements_U_min_dr[10];
      if (min_voltage_dr > measurements_U_min_dr[11]) min_voltage_dr = measurements_U_min_dr[11];
    }
    else
    {
      //Визначаємо мінімальну лінійну напругу між трьома фазами
      min_voltage_dr = measurements_U_min_dr[15];
      if (min_voltage_dr > measurements_U_min_dr[16]) min_voltage_dr = measurements_U_min_dr[16];
      if (min_voltage_dr > measurements_U_min_dr[17]) min_voltage_dr = measurements_U_min_dr[17];
    }

    //Фіксуємо час з моменту початку аварійного запису
    measurements_U_min_dr[19] = time_tmp;
  }
}
inline void start_monitoring_max_U(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимальної фазної/лінійної напруги
  number_max_U_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_U_max_dr[ 0] = measurement[IM_3I0];
//  measurements_U_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_U_max_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_U_max_dr[ 3] = measurement[IM_IA_H];
  measurements_U_max_dr[ 4] = measurement[IM_IB_H];
  measurements_U_max_dr[ 5] = measurement[IM_IC_H];
  measurements_U_max_dr[ 6] = measurement[IM_I2_H];
  measurements_U_max_dr[ 7] = measurement[IM_I1_H];
//  measurements_U_max_dr[ 8] = measurement[IM_I04];
  measurements_U_max_dr[ 9] = measurement[IM_UA];
  measurements_U_max_dr[10] = measurement[IM_UB];
  measurements_U_max_dr[11] = measurement[IM_UC];
  measurements_U_max_dr[12] = measurement[IM_3U0_r];
  measurements_U_max_dr[13] = measurement[IM_U2];
  measurements_U_max_dr[14] = measurement[IM_U1];
  measurements_U_max_dr[15] = measurement[IM_UAB];
  measurements_U_max_dr[16] = measurement[IM_UBC];
  measurements_U_max_dr[17] = measurement[IM_UCA];
  measurements_U_max_dr[18] = (unsigned int)frequency_int;
  
  if ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0)
  {
    //Визначаємо макисальну фазну напругу між трьома фазами
    max_voltage_dr = measurements_U_max_dr[9];
    if (max_voltage_dr < measurements_U_max_dr[10]) max_voltage_dr = measurements_U_max_dr[10];
    if (max_voltage_dr < measurements_U_max_dr[11]) max_voltage_dr = measurements_U_max_dr[11];
  }
  else
  {
    //Визначаємо макисальну лінійну напругу між трьома фазами
    max_voltage_dr = measurements_U_max_dr[15];
    if (max_voltage_dr < measurements_U_max_dr[16]) max_voltage_dr = measurements_U_max_dr[16];
    if (max_voltage_dr < measurements_U_max_dr[17]) max_voltage_dr = measurements_U_max_dr[17];
  }

  //Фіксуємо час з моменту початку аварійного запису
  measurements_U_max_dr[19] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимальної фазної/лінійної напруги
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE);
}
inline void continue_monitoring_max_U(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза досліджувана напуга більша, ніж та що помічена максимальною
  if (
      (
       ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) &&
       (  
        (max_voltage_dr < measurement[IM_UA]) ||
        (max_voltage_dr < measurement[IM_UB]) ||
        (max_voltage_dr < measurement[IM_UC])
       )
      )   
      || 
      (
       ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) != 0) &&
       (  
        (max_voltage_dr < measurement[IM_UAB]) ||
        (max_voltage_dr < measurement[IM_UBC]) ||
        (max_voltage_dr < measurement[IM_UCA])
       )
     )
    )    
  {
    //Зафіксовано зріз при найвищійу досліджуваній напрузі з моменту початку спостереження за нею
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_U_max_dr[ 0] = measurement[IM_3I0];
//    measurements_U_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_U_max_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_U_max_dr[ 3] = measurement[IM_IA_H];
    measurements_U_max_dr[ 4] = measurement[IM_IB_H];
    measurements_U_max_dr[ 5] = measurement[IM_IC_H];
    measurements_U_max_dr[ 6] = measurement[IM_I2_H];
    measurements_U_max_dr[ 7] = measurement[IM_I1_H];
//    measurements_U_max_dr[ 8] = measurement[IM_I04];
    measurements_U_max_dr[ 9] = measurement[IM_UA];
    measurements_U_max_dr[10] = measurement[IM_UB];
    measurements_U_max_dr[11] = measurement[IM_UC];
    measurements_U_max_dr[12] = measurement[IM_3U0_r];
    measurements_U_max_dr[13] = measurement[IM_U2];
    measurements_U_max_dr[14] = measurement[IM_U1];
    measurements_U_max_dr[15] = measurement[IM_UAB];
    measurements_U_max_dr[16] = measurement[IM_UBC];
    measurements_U_max_dr[17] = measurement[IM_UCA];
    measurements_U_max_dr[18] = (unsigned int)frequency_int;

    if ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0)
    {
      //Визначаємо макисальну фазну напругу між трьома фазами
      max_voltage_dr = measurements_U_max_dr[9];
      if (max_voltage_dr < measurements_U_max_dr[10]) max_voltage_dr = measurements_U_max_dr[10];
      if (max_voltage_dr < measurements_U_max_dr[11]) max_voltage_dr = measurements_U_max_dr[11];
    }
    else
    {
      //Визначаємо макисальну лінійну напругу між трьома фазами
      max_voltage_dr = measurements_U_max_dr[15];
      if (max_voltage_dr < measurements_U_max_dr[16]) max_voltage_dr = measurements_U_max_dr[16];
      if (max_voltage_dr < measurements_U_max_dr[17]) max_voltage_dr = measurements_U_max_dr[17];
    }

    //Фіксуємо час з моменту початку аварійного запису
    measurements_U_max_dr[19] = time_tmp;
  }
}
inline void start_monitoring_max_ZOP(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального 3I0
  number_max_ZOP_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
  int frequency_int = (int)frequency;
  if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//  measurements_ZOP_max_dr[ 0] = measurement[IM_3I0];
//  measurements_ZOP_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_ZOP_max_dr[ 2] = measurement[IM_3I0_r_H];
  measurements_ZOP_max_dr[ 3] = measurement[IM_IA_H];
  measurements_ZOP_max_dr[ 4] = measurement[IM_IB_H];
  measurements_ZOP_max_dr[ 5] = measurement[IM_IC_H];
  measurements_ZOP_max_dr[ 6] = measurement[IM_I2_H];
  measurements_ZOP_max_dr[ 7] = measurement[IM_I1_H];
//  measurements_ZOP_max_dr[ 8] = measurement[IM_I04];
  measurements_ZOP_max_dr[ 9] = measurement[IM_UA];
  measurements_ZOP_max_dr[10] = measurement[IM_UB];
  measurements_ZOP_max_dr[11] = measurement[IM_UC];
  measurements_ZOP_max_dr[12] = measurement[IM_3U0_r];
  measurements_ZOP_max_dr[13] = measurement[IM_U2];
  measurements_ZOP_max_dr[14] = measurement[IM_U1];
  measurements_ZOP_max_dr[15] = measurement[IM_UAB];
  measurements_ZOP_max_dr[16] = measurement[IM_UBC];
  measurements_ZOP_max_dr[17] = measurement[IM_UCA];
  measurements_ZOP_max_dr[18] = (unsigned int)frequency_int;

  //Фіксуємо час з моменту початку аварійного запису
  measurements_ZOP_max_dr[19] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимального струму зворотньої послідовності
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP);
}
inline void continue_monitoring_max_ZOP(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза струм зворотньої послідовності більший, ніж той що помічений максимальним
/*
      _I2 - струм зворотньої послідовності при попередньому зафіксованому максимальному відношенні I2/I1
      _I1 - струм прямої послідовності при попередньому зафіксованому максимальному відношенні I2/I1
      
      I2 -  текучий струм зворотньої послідовності
      I1 -  текучий струм прямої послідовності
      
      Умова перезапису параметрів:
      _I2     I2
      ---  < --- /x на _I1*I1  
      _I1     I1
      
      (_I2*I1 < I2*_I1)  - це є умова, що зараз є більше ЗОП(КОФ) ніж попередній раз
*/
  unsigned int I2, I1, _I1, _I2;
   I2 = measurement[IM_I2_H];
   I1 = measurement[IM_I1_H];
  _I2 = measurements_ZOP_max_dr[6];
  _I1 = measurements_ZOP_max_dr[7];
  if (
      ( (_I1 >  0) && ( ((_I2*I1) < (I2*_I1)) || (I1 == 0) ) ) ||
      ( (_I1 == 0) && (I1 == 0) && ( _I2 < I2 ) ) 
     )
  {
    //Зафіксовано зріз при найвищому струмі зворотньої послідовності з моменту початку запису
    int frequency_int = (int)frequency;
    if (frequency_int >= 0) frequency_int = (int)(frequency*1000);
  
//    measurements_ZOP_max_dr[ 0] = measurement[IM_3I0];
//    measurements_ZOP_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_ZOP_max_dr[ 2] = measurement[IM_3I0_r_H];
    measurements_ZOP_max_dr[ 3] = measurement[IM_IA_H];
    measurements_ZOP_max_dr[ 4] = measurement[IM_IB_H];
    measurements_ZOP_max_dr[ 5] = measurement[IM_IC_H];
    measurements_ZOP_max_dr[ 6] = measurement[IM_I2_H];
    measurements_ZOP_max_dr[ 7] = measurement[IM_I1_H];
//    measurements_ZOP_max_dr[ 8] = measurement[IM_I04];
    measurements_ZOP_max_dr[ 9] = measurement[IM_UA];
    measurements_ZOP_max_dr[10] = measurement[IM_UB];
    measurements_ZOP_max_dr[11] = measurement[IM_UC];
    measurements_ZOP_max_dr[12] = measurement[IM_3U0_r];
    measurements_ZOP_max_dr[13] = measurement[IM_U2];
    measurements_ZOP_max_dr[14] = measurement[IM_U1];
    measurements_ZOP_max_dr[15] = measurement[IM_UAB];
    measurements_ZOP_max_dr[16] = measurement[IM_UBC];
    measurements_ZOP_max_dr[17] = measurement[IM_UCA];
    measurements_ZOP_max_dr[18] = (unsigned int)frequency_int;

    //Фіксуємо час з моменту початку аварійного запису
    measurements_ZOP_max_dr[19] = time_tmp;
  }
}
inline void end_monitoring_min_max_measurement(unsigned int type_current, unsigned int* carrent_active_functions)
{
  if(
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE   ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0     ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0     ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     )
    )
  {
    int step = number_max_phase_dr   + 
               number_max_3I0_dr     + 
               number_max_3U0_dr     + 
               number_min_U_dr       +
               number_max_U_dr       +
               number_max_ZOP_dr;
    
    //Перевірка на коректність роботи програмного забеспечення
    if(
       ( (number_max_phase_dr   > 0) || ( (number_max_phase_dr   == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  )) == 0) ) ) &&
       ( (number_max_3I0_dr     > 0) || ( (number_max_3I0_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0    )) == 0) ) ) &&
       ( (number_max_3U0_dr     > 0) || ( (number_max_3U0_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0    )) == 0) ) ) &&
       ( (number_min_U_dr       > 0) || ( (number_min_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        )) == 0) ) ) &&
       ( (number_max_U_dr       > 0) || ( (number_max_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        )) == 0) ) ) &&
       ( (number_max_ZOP_dr     > 0) || ( (number_max_ZOP_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    )) == 0) ) ) &&
       ( (step > 0) && (step <= MAX_NUMBER_FIX_MAX_MEASUREMENTS)) 
      )
    {
      unsigned char *input_data_point, *output_data_point;
      
      //Визначаємо джерело звідки  будемо копіювати дані
      if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)
      {
        input_data_point = (unsigned char *)(measurements_phase_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)
      {
        input_data_point = (unsigned char *)(measurements_3I0_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)
      {
        input_data_point = (unsigned char *)(measurements_3U0_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)
      {
        input_data_point = (unsigned char *)(measurements_U_min_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)
      {
        input_data_point = (unsigned char *)(measurements_U_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)
      {
        input_data_point = (unsigned char *)(measurements_ZOP_max_dr);
      }
      
      //Визначаємо адресу киди дані треба копіювати
      step -= 1; //Тому що  нумерація починається з 0, а не з 1 (step гарантовано не менше 1(це перевірено вище), тому від'ємного числа не може бути)
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE  ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0    )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0    ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0    )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0    ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE        ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE        ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP    ))
        step -= 1;
      
      if(step >= 0)
      {
        output_data_point = (buffer_for_save_dr_record + FIRST_INDEX_FIRST_BLOCK_DR +step*sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS);
        
        for(unsigned int i = 0; i < (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS); i++)
        {
          if(i != (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS - 1))
          {
            *(output_data_point + i) = *(input_data_point + i);
          }
          else
          {
            //У останній байт масиву, що відповідає згідно з Little-endian формату старшову байту останнього елементу масиву, мітку типу струму, по якому фіксувався максимальний струм
            *(output_data_point + i) = type_current;
          }
        }

        //Знімаємо помітку, що ми на стадії моніторингу 
        state_current_monitoring &= ~(1<<type_current);
      }
      else
      {
        //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
        fix_undefined_error_dr(carrent_active_functions);
      }
    }
    else
    {
      //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
      fix_undefined_error_dr(carrent_active_functions);
    }
  }
  else
  {
    //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
    fix_undefined_error_dr(carrent_active_functions);
  }
}
