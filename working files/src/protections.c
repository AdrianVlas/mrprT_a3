#include "header.h"

/*****************************************************/
//Діагностика АЦП
/*****************************************************/
inline void diagnostyca_adc_execution(void)
{
  if (gnd_adc1 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_BIT);

  if (gnd_adc2 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_BIT);

  if ((vref_adc1 <0x709) || (vref_adc1 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC1_TEST_BIT);

  if ((vref_adc2 <0x709) || (vref_adc2 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC2_TEST_BIT);

  if ((vdd_adc1 <0x8F9) || (vdd_adc1 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);

  if ((vdd_adc2 <0x8F9) || (vdd_adc2 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
}
/*****************************************************/

/*****************************************************/
//Пошук розрядності числа
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//Пошук розрядності числа типу int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//Пошук розрядності числа типу int64
/*****************************************************/
inline unsigned int get_order_64(int64_t value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value = -value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//Розрахунок струму зворотньої послідовності
/*****************************************************/
inline void velychyna_zvorotnoi_poslidovnosti(int ortogonal_local_calc[])
{
  enum _n_phase {_A = 0, _B, _C, _A_B_C};
  const enum _index_meas a_b_c[_NUMBER_FOR_I_U][_A_B_C] = 
  {
    {IM_IA_H  , IM_IB_H  , IM_IC_H  },
    {IM_IA_L  , IM_IB_L  , IM_IC_L  },
    {IM_IA_P_H, IM_IB_P_H, IM_IC_P_H},
    {IM_IA_P_L, IM_IB_P_L, IM_IC_P_L},
    {IM_UA    , IM_UB    , IM_UC    }
  };
  const uint32_t const_val[_NUMBER_FOR_I_U][2] = 
  {
    {IM_I2_H  , IM_I1_H  },
    {IM_I2_L  , IM_I1_L  },
    {IM_I2_P_H, IM_I1_P_H},
    {IM_I2_P_L, IM_I1_P_L},
    {IM_U2    , IM_U1    }
  };
    
  int mul_x1, mul_x2, mul_x3, mul_x4, mul_y1, mul_y2, mul_y3, mul_y4;
  
  for (__index_I_U i_u = INDEX_I_H; i_u < _NUMBER_FOR_I_U; i_u++)
  {
    mul_x1 = (      ortogonal_local_calc[2*a_b_c[i_u][_B]    ]>>1 );
    mul_y1 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_B]    ]>>10);

    mul_x2 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_B] + 1]>>10);
    mul_y2 = (      ortogonal_local_calc[2*a_b_c[i_u][_B] + 1]>>1 );

    mul_x3 = (      ortogonal_local_calc[2*a_b_c[i_u][_C]    ]>>1 );
    mul_y3 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_C]    ]>>10);

    mul_x4 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_C] + 1]>>10);
    mul_y4 = (      ortogonal_local_calc[2*a_b_c[i_u][_C] + 1]>>1 );

    //Зворотня послідовність
    ortogonal_local_calc[2*const_val[i_u][0]    ] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A]    ] - mul_x1  + mul_x2  - mul_x3 - mul_x4)))>>10;
    ortogonal_local_calc[2*const_val[i_u][0] + 1] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A] + 1] - mul_y1  - mul_y2  + mul_y3 - mul_y4)))>>10;

    //Пряма послідовність
    ortogonal_local_calc[2*const_val[i_u][1]    ] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A]    ] - mul_x1  - mul_x2  - mul_x3 + mul_x4)))>>10;
    ortogonal_local_calc[2*const_val[i_u][1] + 1] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A] + 1] + mul_y1  - mul_y2  - mul_y3 - mul_y4)))>>10;
  }
}
/*****************************************************/

/*****************************************************/
//Направленість МТЗ з визначенням секторів
/*****************************************************/
inline void directional_mtz(int ortogonal_local_calc[], unsigned int number_group_stp, unsigned int voltage) 
{
  const uint32_t ctr_msz_sel_I[4] = {CTR_MTZ_1_SEL_I, CTR_MTZ_2_SEL_I, CTR_MTZ_3_SEL_I, CTR_MTZ_4_SEL_I};
  for (unsigned int mtz = 0; mtz < 4; mtz++)
  {
    unsigned int current = (current_settings_prt.control_mtz >> ctr_msz_sel_I[mtz]) & 0x1;
    if (voltage != current)
    {
      //Струм і напруга не співпадають, а тому про направленість не може бути задіяна
      sector_directional_mtz[mtz][0] = sector_directional_mtz[mtz][1] = sector_directional_mtz[mtz][2] = 0;
      
      continue;
    }
    else
    {
      int a_cos_fi, a_sin_fi;
      switch (mtz)
      {
      case 0:
        {
          a_cos_fi = current_settings_prt.setpoint_mtz_1_angle_cos[number_group_stp];
          a_sin_fi = current_settings_prt.setpoint_mtz_1_angle_sin[number_group_stp];
        
          break;
        }
      case 1:
        {
          a_cos_fi = current_settings_prt.setpoint_mtz_2_angle_cos[number_group_stp];
          a_sin_fi = current_settings_prt.setpoint_mtz_2_angle_sin[number_group_stp];
          
          break;
        }
      case 2:
        {
          a_cos_fi = current_settings_prt.setpoint_mtz_3_angle_cos[number_group_stp];
          a_sin_fi = current_settings_prt.setpoint_mtz_3_angle_sin[number_group_stp];
        
          break;
        }
      case 3:
        {
          a_cos_fi = current_settings_prt.setpoint_mtz_4_angle_cos[number_group_stp];
          a_sin_fi = current_settings_prt.setpoint_mtz_4_angle_sin[number_group_stp];
        
          break;
        }
      default:
        {
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(54);
        }
      }
      a_sin_fi = -a_sin_fi; //З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

      //Робимо доповорот на встановлений кут
      /*
      За розрахунком описаним при розрахунку діючих значень наші ортогональні є у ворматі (15 біт + знак) = 16-розряжне число
      */
      int amp_cos_U_fi;
      int amp_sin_U_fi;
  
      for (unsigned int i = 0; i < 3; i++)
      {
        unsigned int index_I, index_U;
        switch (i)
        {
        case 0:
          {
            if (current)
            {
              index_I = IM_IA_L;
            }
            else
            {
              index_I = IM_IA_H;
            }

            index_U = IM_UBC;

            break;
          }
        case 1:
          {
            if (current)
            {
              index_I = IM_IB_L;
            }
            else
            {
              index_I = IM_IB_H;
            }

            index_U = IM_UCA;

            break;
          }
        case 2:
          {
            if (current)
            {
              index_I = IM_IC_L;
            }
            else
            {
              index_I = IM_IC_H;
            }

            index_U = IM_UAB;

            break;
          }
        default:
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(60);
          }
        }

        unsigned int porig_Uxy;
        if (Uxy_bilshe_porogu[i] == 0) porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE*KOEF_POVERNENNJA_SECTOR_BLK/100;
        else porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
        unsigned int Uxy_bilshe_porogu_tmp = Uxy_bilshe_porogu[i] = (measurement[index_U] >= porig_Uxy);
      
        unsigned int porig_Ix;
        if (Ix_bilshe_porogu[i] == 0) porig_Ix = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
        else porig_Ix = PORIG_CHUTLYVOSTI_CURRENT;
        unsigned int Ix_bilshe_porogu_tmp = Ix_bilshe_porogu[i]  = (measurement[index_I] >= porig_Ix );

        if (
            (Uxy_bilshe_porogu_tmp != 0) &&
            (Ix_bilshe_porogu_tmp  != 0)
           )
        {
#define SIN_I   ortogonal_local_calc[2*index_I    ]
#define COS_I   ortogonal_local_calc[2*index_I + 1]
#define SIN_U   ortogonal_local_calc[2*index_U    ]
#define COS_U   ortogonal_local_calc[2*index_U + 1]

          amp_cos_U_fi = (COS_U*a_cos_fi - SIN_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних
          amp_sin_U_fi = (SIN_U*a_cos_fi + COS_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних

          //Вираховуємо COS і SIN кута різниці між (U[i]+fi) і I[i]
          int cos_fi, sin_fi;
          /*
          З наведених теоретичних роззрахунків у функції обрахунку діючих значень (calc_measurement())
          випливає, що максимальне значення ортогональних для струму може бути 0x6E51, для лінійної напруги 
          0x120FC, то добуток їх має дати 0x7C87B7BC  - 31 бітне число (плюс знак біту)
          Тобто ми акладаємося у тип int.
          */
          cos_fi = amp_cos_U_fi*COS_I + amp_sin_U_fi*SIN_I;
          sin_fi = -(amp_sin_U_fi*COS_I - amp_cos_U_fi*SIN_I);//З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

          /*
          З вище наведених розрахункыв виходить, що COS і SIN різниці струму і напруги може бути 31-бітне число
          Векторні координати границь секторів задано 7-бінтими числами + знак
          Тоді щоб не отримати переповнення треба гарантувати, що розрядність різниці векторів
          COS і SIN буде = 31 - (7 + 1) = 23
          7 - це розрядність координат векторів границь секторів
          1 - це врахування що ми використовіємо формулу (ab+cd)
          */
          unsigned int order_cos, order_sin, max_order, shift = 0;
          order_cos = get_order(cos_fi);
          order_sin = get_order(sin_fi);
          if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
          if (max_order > 23) shift = max_order - 23;
  
          /*
          Сам зсув я роблю після визначення квадранта - це хоч і втрата на розмірі програмного коду,
          але мало б підвищити точність визначення квадранту.
          Хоч може тут я перемудровую?..
          */

          //Визначення сектору
          int sin_fi1_minus_fi2;
          int *sector;
          if ((sin_fi >= 0) && (cos_fi >= 0))
          {
            //1-ий квадрант
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;
          
            if (sector_directional_mtz[mtz][i] != 1)
              sector = sector_1_mtz_tznp;
            else
              sector = sector_2_mtz_tznp;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

            sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
            sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
          }
          else if ((sin_fi >= 0) && (cos_fi < 0))
          {
            //2-ий квадрант
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;

            if (sector_directional_mtz[mtz][i] != 2)
              sector = sector_1_mtz_tznp;
            else
              sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

            sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
            sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
          }
          else if ((sin_fi < 0) && (cos_fi < 0))
          {
            //3-ий квадрант
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;

            if (sector_directional_mtz[mtz][i] != 2)
              sector = sector_1_mtz_tznp;
            else
              sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

            sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
            sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
          }
          else
          {
            //4-ий квадрант
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;

            if (sector_directional_mtz[mtz][i] != 1)
              sector = sector_1_mtz_tznp;
            else
              sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

            sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
            sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
          }
        }
        else
        {
          sector_directional_mtz[mtz][i] = 0;
        }
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Направленість ТЗНП з визначенням секторів
/*****************************************************/
inline void directional_tznp(int ortogonal_local_calc[], unsigned int number_group_stp, unsigned int voltage) 
{
  for (unsigned int tznp = 0; tznp < 4; tznp++)
  {
    int a_cos_fi, a_sin_fi;
    switch (tznp)
    {
    case 0:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_1_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_1_angle_sin[number_group_stp];
        
        break;
      }
    case 1:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_2_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_2_angle_sin[number_group_stp];
        
        break;
      }
    case 2:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_3_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_3_angle_sin[number_group_stp];
        
        break;
      }
    case 3:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_4_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_4_angle_sin[number_group_stp];
        
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(81);
      }
    }
    a_sin_fi = -a_sin_fi; //З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

    //Робимо доповорот на встановлений кут
    /*
    За розрахунком описаним при розрахунку діючих значень наші ортогональні є у ворматі (15 біт + знак) = 16-розряжне число
    */
    unsigned int porig_U;
    if (TZNP_3U0_bilshe_porogu == 0) porig_U = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_U = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
    unsigned int U_bilshe_porogu_tmp = TZNP_3U0_bilshe_porogu = (measurement[IM_3U0_r] >= porig_U);
      
    unsigned int porig_I;
    if (TZNP_3I0_r_bilshe_porogu == 0) porig_I = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_I = PORIG_CHUTLYVOSTI_CURRENT;
    unsigned int I_bilshe_porogu_tmp = TZNP_3I0_r_bilshe_porogu  = (measurement[IM_3I0_r_H] >= porig_I);

    if (
        (U_bilshe_porogu_tmp != 0) &&
        (I_bilshe_porogu_tmp != 0)
       )
    {
      /*
      Згідно з ТЗ напругу треба довернути на 180 градусів.
      cos(phi + Pi) = -cos(phi)
      sin(phi + Pi) = -sin(phi)
      Тому COS_U змінюємо знак
      */
#define SIN_I           ((voltage) ? ortogonal_local_calc[2*IM_3I0_r_L    ] : ortogonal_local_calc[2*IM_3I0_r_H    ])
#define COS_I           ((voltage) ? ortogonal_local_calc[2*IM_3I0_r_L + 1] : ortogonal_local_calc[2*IM_3I0_r_H + 1])
#define SIN_U_plus_Pi   (-ortogonal_local_calc[2*IM_3U0_r      ])
#define COS_U_plus_Pi   (-ortogonal_local_calc[2*IM_3U0_r   + 1])

      int cos_I_fi = (COS_I*a_cos_fi - SIN_I*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних
      int sin_I_fi = (SIN_I*a_cos_fi + COS_I*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних

      //Вираховуємо COS і SIN кута різниці між (3I0_r+fi) і (3U0 + 180°)
      int cos_fi, sin_fi;
      /*
      З наведених теоретичних роззрахунків у функції обрахунку діючих значень (calc_measurement())
      випливає, що максимальне значення ортогональних для струму може бути 0x6E51, для фазної напруги (3U0)
      0x907E, то добуток їх має дати 0x3E43DBDE  - 30 бітне число (плюс знак біту)
      Тобто ми акладаємося у тип int.
      */
      cos_fi = cos_I_fi*COS_U_plus_Pi + sin_I_fi*SIN_U_plus_Pi;
      sin_fi = -(sin_I_fi*COS_U_plus_Pi - cos_I_fi*SIN_U_plus_Pi);//З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

#undef SIN_I
#undef COS_I
#undef SIN_U_plus_Pi
#undef COS_U_plus_Pi

      /*
      З вище наведених розрахунків виходить, що COS і SIN різниці струму і напруги може бути 31(30)-бітне число
      Векторні координати границь секторів задано 7-бінтими числами + знак
      Тоді щоб не отримати переповнення треба гарантувати, що розрядність різниці векторів
      COS і SIN буде = 31 - (7 + 1) = 23
      7 - це розрядність координат векторів границь секторів
      1 - це врахування що ми використовіємо формулу (ab+cd)
      */
      unsigned int order_cos, order_sin, max_order, shift = 0;
      order_cos = get_order(cos_fi);
      order_sin = get_order(sin_fi);
      if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
      if (max_order > 23) shift = max_order - 23;
  
      /*
      Сам зсув я роблю після визначення квадранта - це хоч і втрата на розмірі програмного коду,
      але мало б підвищити точність визначення квадранту.
      Хоч може тут я перемудровую?..
      */

      //Визначення сектору
      int sin_fi1_minus_fi2;
      int *sector;
      if ((sin_fi >= 0) && (cos_fi >= 0))
      {
        //1-ий квадрант
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;
          
        if (sector_directional_tznp[tznp] != 1)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
      }
      else if ((sin_fi >= 0) && (cos_fi < 0))
      {
        //2-ий квадрант
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 2)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
      else if ((sin_fi < 0) && (cos_fi < 0))
      {
        //3-ий квадрант
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 2)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
      else
      {
        //4-ий квадрант
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 1)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
    }
    else
    {
      sector_directional_tznp[tznp] = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Направленість МТЗ з визначенням секторів
/*****************************************************/
inline void directional_kz_zv(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  /*
  За розрахунком описаним при розрахунку діючих значень наші ортогональні для струму є у ворматі (15 біт + знак) = 16-розряжне число і не перевищують число 0x6E51
  Приведений струм максимально можливий може бути чило помножене на Iном (5А) і поділений на мінімальну уставку Iвир (1,5А). Тобто приведений струм не може бути більший за струм з давача помножений у 4 рази (бо 5/1,5 < 4).
  Отже ортогональні приведеного струму можуть бути у чотири зази більші. 0x6E51 * 4 = 0x1B944
  Оскільки струм зворотньої послідовності не мє більшим за максимальний струм у трифазній мережі, то і максимальне значення ортогональних для приведеного струму зворотної послідовності не буде більшим за 0x1B944 (17- бітне число)
  */
  static unsigned int KZ_ZV_I2_P_H_bilshe_porogu;
  unsigned int porig_I2_P_H;
  if (KZ_ZV_I2_P_H_bilshe_porogu == 0) porig_I2_P_H = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_I2_P_H = PORIG_CHUTLYVOSTI_CURRENT;
  unsigned int KZ_ZV_I2_P_H_bilshe_porogu_tmp = KZ_ZV_I2_P_H_bilshe_porogu = (measurement[IM_I2_P_H] >= porig_I2_P_H);
      
  static unsigned int KZ_ZV_I2_P_L_bilshe_porogu;
  unsigned int porig_I2_P_L;
  if (KZ_ZV_I2_P_L_bilshe_porogu == 0) porig_I2_P_L = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_I2_P_L = PORIG_CHUTLYVOSTI_CURRENT;
  unsigned int KZ_ZV_I2_P_L_bilshe_porogu_tmp = KZ_ZV_I2_P_L_bilshe_porogu = (measurement[IM_I2_P_L] >= porig_I2_P_L);

  if (
      (KZ_ZV_I2_P_H_bilshe_porogu_tmp != 0) &&
      (KZ_ZV_I2_P_L_bilshe_porogu_tmp != 0)
     )
  {
#define SIN_I2_P_H           ortogonal_local_calc[2*IM_I2_P_H    ]
#define COS_I2_P_H           ortogonal_local_calc[2*IM_I2_P_H + 1]

#define SIN_I2_P_L           ortogonal_local_calc[2*IM_I2_P_L    ]
#define COS_I2_P_L           ortogonal_local_calc[2*IM_I2_P_L + 1]
    
    //Вираховуємо COS і SIN кута різниці між I2(ВН пр.) і I2(НН пр.)
    int64_t cos_fi, sin_fi;
    /*
    З наведених вище теоретичних роззрахунківвипливає, що максимальне значення ортогональних для струму може бути 0x1B944
    Тобто ми можемо вийти за межі чотирибайтного числа.
    Тому для забезпечення точності для малих значеть я ввожу 64-бітні змінні.
    */
    cos_fi = COS_I2_P_H*COS_I2_P_L + SIN_I2_P_H*SIN_I2_P_L;
    sin_fi = SIN_I2_P_H*COS_I2_P_L - COS_I2_P_H*SIN_I2_P_L;

#undef SIN_I2_P_H
#undef COS_I2_P_H
    
#undef SIN_I2_P_L
#undef COS_I2_P_L

    /*
    З вище наведених розрахунків виходить, що COS і SIN різниці струмыв і напруги може бути 35(34)-бітне число
    Векторні координати границь секторів задано 7-бінтими числами + знак
    Тоді щоб не отримати переповнення треба гарантувати, що розрядність різниці векторів
    COS і SIN буде = 31 - (7 + 1) = 23
    7 - це розрядність координат векторів границь секторів
    1 - це врахування що ми використовіємо формулу (ab+cd)
    */
    unsigned int order_cos, order_sin, max_order, shift = 0;
    order_cos = get_order_64(cos_fi);
    order_sin = get_order_64(sin_fi);
    if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
    if (max_order > 23) shift = max_order - 23;
  
    /*
    Сам зсув я роблю після визначення квадранта - це хоч і втрата на розмірі програмного коду,
    але мало б підвищити точність визначення квадранту.
    Хоч може тут я перемудровую?..
    */

    //Визначення сектору
    int sin_fi1_minus_fi2;
    int cos_s, sin_s;
    if (
        (cos_fi >  0) && 
        (sin_fi >= 0)
       )
    {
      //1-ий квадрант
      cos_fi = cos_fi >> shift;
      sin_fi = sin_fi >> shift;
          
      if (sector_kz_zv != SECTOR_KZ_V)
      {
        cos_s = current_settings_prt.pickup_kz_zv_angle_cos_1[number_group_stp];
        sin_s = current_settings_prt.pickup_kz_zv_angle_sin_1[number_group_stp];
      }
      else
      {
        cos_s = current_settings_prt.pickup_kz_zv_angle_cos_2[number_group_stp];
        sin_s = current_settings_prt.pickup_kz_zv_angle_sin_2[number_group_stp];
      }
          
      sin_fi1_minus_fi2 = sin_fi*cos_s - cos_fi*sin_s;
      sector_kz_zv = (sin_fi1_minus_fi2 <= 0) ?  SECTOR_KZ_V : SECTOR_KZ_NEVYZN;
    }
    else if (
             (cos_fi <= 0) && 
             (sin_fi >  0)  
            )
    {
      //2-ий квадрант
      cos_fi = cos_fi >> shift;
      sin_fi = sin_fi >> shift;
          
      if (sector_kz_zv != SECTOR_KZ_Z)
      {
        cos_s = -current_settings_prt.pickup_kz_zv_angle_cos_1[number_group_stp];
        sin_s =  current_settings_prt.pickup_kz_zv_angle_sin_1[number_group_stp];
      }
      else
      {
        cos_s = -current_settings_prt.pickup_kz_zv_angle_cos_2[number_group_stp];
        sin_s =  current_settings_prt.pickup_kz_zv_angle_sin_2[number_group_stp];
      }
          
      sin_fi1_minus_fi2 = sin_fi*cos_s - cos_fi*sin_s;
      sector_kz_zv = (sin_fi1_minus_fi2 >= 0) ?  SECTOR_KZ_Z : SECTOR_KZ_NEVYZN;
    }
    else if (
             (cos_fi <  0) && 
             (sin_fi >= 0)  
            )
    {
      //3-ий квадрант
      cos_fi = cos_fi >> shift;
      sin_fi = sin_fi >> shift;
          
      if (sector_kz_zv != SECTOR_KZ_Z)
      {
        cos_s = -current_settings_prt.pickup_kz_zv_angle_cos_1[number_group_stp];
        sin_s = -current_settings_prt.pickup_kz_zv_angle_sin_1[number_group_stp];
      }
      else
      {
        cos_s = -current_settings_prt.pickup_kz_zv_angle_cos_2[number_group_stp];
        sin_s = -current_settings_prt.pickup_kz_zv_angle_sin_2[number_group_stp];
      }
          
      sin_fi1_minus_fi2 = sin_fi*cos_s - cos_fi*sin_s;
      sector_kz_zv = (sin_fi1_minus_fi2 <= 0) ?  SECTOR_KZ_Z : SECTOR_KZ_NEVYZN;
    }
    else
    {
      //4-ий квадрант
      cos_fi = cos_fi >> shift;
      sin_fi = sin_fi >> shift;
         
      if (sector_kz_zv != SECTOR_KZ_V)
      {
        cos_s =  current_settings_prt.pickup_kz_zv_angle_cos_1[number_group_stp];
        sin_s = -current_settings_prt.pickup_kz_zv_angle_sin_1[number_group_stp];
      }
      else
      {
        cos_s =  current_settings_prt.pickup_kz_zv_angle_cos_2[number_group_stp];
        sin_s = -current_settings_prt.pickup_kz_zv_angle_sin_2[number_group_stp];
      }
          
      sin_fi1_minus_fi2 = sin_fi*cos_s - cos_fi*sin_s;
      sector_kz_zv = (sin_fi1_minus_fi2 >= 0) ?  SECTOR_KZ_V : SECTOR_KZ_NEVYZN;
    }
  }
  else
  {
    sector_kz_zv = SECTOR_KZ_NEVYZN;
  }
}
/*****************************************************/

/*****************************************************/
//Визначенням миттєвої потужності
/*****************************************************/
inline void calc_power(int ortogonal_local_calc[], unsigned int voltage) 
{
  /*
  Розраховуємо дійсну і уявну частину потужності у компдексній площині
  
  .    . .     . .     . .
  S = UaIa* + UbIb* + UcIc*
  */
  
#define IA_SIN          ((voltage) ? ortogonal_local_calc[2*IM_IA_L + 1] : ortogonal_local_calc[2*IM_IA_H + 1])
#define IA_COS          ((voltage) ? ortogonal_local_calc[2*IM_IA_L + 0] : ortogonal_local_calc[2*IM_IA_H + 0])
#define UA_SIN          ortogonal_local_calc[2*IM_UA + 1]
#define UA_COS          ortogonal_local_calc[2*IM_UA + 0]
  
#define IB_SIN          ((voltage) ? ortogonal_local_calc[2*IM_IB_L + 1] : ortogonal_local_calc[2*IM_IC_H + 1])
#define IB_COS          ((voltage) ? ortogonal_local_calc[2*IM_IB_L + 0] : ortogonal_local_calc[2*IM_IC_H + 0])
#define UB_SIN          ortogonal_local_calc[2*IM_UB + 1]
#define UB_COS          ortogonal_local_calc[2*IM_UB + 0]

#define IC_SIN          ((voltage) ? ortogonal_local_calc[2*IM_IC_L + 1] : ortogonal_local_calc[2*IM_IC_H + 1])
#define IC_COS          ((voltage) ? ortogonal_local_calc[2*IM_IC_L + 0] : ortogonal_local_calc[2*IM_IC_H + 0])
#define UC_SIN          ortogonal_local_calc[2*IM_UC + 1]
#define UC_COS          ortogonal_local_calc[2*IM_UC + 0]
  
  long long Re_UaIa, Im_UaIa;
  if (measurement[IM_IA_H] >= PORIG_I_ENERGY)
  {
    Re_UaIa = UA_COS*IA_COS + UA_SIN*IA_SIN;
    Im_UaIa = UA_SIN*IA_COS - UA_COS*IA_SIN;
  
  }
  else
  {
    Re_UaIa = 0;
    Im_UaIa = 0;
  }
  
  long long Re_UbIb, Im_UbIb;
  if (measurement[IM_IB_H] >= PORIG_I_ENERGY)
  {
    Re_UbIb = UB_COS*IB_COS + UB_SIN*IB_SIN;
    Im_UbIb = UB_SIN*IB_COS - UB_COS*IB_SIN;
  
  }
  else
  {
    Re_UbIb = 0;
    Im_UbIb = 0;
  }
  
  long long Re_UcIc, Im_UcIc;
  if (measurement[IM_IC_H] >= PORIG_I_ENERGY)
  {
    Re_UcIc = UC_COS*IC_COS + UC_SIN*IC_SIN;
    Im_UcIc = UC_SIN*IC_COS - UC_COS*IC_SIN;
  
  }
  else
  {
    Re_UcIc = 0;
    Im_UcIc = 0;
  }

#undef IA_SIN
#undef IA_COS
#undef UA_SIN
#undef UA_COS
  
#undef IB_SIN
#undef IB_COS
#undef UB_SIN
#undef UB_COS
  
#undef IC_SIN
#undef IC_COS
#undef UC_SIN
#undef UC_COS
  
  long long P_adc_x16 = Re_UaIa + Re_UbIb + Re_UcIc; /*  активна потужність у поділках АЦП і з вхідними сигналами, які є підсилені у 16 разів*/
  long long Q_adc_x16 = Im_UaIa + Im_UbIb + Im_UcIc; /*реактивна потужність у поділках АЦП і з вхідними сигналами, які є підсилені у 16 разів*/
  
  /*
  Коли перемножимо на коефіцієнти MNOGNYK_I_DIJUCHE_FLOAT і MNOGNYK_U_DIJUCHE_FLOAT,
  а потім поділемо на 16x16 - то отримаємо мАхмВ = мкВт/мкВАр/мкВА
  
  Ми хочемо тримати число у мВт/мВАр/мВА. 
  
  Тоді треба поділити ще на 1000
  */
  
  //Активна потужність
  double P_float = ((double)P_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int P_tmp = (int)(P_float); // з точністю до мВт

  //Реактивна потужність
  double Q_float = ((double)Q_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int Q_tmp  = (int)(Q_float); // з точністю до мВАр

  unsigned int bank_for_enegry_tmp = bank_for_enegry;  
  int *energy_array;
  
  //Активна потужність
  if (P_tmp >= 0) energy_array = P_plus;
  else energy_array = P_minus;
  *(energy_array + bank_for_enegry_tmp) += abs(P_tmp);
  
  //Реактивна потужність
  if     ((Q_tmp >= 0) && (P_tmp >= 0)) energy_array = Q_1q;
  else if((Q_tmp >= 0) && (P_tmp <  0)) energy_array = Q_2q;
  else if((Q_tmp <  0) && (P_tmp <  0)) energy_array = Q_3q;
  else                                  energy_array = Q_4q;
  *(energy_array + bank_for_enegry_tmp) += abs(Q_tmp);
  
  if (++lichylnyk_1s_po_20ms >= MAIN_FREQUENCY)
  {
    if (lichylnyk_1s_po_20ms > MAIN_FREQUENCY)
    {
      //Теоретично цього ніколи не мало б бути
      total_error_sw_fixed(64);
    }

    //Переключаємо банк для збереження нових даних s обнулюємо значення у новому банку
    bank_for_enegry = bank_for_enegry_tmp = (bank_for_enegry_tmp + 1) & 0x1;
    P_plus[bank_for_enegry_tmp] = 0;
    P_minus[bank_for_enegry_tmp] = 0;
    Q_1q[bank_for_enegry_tmp] = 0;
    Q_2q[bank_for_enegry_tmp] = 0;
    Q_3q[bank_for_enegry_tmp] = 0;
    Q_4q[bank_for_enegry_tmp] = 0;
    
    lichylnyk_1s_po_20ms = 0;
    if (periodical_tasks_CALC_POWER_DATA == 0)
    {
      //Скидаємо повідомлення у слові діагностики
      _SET_BIT(clear_diagnostyka, LOSE_POWER_DATA);
    }
    else
    {
      //Виствляємо повідомлення у слові діагностики
      _SET_BIT(set_diagnostyka, LOSE_POWER_DATA);
    }
    periodical_tasks_CALC_POWER_DATA = true;
  }
  
}
/*****************************************************/

/*****************************************************/
//Розрахунки віимірювань
/*****************************************************/
inline void calc_measurement(unsigned int number_group_stp)
{
  int ortogonal_local[2*(NUMBER_ANALOG_CANALES + 3*(NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES))];
  int aperiodic_local[NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES];

  //Копіюємо вхідні велечини у локальні змінні
  /*
  оскільки для дискретного перетворення Фурє коефіцієнти діляться на число виборок і множиться на 2 (еквівалент 2/Т),
  то це ми можемо зробити зміщенням
  */
  /*
  Проведені мною розрахунки показують, що якщо просумувати добуток миттєвих значень на синус/косинус за період,
  а потім результат поділити на 2/Т (зробити це відповідним зсуваом, про який я писав вище),
  то максимана розрядність резутьтату буде рівна макисальній розрядності вхідного сигналу
  Тобто для фазних струмів - це 15 біт + знак = ((11 біт + знак)*16   )
  оскільки нам ще треба це число піднімати до квадрату а аж потім добувати корінь квадратний з суми квадратів, то
  фазний струм можна підносити до кваррату - переповнення не буде, бо (15 біт *2) = 30 біт Бо 32 біт unsigned int
  А аж потім забрати множенння на 16, щоб збільшити точність вимірювання
  
  Для покращення точності з 18 листопада 2014 року я забираю амплітуду sin/cos вже
  перед самими розрахунками
  */
  
  {
    unsigned int bank_ortogonal_tmp = (bank_ortogonal + 1) & 0x1;

    uint32_t index_ort = 0;
  
    //Струми/напруги з давачів
    for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++ )
    {
      ortogonal_local[index_ort] = ortogonal[bank_ortogonal_tmp][index_ort];
      index_ort++;

      ortogonal_local[index_ort] = ortogonal[bank_ortogonal_tmp][index_ort];
      index_ort++;
    }

    //Диф.струми
    uint32_t index_aper = 0;
    for(unsigned int i = NUMBER_ANALOG_CANALES; i < (NUMBER_ANALOG_CANALES + 3*(NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES)); i++ )
    {
      aperiodic_local[index_aper] = aperiodic[bank_ortogonal_tmp][index_aper];
      index_aper++;

      ortogonal_local[index_ort] = ortogonal[bank_ortogonal_tmp][index_ort];
      index_ort++;

      ortogonal_local[index_ort] = ortogonal[bank_ortogonal_tmp][index_ort];
      index_ort++;
    }
  
    bank_ortogonal = bank_ortogonal_tmp;
  }
  
  /***
  Довертаємо кути
  ***/
  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    float sin_alpha = ((float)ortogonal_local[2*i    ])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    float cos_alpha = ((float)ortogonal_local[2*i + 1])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    
    float sin_beta =  phi_ustuvannja_sin_cos_meas[2*i    ];
    float cos_beta =  phi_ustuvannja_sin_cos_meas[2*i + 1];
    
    unsigned int new_index = index_converter[i];
    ortogonal_calc[2*new_index    ] = (int)(sin_alpha*cos_beta + cos_alpha*sin_beta);
    ortogonal_calc[2*new_index + 1] = (int)(cos_alpha*cos_beta - sin_alpha*sin_beta);
  }
  for (unsigned int i = NUMBER_ANALOG_CANALES; i < (NUMBER_ANALOG_CANALES + 3*(NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES)); i++)
  {
    unsigned int new_index = index_converter[i];
    ortogonal_calc[2*new_index    ] = ortogonal_local[2*i    ] >> (VAGA_NUMBER_POINT - 1);
    ortogonal_calc[2*new_index + 1] = ortogonal_local[2*i + 1] >> (VAGA_NUMBER_POINT - 1);
  }
  /***/

  /***
  Дорозраховунок ортогональних
  ***/
  //3I0_H(розрахункове)
  ortogonal_calc[2*IM_3I0_r_H + 0] = ortogonal_calc[2*IM_IA_H    ] + ortogonal_calc[2*IM_IB_H    ] + ortogonal_calc[2*IM_IC_H    ];
  ortogonal_calc[2*IM_3I0_r_H + 1] = ortogonal_calc[2*IM_IA_H + 1] + ortogonal_calc[2*IM_IB_H + 1] + ortogonal_calc[2*IM_IC_H + 1];

  //3I0_L(розрахункове)
  ortogonal_calc[2*IM_3I0_r_L + 0] = ortogonal_calc[2*IM_IA_L    ] + ortogonal_calc[2*IM_IB_L    ] + ortogonal_calc[2*IM_IC_L    ];
  ortogonal_calc[2*IM_3I0_r_L + 1] = ortogonal_calc[2*IM_IA_L + 1] + ortogonal_calc[2*IM_IB_L + 1] + ortogonal_calc[2*IM_IC_L + 1];

  //3U0(розрахункове)
  ortogonal_calc[2*IM_3U0_r + 0] = ortogonal_calc[2*IM_UA    ] + ortogonal_calc[2*IM_UB    ] + ortogonal_calc[2*IM_UC    ];
  ortogonal_calc[2*IM_3U0_r + 1] = ortogonal_calc[2*IM_UA + 1] + ortogonal_calc[2*IM_UB + 1] + ortogonal_calc[2*IM_UC + 1];
    
  //Ubc
  ortogonal_calc[2*IM_UBC + 0] = ortogonal_calc[2*IM_UB    ] - ortogonal_calc[2*IM_UC    ];
  ortogonal_calc[2*IM_UBC + 1] = ortogonal_calc[2*IM_UB + 1] - ortogonal_calc[2*IM_UC + 1];
  
  //Uca
  ortogonal_calc[2*IM_UCA + 0] = ortogonal_calc[2*IM_UC    ] - ortogonal_calc[2*IM_UA    ];
  ortogonal_calc[2*IM_UCA + 1] = ortogonal_calc[2*IM_UC + 1] - ortogonal_calc[2*IM_UA + 1];

  //Uab
  ortogonal_calc[2*IM_UAB + 0] = ortogonal_calc[2*IM_UA    ] - ortogonal_calc[2*IM_UB    ];
  ortogonal_calc[2*IM_UAB + 1] = ortogonal_calc[2*IM_UA + 1] - ortogonal_calc[2*IM_UB + 1];

  //Приведені струми високої сторони
  double koef_VH_tmp = koef_VH_meas;
  switch (type_con_ozt_meas)
  {
  case TYPE_CON_OZT_0:
    {
      ortogonal_calc[2*IM_IA_P_H + 0] = (int)(round((double)ortogonal_calc[2*IM_IA_H + 0]*koef_VH_tmp));
      ortogonal_calc[2*IM_IA_P_H + 1] = (int)(round((double)ortogonal_calc[2*IM_IA_H + 1]*koef_VH_tmp));

      ortogonal_calc[2*IM_IB_P_H + 0] = (int)(round((double)ortogonal_calc[2*IM_IB_H + 0]*koef_VH_tmp));
      ortogonal_calc[2*IM_IB_P_H + 1] = (int)(round((double)ortogonal_calc[2*IM_IB_H + 1]*koef_VH_tmp));
      
      ortogonal_calc[2*IM_IC_P_H + 0] = (int)(round((double)ortogonal_calc[2*IM_IC_H + 0]*koef_VH_tmp));
      ortogonal_calc[2*IM_IC_P_H + 1] = (int)(round((double)ortogonal_calc[2*IM_IC_H + 1]*koef_VH_tmp));

      break;
    }
  case TYPE_CON_OZT_1:
    {
      ortogonal_calc[2*IM_IA_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IA_H + 0] - ortogonal_calc[2*IM_IC_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IA_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IA_H + 1] - ortogonal_calc[2*IM_IC_H + 1])*koef_VH_tmp));

      ortogonal_calc[2*IM_IB_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IB_H + 0] - ortogonal_calc[2*IM_IA_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IB_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IB_H + 1] - ortogonal_calc[2*IM_IA_H + 1])*koef_VH_tmp));
      
      ortogonal_calc[2*IM_IC_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IC_H + 0] - ortogonal_calc[2*IM_IB_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IC_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IC_H + 1] - ortogonal_calc[2*IM_IB_H + 1])*koef_VH_tmp));

      break;
    }
  case TYPE_CON_OZT_11:
    {
      ortogonal_calc[2*IM_IA_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IA_H + 0] - ortogonal_calc[2*IM_IB_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IA_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IA_H + 1] - ortogonal_calc[2*IM_IB_H + 1])*koef_VH_tmp));

      ortogonal_calc[2*IM_IB_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IB_H + 0] - ortogonal_calc[2*IM_IC_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IB_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IB_H + 1] - ortogonal_calc[2*IM_IC_H + 1])*koef_VH_tmp));
      
      ortogonal_calc[2*IM_IC_P_H + 0] = (int)(round((double)(ortogonal_calc[2*IM_IC_H + 0] - ortogonal_calc[2*IM_IA_H + 0])*koef_VH_tmp));
      ortogonal_calc[2*IM_IC_P_H + 1] = (int)(round((double)(ortogonal_calc[2*IM_IC_H + 1] - ortogonal_calc[2*IM_IA_H + 1])*koef_VH_tmp));

      break;
    }
  default: total_error_sw_fixed(49);
  }
  
  //Приведені струми низької сторони
  double koef_VL_tmp = koef_VL_meas;
  ortogonal_calc[2*IM_IA_P_L + 0] = (int)(round((double)ortogonal_calc[2*IM_IA_L + 0]*koef_VL_tmp));
  ortogonal_calc[2*IM_IA_P_L + 1] = (int)(round((double)ortogonal_calc[2*IM_IA_L + 1]*koef_VL_tmp));
  
  ortogonal_calc[2*IM_IB_P_L + 0] = (int)(round((double)ortogonal_calc[2*IM_IB_L + 0]*koef_VL_tmp));
  ortogonal_calc[2*IM_IB_P_L + 1] = (int)(round((double)ortogonal_calc[2*IM_IB_L + 1]*koef_VL_tmp));
  
  ortogonal_calc[2*IM_IC_P_L + 0] = (int)(round((double)ortogonal_calc[2*IM_IC_L + 0]*koef_VL_tmp));
  ortogonal_calc[2*IM_IC_P_L + 1] = (int)(round((double)ortogonal_calc[2*IM_IC_L + 1]*koef_VL_tmp));
  
  /***/
  //Розраховуємо напругу прямої і зворотньої послідовності
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc);
  /***/

  /***
  Копіюємо ортогональні для низькопріоритетних задач
  ***/
  if (semaphore_measure_values_low == 0)
  {
    for (size_t i = 0; i < (2*FULL_ORT_MAX_TOTAL); i++) ortogonal_calc_low[i] = ortogonal_calc[i];
  } 
  /***/

  /*
  ---------------------------------------------------------------------------------------------------------
  150А (150 000мА) - максимальний фазний струм
  Коефіцієнст переведення в мА  - Koef_1 = 84,978173543997808495193432804655 для фазних струмів (5439/64 = 84,984375)
  
  Тоді для 150А максимально можливе значення ортогональних може бути
  150000/Koef_1 = 1765,0303364589078874793160507446
  Якщо врахувати, що сигнал є підсиленим у 16 раз, то максимальне значення ортогональних може бути
  16*150000/Koef_1 = 28240,485383342526199669056811914 < 28241(0x6E51) це є 15 бітне число (+ можливий знак)
  ---------------------------------------------------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------
  150В (150 000мВ) - максимальна фазна напруга
  Коефіцієнст переведення в мВ  - Koef_1 = 64,883134509545420915167731259667 для фазних напруг (4152/64 = 64,875)
  
  Тоді для 150В максимально можливе значення ортогональних може бути
  150000/Koef_1 = 2311,848851536795430557291797995
  Якщо врахувати, що сигнал є підсиленим у 16 раз, то максимальне значення ортогональних може бути
  16*150000/Koef_1 = 36989,581624588726888916668767919 < 36990(0x907E) це є 16 бітне число (+ можливий знак) - тобто число виходить 17-бітне
  
  Якщо з фазної напруги розраховується лінійна напруга, то, якщо припустити що вектори розврнуті у різні сторони, то  максимальне
  значення ортогональних може бути
  2*16*150000/Koef_1 = 73979,163249177453777833337535838 < 73980(0x120FC) це є 17 бітне число (+ можливий знак) - тобто число виходить 18-бітне
  ---------------------------------------------------------------------------------------------------------
  */
  
  /***/
  //Розраховуємо діюче значення через перетворення Фур'є
  /***/
  for(enum _index_meas i = IM_UA; i < FULL_ORT_MAX_TOTAL; i++)
  {
    uint32_t mnognyk, vaga_dilennja;
    if (i <= _IM_U_END)
    {
      mnognyk = MNOGNYK_U_DIJUCHE;
      vaga_dilennja = VAGA_DILENNJA_U_DIJUCHE;
    }
    else
    {
      mnognyk = MNOGNYK_I_DIJUCHE;
      vaga_dilennja = VAGA_DILENNJA_I_DIJUCHE;
    }
    
    uint64_t _x = ortogonal_calc[2*i    ];
    uint64_t _y = ortogonal_calc[2*i + 1];

    measurement[i] = ( mnognyk*(sqrt_64(_x*_x + _y*_y)) ) >> (vaga_dilennja + 4);
  }
  /***/

  /***/
  //Розраховуємо аперіодичну складову і струм гальмування
  /***/
  for(size_t i = 0; i < (NUMBER_ANALOG_CANALES_WITH_CALC - NUMBER_ANALOG_CANALES); i++)
  {
    measurement[IM_adIA + i] = ( MNOGNYK_I_DIJUCHE* ((uint64_t)abs(aperiodic_local[i]))) >> (VAGA_NUMBER_POINT + VAGA_DILENNJA_I_DIJUCHE + 3); // (VAGA_DILENNJA_I_DIJUCHE + 4 + VAGA_NUMBER_POINT - 1) = VAGA_NUMBER_POINT + VAGA_DILENNJA_I_DIJUCHE + 3
    
    measurement[IM_gdIA + i] = measurement[IM_IA_P_H + i] + pickup_ozt_k_meas[number_group_stp]*(measurement[IM_IA_P_L + i] - measurement[IM_IA_P_H + i])/1000;
  }
  /***/
  
  unsigned int voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;
  if ((current_settings_prt.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0)
  {
    /***/
    //Фазочутливий елемент для МТЗ (всіх ступенів)
    /***/
    directional_mtz(ortogonal_calc, number_group_stp, voltage);
    /***/
  }
  else
  {
    sector_directional_mtz[0][0] = sector_directional_mtz[0][1] = sector_directional_mtz[0][2] = 
    sector_directional_mtz[1][0] = sector_directional_mtz[1][1] = sector_directional_mtz[1][2] = 
    sector_directional_mtz[2][0] = sector_directional_mtz[2][1] = sector_directional_mtz[2][2] = 
    sector_directional_mtz[3][0] = sector_directional_mtz[3][1] = sector_directional_mtz[3][2] = 0;
  }

  if ((current_settings_prt.configuration & (1<<TZNP_BIT_CONFIGURATION)) != 0)
  {
    /***/
    //Фазочутливий елемент для ТЗНП (всіх ступенів)
    /***/
    directional_tznp(ortogonal_calc, number_group_stp, voltage);
    /***/
  }
  else
  {
    sector_directional_tznp[0] = sector_directional_tznp[1] = sector_directional_tznp[2] = sector_directional_tznp[3] = 0;
  }
  
  if ((current_settings_prt.configuration & (1<<KZ_ZV_BIT_CONFIGURATION)) != 0)
  {
    /***/
    //Фазочутливий елемент для "Зовнішнього/Внутрішнього Пошкодження"
    /***/
    directional_kz_zv(ortogonal_calc, number_group_stp);
    /***/
  }
  else
  {
    sector_kz_zv = SECTOR_KZ_NEVYZN;
  }
  
  if(++number_inputs_for_fix_one_period >= 20)
  {
    /***/
    //Розрахунок миттєвих потужностей (раз на 20мс)
    /***/
    calc_power(ortogonal_calc, voltage);
    /***/
    
    number_inputs_for_fix_one_period = 0;
  }
}
/*****************************************************/

/*****************************************************/
//Модуль обробки дискретних входів
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin = 0; //Змінні у якій формуємо значення входів отримані із входів процесора (пінів)
  static unsigned int state_inputs_into_pin_trigger; //У цій змінній зберігається попередній стан піна, у випадку коли ми перевіряємо .чи утримається цей стан до кінця тактування таймера допуску

  /***************************/
  //У цій частині знімаємо стани входів процесора (пінів), які відповідають за дискретні входи
  /*
  -----------------------------
  значення поміщається у відпорвідні біти змінної state_inputs_into_pin
    "є     сигнал " - відповідає встановленому біту (1)
    "немає сигналу" - відповідає скинутому     біту (0)
  -----------------------------
  */
  state_inputs_into_pin |=  ( _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36)       & 0xffff)
//#if MODYFIKACIA_VERSII_PZ == 0
//                         | (((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) &    0xf) << 16)
//#endif
                        ;
  /***************************/
  
  /***************************/
  //Обробка таймерів допуску дискретних входів
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //Провірка на зміну стану дискретного входу здійснюється тільки тоді, коли величина таймере є від'ємною
      //Що означає що таймер не запущений у попередній момент
      
      //Перевіряємо чи таеперішній стан входу відповідає попердньомук стану
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //Якщо стан входу змінився, то виконуємо дії по зміні стану

        //1-дія: Запям'ятовуємо текучий стан входу
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-дія: Запускаємо таймер допуску дискретного входу
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //Якщо таймер запущений виконуємо дії з таймером
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //Якщо таймер ще не дійшов до свого макисмуму, то просто збільшуємо його величину
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //У випадку, якщо тип сигналу на вхід подається змінний
        //і ми перевіряємо чи не відбувся перехід "є сигнал"->"немає сигналу"
        //то поява сигналу під час тактування таймера допуску означає, що сигнал на вході є - 
        //а це означає, що треба зупинити nаймер, бо переходу "є сигнал"->"немає сигналу" на протязі тактування таймеру не зафіксовано 
        if ((current_settings_prt.type_of_input_signal & maska) != 0)
        {
           if ((state_inputs_into_pin_trigger & maska) == 0)
           {
             if ((state_inputs_into_pin & maska) != 0)
               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
           }
        }
      }
    }
    
    //Якщо величина таймера допуска знаходиться у свому максимальному значенні, то перевіряємо, чи фактично змінився стано входу
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //Перевіряємо, чи стан піна змінився у порівнянні із станом, який був на момент запуску таймера допуску дискретного входу
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //Якщо два стани співпадають, то ми вважаємо, що відбулася зіна стану дискретного входу і формуємо новий стан входу
        //При цьому враховуємо що для прявого    входу 1 - це активний вхід, а 0 - це пасивний вхід
        //                        для інверсного входу 0 - це активний вхід, а 1 - це пасивний вхід
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //У будь-якому випадк, чи змінився стан входу, чи ні, а оскілька таймер допуску дотактував до кінця, то скидаємотаймер у висхідне від'ємне занчення
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
  
  /***************************/
  //Визначаємо, який сигнал є зараз активним
  /***************************/
  active_inputs = (state_inputs ^ current_settings_prt.type_of_input);
  /***************************/
  
}
/*****************************************************/

/*****************************************************/
//Функція обробки таймерів
/*****************************************************/
inline void clocking_global_timers(void)
{
  //Опрацьовуємо дискретні входи
  input_scan();
  
  //опрацьовуємо всі решта таймери логіки
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      //Першою умовою того, що таймер треба тактувати є той факт, що величина таймеру не від'ємна

      //Перевіряємо чи треба збільшувати величину таймеру, якщо він ще не досягнув свого максимуму
      if (global_timers[i] <= (0x7fffffff - DELTA_TIME_FOR_TIMERS)) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
  
  if (++timer_prt_signal_output_mode_2 >= PERIOD_SIGNAL_OUTPUT_MODE_2)
  {
    timer_prt_signal_output_mode_2 = 0;
    output_timer_prt_signal_output_mode_2 ^= true;
  }
}
/*****************************************************/
#include "ozt.c "
#include "G3U0.c"
#include "umin.c"
#include "kzzv.c"
#include "mcp.c"


/*****************************************************/
//Опрацювання Ориділювальних функцій - має запускатися після відкрпацювання блоків всіх захистів
/*****************************************************/
inline void df_handler(unsigned int *p_active_functions, unsigned int *p_changed_state_with_start_new_timeout)
{
  /*
  Джерела активації формуємо в source_activation_df
  Формуємо маску вже активних функцій у maska_active_df
  */
  unsigned int source_activation_df = 0;
  unsigned int state_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    unsigned int number_byte_in, number_bit_in, number_byte_out, number_bit_out;
    switch (i)
    {
    case 0:
      {
        number_byte_in = RANG_DF1_IN >> 5;
        number_bit_in = RANG_DF1_IN & 0x1f;

        number_byte_out = RANG_DF1_OUT >> 5;
        number_bit_out = RANG_DF1_OUT & 0x1f;
        
        break;
      }
    case 1:
      {
        number_byte_in = RANG_DF2_IN >> 5;
        number_bit_in = RANG_DF2_IN & 0x1f;

        number_byte_out = RANG_DF2_OUT >> 5;
        number_bit_out = RANG_DF2_OUT & 0x1f;
        
        break;
      }
    case 2:
      {
        number_byte_in = RANG_DF3_IN >> 5;
        number_bit_in = RANG_DF3_IN & 0x1f;

        number_byte_out = RANG_DF3_OUT >> 5;
        number_bit_out = RANG_DF3_OUT & 0x1f;
        
        break;
      }
    case 3:
      {
        number_byte_in = RANG_DF4_IN >> 5;
        number_bit_in = RANG_DF4_IN & 0x1f;

        number_byte_out = RANG_DF4_OUT >> 5;
        number_bit_out = RANG_DF4_OUT & 0x1f;
        
        break;
      }
    case 4:
      {
        number_byte_in = RANG_DF5_IN >> 5;
        number_bit_in = RANG_DF5_IN & 0x1f;

        number_byte_out = RANG_DF5_OUT >> 5;
        number_bit_out = RANG_DF5_OUT & 0x1f;
        
        break;
      }
    case 5:
      {
        number_byte_in = RANG_DF6_IN >> 5;
        number_bit_in = RANG_DF6_IN & 0x1f;

        number_byte_out = RANG_DF6_OUT >> 5;
        number_bit_out = RANG_DF6_OUT & 0x1f;
        
        break;
      }
    case 6:
      {
        number_byte_in = RANG_DF7_IN >> 5;
        number_bit_in = RANG_DF7_IN & 0x1f;

        number_byte_out = RANG_DF7_OUT >> 5;
        number_bit_out = RANG_DF7_OUT & 0x1f;
        
        break;
      }
    case 7:
      {
        number_byte_in = RANG_DF8_IN >> 5;
        number_bit_in = RANG_DF8_IN & 0x1f;

        number_byte_out = RANG_DF8_OUT >> 5;
        number_bit_out = RANG_DF8_OUT & 0x1f;
        
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(43);
        break;
      }
    }

    if (i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/)
    {
      /***
      Джерело активації ОФ-ії
      ***/
      source_activation_df |= ((p_active_functions[number_byte_in] & (1 << number_bit_in) ) >> number_bit_in ) << i;
      //Перевіряємо ще, чи не іде утимування активним джерела ОФ через таймер-утримування (для активації через кнопки або інтерфейс)
      if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= 0)
      {
        //Таймер запущений, або вже зупинився
        //Факт запуску цього таймеру означає, що активація відбувалася через кнопку, або інтерфейс
        //Тому для забеспечення роботи логічної схеми до кінця роботи цього таймеру виставляємо, що джерело активації активне
        source_activation_df |= (1 << i);
      
        //Відмічаємо, джерело активації утримуємться у активному стані у масиві активуючих функцій
        p_active_functions[number_byte_in] |= (1 << number_bit_in);
      
        //У випадку, якщо таймер дійшов до свого макисального значення, то скидаємо роботу цього таймеру
        if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
      }
      /***/

      /***
      Формування маски до цього часу активних ОФ-ій
      ***/
      state_df |= ((p_active_functions[number_byte_out] & ((unsigned int)(1 << number_bit_out))) != 0) << i;
      /***/
    }
    else
    {
      //Таймери, які не задіяні скидаємо з роботи
      global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
      global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
      global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
      
      etap_execution_df[i] = NONE_DF;
    }
  }
  
  //Визначаємо, чи активовуються опреділювані функції через свої ранжовані функції-джерела
  unsigned int source_blk_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело прямих функцій
      if(
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] & p_active_functions[0] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] & p_active_functions[1] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] & p_active_functions[2] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] & p_active_functions[3] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] & p_active_functions[4] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] & p_active_functions[5] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] & p_active_functions[6] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 7] & p_active_functions[7] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 8] & p_active_functions[8] ) != 0) 
        )
      {
        source_activation_df |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
      if(
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 )||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 )
        )
      {
        source_activation_df |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані насправді на джерело блокування
      if(
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] & p_active_functions[0] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] & p_active_functions[1] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] & p_active_functions[2] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] & p_active_functions[3] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] & p_active_functions[4] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] & p_active_functions[5] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] & p_active_functions[6] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 7] & p_active_functions[7] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 8] & p_active_functions[8] ) != 0 )
        )
      {
        source_blk_df |= (1<< i);
      }
    }
    
    //Запускаємо у роботу лоргічну хему роботи опреділюваної функції
    switch (etap_execution_df[i])
    {
    case NONE_DF:
      {
        if ((source_activation_df & (1<<i)) != 0)
        {
           if (current_settings_prt.timeout_pause_df[i] > 0)
           {
             //Випадок, коли є перед активацією ОФ, треба витримати таймер павзи
             //Запускаємо відраховування таймера паузи
             global_timers[INDEX_TIMER_DF_PAUSE_START + i] = 0;
             //Змінюємо етап виконання логічної схеми на очікування завершення часу павзи
             etap_execution_df[i] = START_TIMER_PAUSE_DF;
           }
           else
           {
             //Випадок, коли таймер павзи рівний нулю, тобто треба зразу активовувати ОФ і запускати таймер роботи

             if (
                 (current_settings_prt.timeout_work_df[i] > 0) ||
                 ((current_settings_prt.type_df & (1<<i)) != 0)
                )   
             {
              //Встановлюємо стан даної ОФ в "АКТИВНИЙ"
              state_df |= (1 << i);
              //Запускаємо відраховування таймера роботи
              global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
              //Переходимо на відраховування таймеру роботи - протягом цього часу ОФ гарантовано активується (якщо немає умови блокування)
              etap_execution_df[i] = EXECUTION_DF;
             }
             else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           }
           
           //Фіксація про зміну стану з початком відслідковуванням нової витримки
           *p_changed_state_with_start_new_timeout |= (1 << i);
        }
        break;
      }
    case START_TIMER_PAUSE_DF:
      {
        //Зараз іде відлік часу таймеру павзи
        //Перевіряємо, чи ОФ ще утимується в стані активації через своє джерело
        if ((source_activation_df & (1<< i)) != 0)
        {
          //Перевіряємо, чи завершилася робота таймеру павзи
          if (global_timers[INDEX_TIMER_DF_PAUSE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          {
            if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
            {
              //Завершився час роботи таймеру павзи
              global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
  
              if (
                  (current_settings_prt.timeout_work_df[i] > 0) ||
                  ((current_settings_prt.type_df & (1<<i)) != 0)
                 )   
              {
                //Встановлюємо стан даної ОФ в "АКТИВНИЙ"
                state_df |= (1 << i);
                //Запускаємо відраховування таймера роботи
                global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
                //Переходимо на відраховування таймеру роботи - протягом цього часу ОФ гарантовано активується (якщо немає умови блокування)
                etap_execution_df[i] = EXECUTION_DF;
              }
              else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           
              //Фіксація про зміну стану з початком відслідковуванням нової витримки
              *p_changed_state_with_start_new_timeout |= (1 << i);
            }
          }
        }
        else
        {
          //Активація знята до завершення роботи таймеру павзи, тому скидаємо всю роботу по даній оприділюваеній функції
          global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
          etap_execution_df[i] = NONE_DF;
           
          //Відміна фіксації про зміну стану з початком відслідковуванням нової витримки
          *p_changed_state_with_start_new_timeout &= (unsigned int)(1 << i);
        }
        break;
      }
    case EXECUTION_DF:
      {
        //Подальша робота даної ОФ залежить від типу ОФ
        if ((current_settings_prt.type_df & (1<<i)) != 0)
        {
          //Дана ОФ ЗВОРОТНЯ
          //Згідно логічної схеми утримуємо ОФ таймер роботи має запуститися після деактивації джерела
          if ((source_activation_df & (1<< i)) != 0)
          {
            //Джерело ще є активне, а тому таймер роботи утримуємо у нульовому значенні
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }

        //Перевіряємо, чи завершилася робота таймеру роботи
        /*
        Умовою продовження активації ОФ є випадок коли ОФ зворотня і джерело є активним
        Впринципі на рівні таймеру все б мало працювати правильно, але є один нюанс, коли
        функція є звороньою і джерело активне, то код вище скине таймер роботи в 0, 
        тобто він буде гарантовано в 0, але коли уставка "Таймер роботи" для даної функції буде 0,
        то по аналізу самого таймеру робота функції може зупинитися, що не правильно.
        Тому тут ще я добавляю перевірку, що ОФ не може деактивуватися навіть коли таймер роботи
        перевищує свою уставку у випадку коли і ОФ є зворотньою і джерело є активним
        */
        if (
            (global_timers[INDEX_TIMER_DF_WORK_START + i] >= ((int)current_settings_prt.timeout_work_df[i])) &&
            (
             !( 
               ((current_settings_prt.type_df & (1 << i)) != 0) && 
               ((source_activation_df         & (1 << i)) != 0) 
              )
            )  
           )
        {
          if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
          {
            //Завершився час роботи таймеру роботи
            global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
            //Переводимо ОФ у ПАСИВНИЙ стан
            state_df &= ~(1 << i);
          
            //Перевіряємо, чи нам треба перейти в очікування деактивації джерела ОФ, чи перейти у висхідний стан
            if ((source_activation_df & (1<< i)) == 0)
            {
              //Переходимо у режим висхідний стан
              etap_execution_df[i] = NONE_DF;
            }
            else 
            {
              //Якщо джерело запуску цієї ОФ ще активне, то переходимо на оцікування його завершення
              etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
            }
          }
        }
        break;
      }
    case WAITING_DEACTIVATION_SOURCE_DF:
      {
        //У цьому режимі ми перебуваємо доти, поки джерело активації ОФ не буде зняте
        if ((source_activation_df & (1 << i)) == 0)
        {
          //Переходимо у режим висхідний стан
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    default: break;
    }
  }

  //Установлюємо, або скидаємо ОФ у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені виходи ОФ-ій, тому що інші ОФ-ії
  можуть бути джерелом активації, але джерелом активації може буте попереднє значення ОФ, а не те,
  що зараз встановлюється. А оскілдьки у другому масиві ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом активації/деактивації)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    //Установлюємо, або скидаємо ОФ
    unsigned int index_df;
    switch (i)
    {
    case 0:
      {
       index_df = RANG_DF1_OUT;
        break;
      }
    case 1:
      {
        index_df = RANG_DF2_OUT;
        break;
      }
    case 2:
      {
        index_df = RANG_DF3_OUT;
        break;
      }
    case 3:
      {
        index_df = RANG_DF4_OUT;
        break;
      }
    case 4:
      {
        index_df = RANG_DF5_OUT;
        break;
      }
    case 5:
      {
        index_df = RANG_DF6_OUT;
        break;
      }
    case 6:
      {
        index_df = RANG_DF7_OUT;
        break;
      }
    case 7:
      {
        index_df = RANG_DF8_OUT;
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(44);
        break;
      }
    }
      
    if ((state_df & (1 << i)) != 0 )
    {
      /*
      ОФ функція зараз є активною
      але перед тим, як виставити реальний стан цієї функції на даний момент часу - 
      перевіряєио, чи не йде блокування її 
      */     
      if ((source_blk_df & (1<< i)) == 0 ) _SET_BIT(p_active_functions, index_df);
      else _CLEAR_BIT(p_active_functions, index_df);
    }
    else
    {
      _CLEAR_BIT(p_active_functions, index_df);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання Ориділювальних триґерів - має запускатися після відкрпацювання опреділювальних функцій
/*****************************************************/
inline void dt_handler(unsigned int *p_active_functions)
{
  /*
  Попередній стан визначуваних триґерів формуємо у state_defined_triggers
  Джерела встановлення формуємо в source_set_dt
  Джерела скидання формуємо в source_reset_dt
  */
  unsigned int state_defined_triggers = 0, source_set_dt = 0, source_reset_dt = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    unsigned int number_byte_set, number_bit_set, number_byte_reset, number_bit_reset;
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
        number_byte_set = RANG_DT1_SET >> 5;
        number_bit_set = RANG_DT1_SET & 0x1f;

        number_byte_reset = RANG_DT1_RESET >> 5;
        number_bit_reset = RANG_DT1_RESET & 0x1f;
        
        index_dt = RANG_DT1_OUT;
        
        break;
      }
    case 1:
      {
        number_byte_set = RANG_DT2_SET >> 5;
        number_bit_set = RANG_DT2_SET & 0x1f;

        number_byte_reset = RANG_DT2_RESET >> 5;
        number_bit_reset = RANG_DT2_RESET & 0x1f;
        
        index_dt = RANG_DT2_OUT;
        
        break;
      }
    case 2:
      {
        number_byte_set = RANG_DT3_SET >> 5;
        number_bit_set = RANG_DT3_SET & 0x1f;

        number_byte_reset = RANG_DT3_RESET >> 5;
        number_bit_reset = RANG_DT3_RESET & 0x1f;
        
        index_dt = RANG_DT3_OUT;
        
        break;
      }
    case 3:
      {
        number_byte_set = RANG_DT4_SET >> 5;
        number_bit_set = RANG_DT4_SET & 0x1f;

        number_byte_reset = RANG_DT4_RESET >> 5;
        number_bit_reset = RANG_DT4_RESET & 0x1f;
        
        index_dt = RANG_DT4_OUT;
        
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(55);
        break;
      }
    }

    state_defined_triggers |= ( (p_active_functions[index_dt >> 5] & ( 1 << (index_dt & 0x1f) ) ) >> (index_dt & 0x1f) ) << i;
    /***
    Джерела встановлення і скидання ОТ
    ***/
    source_set_dt   |= ((p_active_functions[number_byte_set  ] & (1 << number_bit_set  ) ) >> number_bit_set   ) << i;
    source_reset_dt |= ((p_active_functions[number_byte_reset] & (1 << number_bit_reset) ) >> number_bit_reset ) << i;
    /***/
  }
  
  //Визначаємо, чи встановлюються/скидаються опреділювані триґери через свої ранжовані функції-джерела
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело прямих функцій
      if(
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 8] & p_active_functions[8]) != 0)
        )
      {
        source_set_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
      if(
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 )
        )
      {
        source_set_dt |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело прямих функцій
      if(
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 8] & p_active_functions[8]) != 0)
        )
      {
        source_reset_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 8] !=0)
       )
    {
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
      if(
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 )
        )
      {
        source_reset_dt |= (1<< i);
      }
    }

    //Запускаємо у роботу лоргічну схему роботи опреділюваного триґера (встановлення має пріоритет)
    if ((source_set_dt   & (1 << i)) != 0) state_defined_triggers |= (1 << i);
    if ((source_reset_dt & (1 << i)) != 0) state_defined_triggers &= (unsigned int)(~(1 << i));
  }

  //Установлюємо, або скидаємо ОТ у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходыв ОТ-ів, тому що інші ОТ-и
  можуть бути джерелом встановлення/скидання, але джерелом встановлення/скидання може буте попереднє значення ОТ, а не те,
  що зараз встановлюється. А оскілдьки у ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    //Установлюємо, або скидаємо ОТ
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
       index_dt = RANG_DT1_OUT;
        break;
      }
    case 1:
      {
       index_dt = RANG_DT2_OUT;
        break;
      }
    case 2:
      {
       index_dt = RANG_DT3_OUT;
        break;
      }
    case 3:
      {
       index_dt = RANG_DT4_OUT;
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(56);
        break;
      }
    }
      
    if ((state_defined_triggers & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_dt);
    else _CLEAR_BIT(p_active_functions, index_dt);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "І"
/*****************************************************/
inline void d_and_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_and = 0;

  //Визначаємо стан всіх визначуваних "І" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND/*current_settings_prt.number_defined_and*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 0] & p_active_functions[0]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 0]) && 
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 1] & p_active_functions[1]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 1]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 2] & p_active_functions[2]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 2]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 3] & p_active_functions[3]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 3]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 4] & p_active_functions[4]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 4]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 5] & p_active_functions[5]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 5]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 6] & p_active_functions[6]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 6]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 7] & p_active_functions[7]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 7]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 8] & p_active_functions[8]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 8])
       )
    {
      state_defined_and |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "І" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"І", тому що інші В-"І"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"І", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    //Установлюємо, або скидаємо В-"І"
    unsigned int index_d_and = RANG_D_AND1 + i;
      
    if ((state_defined_and & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_and);
    else _CLEAR_BIT(p_active_functions, index_d_and);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "АБО"
/*****************************************************/
inline void d_or_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_or = 0;

  //Визначаємо стан всіх визначуваних "АБО" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR/*current_settings_prt.number_defined_or*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 0] & p_active_functions[0]) != 0) || 
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 8] & p_active_functions[8]) != 0)
       )
    {
      state_defined_or |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "АБО" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"АБО", тому що інші В-"АБО"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"АБО", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    //Установлюємо, або скидаємо В-"АБО"
    unsigned int index_d_or = RANG_D_OR1 + i;
      
    if ((state_defined_or & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_or);
    else _CLEAR_BIT(p_active_functions, index_d_or);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "Викл.АБО"
/*****************************************************/
inline void d_xor_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_xor = 0;

  //Визначаємо стан всіх визначуваних "Викл.АБО" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR/*current_settings_prt.number_defined_xor*/; i++)
  {
    unsigned int temp_array[N_BIG];
    temp_array[0] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 0] & p_active_functions[0];
    temp_array[1] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 1] & p_active_functions[1];
    temp_array[2] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 2] & p_active_functions[2];
    temp_array[3] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 3] & p_active_functions[3];
    temp_array[4] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 4] & p_active_functions[4];
    temp_array[5] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 5] & p_active_functions[5];
    temp_array[6] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 6] & p_active_functions[6];
    temp_array[7] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 7] & p_active_functions[7];
    temp_array[8] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 8] & p_active_functions[8];
    
    if (
        (temp_array[0] != 0) || 
        (temp_array[1] != 0) ||
        (temp_array[2] != 0) ||
        (temp_array[3] != 0) ||
        (temp_array[4] != 0) ||
        (temp_array[5] != 0) ||
        (temp_array[6] != 0) ||
        (temp_array[7] != 0) ||
        (temp_array[8] != 0)
       )
    {
      unsigned int signals = 0;
      for (unsigned int j = 0; j < N_BIG; j++)
      {
        for (unsigned int k = 0; k < 32; k++)
        {
          if ((temp_array[j] & (1 << k)) != 0) signals++;
        }
      }
      if (signals == 1) state_defined_xor |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "Викл.АБО" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"Викл.АБО", тому що інші В-"Викл.АБО"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"Викл.АБО", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    //Установлюємо, або скидаємо В-"Викл.АБО"
    unsigned int index_d_xor = RANG_D_XOR1 + i;
      
    if ((state_defined_xor & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_xor);
    else _CLEAR_BIT(p_active_functions, index_d_xor);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "НЕ"
/*****************************************************/
inline void d_not_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_not = 0;

  //Визначаємо стан всіх визначуваних "НЕ" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT/*current_settings_prt.number_defined_not*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 0] & p_active_functions[0]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 1] & p_active_functions[1]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 2] & p_active_functions[2]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 3] & p_active_functions[3]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 4] & p_active_functions[4]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 5] & p_active_functions[5]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 6] & p_active_functions[6]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 7] & p_active_functions[7]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 8] & p_active_functions[8]) == 0)
       )
    {
      state_defined_not |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "НЕ" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"НЕ", тому що інші В-"НЕ"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"НЕ", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    //Установлюємо, або скидаємо В-"НЕ"
    unsigned int index_d_not = RANG_D_NOT1 + i;
      
    if ((state_defined_not & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_not);
    else _CLEAR_BIT(p_active_functions, index_d_not);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання Передавальних функцій
/*****************************************************/
inline void tf_handler(unsigned int *p_previous_active_functions, unsigned int *p_active_functions)
{
  for (size_t i = 0; i < NUMBER_TRANSFER_FUNCTIONS; i++)
  {
    uint32_t value = current_settings_prt.ranguvannja_tf[i];
    uint32_t value_input = value & 0xffff;
    if (value_input > 0)
    {
      value_input--;
      if (value_input < NUMBER_TOTAL_SIGNAL_FOR_RANG)
      {
        if (_CHECK_SET_BIT(p_previous_active_functions, value_input) != 0)
        {
          uint32_t value_output = (value >> 16) & 0xffff;
          if (value_output > 0)
          {
            value_output--;
            if (value_output < NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL)
            {
              _SET_BIT(p_active_functions, small_big_rang[value_output]);
            }
            else
            {
              //Відбулася невизначена помилка, тому треба піти на перезавантаження
              total_error_sw_fixed(102);
            }
          }
        }
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(101);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Вираховування часової витримки  для залежної МТЗ2 (універсальна формула)
/*
-------------------------------------------------
Т(c) = K*Tу/( ((I/Iу)^alpha) - 1 )
-------------------------------------------------
*/
/*****************************************************/
inline int timeout_dependent_general(unsigned int i, unsigned int setpoint_mtz_2, int timeout_mtz_2, int type_mtz2_tmp)
{
  int timeout_result = 0;
  
  if (
      (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
      (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
     )   
  {
    unsigned int Iust = setpoint_mtz_2;
    if (i > Iust)
    {
      register float timeout = (((float)timeout_mtz_2)/1000.0f);
      register float timeout_dependent = 0;
      
      if (
          (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
          (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_C)
         )   
      {
        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
          case TYPE_MTZ_DEPENDENT_A:
          {
            K = 0.14f;
            alpha = 0.02f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_B:
          {
            K = 13.5f;
            alpha = 1.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_C:
          {
            K = 80.0f;
            alpha = 2.0f;
            break;
          }
        default:
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(42);
          }
        }
    
        register float I_div_Iusy = ((float)i)/((float)Iust);
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 1)
          )
        {
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(57);
        }
  
        timeout_dependent = K*timeout/(rising_to_power - 1);
      }
      else if (
               (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_RT_80) &&
               (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
              )   
      {
        register float I_div_Iusy = ((float)i)/((float)Iust);
        I_div_Iusy = I_div_Iusy - 1.0f;

        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
        case TYPE_MTZ_DEPENDENT_RT_80:
          {
            K = 20.0f;
            alpha = 1.8f;
          
            I_div_Iusy /= 6.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_RTV_I:
          {
            K = 30.0f;
            alpha = 3.0f;
            break;
          } 
        default:
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(87);
          }
        }
      
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 0)
           )
        {
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(86);
        }
      
        timeout_dependent = 1.0f/(K*rising_to_power)+ timeout;
      }

      int timeout_dependent_int = (int)timeout_dependent;
      if (timeout_dependent_int > (TIMEOUT_MTZ2_MAX/1000)) timeout_dependent = (TIMEOUT_MTZ2_MAX/1000);
      else if (timeout_dependent_int < 0) timeout_dependent = 0;
    
      timeout_result = (int)(timeout_dependent*1000.0f);
    }
    else timeout_result = TIMEOUT_MTZ2_MAX;
  }
  
  return timeout_result;
}
/*****************************************************/
#ifdef MCP_ORIGIN
/*****************************************************/
// МТЗ
/*****************************************************/
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
  
  previous_state_mtz_po_incn = ((measurement[IM_IA_H] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB_H] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC_H] <= po_i_ncn_setpoint));
  
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
    
    tmp_value |= ((measurement[IM_IA_H] >= po_mtz_x) ||
          (measurement[IM_IB_H] >= po_mtz_x) ||
          (measurement[IM_IC_H] >= po_mtz_x)) << 4; //ПО МТЗх
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
    
    direction_ABC_tmp |= (measurement[IM_IA_H] >= po_mtzn_x_vpered_setpoint) << 8; //Сравниваем с уставкой тока по фазе А (вперед)
    direction_ABC_tmp |= (measurement[IM_IB_H] >= po_mtzn_x_vpered_setpoint) << 9; //Сравниваем с уставкой тока по фазе B (вперед)
    direction_ABC_tmp |= (measurement[IM_IC_H] >= po_mtzn_x_vpered_setpoint) << 10; //Сравниваем с уставкой тока по фазе C (вперед)
    
    //Уставка ПО МТЗН1 прям. с учетом гистерезиса
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA_H] >= po_mtzn_x_nazad_setpoint) << 11; //Сравниваем с уставкой тока по фазе А (назад)
    direction_ABC_tmp |= (measurement[IM_IB_H] >= po_mtzn_x_nazad_setpoint) << 12; //Сравниваем с уставкой тока по фазе B (назад)
    direction_ABC_tmp |= (measurement[IM_IC_H] >= po_mtzn_x_nazad_setpoint) << 13; //Сравниваем с уставкой тока по фазе C (назад)
    
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
    
    tmp_value |= ((measurement[IM_IA_H] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB_H] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC_H] >= po_mtzpn_x_setpoint)) << 17; //ПО МТЗПНх
    /******ПО МТЗПНх***********************/
    
    if (mtz_level == 1) { //только для 2-ой ступени
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_USK_MTZ]) == 0) << 9; //Блокировка ускорения МТЗ 2
      //М
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENA) != 0) << 10; //МТЗ2 Ускоренная
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV_H) != 0) << 18; //Положение ВВ
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
      
      unsigned int i_max = measurement[IM_IA_H];
      if (i_max < measurement[IM_IB_H]) i_max = measurement[IM_IB_H];
      if (i_max < measurement[IM_IC_H]) i_max = measurement[IM_IC_H];
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
/*****************************************************/
#endif
/*****************************************************/
//ТЗНП
/*****************************************************/
inline void tznp_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
#define CTR_TZNP                CTR_TZNP1      
#define CTR_TZNP_VPERED         CTR_TZNP1_VPERED      
#define CTR_TZNP_NAZAD          CTR_TZNP1_NAZAD      

#define RANG_BLOCK_TZNP         RANG_BLOCK_TZNP1
#define RANG_SECTOR_TZNP_VPERED RANG_SECTOR_TZNP1_VPERED
#define RANG_SECTOR_TZNP_NAZAD  RANG_SECTOR_TZNP1_NAZAD
#define RANG_PO_3I0_TZNP_VPERED RANG_PO_3I0_TZNP1_VPERED
#define RANG_PO_3I0_TZNP_NAZAD  RANG_PO_3I0_TZNP1_NAZAD
#define RANG_PO_3U0_TZNP_VPERED RANG_PO_3U0_TZNP1_VPERED
#define RANG_PO_3U0_TZNP_NAZAD  RANG_PO_3U0_TZNP1_NAZAD
#define RANG_PO_TZNP_VPERED     RANG_PO_TZNP1_VPERED
#define RANG_PO_TZNP_NAZAD      RANG_PO_TZNP1_NAZAD
#define RANG_TZNP               RANG_TZNP1
  
  unsigned int maska_ctrl_bits = CTR_TZNP | CTR_TZNP_VPERED | CTR_TZNP_NAZAD;
  
  for (unsigned int tznp = 0; tznp < 4; tznp++)
  {
    unsigned int setpoint_tznp_3I0_vpered;
    unsigned int setpoint_tznp_3U0_vpered;
    unsigned int setpoint_tznp_3I0_nazad;
    unsigned int setpoint_tznp_3U0_nazad;

    int timeout_tznp_vpered;
    int timeout_tznp_nazad;
    
    unsigned int index_timer_vpered;
    unsigned int index_timer_nazad;
    
    unsigned int control_tznp;
    
    unsigned int shift_to_base_rang_index;
    
    switch(tznp)
    {
    case 0:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_1_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_1_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_1_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_1_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_1_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_1_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP1_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP1_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP1) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP1 - RANG_BLOCK_TZNP;
        
        break;
      }
    case 1:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_2_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_2_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_2_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_2_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_2_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_2_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP2_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP2_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP2) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP2 - RANG_BLOCK_TZNP;
        
        break;
      }
    case 2:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_3_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_3_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_3_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_3_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_3_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_3_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP3_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP3_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP3) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP3 - RANG_BLOCK_TZNP;
        
        break;
      }
    case 3:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_4_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_4_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_4_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_4_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_4_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_4_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP4_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP4_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP4) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP4 - RANG_BLOCK_TZNP;
        
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(82);
      }
    }

    unsigned int logic_TZNP_0 = 0;
    unsigned int setpoint;
    
    /***
    Сектор вперед
    ***/
    if(sector_directional_tznp[tznp] == 1)
    {
      logic_TZNP_0 |= 1 << 0;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_VPERED));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_VPERED));
    /***/
    
    /***
    Сектор назад
    ***/
    if(sector_directional_tznp[tznp] == 2)
    {
      logic_TZNP_0 |= 1 << 1;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_NAZAD));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_NAZAD));
    /***/
    
    /***
    ПО 3I0 ВПЕРЕД
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED)) == 0)
    {
      //Працюємо по уставці спрацювання
      setpoint = setpoint_tznp_3I0_vpered;
    }
    else
    {
      //Працюємо по уставці відпускання
      setpoint = setpoint_tznp_3I0_vpered*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
	if(ch_type_voltage){//0-VH 1 - VL 
		if (measurement[IM_3I0_r_L] >= setpoint)
		{
		  logic_TZNP_0 |=  1 << 3;
		  _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
		}
		else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
	}
	else{
		if (measurement[IM_3I0_r_H] >= setpoint)
		{
		  logic_TZNP_0 |=  1 << 3;
		  _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
		}
		else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
	}
    /***/
    
    /***
    ПО 3U0 ВПЕРЕД
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED)) == 0)
    {
      //Працюємо по уставці спрацювання
      setpoint = setpoint_tznp_3U0_vpered;
    }
    else
    {
      //Працюємо по уставці відпускання
      setpoint = setpoint_tznp_3U0_vpered*KOEF_POVERNENNJA_3U0/100;
    }
    if (measurement[IM_3U0_r] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 4;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED));
    /***/
    
    /***
    ПО 3I0 НАЗАД
    ***/
	

    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD)) == 0)
    {
      //Працюємо по уставці спрацювання
      setpoint = setpoint_tznp_3I0_nazad;
    }
    else
    {
      //Працюємо по уставці відпускання
      setpoint = setpoint_tznp_3I0_nazad*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
	if(ch_type_voltage){//0-VH 1 - VL 
		if (measurement[IM_3I0_r_L] >= setpoint)
		{
		logic_TZNP_0 |=  1 << 5;
		_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
		}
		else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
	}else{
		if (measurement[IM_3I0_r_H] >= setpoint)
		{
		logic_TZNP_0 |=  1 << 5;
		_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
		}
		else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
	}
    /***/

    /***
    ПО 3U0 НАЗАД
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD)) == 0)
    {
      //Працюємо по уставці спрацювання
      setpoint = setpoint_tznp_3U0_nazad;
    }
    else
    {
      //Працюємо по уставці відпускання
      setpoint = setpoint_tznp_3U0_nazad*KOEF_POVERNENNJA_3U0/100;
    }
    if (measurement[IM_3U0_r] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 6;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD));
    /***/
    
    //Стан ступеню захисту
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP) != 0) << 7;
    
    //Стан блокування захисту
    logic_TZNP_0 |= (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_BLOCK_TZNP)) == 0) << 8;
    
    //Стан напрямку ВПЕРЕД
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP_VPERED) != 0) << 10;
    
    //Стан напрямку НАЗАД
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP_NAZAD) != 0) << 11;

    _AND2(logic_TZNP_0, 7, logic_TZNP_0, 8, logic_TZNP_0, 9);

    //ПО ТЗНП вперед
    _AND5(logic_TZNP_0, 9, logic_TZNP_0, 10, logic_TZNP_0, 3, logic_TZNP_0, 4, logic_TZNP_0, 0, logic_TZNP_0, 12);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 12)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_VPERED));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_VPERED));
      
    //ПО ТЗНП назад
    _AND5(logic_TZNP_0, 9, logic_TZNP_0, 11, logic_TZNP_0, 5, logic_TZNP_0, 6, logic_TZNP_0, 1, logic_TZNP_0, 13);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 13)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_NAZAD));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_NAZAD));

    _TIMER_T_0(index_timer_vpered, timeout_tznp_vpered, logic_TZNP_0, 12, logic_TZNP_0, 14);
    _TIMER_T_0(index_timer_nazad,  timeout_tznp_nazad,  logic_TZNP_0, 13, logic_TZNP_0, 15);
    
    //ТЗНП
    _OR2(logic_TZNP_0, 14, logic_TZNP_0, 15, logic_TZNP_0, 16);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 16)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_TZNP));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_TZNP));
  }

#undef CTR_TZNP
#undef CTR_TZNP_VPERED
#undef CTR_TZNP_NAZAD

#undef RANG_BLOCK_TZNP
#undef RANG_SECTOR_TZNP_VPERED
#undef RANG_SECTOR_TZNP_NAZAD
#undef RANG_PO_3I0_TZNP_VPERED
#undef RANG_PO_3I0_TZNP_NAZAD
#undef RANG_PO_3U0_TZNP_VPERED
#undef RANG_PO_3U0_TZNP_NAZAD
#undef RANG_PO_TZNP_VPERED
#undef RANG_PO_TZNP_NAZAD
#undef RANG_TZNP
}
/*****************************************************/

/*****************************************************/
// ЗОП(КОФ)
/*****************************************************/
inline void zop_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
   //Фуксуємо у локальній змінній текучі струми зворотньої послідовності і прямоїпослідовності
  /*******************************/
  unsigned int i2_current,i1_current;
  
  /*******************************/
  //1 ступінь ЗОП(КОФ)
  /*******************************/
  if ((current_settings_prt.control_zop & MASKA_FOR_BIT(INDEX_ML_CTRZOP_1_STATE)) != 0)
  {
    //1 ступінь ЗОП(КОФ) включена
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    
    unsigned int previous_state_po_zop1;
    if((current_settings_prt.control_zop & MASKA_FOR_BIT(INDEX_ML_CTRZOP_1_SEL_I)) != 0){//0-VH 1 - VL 
	i2_current = measurement[IM_I2_L], i1_current = measurement[IM_I1_L];
	}else{
	i2_current = measurement[IM_I2_H], i1_current = measurement[IM_I1_H];
	}
	unsigned int setpoint_i1, setpoint_i2,i1_bilshe_porogu_tmp,i2_bilshe_porogu_tmp;
	setpoint_i1 = 0;i1_bilshe_porogu_tmp = i2_bilshe_porogu_tmp = 0;
  
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
     i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
     i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //Якщо ПО ЗОП(КОФ) ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО ЗОП(КОФ) вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_zop1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_ZOP1) ) == 0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_zop1[number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_zop1[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //Виставляємо, або скидаємо сигнал "ПО КОФ"
    /*
    I2
    -- >= K
    I1
    оскільки величина устаки у нас є перемножена на 1000, ,бо 0,010 відповідає 10, а 1,000 відповідає 1000,
    то K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    струми зворотньої і прямої послідовності не треба ні нащо перемножувати, бо вони є у однакових величинах (міліампери), а нас цікавить їх відношення
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ZOP1) == 0)
       )
    {
      //Існує умова активного пускового органу зворотньої послідовності
      if(previous_state_po_zop1 == 0)
      {
        //Встановлюємо сигнал "ПО КОФ"
        _SET_BIT(p_active_functions, RANG_PO_ZOP1);
      
        //Запускаємо таймер ЗОП(КОФ), якщо він ще не запущений
        global_timers[INDEX_TIMER_ZOP1] = 0;
      }
    }
    else 
    {
      //Не існує умови активного пускового органу зворотньої послідовності
      if(previous_state_po_zop1 != 0)
      {
        //Скидаємо сигнал "ПО КОФ"
        _CLEAR_BIT(p_active_functions, RANG_PO_ZOP1);
        //Це є умовою також скидання сигналу "Сраб. КОФ"
        _CLEAR_BIT(p_active_functions, RANG_ZOP1);
        //Якщо таймер ще не скинутий? то скидаємо його
        if ( global_timers[INDEX_TIMER_ZOP1] >=0) global_timers[INDEX_TIMER_ZOP1] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP1] >= current_settings_prt.timeout_zop1[number_group_stp])
    {
      //Якщо витримана Витримка ЗОП(КОФ) то встановлюємо сигнал "Сраб. КОФ"
      _SET_BIT(p_active_functions, RANG_ZOP1);

      //Скидаємо таймер ЗОП(КОФ)
      global_timers[INDEX_TIMER_ZOP1] = -1;
    }
  }
  else
  {
    //Треба скинути всі таймери і сигнали, які за 1 ступінь ЗОП(КОФ) відповідають
    _CLEAR_BIT(p_active_functions, RANG_PO_ZOP1);
    _CLEAR_BIT(p_active_functions, RANG_ZOP1);
    global_timers[INDEX_TIMER_ZOP1] = -1;

  }  
/*******************************/
  //2 ступінь ЗОП(КОФ)
  /*******************************/
  if ((current_settings_prt.control_zop & MASKA_FOR_BIT(INDEX_ML_CTRZOP_2_STATE)) != 0)
  {
    //1 ступінь ЗОП(КОФ) включена
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    //unsigned int setpoint_i1, setpoint_i2;
    unsigned int previous_state_po_zop2;
	
	if((current_settings_prt.control_zop & MASKA_FOR_BIT(INDEX_ML_CTRZOP_2_SEL_I)) != 0){//0-VH 1 - VL 
	i2_current = measurement[IM_I2_L], i1_current = measurement[IM_I1_L];
	}else{
	i2_current = measurement[IM_I2_H], i1_current = measurement[IM_I1_H];
	}
	unsigned int setpoint_i1, setpoint_i2,i1_bilshe_porogu_tmp,i2_bilshe_porogu_tmp;
	setpoint_i1 = 0;i1_bilshe_porogu_tmp = i2_bilshe_porogu_tmp = 0;
  
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
     i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
     i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //Якщо ПО ЗОП(КОФ) ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО ЗОП(КОФ) вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_zop2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_ZOP2) ) == 0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_zop2[number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_zop2[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //Виставляємо, або скидаємо сигнал "ПО КОФ"
    /*
    I2
    -- >= K
    I1
    оскільки величина устаки у нас є перемножена на 1000, ,бо 0,010 відповідає 10, а 1,000 відповідає 1000,
    то K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    струми зворотньої і прямої послідовності не треба ні нащо перемножувати, бо вони є у однакових величинах (міліампери), а нас цікавить їх відношення
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ZOP2) == 0)
       )
    {
      //Існує умова активного пускового органу зворотньої послідовності
      if(previous_state_po_zop2 == 0)
      {
        //Встановлюємо сигнал "ПО КОФ"
        _SET_BIT(p_active_functions, RANG_PO_ZOP2);
      
        //Запускаємо таймер ЗОП(КОФ), якщо він ще не запущений
        global_timers[INDEX_TIMER_ZOP2] = 0;
      }
    }
    else 
    {
      //Не існує умови активного пускового органу зворотньої послідовності
      if(previous_state_po_zop2 != 0)
      {
        //Скидаємо сигнал "ПО КОФ"
        _CLEAR_BIT(p_active_functions, RANG_PO_ZOP2);
        //Це є умовою також скидання сигналу "Сраб. КОФ"
        _CLEAR_BIT(p_active_functions, RANG_ZOP2);
        //Якщо таймер ще не скинутий? то скидаємо його
        if ( global_timers[INDEX_TIMER_ZOP2] >=0) global_timers[INDEX_TIMER_ZOP2] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP2] >= current_settings_prt.timeout_zop2[number_group_stp])
    {
      //Якщо витримана Витримка ЗОП(КОФ) то встановлюємо сигнал "Сраб. КОФ"
      _SET_BIT(p_active_functions, RANG_ZOP2);

      //Скидаємо таймер ЗОП(КОФ)
      global_timers[INDEX_TIMER_ZOP2] = -1;
    }
  }
  else
  {
    //Треба скинути всі таймери і сигнали, які за 2 ступінь ЗОП(КОФ) відповідають
    _CLEAR_BIT(p_active_functions, RANG_PO_ZOP2);
    _CLEAR_BIT(p_active_functions, RANG_ZOP2);
    global_timers[INDEX_TIMER_ZOP2] = -1;

  } 
}
/*****************************************************/

/*****************************************************/
// ЗНМИН1
/*****************************************************/
void umin1_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN1) > 0;
  _Bool previous_state_po_ublk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1) > 0;
  _Bool previous_state_po_iblk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin1 ?
          current_settings_prt.setpoint_Umin1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin1[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin1 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin1 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin1 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin1 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin1 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin1 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin1 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin1 ?
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_H] <= setpoint3) &&
                                         (measurement[IM_IB_H] <= setpoint3) &&
                                         (measurement[IM_IC_H] <= setpoint3);
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN1) != 0)                                     << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN1) != 0)                                     << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  } 
  else 
  {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin1
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  
  //ПО Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN1);
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN1);
}
/*****************************************************/

/*****************************************************/
// ЗНМИН2
/*****************************************************/
void umin2_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN2) > 0;
  _Bool previous_state_po_ublk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2) > 0;
  _Bool previous_state_po_iblk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin2 ?
          current_settings_prt.setpoint_Umin2[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin2[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin2 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin2 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin2 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin2 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin2 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin2 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin2 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin2 ?
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_H] <= setpoint3) &&
                                         (measurement[IM_IB_H] <= setpoint3) &&
                                         (measurement[IM_IC_H] <= setpoint3);
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN2) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0))
  {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    
  } 
  else 
  {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin2
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  
  //ПО Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN2);
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN2);
}
/*****************************************************/

/*****************************************************/
// ЗНМАКС1
/*****************************************************/
void umax1_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax1 ?
          current_settings_prt.setpoint_Umax1[number_group_stp] * current_settings_prt.setpoint_kp_Umax[number_group_stp] / 100 :
          current_settings_prt.setpoint_Umax1[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax1 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax1 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax1 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax1 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax1 = measurement[IM_UC] >= setpoint1;
  
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX1_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX1) != 0)                                                            << 3;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX1) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //ПО Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX1);
  
  _TIMER_T_0(INDEX_TIMER_UMAX1, current_settings_prt.timeout_Umax1[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //Сраб. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX1);
}
/*****************************************************/

/*****************************************************/
// ЗНМАКС2
/*****************************************************/
void umax2_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax2 ?
          current_settings_prt.setpoint_Umax2[number_group_stp] * current_settings_prt.setpoint_kp_Umax[number_group_stp] / 100 :
          current_settings_prt.setpoint_Umax2[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax2 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax2 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax2 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax2 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax2 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax2 = measurement[IM_UC] >= setpoint1;
  
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX2_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX2) != 0)                                                            << 3;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX2) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //ПО Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX2);
  
  _TIMER_T_0(INDEX_TIMER_UMAX2, current_settings_prt.timeout_Umax2[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //Сраб. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX2);
}
/*****************************************************/

/*****************************************************/
// Готовность к ТУ
/*****************************************************/
void ready_tu(unsigned int *p_active_functions)
{
  unsigned int tmp_value = ((_CHECK_SET_BIT(p_active_functions, RANG_PRYVID_VV_H) == 0) && (_CHECK_SET_BIT(p_active_functions, RANG_PRYVID_VV_L) == 0)) << 0;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV) != 0)                    << 1;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0)      << 2;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_AVAR_DEFECT) == 0)                            << 3;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_MISCEVE_DYSTANCIJNE) == 0)                    << 6;
  
  _Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);
  
  if (!previous_states_ready_tu && _GET_OUTPUT_STATE(tmp_value, 1)) {
    previous_states_ready_tu = 0;
  }
  
  _OR2(tmp_value, 2, ctrl_ready_tu, 0, tmp_value, 7);
  _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 7), previous_states_ready_tu, 0, tmp_value, 1, trigger_ready_tu, 0);
  
  _AND4(tmp_value, 0, tmp_value, 3, !trigger_ready_tu, 0, tmp_value, 6, tmp_value, 5);
  
  //Готовность к ТУ
  if (_GET_OUTPUT_STATE(tmp_value, 5))
    _SET_BIT(p_active_functions, RANG_READY_TU);
  else
    _CLEAR_BIT(p_active_functions, RANG_READY_TU);
}
/*****************************************************/
/*****************************************************/
// УРОВ
/*****************************************************/
inline void urov_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{

  /*******************************/
  
  /*******************************/
  uint32_t state_UROV1 = (( current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STATE)) != 0);
  uint32_t start_from_UP = false;
  if (
      (state_UROV1 != 0) &&
      ((current_settings_prt.control_urov[0] & ((MASKA_FOR_BIT(NUMBER_UP) - 1) << INDEX_ML_CTRUROV_STARTED_FROM_UP1)) != 0)
     )   
  {
    //Налаштовано запуск ПРЗЗ від УЗ
    for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
    {
      if ( 
          ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UP1 + n_UP)) != 0) && 
          (_CHECK_SET_BIT(p_active_functions, (RANG_UP1 + 3*n_UP)      ) != 0)
         )
      {
        start_from_UP = true;
      }
    }
  }
  
  if(
     (state_UROV1 != 0) &&
     (
      (start_from_UP == true) ||
      (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_UROV1_VID_DV) != 0) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_OZT1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_OZT1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_OZT2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_OZT2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ3)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_P_3U0)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_P_3U0 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP2 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP3)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP3 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP4)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP4 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN2 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX2 ) != 0))
     )     
    )
  {
    //Є умова запуску УРОВ
    
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    unsigned int previous_state_po_urov1;
    
    //Якщо ПО УРОВ ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО УРОВ вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_urov1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UROV1) ) ==0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_urov[0][number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_urov[0][number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
  /*******************************/
  //Визначаємо максимальний фазовий струм для УРОВ
  /*******************************/
  unsigned int max_faze_current = measurement[IM_IA_H];
  if(((current_settings_prt.control_urov[0] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_SEL_I)  ) != 0)){
  max_faze_current = measurement[IM_IA_L];
  if (max_faze_current < measurement[IM_IB_L]) max_faze_current = measurement[IM_IB_L];
  if (max_faze_current < measurement[IM_IC_L]) max_faze_current = measurement[IM_IC_L];
  }
  else{
   max_faze_current = measurement[IM_IA_H];
  if (max_faze_current < measurement[IM_IB_H]) max_faze_current = measurement[IM_IB_H];
  if (max_faze_current < measurement[IM_IC_H]) max_faze_current = measurement[IM_IC_H];
  }
    //Виставляємо, або скидаємо сигнал "ПО УРОВ"
    if (max_faze_current >= setpoint)
    {
      //Максимальний фазний стум перевищує свою уставку
      if(previous_state_po_urov1 == 0)
      {
        //Встановлюємо сигнал "ПО УРОВ"
        _SET_BIT(p_active_functions, RANG_PO_UROV1);
      
        //Запускаємо таймери УРОВ1 і УРОВ2, якщо вони ще не запущені
        global_timers[INDEX_TIMER_UROV1_1] = 0;
        global_timers[INDEX_TIMER_UROV1_2] = 0;
      }
    }
    else 
    {
      //Максимальний фазний стум нижче уставки
      if(previous_state_po_urov1 != 0)
      {
        //Скидаємо сигнал "ПО УРОВ"
        _CLEAR_BIT(p_active_functions, RANG_PO_UROV1);
        //Це є умовою також скидання сигналів "Сраб. УРОВ1" і "Сраб. УРОВ2"
        _CLEAR_BIT(p_active_functions, RANG_UROV1_1);
        _CLEAR_BIT(p_active_functions, RANG_UROV1_2);
        //Якщо таймери ще не скинуті, то скидаємо їх
        if ( global_timers[INDEX_TIMER_UROV1_1] >=0) global_timers[INDEX_TIMER_UROV1_1] = -1;
        if ( global_timers[INDEX_TIMER_UROV1_2] >=0) global_timers[INDEX_TIMER_UROV1_2] = -1;
      }
    }
    
    //Перевіряємо чи таймер УРОВ1 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV1_1] >= current_settings_prt.timeout_urov_1[0][number_group_stp])
    {
      //Якщо витримана Витримка УРОВ1 то встановлюємо сигнал "Сраб. УРОВ1"
      _SET_BIT(p_active_functions, RANG_UROV1_1);

      //Скидаємо таймер УРОВ1
      global_timers[INDEX_TIMER_UROV1_1] = -1;
    }

    //Перевіряємо чи таймер УРОВ2 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV1_2] >= current_settings_prt.timeout_urov_2[0][number_group_stp])
    {
      //Якщо витримана Витримка УРОВ2 то встановлюємо сигнал "Сраб. УРОВ2"
      _SET_BIT(p_active_functions, RANG_UROV1_2);

      //Скидаємо таймер УРОВ2
      global_timers[INDEX_TIMER_UROV1_2] = -1;
    }
  }
  else
  {
    //Треба скинути всі таймери і сигнали, які за УРОВ відповідають
    _CLEAR_BIT(p_active_functions, RANG_PO_UROV1);
    _CLEAR_BIT(p_active_functions, RANG_UROV1_1);
    _CLEAR_BIT(p_active_functions, RANG_UROV1_2);
    global_timers[INDEX_TIMER_UROV1_1] = -1;
    global_timers[INDEX_TIMER_UROV1_2] = -1;
  }
  //////////////////////////////==========================================================////////////////////////////////

  /*******************************/
  
  /*******************************/
  uint32_t state_UROV2 = (( current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STATE)) != 0);
  //uint32_t start_from_UP = false;
  if (
      (state_UROV2 != 0) &&
      ((current_settings_prt.control_urov[1] & ((MASKA_FOR_BIT(NUMBER_UP) - 1) << INDEX_ML_CTRUROV_STARTED_FROM_UP1)) != 0)
     )   
  {
    //Налаштовано запуск ПРЗЗ від УЗ
    for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
    {
      if ( 
          ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UP1 + n_UP)) != 0) && 
          (_CHECK_SET_BIT(p_active_functions, (RANG_UP1 + 3*n_UP)      ) != 0)
         )
      {
        start_from_UP = true;
      }
    }
  }
  
  if(
     (state_UROV2 != 0) &&
     (
      (start_from_UP == true) ||
      (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_UROV1_VID_DV) != 0) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_OZT1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_OZT1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_OZT2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_OZT2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ3)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_P_3U0)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_P_3U0 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP2 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP3)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP3 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP4)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP4 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP1  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP2  ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN2 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX1 ) != 0)) ||
      ( ((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX2 ) != 0))
     )     
    )
  {
    //Є умова запуску УРОВ
    
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    unsigned int previous_state_po_urov2;
    
    //Якщо ПО УРОВ ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО УРОВ вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_urov2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UROV2) ) ==0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_urov[1][number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_urov[1][number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
	unsigned int max_faze_current = measurement[IM_IA_L];
  /*******************************/
  //Визначаємо максимальний фазовий струм для УРОВ
  /*******************************/
  if(((current_settings_prt.control_urov[1] & MASKA_FOR_BIT(INDEX_ML_CTRUROV_SEL_I)  ) != 0)){
   max_faze_current = measurement[IM_IA_L];
  if (max_faze_current < measurement[IM_IB_L]) max_faze_current = measurement[IM_IB_L];
  if (max_faze_current < measurement[IM_IC_L]) max_faze_current = measurement[IM_IC_L];
  }
  else{
   max_faze_current = measurement[IM_IA_H];
  if (max_faze_current < measurement[IM_IB_H]) max_faze_current = measurement[IM_IB_H];
  if (max_faze_current < measurement[IM_IC_H]) max_faze_current = measurement[IM_IC_H];
  }
    //Виставляємо, або скидаємо сигнал "ПО УРОВ"
    if (max_faze_current >= setpoint)
    {
      //Максимальний фазний стум перевищує свою уставку
      if(previous_state_po_urov2 == 0)
      {
        //Встановлюємо сигнал "ПО УРОВ"
        _SET_BIT(p_active_functions, RANG_PO_UROV2);
      
        //Запускаємо таймери УРОВ1 і УРОВ2, якщо вони ще не запущені
        global_timers[INDEX_TIMER_UROV2_1] = 0;
        global_timers[INDEX_TIMER_UROV2_2] = 0;
      }
    }
    else 
    {
      //Максимальний фазний стум нижче уставки
      if(previous_state_po_urov2 != 0)
      {
        //Скидаємо сигнал "ПО УРОВ"
        _CLEAR_BIT(p_active_functions, RANG_PO_UROV2);
        //Це є умовою також скидання сигналів "Сраб. УРОВ1" і "Сраб. УРОВ2"
        _CLEAR_BIT(p_active_functions, RANG_UROV2_1);
        _CLEAR_BIT(p_active_functions, RANG_UROV2_2);
        //Якщо таймери ще не скинуті, то скидаємо їх
        if ( global_timers[INDEX_TIMER_UROV2_1] >=0) global_timers[INDEX_TIMER_UROV2_1] = -1;
        if ( global_timers[INDEX_TIMER_UROV2_2] >=0) global_timers[INDEX_TIMER_UROV2_2] = -1;
      }
    }
    
    //Перевіряємо чи таймер УРОВ2 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV2_1] >= current_settings_prt.timeout_urov_1[1][number_group_stp])
    {
      //Якщо витримана Витримка УРОВ1 то встановлюємо сигнал "Сраб. УРОВ1"
      _SET_BIT(p_active_functions, RANG_UROV2_1);

      //Скидаємо таймер УРОВ2
      global_timers[INDEX_TIMER_UROV2_1] = -1;
    }

    //Перевіряємо чи таймер УРОВ2 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV2_2] >= current_settings_prt.timeout_urov_2[1][number_group_stp])
    {
      //Якщо витримана Витримка УРОВ2 то встановлюємо сигнал "Сраб. УРОВ2"
      _SET_BIT(p_active_functions, RANG_UROV2_2);

      //Скидаємо таймер УРОВ2
      global_timers[INDEX_TIMER_UROV2_2] = -1;
    }
  }
  else
  {
    //Треба скинути всі таймери і сигнали, які за УРОВ відповідають
    _CLEAR_BIT(p_active_functions, RANG_PO_UROV2);
    _CLEAR_BIT(p_active_functions, RANG_UROV2_1);
    _CLEAR_BIT(p_active_functions, RANG_UROV2_2);
    global_timers[INDEX_TIMER_UROV2_1] = -1;
    global_timers[INDEX_TIMER_UROV2_2] = -1;
  }  
}  


  /*******************************/
/*****************************************************/

/*****************************************************/
// Універсальний Захист
/*****************************************************/
inline void up_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
  {
    uint32_t logic_UP_0 = 0;
    
    logic_UP_0 |= (
                   ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_STATE_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0)
                   &&
                   (_CHECK_SET_BIT(p_active_functions, (RANG_BLOCK_UP1 + 3*n_UP)) == 0)
                  ) << 0;

    int32_t pickup = current_settings_prt.setpoint_UP[n_UP][0][number_group_stp];
    if (_CHECK_SET_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP)) != 0) pickup = (pickup * current_settings_prt.setpoint_UP_KP[n_UP][0][number_group_stp])/100;

    unsigned int more_less = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_MORE_LESS_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
    
    int32_t analog_value;
    uint32_t PQ = false;
    switch (current_settings_prt.ctrl_UP_input[n_UP])
    {
    case UP_CTRL_Ia_Ib_Ic_H:
      {
        analog_value = measurement[IM_IA_H];

        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
         if ((uint32_t)analog_value < measurement[IM_IB_H]) analog_value = measurement[IM_IB_H];
         if ((uint32_t)analog_value < measurement[IM_IC_H]) analog_value = measurement[IM_IC_H];
        }
        else
        {
         if ((uint32_t)analog_value > measurement[IM_IB_H]) analog_value = measurement[IM_IB_H];
         if ((uint32_t)analog_value > measurement[IM_IC_H]) analog_value = measurement[IM_IC_H];
        }
        
        break;
      }
    case UP_CTRL_Ia_H:
      {
        analog_value = measurement[IM_IA_H];
        
        break;
      }
    case UP_CTRL_Ib_H:
      {
        analog_value = measurement[IM_IB_H];
        
        break;
      }
    case UP_CTRL_Ic_H:
      {
        analog_value = measurement[IM_IC_H];
        
        break;
      }
    case UP_CTRL_I1_H:
      {
        analog_value = measurement[IM_I1_H];
        
        break;
      }
    case UP_CTRL_I2_H:
      {
        analog_value = measurement[IM_I2_H];
        
        break;
      }
    case UP_CTRL_3I0_r_H:
      {
        analog_value = measurement[IM_3I0_r_H];
        
        break;
      }
    case UP_CTRL_Ia_Ib_Ic_L:
      {
        analog_value = measurement[IM_IA_L];

        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
         if ((uint32_t)analog_value < measurement[IM_IB_L]) analog_value = measurement[IM_IB_L];
         if ((uint32_t)analog_value < measurement[IM_IC_L]) analog_value = measurement[IM_IC_L];
        }
        else
        {
         if ((uint32_t)analog_value > measurement[IM_IB_L]) analog_value = measurement[IM_IB_L];
         if ((uint32_t)analog_value > measurement[IM_IC_L]) analog_value = measurement[IM_IC_L];
        }
        
        break;
      }
    case UP_CTRL_Ia_L:
      {
        analog_value = measurement[IM_IA_L];
        
        break;
      }
    case UP_CTRL_Ib_L:
      {
        analog_value = measurement[IM_IB_L];
        
        break;
      }
    case UP_CTRL_Ic_L:
      {
        analog_value = measurement[IM_IC_L];
        
        break;
      }
    case UP_CTRL_I1_L:
      {
        analog_value = measurement[IM_I1_L];
        
        break;
      }
    case UP_CTRL_I2_L:
      {
        analog_value = measurement[IM_I2_L];
        
        break;
      }
    case UP_CTRL_3I0_r_L:
      {
        analog_value = measurement[IM_3I0_r_L];
        
        break;
      }
    case UP_CTRL_Ua_Ub_Uc:
      {
        analog_value = measurement[IM_UA];
        
        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        uint32_t analog_value_tmp = measurement[IM_UB];
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UC];
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
        }
        else
        {
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UC];
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
        }
        
        break;
      }
    case UP_CTRL_Ua:
      {
        analog_value = measurement[IM_UA];
        
        break;
      }
    case UP_CTRL_Ub:
      {
        analog_value = measurement[IM_UB];
        
        break;
      }
    case UP_CTRL_Uc:
      {
        analog_value = measurement[IM_UC];
        
        break;
      }
    case UP_CTRL_Uab_Ubc_Uca:
      {
        analog_value = measurement[IM_UAB];
        
        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        uint32_t analog_value_tmp = measurement[IM_UBC];
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UCA];
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
        }
        else
        {
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UCA];
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
        }
        
        break;
      }
    case UP_CTRL_Uab:
      {
        analog_value = measurement[IM_UAB];
        
        break;
      }
    case UP_CTRL_Ubc:
      {
        analog_value = measurement[IM_UBC];
        
        break;
      }
    case UP_CTRL_Uca:
      {
        analog_value = measurement[IM_UCA];
        
        break;
      }
    case UP_CTRL_U1:
      {
        analog_value = measurement[IM_U1];
        
        break;
      }
    case UP_CTRL_U2:
      {
        analog_value = measurement[IM_U2];
        
        break;
      }
    case UP_CTRL_3U0:
      {
        analog_value = measurement[IM_3U0_r];
        
        break;
      }
    case UP_CTRL_P:
      {
        PQ = true;
        analog_value = P[mutex_power != 0];
        
        break;
      }
    case UP_CTRL_Q:
      {
        PQ = true;
        analog_value = Q[mutex_power != 0];
        
        break;
      }
    case UP_CTRL_S:
      {
        analog_value = S[mutex_power != 0];
        
        break;
      }
    default:
      {
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(100);
      }
    }
    
    if (more_less)
    {
      if (PQ)
      {
        if (
            (
             (analog_value >= 0) &&
             (pickup >= 0)  
            )
            ||
            (
             (analog_value < 0) &&
             (pickup < 0)  
            ) 
           ) 
        {
          logic_UP_0 |= (abs(analog_value) <= abs(pickup)) << 1;
        }
      }
      else
      {
        logic_UP_0 |= (analog_value <= pickup) << 1;
      }
    }
    else
    {
      if (PQ)
      {
        if (
            (
             (analog_value >= 0) &&
             (pickup >= 0)  
            )
            ||
            (
             (analog_value < 0) &&
             (pickup < 0)  
            ) 
           ) 
        {
          logic_UP_0 |= (abs(analog_value) >= abs(pickup)) << 1;
        }
      }
      else
      {
        logic_UP_0 |= (analog_value >= pickup) << 1;
      }
    }

    _AND2(logic_UP_0, 0, logic_UP_0, 1, logic_UP_0, 2);
    if (_GET_OUTPUT_STATE(logic_UP_0, 2)) _SET_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP));
    else _CLEAR_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP));
    
    _TIMER_T_0(INDEX_TIMER_UP1 + n_UP, current_settings_prt.timeout_UP[n_UP][0][number_group_stp], logic_UP_0, 2, logic_UP_0, 3);
    if (_GET_OUTPUT_STATE(logic_UP_0, 3)) _SET_BIT(p_active_functions, (RANG_UP1 + 3*n_UP));
    else _CLEAR_BIT(p_active_functions, (RANG_UP1 + 3*n_UP));
  }
}
/*****************************************************/

/*****************************************************/
//Функція управління блоками включення і відключення
/*****************************************************/
inline void on_off_handler(unsigned int *p_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  /*********************/
  //Спочатку опрацьовуємо таймери
  /*********************/
  //Таймер  відключення
  if (global_timers[INDEX_TIMER_VIDKL_VV_H] >= 0)
  {
    //Таймер БО зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_VIDKL_VV_H] >= current_settings_prt.timeout_swch_off[0])
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
    if (global_timers[INDEX_TIMER_BLK_VKL_VV_H] >= current_settings_prt.timeout_swch_udl_blk_on[0])
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
      if (global_timers[INDEX_TIMER_VKL_VV_H] >= current_settings_prt.timeout_swch_on[0])
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
  if (
      ((p_active_functions[0] & current_settings_prt.ranguvannja_off_cb[0][0]) != 0) ||
      ((p_active_functions[1] & current_settings_prt.ranguvannja_off_cb[0][1]) != 0) ||
      ((p_active_functions[2] & current_settings_prt.ranguvannja_off_cb[0][2]) != 0) ||
      ((p_active_functions[3] & current_settings_prt.ranguvannja_off_cb[0][3]) != 0) ||
      ((p_active_functions[4] & current_settings_prt.ranguvannja_off_cb[0][4]) != 0) ||
      ((p_active_functions[5] & current_settings_prt.ranguvannja_off_cb[0][5]) != 0) ||
      ((p_active_functions[6] & current_settings_prt.ranguvannja_off_cb[0][6]) != 0) ||
      ((p_active_functions[7] & current_settings_prt.ranguvannja_off_cb[0][7]) != 0) ||
      ((p_active_functions[8] & current_settings_prt.ranguvannja_off_cb[0][8]) != 0)
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
    for (unsigned int i = 0; i < N_BIG; i++ )  maska[i] = (unsigned int)(~0);
    _CLEAR_BIT(maska, RANG_OTKL_VV_H);
    _CLEAR_BIT(maska, RANG_WORK_BO_H);
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
         (_CHECK_SET_BIT(previous_active_functions, RANG_OZT1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT1);
      }
      
      //ОЗТ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OZT2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_OZT2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_OZT2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_OZT2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OZT2);
      }
      
      //МТЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ1);
      }
      
      //МТЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ2);
      }
      
      //МТЗ3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ3);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ3);
      }
      
      //МТЗ4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ4);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ4);
      }
          
      //3U0
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_P_3U0) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_P_3U0) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_P_3U0);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_P_3U0][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_P_3U0);
      }
          
      //ТЗНП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP1);
      }

      //ТЗНП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP2);
      }

      //ТЗНП3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP3);
      }

      //ТЗНП4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP4);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP4][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP4);
      }

      //ПРВВ1_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV1_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV1_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1_2);
      }

      //ПРВВ2_1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV2_1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_1);
      }
      
      //ПРВВ1_2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2_2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV2_2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2_2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2_2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2_2);
      }

      //ЗЗП1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZOP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP1);
      }

      //ЗЗП2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZOP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP2);
      }
      
      //Umin1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN1);
      }
      
      //Umin2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN2);
      }
      
      //Umax1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX1);
      }
      
      //Umax2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX2);
      }
      
      //ГЗ1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_GP1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP1);
      }
      
      //ГЗ2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_GP2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP2);
      }
      
      //ГЗ-РПН
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_GP_RPN) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_GP_RPN) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_GP_RPN);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_GP_RPN][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_GP_RPN);
      }
      
      //ТЗ
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TP) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TP) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
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
           (_CHECK_SET_BIT(previous_active_functions, (RANG_UP1 + 3*n_UP)) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
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
          ((previous_active_functions[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
          ((previous_active_functions[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
          ((previous_active_functions[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
          ((previous_active_functions[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
          ((previous_active_functions[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
          ((previous_active_functions[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5]) ||
          ((previous_active_functions[6] & temp_array_of_outputs[6])!= temp_array_of_outputs[6]) ||
          ((previous_active_functions[7] & temp_array_of_outputs[7])!= temp_array_of_outputs[7]) ||
          ((previous_active_functions[8] & temp_array_of_outputs[8])!= temp_array_of_outputs[8])
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

    if (
        ((p_active_functions[0] & current_settings_prt.ranguvannja_on_cb[0][0]) != 0) ||
        ((p_active_functions[1] & current_settings_prt.ranguvannja_on_cb[0][1]) != 0) ||
        ((p_active_functions[2] & current_settings_prt.ranguvannja_on_cb[0][2]) != 0) ||
        ((p_active_functions[3] & current_settings_prt.ranguvannja_on_cb[0][3]) != 0) ||
        ((p_active_functions[4] & current_settings_prt.ranguvannja_on_cb[0][4]) != 0) ||
        ((p_active_functions[5] & current_settings_prt.ranguvannja_on_cb[0][5]) != 0) ||
        ((p_active_functions[6] & current_settings_prt.ranguvannja_on_cb[0][6]) != 0) ||
        ((p_active_functions[7] & current_settings_prt.ranguvannja_on_cb[0][7]) != 0) ||
        ((p_active_functions[8] & current_settings_prt.ranguvannja_on_cb[0][8]) != 0)
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
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = p_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//Контроль приводу вимикача
/*****************************************************/
void control_VV(unsigned int *p_active_functions)
{
  unsigned int logic_control_VV_0 = 0;

  //"Контроль Вкл."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_VKL_H ) != 0) << 0;
  //"Контроль Откл."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_OTKL_H) != 0) << 1;
  
  _XOR_INVERTOR(logic_control_VV_0, 0, logic_control_VV_0, 1, logic_control_VV_0, 2);

  _TIMER_T_0(INDEX_TIMER_PRYVOD_VV_H, current_settings_prt.timeout_pryvoda_VV[0], logic_control_VV_0, 2, logic_control_VV_0, 3);

  //М:"Контроль ВВ"
  logic_control_VV_0 |= ((current_settings_prt.control_switch[0] & CTR_PRYVOD_VV) != 0) << 4;
  
  _AND2(logic_control_VV_0, 3, logic_control_VV_0, 4, logic_control_VV_0, 5);
  
  if (_GET_OUTPUT_STATE(logic_control_VV_0, 5))
    _SET_BIT(p_active_functions, RANG_PRYVID_VV_H);
  else
    _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV_H);
}
/*****************************************************/

/*****************************************************/
//Перевірка на необхідність завершення роботи аналогового/дискретного реєстраторів
/*****************************************************/
inline unsigned int stop_regisrator(unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator)
{
  unsigned int stop = 0;

  {
    if (
        ((carrent_active_functions[0] & ranguvannja_registrator[0]) == 0) &&
        ((carrent_active_functions[1] & ranguvannja_registrator[1]) == 0) &&
        ((carrent_active_functions[2] & ranguvannja_registrator[2]) == 0) &&
        ((carrent_active_functions[3] & ranguvannja_registrator[3]) == 0) &&
        ((carrent_active_functions[4] & ranguvannja_registrator[4]) == 0) &&
        ((carrent_active_functions[5] & ranguvannja_registrator[5]) == 0) &&
        ((carrent_active_functions[6] & ranguvannja_registrator[6]) == 0) &&
        ((carrent_active_functions[7] & ranguvannja_registrator[7]) == 0) &&
        ((carrent_active_functions[8] & ranguvannja_registrator[8]) == 0)
      )
    {
      //Зафіксовано, що ні одне джерело активації реєстратора зараз не активне
      
      if (
          ((carrent_active_functions[0] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0) == 0) &&
          ((carrent_active_functions[1] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1) == 0) &&
          ((carrent_active_functions[2] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2) == 0) &&
          ((carrent_active_functions[3] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3) == 0) &&
          ((carrent_active_functions[4] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4) == 0) &&
          ((carrent_active_functions[5] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5) == 0) &&
          ((carrent_active_functions[6] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_6) == 0) &&
          ((carrent_active_functions[7] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_7) == 0) &&
          ((carrent_active_functions[8] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_8) == 0)
        )
      {
        //Зафіксовано, що всі функції, які можуть утримувати реєстратор активним зараз скинуті
          
        //Перевіряємо, чи всі таймери, які працють у логіці схеми виключені
        unsigned int global_timers_work = 0, i = INDEX_TIMER_DF_PAUSE_START;
        while ((i < NEXT_TIMER) && (global_timers_work == 0))
        {
          if (global_timers[i] >= 0) 
          {
            if (
                (
                 (i != INDEX_TIMER_PRYVOD_VV_H) ||
                 (  
                  ((current_settings_prt.control_switch[0] & CTR_PRYVOD_VV) != 0) &&
                  (global_timers[i] < current_settings_prt.timeout_pryvoda_VV[0]) 
                 )
                )
                &&
                (
                 (i != INDEX_TIMER_PRYVOD_VV_L) ||
                 (  
                  ((current_settings_prt.control_switch[1] & CTR_PRYVOD_VV) != 0) &&
                  (global_timers[i] < current_settings_prt.timeout_pryvoda_VV[1]) 
                 )
                )
               )
            global_timers_work = 1;
          }
          i++;
        }
          
        if (global_timers_work == 0)
        {
          //Зафіксовано, що всі таймери, які працюють у лозіці неактивні
        
          //Помічаємо, що реєстратор може бути зупиненим
          stop = 0xff;
        }
      }
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи дискретного реєстратора
/*****************************************************/
void fix_undefined_error_dr(unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  state_dr_record = STATE_DR_NO_RECORD;
  //Скидаєсо сигнал роботи дискретного реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//Подача команди почати запис у DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
  _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //Виставляємо першу частину запису
  part_writing_dr_into_dataflash = 0;
  //Виставляємо команду запису у мікросхему DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//Функція обробки черги зформованих записів дискретного реєстратора
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*Стоїть умова сформовані дані передати на запис у DataFlsh без повторного початку  нового запису, бо умова завершення запиу    досягнкта, а не стояла умова примусового завершення даного сформованого запису*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*Стоїть умова сформовані дані передати на запис у DataFlsh   з повторним  початком нового запису, бо умова завершення запиу не досягнкта, а    стояла умова примусового завершення даного сформованого запису*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //На даний момент запису у Datafalsh не проводиться
      unsigned char *buffer_source, *buffer_target;
        
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++)
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 0;
      }
      else if (number_records_dr_waiting_for_saving_operation == 1)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        
        if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
        {
          buffer_target = buffer_for_save_dr_record_level_1;
          buffer_source = buffer_for_save_dr_record;
          for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
          {
            *(buffer_target + i) = *(buffer_source + i);
            *(buffer_source + i) = 0xff;
          }
          number_records_dr_waiting_for_saving_operation = 1;
        }
        else number_records_dr_waiting_for_saving_operation = 0;
      }
      else
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target + i) = *(buffer_source + i);
        buffer_target = buffer_for_save_dr_record_level_1;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 1;
      }
        
      //Подаємо команду почати запис у DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //На даний момент запису у Datafalsh проводиться
      //Треба наш теперішній запис поставити у чергу
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, більше ніяких записів у черзі немає
        //Переміщаємо текучий запис у буфер buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
          buffer_for_save_dr_record[i] = 0xff;
        }
    
        //Помічаємо, що один запис очікує передау його на безпосередній запис у dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, ще один сформований запис стоїть у буфері buffer_for_save_dr_record_level_1
          /*
          Тому даний запис залишаємо у цьому самому буфері buffer_for_save_dr_record, але збільшуємо кількість записів. які стоять у черзі
          і якщо буде спроба почати новий запис, то будемо фіксувати помилку втрати даних
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //Помічаємо, що ми готові приймати наступний запис
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //Помічаємо, що треба примусово запустити новий запис
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void digital_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  
  static unsigned int number_items_dr;
  static unsigned int number_changes_into_dr_record;
  static unsigned int time_from_start_record_dr;
  
  switch (state_dr_record)
  {
  case STATE_DR_NO_RECORD:
  case STATE_DR_FORCE_START_NEW_RECORD:
    {
      //Попередньо скидаємо невизначену помилку  роботи дискретного реєстратора
      _SET_BIT(clear_diagnostyka, ERROR_DR_UNDEFINED_BIT);
      if(number_records_dr_waiting_for_saving_operation < (WIGHT_OF_DR_WAITING - 1))
      {
        //Ця ситуація означає, що як мінімум на один новий запис у нас є вільне місц, тому скидаємо сигналізацію про втрату даних
        _SET_BIT(clear_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
      }
      
      //На початок аналізу покищо ще дискретний реєстратор не запущений
      
      //Аналізуємо, чи стоїть умова запуску дискретного реєстратора
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_digital_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_digital_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_digital_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_digital_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_digital_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_digital_registrator[5]) != 0) ||
           ((carrent_active_functions[6] & current_settings_prt.ranguvannja_digital_registrator[6]) != 0) ||
           ((carrent_active_functions[7] & current_settings_prt.ranguvannja_digital_registrator[7]) != 0) ||
           ((carrent_active_functions[8] & current_settings_prt.ranguvannja_digital_registrator[8]) != 0) ||
           (state_dr_record == STATE_DR_FORCE_START_NEW_RECORD)
          )   
         )
      {
        //Є умова запуску дискретного реєстратора
        
        //Перевіряємо, чи при початку нового запису ми не втратимо попередню інформацію
        if(number_records_dr_waiting_for_saving_operation < WIGHT_OF_DR_WAITING)
        {
          //Можна починати новий запис
          
          //Переводимо режим роботи із дискретним реєстратором у стан "Іде процес запису реєстратора"
          state_dr_record = STATE_DR_EXECUTING_RECORD;
          //Виставляємо активну функцію
          _SET_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
        
          //Записуємо мітку початку запису
          buffer_for_save_dr_record[FIRST_INDEX_START_START_RECORD_DR] = LABEL_START_RECORD_DR;
         
          //Записуємо час початку запису
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_for_save_dr_record[FIRST_INDEX_DATA_TIME_DR + i] = *(label_to_time_array + i);
          
           //І'мя комірки
          for(unsigned int i=0; i< MAX_CHAR_IN_NAME_OF_CELL; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_NAME_OF_CELL_DR + i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //Помічаємо скільки часу пройшло з початку запуску запису
          time_from_start_record_dr = 0;
          
          //Записуємо попередній cтан сигналів перед аварією
          //Мітка часу попереднього стану сигналів до моменту початку запису
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  0] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  1] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  2] = 0xff;
          //Попередній стан
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  3] =  previous_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  4] = (previous_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  5] = (previous_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  6] = (previous_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  7] =  previous_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  8] = (previous_active_functions[1] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  9] = (previous_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 10] = (previous_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 11] =  previous_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 12] = (previous_active_functions[2] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 13] = (previous_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 14] = (previous_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 15] =  previous_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 16] = (previous_active_functions[3] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 17] = (previous_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 18] = (previous_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 19] =  previous_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 20] = (previous_active_functions[4] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 21] = (previous_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 22] = (previous_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 23] =  previous_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 24] = (previous_active_functions[5] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 25] = (previous_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 26] = (previous_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 27] =  previous_active_functions[6]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 28] = (previous_active_functions[6] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 29] = (previous_active_functions[6] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 30] = (previous_active_functions[6] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 31] =  previous_active_functions[7]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 32] = (previous_active_functions[7] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 33] = (previous_active_functions[7] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 34] = (previous_active_functions[7] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 35] =  previous_active_functions[8]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 36] = (previous_active_functions[8] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 37] = (previous_active_functions[8] >> 16) & 0xff;
          //Нулем позначаємо у цій позиції кількість змін
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 38] = 0;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 39] = 0;

          //Помічаємо кількість нових зрізів
          number_items_dr = 1;
      
          //Вираховуємо кількість змін сигналів
          number_changes_into_dr_record = 0;
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //Записуємо текучий cтан сигналів
          //Мітка часу
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //Текучий стан сигналів
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 27] =  carrent_active_functions[6]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 28] = (carrent_active_functions[6] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 29] = (carrent_active_functions[6] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 30] = (carrent_active_functions[6] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 31] =  carrent_active_functions[7]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 32] = (carrent_active_functions[7] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 33] = (carrent_active_functions[7] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 34] = (carrent_active_functions[7] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 35] =  carrent_active_functions[8]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 36] = (carrent_active_functions[8] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 37] = (carrent_active_functions[8] >> 16) & 0xff;
          
          //Кількість змін сигналів у порівнянні із попереднім станом
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 38] = number_changes_into_current_item & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 39] = (number_changes_into_current_item >> 8) & 0xff;
      
//          //Решту масиву очищаємо, щоб у запис не пішла інформація із попередніх записів
//          for(unsigned int i = FIRST_INDEX_FIRST_BLOCK_DR; i < FIRST_INDEX_FIRST_DATA_DR; i++)
//            buffer_for_save_dr_record[i] = 0xff;
//          for(unsigned int i = (FIRST_INDEX_FIRST_DATA_DR + (number_items_dr + 1)*40); i < SIZE_BUFFER_FOR_DR_RECORD; i++)
//            buffer_for_save_dr_record[i] = 0xff;
        }
        else
        {
          //Виставляємо помилку, що є умова на роботу дискретного реєстратора тоді, як всі вільні буфери зайняті
          _SET_BIT(set_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      else state_dr_record = STATE_DR_NO_RECORD;
      
      break;
    }
  case STATE_DR_EXECUTING_RECORD:
    {
      //Збільшуємо час з початку запуску запису
      time_from_start_record_dr++;

      //Включно до цього часу іде процес запису

      //Перевіряємо, чи ще існує умова продовження запису
      //Якщо такої умови немає - то скидаємо сигнал запущеного дискретного реєстратора, що це зафіксувати у змінених сигналах
      if (stop_regisrator(carrent_active_functions, current_settings_prt.ranguvannja_digital_registrator) != 0)
      {
        //Скидаємо сигнал роботи дискретного реєстратора
        _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);

        //Переводимо режим роботи із дискретним реєстратором у стан "Виконується безпосередній запис у послідовну DataFlash"
        state_dr_record = STATE_DR_MAKE_RECORD;
      }
      
      //Перевіряємо чи відбуласа зміна сигналів у порівнянні із попереднім станом. Якщо така зміна є, то формуєм новий зріз сигналів у записі
      if (
          ((carrent_active_functions[0] != previous_active_functions[0])) ||
          ((carrent_active_functions[1] != previous_active_functions[1])) ||
          ((carrent_active_functions[2] != previous_active_functions[2])) ||
          ((carrent_active_functions[3] != previous_active_functions[3])) ||
          ((carrent_active_functions[4] != previous_active_functions[4])) ||
          ((carrent_active_functions[5] != previous_active_functions[5])) ||
          ((carrent_active_functions[6] != previous_active_functions[6])) ||
          ((carrent_active_functions[7] != previous_active_functions[7])) ||
          ((carrent_active_functions[8] != previous_active_functions[8])) 
         )
      {
        //Теперішній стан сигналів не співпадає з попереднім станом сигналів

        //Збільшуємо на один кількість нових зрізів
        number_items_dr++;
      
        //Вираховуємо кількість змін сигналів
        unsigned int number_changes_into_current_item;
        _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
        number_changes_into_dr_record += number_changes_into_current_item;
      
        //Записуємо текучий cтан сигналів
        //Мітка часу
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  0] =  time_from_start_record_dr        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  2] = (time_from_start_record_dr >> 16) & 0xff;
        //Текучий стан сигналів
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  3] =  carrent_active_functions[0]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  7] =  carrent_active_functions[1]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 11] =  carrent_active_functions[2]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 15] =  carrent_active_functions[3]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 19] =  carrent_active_functions[4]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 23] =  carrent_active_functions[5]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 27] =  carrent_active_functions[6]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 28] = (carrent_active_functions[6] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 29] = (carrent_active_functions[6] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 30] = (carrent_active_functions[6] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 31] =  carrent_active_functions[7]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 32] = (carrent_active_functions[7] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 33] = (carrent_active_functions[7] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 34] = (carrent_active_functions[7] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 35] =  carrent_active_functions[8]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 36] = (carrent_active_functions[8] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 37] = (carrent_active_functions[8] >> 16) & 0xff;
        //Кількість змін сигналів у порівнянні із попереднім станом
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 38] = number_changes_into_current_item & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*40 + 39] = (number_changes_into_current_item >> 8) & 0xff;
      }
        
      //Перевіряємо, чи стоїть умова завершення запису
      if (
          (state_dr_record == STATE_DR_MAKE_RECORD)                  ||
          (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)  ||
          ((number_items_dr + 1)     >= MAX_EVENTS_IN_ONE_RECORD  )  
         )
      {
        //Немає умови продовження запису, або є умова завершення запису - завершуємо формування запису і подаємо команду на запис
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] =  number_changes_into_dr_record       & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

        //Переводимо режим роботи із дискретним реєстратором у стан "Виконується безпосередній запис у DataFlash"
        if (state_dr_record != STATE_DR_MAKE_RECORD)
        {
          if (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)
          {
            //Якщо відбулося перевищення по часу запису, то подаємо команду завершити запис без продовження потім цього запису у наступному записі
            state_dr_record = STATE_DR_MAKE_RECORD;
          }
          else
          {
            //Якщо відбулося перевищення по досягнкнні максимальної кількості зрізів (або іншої причини, яка покищо не оговорена, але може з'явитися у майбутньому), то подаємо команду завершити запис але на наступному проході почати новий запис
            state_dr_record = STATE_DR_CUT_RECORD;
          }
        }
        
        //Скидаємо сигнал роботи дискретного реєстратора
        _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
      }

      break;
    }
  default:
    {
      //По ідеї сюди програма ніколи не мала б зайти
      fix_undefined_error_dr(carrent_active_functions);
      break;
    }
  }
  
  //Перевіряємо, чи стоїть умова сформований запис передати на запис у DataFlash
  routine_for_queue_dr();

  /*********************/
  //Формуємо попереденій стан сигналів для функції ввімкнення/вимкнення
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = carrent_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи аналогового реєстратора
/*****************************************************/
void fix_undefined_error_ar(unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  continue_previous_record_ar = 0; /*помічаємо, що ми не чикаємо деактивації всіх джерел активації аналогового реєстратора*/
  state_ar_record = STATE_AR_NO_RECORD;
  //Скидаєсо сигнал роботи аналогового реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

  //Виставляємо команду запису структуру для аналогового реєстратора у EEPROM
  _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
  //Відновлюємо інформаційну структуру для аналогового реєстратора
  /*
  Адресу залишаємо попередню, тобто така яка і була
  */
  info_rejestrator_ar.saving_execution = 0;
  /*
  оскільки скоріше всього якась частна запису відбулася, а це значить, що, якщо там були корисні дані
  якогось запису, то вони зіпсовані. Тому треба помітити, що якщо у аналоговому реєстраторі до цього часу була
  максимально можлива кількість записів, то зараз оснанній з них є зіпсований, тобто кількість записів стала 
  у такому випадку на одиницю менша
  */
  unsigned int max_number_records_ar_tmp = max_number_records_ar;
  if (info_rejestrator_ar.number_records >= max_number_records_ar_tmp) 
    info_rejestrator_ar.number_records = max_number_records_ar_tmp - 1; /*Умова мал аб бути ==, але щоб перестахуватися на невизначену помилку я поставив >=*/
}
/*****************************************************/

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void analog_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int unsaved_bytes_of_header_ar;

  //Попередньо скидаємо невизначену помилку  роботи аналогового реєстратора
  _SET_BIT(clear_diagnostyka, ERROR_AR_UNDEFINED_BIT);

  if (continue_previous_record_ar != 0)
  {
    /*
    Ця ситуація означає, що були активними джерела аналогового реєстратора, які запустили
    в роботу аналоговий реєстратор, і тепер для розблокування можливості запускати новий запис ми 
    чекаємо ситуації, що всі джерела активації деактивуються (у будь-який час чи до
    завершення записування текучого запису аналогового реєстратора, чи вже після завершення
    записування. Це буде умовою розблокування можливості запису нового запису)
    */
    if(
       ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) == 0) &&
       ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) == 0) &&
       ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) == 0) &&
       ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) == 0) &&
       ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) == 0) &&
       ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) == 0) &&
       ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) == 0) &&
       ((carrent_active_functions[7] & current_settings_prt.ranguvannja_analog_registrator[7]) == 0) &&
       ((carrent_active_functions[8] & current_settings_prt.ranguvannja_analog_registrator[8]) == 0) 
      ) 
    {
      //Умова розблокування можливості початку нового запису виконана
      continue_previous_record_ar = 0;
    }
  }

  switch (state_ar_record)
  {
  case STATE_AR_NO_RECORD:
    {
      if(semaphore_read_state_ar_record == 0)
      {
        /*
        Можливо була ситуація, що при попередній роботі модуля аналогового реєстратора відбувалося блокування роботи аналоговго реєстратора
        Знятий семафор semaphore_read_state_ar_record при умові, що стан роботи аналогового реєстратора STATE_AR_NO_RECORD означає,
        що зараз немає перешкод на його запуск, тому знімаємо теоретично можливу подію про тимчасову неготовність роботи аналогового реєстратора
        */
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
           ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0) ||
           ((carrent_active_functions[7] & current_settings_prt.ranguvannja_analog_registrator[7]) != 0) ||
           ((carrent_active_functions[8] & current_settings_prt.ranguvannja_analog_registrator[8]) != 0)
          )
          &&  
          (continue_previous_record_ar == 0) /*при попередній роботі ан.реєстротора (якщо така була) вже всі джерела активації були зняті і зароз вони знову виникли*/ 
         )
      {
        //Перевіряємо, чи при початку нового запису у нас не іде спроба переналаштвати аналоговий реєстратор
        if(semaphore_read_state_ar_record == 0)
        {
          //Є умова запуску аналогового реєстратора
          continue_previous_record_ar = 0xff; /*помічаємо будь-яким числом, що активувалися дзжерела ан.реєстратора, які запустили роботц аналогового реєстратора*/
    
          //Можна починати новий запис
          
          //Записуємо мітку початку запису
          header_ar.label_start_record = LABEL_START_RECORD_AR;
          //Записуємо час початку запису
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
          //Коефіцієнт трансформації TС(ВН)
          header_ar.TCurrent_H = current_settings_prt.TCurrent_H;
          //Коефіцієнт трансформації TС(НН)
          header_ar.TCurrent_L = current_settings_prt.TCurrent_L;
          //Коефіцієнт трансформації TН
          header_ar.TVoltage = current_settings_prt.TVoltage;
          //І'мя ячейки
          for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
            header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //Помічаємо, що ще ми ще не "відбирали" миттєві значення з масив для аналогового реєстратора
          copied_number_samples = 0;
          //Визначаємо загальну кількість миттєвих значень, які мають бути записані у мікросхему dataFlash2
          total_number_samples = ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES_WITH_CALC + number_word_digital_part_ar);

          //Визначаємо,що покищо заготовок аналогового реєстратора не скопійоманий у масив звідки будуть дані забирватися вже для запису у DataFlash
          unsaved_bytes_of_header_ar = sizeof(__HEADER_AR);

          //Визначаємо з якої адреси записувати
          temporary_address_ar = info_rejestrator_ar.next_address;

          //Визначаєом, що поки що немає підготовлених даних для запису
          count_to_save = 0;
          //Виставляємо будь-яким ненульовим числом дозвіл на підготовку нових даних для запису
          permit_copy_new_data = 0xff;

          //Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра і підготовлених даних у масив для запису в DataFlash
          if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
          {
            //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
            fix_undefined_error_ar(carrent_active_functions);
          }
          else
          {
            //Переводимо режим роботи із аналоговим реєстратором у стан "Запус нового запису"
            state_ar_record = STATE_AR_START;
            //Виставляємо активну функцію
            _SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

            //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            info_rejestrator_ar.saving_execution = 1;
          }
        }
        else
        {
          //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що іде намаганні змінити часові витримки)
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      break;
    }
  case STATE_AR_START:
    {
      //Ніяких дій не виконуємо, поки не встанвиться режим STATE_AR_SAVE_SRAM_AND_SAVE_FLASH,  або STATE_AR_ONLY_SAVE_FLASH
      break;
    }
  case STATE_AR_SAVE_SRAM_AND_SAVE_FLASH:
  case STATE_AR_ONLY_SAVE_FLASH:
    {
      if (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)
      {
        /*
        Весь післяаварійний масив підготовлений до запису
        */
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) != 0)
        {
          //Знімаємо сигнал роботи аналогового реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);
        }
        
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) == 0)
        {
          /*
          Враховуємо також той момент, коли сигнал запуску роботи аналогового реєсстратора був знятий
          */
          if  (continue_previous_record_ar == 0)
          {
            /*
            Перевіряємо, чи немає умови запуску нового заппису до моменту, 
            поки ще старий запис не закінчився повністю
            */
            if (
                ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
                ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
                ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
                ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
                ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
                ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
                ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0) ||
                ((carrent_active_functions[7] & current_settings_prt.ranguvannja_analog_registrator[7]) != 0) ||
                ((carrent_active_functions[8] & current_settings_prt.ranguvannja_analog_registrator[8]) != 0)
               ) 
            {
              //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що завершується попередній запис)
              _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
              _SET_BIT(carrent_active_functions, RANG_DEFECT);
            }
          }
        }
      }
      
      if (permit_copy_new_data != 0)
      {
        /*
        Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра 
        і підготовлених даних у масив для запису в DataFlash тільки тоді, коли є дозвіл
        на цю операцію
        */
        if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
        {
          //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
          fix_undefined_error_ar(carrent_active_functions);
        }
      }
      else
      {
        if (
            (copied_number_samples == total_number_samples) &&
            (count_to_save == 0                           ) && 
            (
             (control_tasks_dataflash &
              (
               TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
               TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
              )
             ) == 0
            )   
           )
        {
          //Умова зупинки роботи анаалогового реєстратора
          if(
             (index_array_ar_tail == index_array_ar_heat) &&
             (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)  
            )  
          {
            //Коректна умова зупинки роботи аналогового реєстратора
            state_ar_record = STATE_AR_NO_RECORD;

            //Виставляємо команду запису структури аналогового реєстратора у EEPROM
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            //Визначаємо нову адресу наступного запису, нову кількість записів і знімаємо сигналізацію, що зараз іде запис
            if ((temporary_address_ar + size_one_ar_record) > (NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))
              temporary_address_ar = 0; 
            info_rejestrator_ar.next_address = temporary_address_ar;
            info_rejestrator_ar.saving_execution = 0;
            unsigned int max_number_records_ar_tmp = max_number_records_ar;
            if (info_rejestrator_ar.number_records < max_number_records_ar_tmp) info_rejestrator_ar.number_records += 1;
            else info_rejestrator_ar.number_records = max_number_records_ar_tmp;
          }
          else
          {
            /*В процесі роботи аналогового реєстратора відбувся збій, який привів
            до непередбачуваного завершення роботи аналогового реєстратора
            
            Це скоріше всього виникло внаслідок того, що ми досягнули передчасно
            максимальної кількості зкопійованих миттєвих значень
            */
            fix_undefined_error_ar(carrent_active_functions);
          }
        }
        else
        {
          //Треба подати команду на запис підготовлених даних
          if (
              (count_to_save != 0 ) 
              && 
              (
               (control_tasks_dataflash &
                (
                 TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
                 TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
                )
               ) == 0
              )   
             )
          {
            /*
            Подаємо команду на запис нових даних тільки тоді коли не іде зараз запис
            попередньо підготованих даних і коли є нові дані для запису
            */
            
            if (((temporary_address_ar & 0x1ff) + count_to_save) <= SIZE_PAGE_DATAFLASH_2)
            {
              //Немає помилки при фомауванні кількості байт для запису (в одну сторінку дані поміщаються з текучої адреси)
              
              if (count_to_save == SIZE_PAGE_DATAFLASH_2) control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
              else control_tasks_dataflash |= TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
            }
            else
            {
              //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
              fix_undefined_error_ar(carrent_active_functions);
            }
          }
        }

      }
      break;
    }
  case STATE_AR_TEMPORARY_BLOCK:
    {
      //На даний момент певні внутрішні операції блокують роботу аналогового реєстратрора
      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
      if (
          ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
          ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
          ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
          ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
          ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
          ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
          ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0) ||
          ((carrent_active_functions[7] & current_settings_prt.ranguvannja_analog_registrator[7]) != 0) ||
          ((carrent_active_functions[8] & current_settings_prt.ranguvannja_analog_registrator[8]) != 0)
         )
      {
        //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий
        _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        _SET_BIT(carrent_active_functions, RANG_DEFECT);
      }
      break;
    }
  default:
    {
      //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
      fix_undefined_error_ar(carrent_active_functions);
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Функція захистів з якої здійснюються всі інші операції
/*****************************************************/
inline void main_protection(void)
{
  copying_active_functions = 1; //Помічаємо, що зараз обновляємо значення активних функцій
  
  //Скижаємо ті сигнали, які відповідають за входи, кнопки і активацію з інтерфейсу
  const unsigned int maska_input_signals[N_BIG] = 
  {
    MASKA_FOR_INPUT_SIGNALS_0, 
    MASKA_FOR_INPUT_SIGNALS_1, 
    MASKA_FOR_INPUT_SIGNALS_2, 
    MASKA_FOR_INPUT_SIGNALS_3, 
    MASKA_FOR_INPUT_SIGNALS_4, 
    MASKA_FOR_INPUT_SIGNALS_5, 
    MASKA_FOR_INPUT_SIGNALS_6, 
    MASKA_FOR_INPUT_SIGNALS_7, 
    MASKA_FOR_INPUT_SIGNALS_8
  };
  for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_input_signals[i]);
  
  /**************************/
  //Перевірка, чи треба очистити трігерні функції
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    if ((reset_trigger_function_from_interface & (1 << USB_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_USB[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << USB_RECUEST));
    }
    if ((reset_trigger_function_from_interface & (1 << RS485_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_RS485[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << RS485_RECUEST));
    }
    //Помічаємо що ми виконали очистку по ВСІХ інтерфейсах
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  unsigned int active_inputs_grupa_ustavok = 0;
  /**************************/
  //Опрацьовуємо ФК, дискретні входи і верхній рівень
  /**************************/
  //Опрцьовуємо логіку натиснутих кнопок
  uint32_t pressed_buttons_tmp = 0;
  uint32_t buttons_mode_tmp = current_settings_prt.buttons_mode;
  if (
      (mutex_buttons == false) &&
      (pressed_buttons != 0)
     )   
  {
    pressed_buttons_tmp = pressed_buttons;
    //Очищаємо натиснуті кнопкb, інформацію про яких ми вже забрали у роботу (аде ще не опрацювали)
    pressed_buttons = 0;
  }
      
  uint32_t pressed_buttons_switcher = pressed_buttons_tmp & buttons_mode_tmp; /*натиснуті в даний момент кнопки-ключі*/
  pressed_buttons_tmp &= (uint32_t)(~buttons_mode_tmp); /*натиснуті в даний момент всі інші типи кнопок*/
      
  //Опрацьвуємо спочатку кнопки-ключі
  uint32_t fix_active_buttons_tmp = (fix_active_buttons ^ pressed_buttons_switcher) & buttons_mode_tmp;
  if (fix_active_buttons_tmp != fix_active_buttons) 
  {
    fix_active_buttons = fix_active_buttons_tmp;
    /*
    Змінилися стани кнопок-ключів
    */
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
    
  //Формуємо стан натиснутих кнопок з урахуванням нового стану копок клічів і інших кнопок
  uint32_t pressed_buttons_united = pressed_buttons_tmp | fix_active_buttons_tmp;

  //Світлова індикація натиснутих кнопок-ключів
  for (size_t i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
  {
    uint32_t maska_yellow = ((1 << (i*NUMBER_LED_COLOR + LED_COLOR_RED_BIT)) | (1 << (i*NUMBER_LED_COLOR + LED_COLOR_GREEN_BIT)));
    if (((buttons_mode_tmp >> i) & 0x1) == BUTTON_MODE_SWITCHER)
    {
      if (((fix_active_buttons_tmp >> i) & 0x1) != 0) 
      {
#ifndef KEYBOARD_VER_2_1
        state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
        state_leds_Fx[1] |= maska_yellow;
#else
        if (i != (4 - 1))
        {
          state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[1] |= maska_yellow;
        }
        else
        {
          state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[0] |= maska_yellow;
        }
#endif
      }    
      else
      {
#ifndef KEYBOARD_VER_2_1
        state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
        state_leds_Fx[0] |= maska_yellow;
#else
        if (i != (4 - 1))
        {
          state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[0] |= maska_yellow;
        }
        else
        {
          state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[1] |= maska_yellow;
        }
#endif
      }    
    }
    else
    {
      state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
      state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
    }
  }

  //Перевіряємо чи є зараз активні входи
  if (
      (pressed_buttons_united !=0)
      ||  
      (  
       (mutex_interface == false) &&
       (
        (activation_function_from_interface[0] != 0) ||
        (activation_function_from_interface[1] != 0) ||
        (activation_function_from_interface[2] != 0)
       )
      )
      ||  
      (active_inputs !=0)
     )   
  {
    unsigned int temp_value_for_activated_function_button_interface[N_SMALL] = {0, 0, 0};
    unsigned int temp_value_for_activated_function[N_SMALL] = {0, 0, 0};

    //Активація з кнопуки
    if (pressed_buttons_united != 0)
    {
      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        if ((pressed_buttons_united & (1 << i)) != 0)
        {
          unsigned int *point_temp_value_for_activated_function = ((pressed_buttons_tmp & (1 << i)) != 0) ? temp_value_for_activated_function_button_interface : temp_value_for_activated_function;
          point_temp_value_for_activated_function[0] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i  ];
          point_temp_value_for_activated_function[1] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i+1];
          point_temp_value_for_activated_function[2] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i+2];
        }
      }
      if ((pressed_buttons_united & (1 << (BIT_KEY_C - BIT_KEY_1))) != 0)
      {
        _SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_LEDS);
        _SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_RELES);
      }
      if ((pressed_buttons_united & (1 << (BIT_KEY_I - BIT_KEY_1))) != 0) _SET_BIT(temp_value_for_activated_function, RANG_SMALL_VKL_VV_H);
      if ((pressed_buttons_united & (1 << (BIT_KEY_O - BIT_KEY_1))) != 0) _SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VV_H);
    }
    
    //Активація з інтерфейсу
    if (mutex_interface == false)
    {
      temp_value_for_activated_function_button_interface[0] |= activation_function_from_interface[0];
      activation_function_from_interface[0] = 0;
      temp_value_for_activated_function_button_interface[1] |= activation_function_from_interface[1];
      activation_function_from_interface[1] = 0;
      temp_value_for_activated_function_button_interface[2] |= activation_function_from_interface[2];
      activation_function_from_interface[2] = 0;
    }
    
    //Обєднуємо активації з кнопок (режим кнопка) + активації з інтерфейсу і кнопок (режим ключ) + кнопки фіксованого функціоналу
    temp_value_for_activated_function[0] |= temp_value_for_activated_function_button_interface[0];
    temp_value_for_activated_function[1] |= temp_value_for_activated_function_button_interface[1];
    temp_value_for_activated_function[2] |= temp_value_for_activated_function_button_interface[2];

    //Активація з Д.Входу
    if (active_inputs != 0)
    {
      for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
      {
        if ((active_inputs & (1 << i)) != 0)
        {
          temp_value_for_activated_function[0] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i  ];
          temp_value_for_activated_function[1] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+1];
          temp_value_for_activated_function[2] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+2];
        }
      }
    }
    
    //Опреділювані функції
    for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      switch (i)
      {
      case 0:
        {
          active_functions[RANG_DF1_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF1_IN) != 0) << (RANG_DF1_IN & 0x1f);
          break;
        }
      case 1:
        {
          active_functions[RANG_DF2_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF2_IN) != 0) << (RANG_DF2_IN & 0x1f);
          break;
        }
      case 2:
        {
          active_functions[RANG_DF3_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF3_IN) != 0) << (RANG_DF3_IN & 0x1f);
          break;
        }
      case 3:
        {
          active_functions[RANG_DF4_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF4_IN) != 0) << (RANG_DF4_IN & 0x1f);
          break;
        }
      case 4:
        {
          active_functions[RANG_DF5_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF5_IN) != 0) << (RANG_DF5_IN & 0x1f);
          break;
        }
      case 5:
        {
          active_functions[RANG_DF6_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF6_IN) != 0) << (RANG_DF6_IN & 0x1f);
          break;
        }
      case 6:
        {
          active_functions[RANG_DF7_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF7_IN) != 0) << (RANG_DF7_IN & 0x1f);
          break;
        }
      case 7:
        {
          active_functions[RANG_DF8_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF8_IN) != 0) << (RANG_DF8_IN & 0x1f);
          break;
        }
      default: break;
      }
    
      //Перевірка на необхідність пролонгації активації В-функції на час  таймеру павзи
      if (_CHECK_SET_BIT(temp_value_for_activated_function_button_interface, (RANG_SMALL_DF1_IN + i)) != 0)
      {
        //Зараз має активуватися В-ФункціяХ, тому треба запустити таймер її утримування,
        //для того, щоб потім час цей можна було зрівняти з часом таймера павзи
        if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] < 0)
        {
          //Запускаємо таймер таймер утримування цієї функції в активному стані (емітація активного входу)
          //Запуск робимо тільки ту тому випадкук, якщо він ще не почався
          global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = 0;
        }
      }
    }

    //Опреділювані триґери
    for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      switch (i)
      {
      case 0:
        {
          active_functions[RANG_DT1_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT1_SET  ) != 0) << (RANG_DT1_SET   & 0x1f);
          active_functions[RANG_DT1_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT1_RESET) != 0) << (RANG_DT1_RESET & 0x1f);
          break;
        }
      case 1:
        {
          active_functions[RANG_DT2_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT2_SET  ) != 0) << (RANG_DT2_SET   & 0x1f);
          active_functions[RANG_DT2_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT2_RESET) != 0) << (RANG_DT2_RESET & 0x1f);
          break;
        }
      case 2:
        {
          active_functions[RANG_DT3_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT3_SET  ) != 0) << (RANG_DT3_SET   & 0x1f);
          active_functions[RANG_DT3_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT3_RESET) != 0) << (RANG_DT3_RESET & 0x1f);
          break;
        }
      case 3:
        {
          active_functions[RANG_DT4_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT4_SET  ) != 0) << (RANG_DT4_SET   & 0x1f);
          active_functions[RANG_DT4_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT4_RESET) != 0) << (RANG_DT4_RESET & 0x1f);
          break;
        }
      default: break;
      }
    }
    
      
    //Загальні функції (без ОФ-ій і функцій, які можуть блокуватися у місцевому управлінні)
    active_functions[RANG_RESET_LEDS                        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_LEDS                       ) != 0) << (RANG_RESET_LEDS                        & 0x1f);
    active_functions[RANG_RESET_RELES                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_RELES                      ) != 0) << (RANG_RESET_RELES                       & 0x1f);
    active_functions[RANG_MISCEVE_DYSTANCIJNE               >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_MISCEVE_DYSTANCIJNE              ) != 0) << (RANG_MISCEVE_DYSTANCIJNE               & 0x1f);
    active_functions[RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0) << (RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV & 0x1f);

    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_1_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_1_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_2_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_2_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_3_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_3_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_4_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_4_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
      
    active_functions[RANG_BLOCK_VKL_VV_H >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_VKL_VV_H) != 0) << (RANG_BLOCK_VKL_VV_H & 0x1f);
    active_functions[RANG_STATE_VV_H     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_STATE_VV_H    ) != 0) << (RANG_STATE_VV_H     & 0x1f);
    active_functions[RANG_VKL_VV_H       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_VKL_VV_H      ) != 0) << (RANG_VKL_VV_H       & 0x1f);
    active_functions[RANG_CTRL_VKL_H     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_VKL_H    ) != 0) << (RANG_CTRL_VKL_H     & 0x1f);
    active_functions[RANG_OTKL_VV_H      >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VV_H     ) != 0) << (RANG_OTKL_VV_H      & 0x1f);
    active_functions[RANG_CTRL_OTKL_H    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_OTKL_H   ) != 0) << (RANG_CTRL_OTKL_H    & 0x1f);
      
    active_functions[RANG_BLOCK_VKL_VV_L >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_VKL_VV_L) != 0) << (RANG_BLOCK_VKL_VV_L & 0x1f);
    active_functions[RANG_STATE_VV_L     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_STATE_VV_L    ) != 0) << (RANG_STATE_VV_L     & 0x1f);
    active_functions[RANG_VKL_VV_L       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_VKL_VV_L      ) != 0) << (RANG_VKL_VV_L       & 0x1f);
    active_functions[RANG_CTRL_VKL_L     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_VKL_L    ) != 0) << (RANG_CTRL_VKL_L     & 0x1f);
    active_functions[RANG_OTKL_VV_L      >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VV_L     ) != 0) << (RANG_OTKL_VV_L      & 0x1f);
    active_functions[RANG_CTRL_OTKL_L    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_OTKL_L   ) != 0) << (RANG_CTRL_OTKL_L    & 0x1f);

    //ОЗТ
    active_functions[RANG_BLOCK_OZT1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_OZT1    ) != 0) << (RANG_BLOCK_OZT1     & 0x1f);
    active_functions[RANG_BLOCK_OZT2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_OZT2    ) != 0) << (RANG_BLOCK_OZT2     & 0x1f);

    //МТЗ
    active_functions[RANG_BLOCK_MTZ1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ1    ) != 0) << (RANG_BLOCK_MTZ1     & 0x1f);
    active_functions[RANG_BLOCK_MTZ2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ2    ) != 0) << (RANG_BLOCK_MTZ2     & 0x1f);
    active_functions[RANG_BLOCK_USK_MTZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_USK_MTZ2) != 0) << (RANG_BLOCK_USK_MTZ2 & 0x1f);
    active_functions[RANG_BLOCK_MTZ3     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ3    ) != 0) << (RANG_BLOCK_MTZ3     & 0x1f);
    active_functions[RANG_BLOCK_MTZ4     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ4    ) != 0) << (RANG_BLOCK_MTZ4     & 0x1f);

    //3U0
    active_functions[RANG_BLOCK_P_3U0 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_P_3U0) != 0) << (RANG_BLOCK_P_3U0 & 0x1f);

    //Блок ТЗНП
    active_functions[RANG_BLOCK_TZNP1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP1) != 0) << (RANG_BLOCK_TZNP1 & 0x1f);
    active_functions[RANG_BLOCK_TZNP2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP2) != 0) << (RANG_BLOCK_TZNP2 & 0x1f);
    active_functions[RANG_BLOCK_TZNP3 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP3) != 0) << (RANG_BLOCK_TZNP3 & 0x1f);
    active_functions[RANG_BLOCK_TZNP4 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP4) != 0) << (RANG_BLOCK_TZNP4 & 0x1f);

    //УРОВ
    active_functions[RANG_PUSK_UROV1_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_PUSK_UROV1_VID_DV) != 0) << (RANG_PUSK_UROV1_VID_DV & 0x1f);
    active_functions[RANG_PUSK_UROV2_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_PUSK_UROV2_VID_DV) != 0) << (RANG_PUSK_UROV2_VID_DV & 0x1f);

    //Блок ЗОП(КОФ)
    active_functions[RANG_BLOCK_ZOP1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ZOP1) != 0) << (RANG_BLOCK_ZOP1 & 0x1f);
    active_functions[RANG_BLOCK_ZOP2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ZOP2) != 0) << (RANG_BLOCK_ZOP2 & 0x1f);

    //Блок для Umin
    active_functions[RANG_BLOCK_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMIN1) != 0) << (RANG_BLOCK_UMIN1 & 0x1f);
    active_functions[RANG_START_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_START_UMIN1) != 0) << (RANG_START_UMIN1 & 0x1f);
    active_functions[RANG_BLOCK_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMIN2) != 0) << (RANG_BLOCK_UMIN2 & 0x1f);
    active_functions[RANG_START_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_START_UMIN2) != 0) << (RANG_START_UMIN2 & 0x1f);
      
    //Блок для Umax
    active_functions[RANG_BLOCK_UMAX1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMAX1) != 0) << (RANG_BLOCK_UMAX1 & 0x1f);
    active_functions[RANG_BLOCK_UMAX2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMAX2) != 0) << (RANG_BLOCK_UMAX2 & 0x1f);

    //Блок для КЗ З/В
    active_functions[RANG_BLOCK_KZ_ZV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_KZ_ZV) != 0) << (RANG_BLOCK_KZ_ZV & 0x1f);

    //Блок для Газового захисту
    active_functions[RANG_BLOCK_GP  >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_GP ) != 0) << (RANG_BLOCK_GP  & 0x1f);
    active_functions[RANG_IN_GP1    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_IN_GP1   ) != 0) << (RANG_IN_GP1    & 0x1f);
    active_functions[RANG_IN_GP2    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_IN_GP2   ) != 0) << (RANG_IN_GP2    & 0x1f);
    active_functions[RANG_IN_GP_RPN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_IN_GP_RPN) != 0) << (RANG_IN_GP_RPN & 0x1f);

    //Блок для Теплового захисту
    active_functions[RANG_BLOCK_TP >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TP) != 0) << (RANG_BLOCK_TP & 0x1f);
    active_functions[RANG_IN_TP    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_IN_TP   ) != 0) << (RANG_IN_TP    & 0x1f);
    
    //Блокування для УЗ
    for (size_t i = 0; i < NUMBER_UP; i++)
    {
      uint32_t rang_small_block_up = RANG_SMALL_BLOCK_UP1 + i;
      uint32_t rang_block_up = RANG_BLOCK_UP1 + 3*i;
      active_functions[rang_block_up >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, rang_small_block_up) != 0) << (rang_block_up & 0x1f);
    }
  }
  /**************************/

  /**************************/
  //Виконуємо фільтрацію переднього фронту для тих сигналів, які мають активуватися тільки по передньому фронтові
  /**************************/
  {
    static unsigned int previous_activating_functions[N_BIG];
    //Формуємо маску сигналів, які треба позначити, як активні тільки в момент переходу з "0" в "1"
    unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int temp_activating_functions[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  
    //Сигнал "Сблос индикации"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_LEDS);
  
    //Сигнал "Сблос реле"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_RELES);

    //Сигнал "Скидання блокування готовності до ТУ"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);

    //Сигнал "Включить ВВ(В)"
    _SET_BIT(temp_maska_filter_function, RANG_VKL_VV_H);
    
    //Сигнал "Отключить ВВ(В)"
    _SET_BIT(temp_maska_filter_function, RANG_OTKL_VV_H);

    //Сигнал "Включить ВВ(Н)"
    _SET_BIT(temp_maska_filter_function, RANG_VKL_VV_L);
    
    //Сигнал "Отключить ВВ(Н)"
    _SET_BIT(temp_maska_filter_function, RANG_OTKL_VV_L);
  
    for (unsigned int i = 0; i < N_BIG; i++)
    {
      //З масиву попередніх станів виділяємо тільки ті функції, якиї нас цікавить фронт змін і поміщаємо їх у тимчасовий масив
      temp_activating_functions[i] = previous_activating_functions[i] & temp_maska_filter_function[i];
  
      //У тимчасовому масиві виділяємо тільки ті функції, у яких зафіксовано або передній, або задній фронти
      temp_activating_functions[i] ^= (active_functions[i] & temp_maska_filter_function[i]);
  
      //Тепер виділяємо у тимчасовому масиві тільки ті функції у яких зараз значення стоять рівні "1" (тобто відбувся перехід з "0" в "1")
      temp_activating_functions[i] &= active_functions[i];

      /*
      Перед тим, як виділити ті функції, які у цьому циклі будуть відмічені як активні 
      з урахуванням того, що деякі функції активоються по передньому фронті
      копіюємо статичний стан функцій (без врахування фронтів) у тимчасовий масив
      щоб при наступному аналізі мати попередній статичний стан активних функцій
      */ 
      previous_activating_functions[i] = active_functions[i];

      //Обновляємо масив функцій, які зараз активуються з врахуванням того, що серед виділених функцій маскою активними мають юути тільки ті, у яких перехід був з "0" в "1"
      active_functions[i] = (active_functions[i] & (~temp_maska_filter_function[i])) | temp_activating_functions[i];
    }
  }
  /**************************/
  
  /**************************
  Світлова індикація стану вимикача
  **************************/
  {
    uint32_t state_vv_H_dv = false;
    for (size_t i = 0; i < NUMBER_INPUTS; i++)
    {
      if (_CHECK_SET_BIT ((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_STATE_VV_H) != 0)
      {
        state_vv_H_dv = true;
        break;
      }
    }
    
    if (state_vv_H_dv)
    {
      if (_CHECK_SET_BIT(active_functions, RANG_STATE_VV_H) !=0) 
      {
        state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)));
        state_leds_ctrl |=  (uint32_t)(  (1 << LED_COLOR_RED_BIT  ) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I) );
      }
      else
      {
        state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_RED_BIT  ) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)));
        state_leds_ctrl |=  (uint32_t)(  (1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O) );
      }
    }
    else
    {
      state_leds_ctrl &=  (uint32_t)(~(((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) | ((1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I))));
    }
  }
  /**************************/

  /**************************/
  //Вибір групи уставок
  /**************************/
  for (size_t i = 0; i < NUMBER_GROUP_USTAVOK; i++)
  {
    if (active_inputs_grupa_ustavok & (1 << i)) 
    {
      _CLEAR_BIT(active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
      break;
    }
    else
    {
      if (i == (NUMBER_GROUP_USTAVOK - 1)) _SET_BIT(active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
    }
  }
  
  if (count_number_set_bit(&active_inputs_grupa_ustavok, NUMBER_GROUP_USTAVOK) > 1)
    _SET_BIT(set_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
  else
    _SET_BIT(clear_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
   
  if (
      ((active_functions[0] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_0) != 0) ||
      ((active_functions[1] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_1) != 0) ||
      ((active_functions[2] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_2) != 0) ||
      ((active_functions[3] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_3) != 0) ||
      ((active_functions[4] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_4) != 0) ||
      ((active_functions[5] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_5) != 0) ||
      ((active_functions[6] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_6) != 0) ||
      ((active_functions[7] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_7) != 0) ||
      ((active_functions[8] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_8) != 0)
    )
  {
    //Іде блокування груп уставок - група уставок залишається тою, яка вибрана попередньо
    _SET_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);

    unsigned int number_group_stp_tmp = 0;
    if(( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    
    if (number_group_stp_tmp != 1)
    {
      //Теоретично цього ніколи не мало б бути
      total_error_sw_fixed(52);
    }
  }
  else
  {
    //Можна вибирати групу уставок - захисти цю операцію не блокують
    _CLEAR_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);
    setpoints_selecting(active_functions, active_inputs_grupa_ustavok);
  }

  unsigned int number_group_stp;
  if     (( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 0;
  else if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 1;
  else if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 2;
  else if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 3;
  else
  {
    //Теоретично цього ніколи не мало б бути
    total_error_sw_fixed(51);
  }
  /**************************/

  /***********************************************************/
  //Розрахунок вимірювань
  /***********************************************************/
  calc_measurement(number_group_stp);

#ifdef DEBUG_TEST
  /***/
  //Тільки для відладки
  /***/
  if (temp_value_3I0_1 != 0)
    measurement[IM_3I0]         = temp_value_3I0_1;
  if (temp_value_3I0_other != 0)
    measurement[IM_3I0_other_g] = temp_value_3I0_other;
  if (temp_value_IA != 0)
    measurement[IM_IA_H]          = temp_value_IA;
  if (temp_value_IC != 0)
    measurement[IM_IC_H]          = temp_value_IC;
  if (temp_value_UA != 0)
    measurement[IM_UA]          = temp_value_UA;
  if (temp_value_UB != 0)
    measurement[IM_UB]          = temp_value_UB;
  if (temp_value_UC != 0)
    measurement[IM_UC]          = temp_value_UC;
  if (temp_value_3U0 != 0)
    measurement[IM_3U0_r]         = temp_value_3U0;
  if (temp_value_I2 != 0)
    measurement[IM_I2_H]          = temp_value_I2;
  if (temp_value_I1 != 0)
    measurement[IM_I1_H]          = temp_value_I1;
  /***/
#endif
    
      
  //Діагностика справності раз на період
  diagnostyca_adc_execution();
  
  //Копіюємо вимірювання для низькопріоритетних і високопріоритетних завдань
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < _NUMBER_IM; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
  }
  else
  {
    for (unsigned int i = 0; i < _NUMBER_IM; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /***********************************************************/
  
  
  /**************************/
  //Сигнал "Несправность Общая"
  /**************************/
  unsigned int diagnostyka_tmp[N_DIAGN];
  diagnostyka_tmp[0] = diagnostyka[0];
  diagnostyka_tmp[1] = diagnostyka[1];
  diagnostyka_tmp[2] = diagnostyka[2];
  diagnostyka_tmp[3] = diagnostyka[3];

  diagnostyka_tmp[0] &= (unsigned int)(~clear_diagnostyka[0]); 
  diagnostyka_tmp[0] |= set_diagnostyka[0]; 

  diagnostyka_tmp[1] &= (unsigned int)(~clear_diagnostyka[1]); 
  diagnostyka_tmp[1] |= set_diagnostyka[1]; 

  diagnostyka_tmp[2] &= (unsigned int)(~clear_diagnostyka[2]); 
  diagnostyka_tmp[2] |= set_diagnostyka[2]; 

  diagnostyka_tmp[3] &= (unsigned int)(~clear_diagnostyka[3]); 
  diagnostyka_tmp[3] |= set_diagnostyka[3]; 
  
  diagnostyka_tmp[3] &= USED_BITS_IN_LAST_INDEX; 

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_SOFT_RESTART_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  if (
      (diagnostyka_tmp[0] != 0) ||
      (diagnostyka_tmp[1] != 0) ||
      (diagnostyka_tmp[2] != 0) ||
      (diagnostyka_tmp[3] != 0)
     )   
  {
    _SET_BIT(active_functions, RANG_DEFECT);
    /**************************/
    //Сигнал "Несправность Аварийная"
    /**************************/
    if (
        ((diagnostyka_tmp[0] & MASKA_AVAR_ERROR_0) != 0) ||
        ((diagnostyka_tmp[1] & MASKA_AVAR_ERROR_1) != 0) ||
        ((diagnostyka_tmp[2] & MASKA_AVAR_ERROR_2) != 0) ||
        ((diagnostyka_tmp[3] & MASKA_AVAR_ERROR_3) != 0)
       )   
    {
      _SET_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    else
    {
      _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    /**************************/
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_DEFECT);
    _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  /**************************/

  
  static unsigned int previous_active_functions[N_BIG];
  
  //Логічні схеми мають працювати тільки у тому випадку, якщо немє сигналу "Аварийная неисправность"
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0 || _CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) != 0 )
  {
    //Аварійна ситуація не зафіксована
    
    /**************************/
    //Обробка передавальних функцій
    /**************************/
    tf_handler(previous_active_functions, active_functions);
    /**************************/

    /**************************/
    //Контроль привода ВВ
    /**************************/
    control_2VV(active_functions);//control_VV(active_functions);
	
    /**************************/

    /**************************/
    //ОЗТ
    /**************************/
    if ((current_settings_prt.configuration & (1 << OZT_BIT_CONFIGURATION)) != 0)
    {
      ozt_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_ozt_signals[N_BIG] = 
      {
        MASKA_OZT_SIGNALS_0,
        MASKA_OZT_SIGNALS_1,
        MASKA_OZT_SIGNALS_2, 
        MASKA_OZT_SIGNALS_3, 
        MASKA_OZT_SIGNALS_4, 
        MASKA_OZT_SIGNALS_5,
        MASKA_OZT_SIGNALS_6, 
        MASKA_OZT_SIGNALS_7, 
        MASKA_OZT_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_ozt_signals[i]);

      global_timers[INDEX_TIMER_OZT1] = -1;
      global_timers[INDEX_TIMER_OZT2] = -1;
      global_timers[INDEX_TIMER_OZT_AB] = -1;
    }
    /**************************/

    /**************************/
    //МТЗ
    /**************************/
    if ((current_settings_prt.configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
    {
      mtz_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_mtz_signals[N_BIG] = 
      {
        MASKA_MTZ_SIGNALS_0,
        MASKA_MTZ_SIGNALS_1,
        MASKA_MTZ_SIGNALS_2, 
        MASKA_MTZ_SIGNALS_3, 
        MASKA_MTZ_SIGNALS_4, 
        MASKA_MTZ_SIGNALS_5,
        MASKA_MTZ_SIGNALS_6, 
        MASKA_MTZ_SIGNALS_7, 
        MASKA_MTZ_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_mtz_signals[i]);
      
      global_timers[INDEX_TIMER_MTZ1] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ1_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2] = -1;
      global_timers[INDEX_TIMER_MTZ2_DEPENDENT] = -1;
      global_timers[INDEX_TIMER_MTZ2_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_VVID_PR] = -1;
      global_timers[INDEX_TIMER_MTZ3] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ3_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ4] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ4_PO_NAPRUZI] = -1;
    }
    /**************************/
    
    /**************************/
    //Захист 3U0
    /**************************/
    if ((current_settings_prt.configuration & (1 << P_3U0_BIT_CONFIGURATION)) != 0)
    {
      p_3U0_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_p_3U0_signals[N_BIG] = 
      {
        MASKA_P_3U0_SIGNALS_0,
        MASKA_P_3U0_SIGNALS_1,
        MASKA_P_3U0_SIGNALS_2, 
        MASKA_P_3U0_SIGNALS_3, 
        MASKA_P_3U0_SIGNALS_4, 
        MASKA_P_3U0_SIGNALS_5,
        MASKA_P_3U0_SIGNALS_6, 
        MASKA_P_3U0_SIGNALS_7, 
        MASKA_P_3U0_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_p_3U0_signals[i]);
      global_timers[INDEX_TIMER_P_3U0] = -1;
    }
    /**************************/
    
    /**************************/
    //ТЗНП
    /**************************/
    if ((current_settings_prt.configuration & (1 << TZNP_BIT_CONFIGURATION)) != 0)
    {
      tznp_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_tznp_signals[N_BIG] = 
      {
        MASKA_TZNP_SIGNALS_0, 
        MASKA_TZNP_SIGNALS_1, 
        MASKA_TZNP_SIGNALS_2,
        MASKA_TZNP_SIGNALS_3, 
        MASKA_TZNP_SIGNALS_4, 
        MASKA_TZNP_SIGNALS_5, 
        MASKA_TZNP_SIGNALS_6, 
        MASKA_TZNP_SIGNALS_7, 
        MASKA_TZNP_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_tznp_signals[i]);

      global_timers[INDEX_TIMER_TZNP1_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP1_NAZAD] = -1;
      global_timers[INDEX_TIMER_TZNP2_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP2_NAZAD] = -1;
      global_timers[INDEX_TIMER_TZNP3_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP3_NAZAD] = -1;
      global_timers[INDEX_TIMER_TZNP4_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP4_NAZAD] = -1;
    }
    /**************************/
  
    /**************************/
    //ЗОП(КОФ)
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZOP_BIT_CONFIGURATION)) != 0)
    {
      zop_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_zop_signals[N_BIG] = 
      {
        MASKA_ZOP_SIGNALS_0, 
        MASKA_ZOP_SIGNALS_1, 
        MASKA_ZOP_SIGNALS_2,
        MASKA_ZOP_SIGNALS_3, 
        MASKA_ZOP_SIGNALS_4, 
        MASKA_ZOP_SIGNALS_5, 
        MASKA_ZOP_SIGNALS_6, 
        MASKA_ZOP_SIGNALS_7, 
        MASKA_ZOP_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_zop_signals[i]);
      global_timers[INDEX_TIMER_ZOP1] = -1;
      global_timers[INDEX_TIMER_ZOP2] = -1;
    }
    /**************************/
    
    if ((current_settings_prt.configuration & (1 << UMIN_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //ЗНМИН1
      /**************************/
      //umin1_handler(active_functions, number_group_stp);
      umin1_handler2(active_functions, number_group_stp);
	  
      /**************************/
      
      /**************************/
      //ЗНМИН2
      /**************************/
      //umin2_handler(active_functions, number_group_stp);
      umin2_handler1(active_functions, number_group_stp);
	  
      /**************************/
    } 
    else 
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_umin_signals[N_BIG] = 
      {
        MASKA_UMIN_SIGNALS_0, 
        MASKA_UMIN_SIGNALS_1, 
        MASKA_UMIN_SIGNALS_2,
        MASKA_UMIN_SIGNALS_3, 
        MASKA_UMIN_SIGNALS_4, 
        MASKA_UMIN_SIGNALS_5, 
        MASKA_UMIN_SIGNALS_6, 
        MASKA_UMIN_SIGNALS_7, 
        MASKA_UMIN_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umin_signals[i]);

      global_timers[INDEX_TIMER_UMIN1] = -1;
      global_timers[INDEX_TIMER_UMIN2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << UMAX_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //ЗНМАКС1
      /**************************/
      umax1_handler(active_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //ЗНМАКС2
      /**************************/
      umax2_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_umax_signals[N_BIG] = 
      {
        MASKA_UMAX_SIGNALS_0, 
        MASKA_UMAX_SIGNALS_1, 
        MASKA_UMAX_SIGNALS_2,
        MASKA_UMAX_SIGNALS_3, 
        MASKA_UMAX_SIGNALS_4, 
        MASKA_UMAX_SIGNALS_5, 
        MASKA_UMAX_SIGNALS_6, 
        MASKA_UMAX_SIGNALS_7, 
        MASKA_UMAX_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umax_signals[i]);

      global_timers[INDEX_TIMER_UMAX1] = -1;
      global_timers[INDEX_TIMER_UMAX2] = -1;
    }
    
    /**************************/
    //УРОВ
    /**************************/
    if ((current_settings_prt.configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
    {
      urov_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_urov_signals[N_BIG] = 
      {
        MASKA_UROV_SIGNALS_0, 
        MASKA_UROV_SIGNALS_1, 
        MASKA_UROV_SIGNALS_2,
        MASKA_UROV_SIGNALS_3, 
        MASKA_UROV_SIGNALS_4, 
        MASKA_UROV_SIGNALS_5, 
        MASKA_UROV_SIGNALS_6, 
        MASKA_UROV_SIGNALS_7, 
        MASKA_UROV_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_urov_signals[i]);

      global_timers[INDEX_TIMER_UROV1_1] = -1;
      global_timers[INDEX_TIMER_UROV1_2] = -1;

      global_timers[INDEX_TIMER_UROV2_1] = -1;
      global_timers[INDEX_TIMER_UROV2_2] = -1;
    }
    /**************************/

    /**************************/
    //Вн.Зовн.Пошкодження
    /**************************/
    if ((current_settings_prt.configuration & (1 << KZ_ZV_BIT_CONFIGURATION)) != 0)
    {
      //kz_zv_handler(active_functions, number_group_stp);
      Kz_zv_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_kz_zv_signals[N_BIG] = 
      {
        MASKA_KZ_ZV_SIGNALS_0,
        MASKA_KZ_ZV_SIGNALS_1,
        MASKA_KZ_ZV_SIGNALS_2, 
        MASKA_KZ_ZV_SIGNALS_3, 
        MASKA_KZ_ZV_SIGNALS_4, 
        MASKA_KZ_ZV_SIGNALS_5,
        MASKA_KZ_ZV_SIGNALS_6, 
        MASKA_KZ_ZV_SIGNALS_7, 
        MASKA_KZ_ZV_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_kz_zv_signals[i]);
    }
    /**************************/

    /**************************/
    //Газовий захист
    /**************************/
    if ((current_settings_prt.configuration & (1 << GP_BIT_CONFIGURATION)) != 0)
    {
      //gp_handler(active_functions, number_group_stp);
      GP_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_gp_signals[N_BIG] = 
      {
        MASKA_GP_SIGNALS_0,
        MASKA_GP_SIGNALS_1,
        MASKA_GP_SIGNALS_2, 
        MASKA_GP_SIGNALS_3, 
        MASKA_GP_SIGNALS_4, 
        MASKA_GP_SIGNALS_5,
        MASKA_GP_SIGNALS_6, 
        MASKA_GP_SIGNALS_7, 
        MASKA_GP_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_gp_signals[i]);

      global_timers[INDEX_TIMER_GZ1] = -1;
      global_timers[INDEX_TIMER_GZ2] = -1;
    }
    /**************************/

    /**************************/
    //Тепловий захист
    /**************************/
    if ((current_settings_prt.configuration & (1 << TP_BIT_CONFIGURATION)) != 0)
    {
      //tp_handler(active_functions, number_group_stp);
      TP_handler(active_functions, number_group_stp);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_tp_signals[N_BIG] = 
      {
        MASKA_TP_SIGNALS_0,
        MASKA_TP_SIGNALS_1,
        MASKA_TP_SIGNALS_2, 
        MASKA_TP_SIGNALS_3, 
        MASKA_TP_SIGNALS_4, 
        MASKA_TP_SIGNALS_5,
        MASKA_TP_SIGNALS_6, 
        MASKA_TP_SIGNALS_7, 
        MASKA_TP_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_tp_signals[i]);

      global_timers[INDEX_TIMER_TZ] = -1;
    }
    /**************************/

    /**************************/
    //Універсальний захист
    /**************************/
    if ((current_settings_prt.configuration & (1 << UP_BIT_CONFIGURATION)) != 0) 
    {
      up_handler(active_functions, number_group_stp);
    } 
    else 
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_up_signals[N_BIG] = 
      {
        MASKA_UP_SIGNALS_0, 
        MASKA_UP_SIGNALS_1, 
        MASKA_UP_SIGNALS_2,
        MASKA_UP_SIGNALS_3, 
        MASKA_UP_SIGNALS_4, 
        MASKA_UP_SIGNALS_5, 
        MASKA_UP_SIGNALS_6, 
        MASKA_UP_SIGNALS_7, 
        MASKA_UP_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_up_signals[i]);

      for (size_t i = 0; i < NUMBER_UP; i++) global_timers[INDEX_TIMER_UP1 + i] = -1;
    }
    /**************************/
    
    /**************************/
    //Розширена логіка
    /**************************/
    if ((current_settings_prt.configuration & (1 << EL_BIT_CONFIGURATION)) != 0)
    {
      unsigned int active_functions_tmp[NUMBER_ITERATION_EL_MAX][N_BIG];
      unsigned int iteration = 0;
	  unsigned int repeat_state = false;
      unsigned int df_changed_state_with_start_new_timeout = 0;
      do
      {
        for (unsigned int i = 0; i < iteration; i++)
        {
          if (
              (active_functions_tmp[i][0] == active_functions[0]) &&
              (active_functions_tmp[i][1] == active_functions[1]) &&
              (active_functions_tmp[i][2] == active_functions[2]) &&
              (active_functions_tmp[i][3] == active_functions[3]) &&
              (active_functions_tmp[i][4] == active_functions[4]) &&
              (active_functions_tmp[i][5] == active_functions[5]) &&
              (active_functions_tmp[i][6] == active_functions[6]) &&
              (active_functions_tmp[i][7] == active_functions[7]) &&
              (active_functions_tmp[i][8] == active_functions[8])
             )
          {
            repeat_state = true;
            break;
          }
        }
        if (repeat_state != false ) break;
        
        active_functions_tmp[iteration][0] = active_functions[0];
        active_functions_tmp[iteration][1] = active_functions[1];
        active_functions_tmp[iteration][2] = active_functions[2];
        active_functions_tmp[iteration][3] = active_functions[3];
        active_functions_tmp[iteration][4] = active_functions[4];
        active_functions_tmp[iteration][5] = active_functions[5];
        active_functions_tmp[iteration][6] = active_functions[6];
        active_functions_tmp[iteration][7] = active_functions[7];
        active_functions_tmp[iteration][8] = active_functions[8];

        d_and_handler(active_functions);
        d_or_handler(active_functions);
        d_xor_handler(active_functions);
        d_not_handler(active_functions);
        df_handler(active_functions, &df_changed_state_with_start_new_timeout);
        dt_handler(active_functions);
        
        iteration++;
      }
      while (
             (iteration < current_settings_prt.number_iteration_el)
             &&
             (
              (active_functions_tmp[iteration - 1][0] != active_functions[0]) ||
              (active_functions_tmp[iteration - 1][1] != active_functions[1]) ||
              (active_functions_tmp[iteration - 1][2] != active_functions[2]) ||
              (active_functions_tmp[iteration - 1][3] != active_functions[3]) ||
              (active_functions_tmp[iteration - 1][4] != active_functions[4]) ||
              (active_functions_tmp[iteration - 1][5] != active_functions[5]) ||
              (active_functions_tmp[iteration - 1][6] != active_functions[6]) ||
              (active_functions_tmp[iteration - 1][7] != active_functions[7]) ||
              (active_functions_tmp[iteration - 1][8] != active_functions[8])
             ) 
            );
      
      if (
          (repeat_state != false ) ||
          (iteration >= current_settings_prt.number_iteration_el)
         )
      {
        _SET_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
      else
      {
        _CLEAR_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_el_signals[N_BIG] = 
      {
        MASKA_EL_SIGNALS_0, 
        MASKA_EL_SIGNALS_1, 
        MASKA_EL_SIGNALS_2,
        MASKA_EL_SIGNALS_3, 
        MASKA_EL_SIGNALS_4, 
        MASKA_EL_SIGNALS_5, 
        MASKA_EL_SIGNALS_6, 
        MASKA_EL_SIGNALS_7, 
        MASKA_EL_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_el_signals[i]);
      
      //Скидаємо всі таймери, які відповідають за розширену логіку
      for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < (INDEX_TIMER_DF_WORK_START + NUMBER_DEFINED_FUNCTIONS); i++)
        global_timers[i] = -1;
    }
    /**************************/

    /**************************/
    //Включення-Відключення
    /**************************/
    if ((current_settings_prt.configuration & (1 << OFF_ON_BIT_CONFIGURATION)) != 0)
    {
      //on_off_handler(active_functions);
	  Bvhs_handler(active_functions);
	  Bvls_handler(active_functions);
    }
    else
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_on_off_signals[N_BIG] = 
      {
        MASKA_OFF_ON_SIGNALS_0,
        MASKA_OFF_ON_SIGNALS_1,
        MASKA_OFF_ON_SIGNALS_2, 
        MASKA_OFF_ON_SIGNALS_3, 
        MASKA_OFF_ON_SIGNALS_4, 
        MASKA_OFF_ON_SIGNALS_5,
        MASKA_OFF_ON_SIGNALS_6, 
        MASKA_OFF_ON_SIGNALS_7, 
        MASKA_OFF_ON_SIGNALS_8
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_on_off_signals[i]);

      global_timers[INDEX_TIMER_VIDKL_VV_H] = -1;
      global_timers[INDEX_TIMER_BLK_VKL_VV_H] = -1;
      global_timers[INDEX_TIMER_VKL_VV_H] = -1;
      global_timers[INDEX_TIMER_PRYVOD_VV_H] = -1;
      
      global_timers[INDEX_TIMER_VIDKL_VV_L] = -1;
      global_timers[INDEX_TIMER_BLK_VKL_VV_L] = -1;
      global_timers[INDEX_TIMER_VKL_VV_L] = -1;
      global_timers[INDEX_TIMER_PRYVOD_VV_L] = -1;
    }
    /**************************/
    
    /**************************/
    //Готовность к ТУ
    /**************************/
    ready_tu(active_functions);
    /**************************/
  }
  else
  {
    //Аварійна ситуація зафіксована
    
    //Скидаємо всі активні функції, крім інформативних
    active_functions[0] &= MASKA_INFO_SIGNALES_0;
    active_functions[1] &= MASKA_INFO_SIGNALES_1;
    active_functions[2] &= MASKA_INFO_SIGNALES_2;
    active_functions[3] &= MASKA_INFO_SIGNALES_3;
    active_functions[4] &= MASKA_INFO_SIGNALES_4;
    active_functions[5] &= MASKA_INFO_SIGNALES_5;
    active_functions[6] &= MASKA_INFO_SIGNALES_6;
    active_functions[7] &= MASKA_INFO_SIGNALES_7;
    active_functions[8] &= MASKA_INFO_SIGNALES_8;
    
    //Деактивовуємо всі реле
    state_outputs = 0;
    
    //Переводимо у початковий стан деякі глобальні змінні
    previous_states_ready_tu = 0;
    trigger_ready_tu = 0;
    
    //Скидаємо всі таймери, які присутні у лозіці
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
//    //Стан всіх ОФ переводимо у пасивний
//    state_df = 0;
    
    //Стан виконання ОФ переводимо у початковий
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //Обробка аналогового реєстратора
  /**************************/
  analog_registrator(active_functions);
  /**************************/

  /**************************/
  //Обробка дискретного реєстратора
  /**************************/
  digital_registrator(active_functions);
  /**************************/

  /**************************/
  //Робота з функціями, які мають записуватися у енергонезалежну пам'ять
  /**************************/
  const unsigned int maska_trg_func_array[N_BIG] = {
                                                    MASKA_TRIGGER_SIGNALES_0,
                                                    MASKA_TRIGGER_SIGNALES_1,
                                                    MASKA_TRIGGER_SIGNALES_2,
                                                    MASKA_TRIGGER_SIGNALES_3,
                                                    MASKA_TRIGGER_SIGNALES_4,
                                                    MASKA_TRIGGER_SIGNALES_5,
                                                    MASKA_TRIGGER_SIGNALES_6,
                                                    MASKA_TRIGGER_SIGNALES_7,
                                                    MASKA_TRIGGER_SIGNALES_8
                                                  };
  unsigned int comparison_true = true;
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int tmp_data;
    if (trigger_active_functions[i] != (tmp_data = (active_functions[i] & maska_trg_func_array[i])))
    {
      comparison_true = false;
      trigger_active_functions[i] = tmp_data;
    }
  }
  if (comparison_true != true)
  {
    /*
    Сигнали, значення яких записується у енергонезалежну пам'1ять змінилися.
    Подаємо команду на їх запис у енергонезалежну пам'ять
    */
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //Перекидання інфомації у масиви активних і тригерних функцій
  /**************************/
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int temp_data = active_functions[i];
    trigger_functions_USB[i]   |= temp_data;
    trigger_functions_RS485[i] |= temp_data;
  }

  copying_active_functions = 0; //Помічаємо, що обновлення значення активних функцій завершене
  
  /*
  Робимо копію значення активних функцій для того, щоб коли ці знаення будуть
  обновлятися, то можна було б іншим модулям  (запис у об'єднаний аналоговий
  реєстратор) взяти попереднє, але достовірне значення
  */
  for (unsigned int i = 0; i < N_BIG; i++) 
  {
    unsigned int temp_data = active_functions[i];
    active_functions_copy[i] = temp_data;
    previous_active_functions[i] = temp_data;
  }
  /**************************/

  /**************************/
  //Вивід інформації на виходи
  /**************************/
  //Спочатку перевіряємо, чи не активовувалвся команда "Сблос реле" - і якщо так, то попередньо скидаємо всі реле
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_RELES) !=0)
  {
    state_outputs = 0;
  }
  
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //Не зафіксовано аварійної ситуації, тому встановлювати реле можна
    
    //Визначаємо, які реле зараз мають бути замкнутими
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //У тимчасовий масив поміщаємо ЛОГІЧНЕ І ранжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
      unsigned int temp_array_of_outputs[N_BIG];
    
      for (unsigned int j = 0; j < N_BIG; j++) temp_array_of_outputs[j] = current_settings_prt.ranguvannja_outputs[N_BIG*i + j] & active_functions[j];

      //Сигнал "Аварійна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_AVAR_DEFECT) !=0)
      {
        //Сигнал "Aварийная неисправность"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT) == 0)
        {
          //Сигнал "Aварийная неисправность" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
        else
        {
          //Сигнал "Aварийная неисправность" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
      }
      
      //Сигнал "Загальна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_DEFECT) !=0)
      {
        //Сигнал "Загальна несправність"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DEFECT) ==0)
        {
          //Сигнал "Загальна несправність" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
        else
        {
          //Сигнал "Загальна несправність" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
      }

      //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому виході і функціями, які зараз є активними - умова активації виходу
      if (
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
      {
        //Для сигнального реле виконуємо його замикання, а для командного перевіряємо чи нема спроби активувати реле при умові що на нього заведено блок включення, причому він блокований
        if ((current_settings_prt.type_of_output & (1 << i)) != 0)
        {
          //Вихід сигнальний, тому у буль якому разі замикаємо реле
          //Відмічаємо, що даний вихід - ЗАМКНУТИЙ
          state_outputs |= (1 << i);
        }
        else
        {
          //Вихід командний, тому перевіряємо чи не йде спроба активувати реле, на яке заведено БВ, причому блок БВ з пеквних причин блокований (неактивний)
          if (
              (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV_H) == 0) &&
              (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV_L) == 0)
             )   
          {
            //На дане реле не заводиться сигнали БВ (блоки включення)
          
            //Відмічаємо, що даний вихід - ЗАМКНУТИЙ
            state_outputs |= (1 << i);
          }
          else
          {
            //На дане реле заводиться сигнал БВ (блок включення)
          
            //Відмічаємо, що даний вихід - ЗАМКНУТИЙ тільки тоді, коли відповідна функція БВ активна зараз
            if (
                ((_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV_H) != 0) && (_CHECK_SET_BIT(active_functions, RANG_WORK_BV_H) == 0)) ||
                ((_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV_L) != 0) && (_CHECK_SET_BIT(active_functions, RANG_WORK_BV_L) == 0))
               )
            {
              state_outputs &= ~(1 << i);
            }
            else
            {
              state_outputs |= (1 << i);
            }
          }
        }
      }
      else
      {
        //Перевіряємо, чи вихід командний, чи сигнальний
        if ((current_settings_prt.type_of_output & (1 << i)) == 0)
        {
          //Вихід командний
        
          //Відмічаємо, що даний вихід - РОЗІМКНУТИЙ
          state_outputs &= ~(1 << i);
        }
      }
    }
  }
  else
  {
    //Зафіксовано аварійнe ситуацію, тому деактивуємо всі реле!!!

    //Деактивовуємо всі реле
    state_outputs = 0;
  }
  
  //Перевіряємо чи треба записувати стан сигнальних виходів у EEPROM
  if((state_outputs  & current_settings_prt.type_of_output) != state_signal_outputs)
  {
    state_signal_outputs = state_outputs  & current_settings_prt.type_of_output;
    //Виставляємо повідомлення про те, що в EEPROM треба записати нові значення сигнальних виходів і тригерних світлоіндикаторів
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //Стан виходу з уразуванням імпульсного режиму роботи сигнальних виходів
  unsigned int output_signal_modif = (current_settings_prt.type_of_output_modif & current_settings_prt.type_of_output);
  state_outputs_raw = ( state_outputs & ((unsigned int)(~output_signal_modif)) ) | ((state_outputs & output_signal_modif)*output_timer_prt_signal_output_mode_2);
  
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37) = state_outputs_raw;
  TIM_PRT_write_tick = TIM2->CNT;
  /**************************/

  /**************************/
  //Вивід інформації на світлодіоди
  /**************************/
  //Спочатку перевіряємо, чи не активовувалвся команда "Сблос индикации" - і якщо так, то попередньо скидаємо всю індикацію
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_LEDS) !=0)
  {
    state_leds = 0;
  }
  
  //Визначаємо, які світлоіндикатори зараз мають бути активними
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //У тимчасовий масив копіюємо ранжування світлоіндикатора, який індексується інедексом "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому світлоіндикаторі і функціями, які зараз є активними - умова активації виходу
    for (unsigned int j = 0; j < N_BIG; j++ ) temp_array_of_leds[j] = current_settings_prt.ranguvannja_leds[N_BIG*i + j] & active_functions[j];

    if (
        (temp_array_of_leds[0] != 0) ||
        (temp_array_of_leds[1] != 0) ||
        (temp_array_of_leds[2] != 0) ||
        (temp_array_of_leds[3] != 0) ||
        (temp_array_of_leds[4] != 0) ||
        (temp_array_of_leds[5] != 0) ||
        (temp_array_of_leds[6] != 0) ||
        (temp_array_of_leds[7] != 0) ||
        (temp_array_of_leds[8] != 0)
       )
    {
      //Відмічаємо, що даний світлоіндикатор - ГОРИТЬ
      state_leds |= (1 << i);
    }
    else
    {
      //Перевіряємо, чи даний світлоіндикатор нормальний, чи тригерний
      if ((current_settings_prt.type_of_led & (1 << i)) == 0)
      {
        //Світлоіндикатор нормальний

        //Відмічаємо, що даний світлоіндикатор - ПОГАШЕНИЙ
        state_leds &= ~(1 << i);
      }
    }
  }
  //Перевіряємо чи треба записувати стан тригерних світлоіндикаторів у EEPROM
  if((state_leds  & current_settings_prt.type_of_led) != state_trigger_leds)
  {
    state_trigger_leds = state_leds  & current_settings_prt.type_of_led;
    //Виставляємо повідомлення про те, що в EEPROM треба записати нові значення сигнальних виходів і тригерних світлоіндикаторів
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //Сервісні світлоіндикатори
  /*Run_Error*/
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0) state_leds_ctrl |=  (1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E);
  else state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)));
  if (
      (_CHECK_SET_BIT(active_functions, RANG_DEFECT     ) != 0) ||
      (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) != 0)
     ) state_leds_ctrl |=  (1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E);
  else state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)));
  
  static uint32_t current_LED_N_COL;
  
  //Очищаємо попередню інформацію
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD32_DD38) = ((1 << current_LED_N_COL) << LED_N_ROW) | ((uint32_t)(~0) & ((1 << LED_N_ROW) - 1));
  //Переходимо на наступний стовбець
  if (++current_LED_N_COL >= LED_N_COL) current_LED_N_COL = 0;
  
  uint32_t state_leds_tmp;
  
  switch (current_LED_N_COL)
  {
  case 0:
    {
      state_leds_tmp = (((state_leds >>  0) & 0x1) << 0) |
                       (((state_leds >>  2) & 0x1) << 1) |
                       (((state_leds >>  4) & 0x1) << 2) |
                       (((state_leds >>  6) & 0x1) << 3) |
                       (((state_leds >>  8) & 0x1) << 4) |
                       (((state_leds >> 10) & 0x1) << 5) |
                       (((state_leds >> 12) & 0x1) << 6) |
                       (((state_leds >> 14) & 0x1) << 7);

//      state_leds_tmp = (((state_leds >> (2*0)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(6 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 1:
    {
      uint32_t temp_state = state_leds;
      state_leds_tmp = (((temp_state >>  1) & 0x1) << 0) |
                       (((temp_state >>  3) & 0x1) << 1) |
                       (((temp_state >>  5) & 0x1) << 2) |
                       (((temp_state >>  7) & 0x1) << 3) |
                       (((temp_state >>  9) & 0x1) << 4) |
                       (((temp_state >> 11) & 0x1) << 5) |
                       (((temp_state >> 13) & 0x1) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*1)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(1 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 2:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E  )) & (1 << LED_COLOR_RED_BIT)) != 0) << 0) |
                      /*
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP )) & (1 << LED_COLOR_RED_BIT)) != 0) << 2) |
                      */
                       (((state_leds >> 15) & 0x1) << 1) |
                       (((state_leds >> 16) & 0x1) << 2) |
      
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 3) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 4) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 5) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 6) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);
      
//      state_leds_tmp = (((state_leds >> (2*2)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(2 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 3:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E  )) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 0) |
                      /*
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 1) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP )) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 2) |
                      */
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 3) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 4) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 5) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);
      
//      state_leds_tmp = (((state_leds >> (2*3)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(1 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(3 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 4:
    {
      state_leds_tmp = ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 0) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 2) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 3) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 4) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 5) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*4)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(2 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(4 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 5:
    {
      state_leds_tmp = ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 0) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 1) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 2) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 3) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 4) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 5) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*5)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(3 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(5 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 6:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*6)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(4 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(6 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
//  case 7:
//    {
//      state_leds_tmp = (((state_leds >> (2*7)) & ((1 << 1) - 1)) << 0) |
//                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(5 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & ((1 << NUMBER_LED_COLOR) - 1)) << 4) |
//                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6);
//      break;
//    }
  default:
    {
      //Теоретично цього ніколи не мало б бути
      total_error_sw_fixed(22);
    }
  }

  //Виводимо інформацію по світлоіндикаторах на світлодіоди
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD32_DD38) = ((1 << current_LED_N_COL) << LED_N_ROW) | ((uint32_t)(~state_leds_tmp) & ((1 << LED_N_ROW) - 1));
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//Переривання від таймеру TIM2, який обслуговує систему захистів
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 1, який генерує переривання кожні 1 мс, для опраціьовування таймерів і систем захистів
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //Перевіряємо, чи відбувалися зміни настройок
    /***********************************************************/
    if (
        (changed_settings == CHANGED_ETAP_ENDED) && /*Це є умова, що нові дані підготовлені для передачі їх у роботу системою захистів (і при цьому зараз дані не змінюються)*/
        (state_ar_record  != STATE_AR_START    )    /*Це є умова, що на даний момент не може виникнути переривання від вимірювальної системи (з вищим пріоритетом за пріоритет системи захистів) з умовою початку формування запису аналогового реєстратора. де треба буде взяти ширину доаварійного і післяаварійного масивів*/ 
       )   
    {
      //Копіюємо таблицю настройок у копію цієї таблиці але з якою працює (читає і змінює) тільки система захистів
      current_settings_prt = current_settings;
      ch_type_voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;
      
      //Помічаємо, що зміни прийняті системою захистів, але ще треба прийняти вимірювальною системою
      changed_settings = CHANGED_ETAP_ENDED_EXTRA_ETAP;
    }
    /***********************************************************/

    /*******************************************************/
    //Перевіряємо, чи відбувалися зміни юстування
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*Це є умова, що нові дані підготовлені для передачі їх у роботу системою захистів(і при цьому зараз дані не змінюються)*/
    {
      //Копіюємо масив юстування у копію цього масиву але з яким працює (читає і змінює) тільки вимірювальна захистема
      for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
      {
        phi_ustuvannja_meas[i] = phi_ustuvannja[i];
        phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ];
        phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1];
      }
      
      //Помічаємо, що зміни прийняті системою захистів
      changed_ustuvannja = CHANGED_ETAP_NONE;
    }
    /*****************************************************/


    /***********************************************************/
    //Перевіряємо необхідність очистки аналогового і дискретного реєстраторів
    /***********************************************************/
    //Аналоговий реєстратор
    if (
        ((clean_rejestrators & CLEAN_AR) != 0 )
        &&  
        (state_ar_record == STATE_AR_NO_RECORD)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR      |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                         |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                       |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU
                                    )
         ) == 0
        )   
       )
    {
      //Виставлено каманда очистити аналогового реєстратора

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
      info_rejestrator_ar.saving_execution = 0;
      info_rejestrator_ar.number_records = 0;
    
      //Помічаємо, що номер запису не вибраний
      number_record_of_ar_for_menu = 0xffff;
      number_record_of_ar_for_USB = 0xffff;
      number_record_of_ar_for_RS485 = 0xffff;

      //Знімаємо команду очистки аналогового реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_AR);
    }
    
    //Дискретний реєстратор
    if (
        ((clean_rejestrators & CLEAN_DR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //Виставлено каманда очистити дискретного реєстратор

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //Помічаємо, що номер запису не вибраний
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //Знімаємо команду очистки дискретного реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //Опрцювання логічних тайменрів і дискретних входів тільки коли настройки успішно прочитані
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //Опрцювання функцій захистів
    /***********************************************************/
    //Діагностика вузлів, яку треба проводити кожен раз перед початком опрацьовуванням логіки пристрою
    uint32_t TIM_PRT_read_tick = TIM2->CNT;

    uint64_t TIM_PRT_delta_write_read;
    if (TIM_PRT_read_tick < TIM_PRT_write_tick)
      TIM_PRT_delta_write_read = TIM_PRT_read_tick + 0x100000000 - TIM_PRT_write_tick;
    else TIM_PRT_delta_write_read = TIM_PRT_read_tick - TIM_PRT_write_tick;
    if (TIM_PRT_delta_write_read > (TIM2_MIN_PERIOD_WRITE_READ + 1))
    {
      unsigned int control_state_outputs = ((~((unsigned int)(_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37)))) & 0xffff);

      if (control_state_outputs != state_outputs_raw) 
      {
        for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
        {
          uint32_t maska = 1 << index;
        
          if ((control_state_outputs & maska) != (state_outputs_raw & maska)) _SET_BIT(set_diagnostyka, (ERROR_DIGITAL_OUTPUT_1_BIT + index));
        }
      }
    }
    //Діагностика необхідно-приєднаних плат
    {
      uint32_t board_register_tmp = _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47);
      uint32_t board_register_diff = board_register_tmp ^ board_register;
      board_register = board_register_tmp;

      if ((board_register_tmp & 0x01) !=  0x1) _SET_BIT(set_diagnostyka, ERROR_BA_1_FIX);
      else if (board_register_diff & 0x01)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BA_1_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x1;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) >> 8) != 0x11)  _SET_BIT(set_diagnostyka, ERROR_BA_1_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }
      
      if ((board_register_tmp & 0x02) !=  0x2) _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_FIX);
      else if (board_register_diff & 0x02)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BDVV5_1_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x2;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) & 0xff) != 0x25)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }

      if ((board_register_tmp & 0x04) !=  0x4) _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_FIX);
      else if (board_register_diff & 0x04)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BDVV5_2_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x4;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) >> 8) != 0x37)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }

//#if MODYFIKACIA_VERSII_PZ == 0
//      if ((board_register_tmp & 0x010) != 0x10) _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_FIX);
//      else if (board_register_diff & 0x10)
//      {
//        _SET_BIT(clear_diagnostyka, ERROR_BDV_DZ_FIX);
//        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x10;
//        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) != 0x14)  _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_CTLR);
//        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
//      }
//#endif
    }
    
    //Перевіряємо достовірність значень для аналогового реєстратора
    if (
        (state_ar_record  != STATE_AR_TEMPORARY_BLOCK) &&
        (changed_settings == CHANGED_ETAP_NONE       )  
       )   
    {
      //Перевірку здійснюємо тільки тоді, коли не іде зміна часових параметрів
      unsigned int size_one_ar_record_tmp = size_one_ar_record, max_number_records_ar_tmp = max_number_records_ar;
      if (
          ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG)
          ||  
          (size_one_ar_record_tmp != (sizeof(__HEADER_AR) + ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES_WITH_CALC + number_word_digital_part_ar)*sizeof(short int)))
          ||
          (
           !(
             (size_one_ar_record_tmp* max_number_records_ar_tmp      <= ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))) &&
             (size_one_ar_record_tmp*(max_number_records_ar_tmp + 1) >  ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2)))
            ) 
          ) 
         )
      {
        //Теоретично ця помилка ніколи не малаб реєструватися
        /*Якщо виникла така ситуація то треба зациклити ропаграму, щоб вона пішла на перезапуск - 
        бо відбулася недопустима незрозуміла помилка у розраховуваних параметрах аналогового реєстратора.
        Не зрозумілу чого вона виникла, коли і де, коректність роботи пригоамного забезпечення під питанням!*/
        total_error_sw_fixed(5);
      }
    }

    //Функції захистів
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //Перевірка на необхідність зроботи резервні копії даних для самоконтролю
    /***********************************************************/
    //Триґерна інформація
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_spi1_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли триґерна інформація успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис триґерної інформації, тому можна здійснити копіювання
          fix_active_buttons_ctrl = fix_active_buttons;
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_TRG_FUNC = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //Аналоговий реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_spi1_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //Дискретний реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_spi1_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //Виставляємо повідомлення про те, система захисів праціює
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//Вибір групи уставок
/*****************************************************/
void setpoints_selecting(unsigned int *p_active_functions, unsigned int act_inp_gr_ustavok) {
  unsigned int grupa_ustavok = 0;
  act_inp_gr_ustavok &= 0xf;
  if (current_settings_prt.grupa_ustavok < SETPOINT_GRUPA_USTAVOK_MIN ||
      current_settings_prt.grupa_ustavok > SETPOINT_GRUPA_USTAVOK_MAX) {
    //Неопределенная ошибка
    while (1);
  } else {
    grupa_ustavok = 1 << (current_settings_prt.grupa_ustavok - 1);
  }
  
  if (_CHECK_SET_BIT(p_active_functions, RANG_INVERS_DV_GRUPA_USTAVOK)) _SET_STATE(act_inp_gr_ustavok, 4);
  
  _AND2(grupa_ustavok, 0, act_inp_gr_ustavok, 4, grupa_ustavok, 4);
  _AND2(grupa_ustavok, 1, act_inp_gr_ustavok, 4, grupa_ustavok, 5);
  _AND2(grupa_ustavok, 2, act_inp_gr_ustavok, 4, grupa_ustavok, 6);
  _AND2(grupa_ustavok, 3, act_inp_gr_ustavok, 4, grupa_ustavok, 7);
  
  unsigned int tmp = gr_ustavok_tmp;
  do {
    _AND4(act_inp_gr_ustavok, 0, gr_ustavok_tmp, 1, gr_ustavok_tmp, 2, gr_ustavok_tmp, 3, act_inp_gr_ustavok, 5);
    _INVERTOR(act_inp_gr_ustavok, 5, tmp, 0);
    
    _AND4(tmp, 0, act_inp_gr_ustavok, 1, tmp, 2, tmp, 3, act_inp_gr_ustavok, 6);
    _INVERTOR(act_inp_gr_ustavok, 6, tmp, 1);
    
    _AND4(tmp, 0, tmp, 1, act_inp_gr_ustavok, 2, tmp, 3, act_inp_gr_ustavok, 7);
    _INVERTOR(act_inp_gr_ustavok, 7, tmp, 2);
    
    _AND4(tmp, 0, tmp, 1, tmp, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 8);
    _INVERTOR(act_inp_gr_ustavok, 8, tmp, 3);
    if (tmp == gr_ustavok_tmp) {
      break;
    }
    gr_ustavok_tmp = tmp;
  } while (1);
  
  _OR2(grupa_ustavok, 4, act_inp_gr_ustavok, 5, grupa_ustavok, 8);
  _OR2(grupa_ustavok, 5, act_inp_gr_ustavok, 6, grupa_ustavok, 9);
  _OR2(grupa_ustavok, 6, act_inp_gr_ustavok, 7, grupa_ustavok, 10);
  _OR2(grupa_ustavok, 7, act_inp_gr_ustavok, 8, grupa_ustavok, 11);
  
  if (_GET_OUTPUT_STATE(grupa_ustavok, 8)) 
    _SET_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 9))
    _SET_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 10))
      _SET_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 11))
      _SET_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
}
/*****************************************************/

/*****************************************************/

/*****************************************************/
//ОЗТ
/*****************************************************/
//void ozt_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
//{
//  UNUSED(p_active_functions);
//  UNUSED(number_group_stp);
//}
/*****************************************************/


/*****************************************************/
//Захист 3U0
/*****************************************************/
//void p_3U0_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
//{
//  UNUSED(p_active_functions);
//  UNUSED(number_group_stp);
//}
/*****************************************************/

/*****************************************************/
//Вн.Зовн.Пошкодження
/*****************************************************/
void kz_zv_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
}
/*****************************************************/

/*****************************************************/
//Газовий захист
/*****************************************************/
void gp_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
}
/*****************************************************/

/*****************************************************/
//Тепловий захист
/*****************************************************/
void tp_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
}
/*****************************************************/
