#ifndef __CONST_MESUREMENT__
#define __CONST_MESUREMENT__

#define USTUVANNJA_VAGA 12
#define DEFAULT_USTUVANNJA_VALUE ((1<<USTUVANNJA_VAGA) - 1)
#define AMPLITUDA_SECTOR_VAGA 7
#define AMPLITUDA_SECTOR      (1 << AMPLITUDA_SECTOR_VAGA)
#define AMPLITUDA_FI_VAGA     10
#define AMPLITUDA_FI          (1 << AMPLITUDA_FI_VAGA)

#define SECTOR1   10
#define POPRAVKA_NZZ  0/*-2*/
#define SECTOR2   5

#define SECTOR1_MTZ_TZNP   7
#define POPRAVKA_MTZ_TZNP  0/*3*/
#define SECTOR2_MTZ_TZNP   2

#define MEASUREMENT_TIM_FREQUENCY       60000000 //���

#define MAIN_FREQUENCY  50      //��
#define MIN_FREQUENCY   45      //��
#define MAX_FREQUENCY   55      //��

#define MIN_TICK_PERIOD (MEASUREMENT_TIM_FREQUENCY/MAX_FREQUENCY - 1)
#define MAX_TICK_PERIOD (MEASUREMENT_TIM_FREQUENCY/MIN_FREQUENCY + 1)

#define NUMBER_ADCs                     2
#define NUMBER_CANALs_ADC               16
#define NUMBER_INPUTs_ADCs              (NUMBER_ADCs*NUMBER_CANALs_ADC)

#define VAGA_NUMBER_POINT                5
#define NUMBER_POINT                     (1 << VAGA_NUMBER_POINT)

#define NUMBER_PERIOD_TRANSMIT           10

/*
����������, ���� ���������� ����� � ��� � ��
          K*2500
Koef = ------------
        R*1*0xFFF
��:
K - ���������� ������������� � �� ����� 2500 ��� ������ ������
2500 - ����������� �������� ������� � ���������, ��� ���� ���������� ��� (� ��� �� � 2,5 � = 2500 ��)
R - ��������, ���� ���������� ��������������� ����� � �������. ����� ����� 12,7 ��
1 - ���� ������������ ������ � ������� �� ����� ��� ������� ��������� ����� ��������� �� ������������ ���������� � ������������ ��������� "1"
0xFFF - ����������� �����, ��� ���� ������ ���

Koef = 24,035457106323248055531520098449 ��� 3I0 (1538/64 = 24,03125)
Koef = 120,17728553161624027765760049225 ��� ������ ������ (7691/64 = 120,171875) 

�������� �� �� ����������� ���������� ������� ��� � ��
*/
#define MNOGNYK_I                     7691           
#define VAGA_DILENNJA_I               6
#define MNOGNYK_I_DIJUCHE             5439//6451          
#define VAGA_DILENNJA_I_DIJUCHE       6
#define MNOGNYK_I_DIJUCHE_DOUBLE       84.984375


/*
����������, ���� ���������� ����� � ��� � �B
          Ku*2500*R1
Koef = --------------
        R2*1*0xFFF
��:
Ku - ���������� ������������� � �� ����� 1
2500 - ����������� �������� ������� � ���������, ��� ���� ���������� ��� (� ��� �� � 2,5 � = 2500 ��)
R1 -  ��������, ���� ������� ����� � �������� ������� ��������������� ������. ����� ����� 86.5(75) ���
R2 - ��������, ���� ���������� ��������������� ����� � �������. ����� ����� 499 ��
1 - ���� ������������ ������ � ������� �� ����� ��� ������� ��������� ����� ��������� �� ������������ ���������� � ������������ ��������� "1"
0xFFF - ����������� �����, ��� ���� ������ ���

Koef = 105.82826214088739138839339240141 (6773/64 = 105.828125)

�������� �� �� ����������� ���������� ������� ��� � ��

��� ���� �� ��������� ���������� � ��������� ������������ ���'�, �� ����������� � �������� 1-�  ������� (��� ����� �������. ���� ���������� �� ���� �� ���)
���� ��� ����� ����������� ����� �� ������� �� ����� � ����.
��� �������� ������� ������������ ����������, �� � ����������� Koef_1 = Koef/sqrt(2)

Koef_1 = 74.831881801009052122160116719483 (4790/64 = 74.84375)
*/
#define MNOGNYK_U                     6773           
#define VAGA_DILENNJA_U               6
#define MNOGNYK_U_DIJUCHE             4790           
#define VAGA_DILENNJA_U_DIJUCHE       6
#define MNOGNYK_U_DIJUCHE_DOUBLE      74.831881801009052122160116719483

/*
��� ����� � �������������� �� �������� � ������� ��� � �������� ��������� � 16 ���
��� �������� ��(��) ����� ��������� ������������ ��������� �� ��������� ������������ ����������
      
��� ���������� ����� ������� ����������������� ���� (MNOGNYK_U_DIJUCHE; VAGA_DILENNJA_U_DIJUCHE)
� (MNOGNYK_I_DIJUCHE; VAGA_DILENNJA_I_DIJUCHE)
      
��� ������������ ����� � ��(��)
            ��
��� ����� -- �� �������� ��������� ��.
            �� 
      
�� ������ �������� ����� � ������� �� ���. ��� ��������� ����� ��������� �� 1000

����������� � ����� 880,67659496230924802353373781945
��� �� ���������� ����������� ��� ������� � ������ long long, �� � ��������� � ����� � ������ long long
*/
#define MNOGNYK_R_FLOAT                 880.67659496230924802353373781945f


#define MAX_INDEX_DATA_FOR_OSCYLOGRAPH  10

#define GND_NORMAL_VALUE                0x0
#define VREF_NORMAL_VALUE               0x800
#define VDD_NORMAL_VALUE                0xb00

//������
#define C_GND_ADC1_1            0
#define C_VDD_ADC1_1            1
#define C_GND_ADC1_2            2
#define C_GND_ADC1_3            3
#define C_GND_ADC1_4            4
#define C_GND_ADC1_5            5
#define C_GND_ADC1_6            6
#define C_GND_ADC1_7            7
#define C_GND_ADC1_8            8
#define C_Uc_16                 9
#define C_Uc_1                  10
#define C_VREF_ADC1_1           11
#define C_Ub_1                  12
#define C_Ub_16                 13
#define C_Ua_1                  14
#define C_Ua_16                 15
#define C_GND_ADC2_1            (0  + NUMBER_CANALs_ADC)
#define C_VDD_ADC2_1            (1  + NUMBER_CANALs_ADC)
#define C_Ic_H_1                (2  + NUMBER_CANALs_ADC)
#define C_Ic_H_16               (3  + NUMBER_CANALs_ADC)
#define C_Ib_H_1                (4  + NUMBER_CANALs_ADC)
#define C_Ib_H_16               (5  + NUMBER_CANALs_ADC)
#define C_GND_ADC2_2            (6  + NUMBER_CANALs_ADC)
#define C_Ia_H_1                (7  + NUMBER_CANALs_ADC)
#define C_Ia_H_16               (8  + NUMBER_CANALs_ADC)
#define C_Ic_L_1                (9  + NUMBER_CANALs_ADC)
#define C_Ic_L_16               (10 + NUMBER_CANALs_ADC)
#define C_VREF_ADC2_1           (11 + NUMBER_CANALs_ADC)
#define C_Ib_L_16               (12 + NUMBER_CANALs_ADC)
#define C_Ib_L_1                (13 + NUMBER_CANALs_ADC)
#define C_Ia_L_1                (14 + NUMBER_CANALs_ADC)
#define C_Ia_L_16               (15 + NUMBER_CANALs_ADC)

#define READ_Ua  (                     \
                  (1 << C_Ua_1   ) |   \
                  (1 << C_Ua_16  )     \
                 )

#define READ_Ub  (                     \
                  (1 << C_Ub_1   ) |   \
                  (1 << C_Ub_16  )     \
                       )

#define READ_Uc  (                     \
                  (1 << C_Uc_1   ) |   \
                  (1 << C_Uc_16  )     \
                 )

#define READ_I   (                       \
                  (1 << C_Ia_H_1   ) |   \
                  (1 << C_Ia_H_16  ) |   \
                  (1 << C_Ib_H_1   ) |   \
                  (1 << C_Ib_H_16  ) |   \
                  (1 << C_Ic_H_1   ) |   \
                  (1 << C_Ic_H_16  ) |   \
                  (1 << C_Ia_L_1   ) |   \
    (unsigned int)(1 << C_Ia_L_16  ) |   \
                  (1 << C_Ib_L_1   ) |   \
                  (1 << C_Ib_L_16  ) |   \
                  (1 << C_Ic_L_1   ) |   \
                  (1 << C_Ic_L_16  )     \
                 )

#define READ_DATA_VAL  (          \
                        READ_I  | \
                        READ_Ua | \
                        READ_Ub | \
                        READ_Uc   \
                      )

#define READ_TEST_VAL  (                                   \
                        (1 << C_GND_ADC1_1)              | \
                        (1 << C_GND_ADC1_2)              | \
                        (1 << C_GND_ADC1_3)              | \
                        (1 << C_GND_ADC1_4)              | \
                        (1 << C_GND_ADC1_5)              | \
                        (1 << C_GND_ADC1_6)              | \
                        (1 << C_GND_ADC1_7)              | \
                        (1 << C_GND_ADC1_8)              | \
                        (1 << C_VREF_ADC1_1)             | \
                        (1 << C_VDD_ADC1_1)              | \
                        (1 << C_GND_ADC2_1)              | \
                        (1 << C_GND_ADC2_2)              | \
                        (1 << C_VREF_ADC2_1)             | \
                        (1 << C_VDD_ADC2_1)                \
                       )

#define DATA_VAL_READ_BIT       0
#define DATA_VAL_READ           (1 << DATA_VAL_READ_BIT)
#define TEST_VAL_READ_BIT       1
#define TEST_VAL_READ           (1 << TEST_VAL_READ_BIT)

#define NUMBER_GND_ADC1         8
#define NUMBER_GND_ADC2         2

#define NUMBER_VREF_ADC1        1
#define NUMBER_VREF_ADC2        1

#define NUMBER_VDD_ADC1         1
#define NUMBER_VDD_ADC2         1

#define I_Ia_H          0
#define I_Ib_H          1
#define I_Ic_H          2
#define I_Ia_L          3
#define I_Ib_L          4
#define I_Ic_L          5
#define I_Ua            6
#define I_Ub            7
#define I_Uc            8

enum _index_meas
{
  IM_IA_H,
  IM_IB_H,
  IM_IC_H,
  IM_IA_L,
  IM_IB_L,
  IM_IC_L,
  IM_UA,
  IM_UB,
  IM_UC,
  IM_IA_P_H,
  IM_IB_P_H,
  IM_IC_P_H,
  IM_IA_P_L,
  IM_IB_P_L,
  IM_IC_P_L,
  IM_adIA,
  IM_adIB,
  IM_adIC,
  IM_dIA,
  IM_dIB,
  IM_dIC,
  IM_2dIA,
  IM_2dIB,
  IM_2dIC,
  IM_5dIA,
  IM_5dIB,
  IM_5dIC,
  IM_gdIA,
  IM_gdIB,
  IM_gdIC,
  IM_3I0_r_H,
  IM_I2_H,
  IM_I1_H,
  IM_I2_P_H,
  IM_I1_P_H,
  IM_3I0_r_L,
  IM_I2_L,
  IM_I1_L,
  IM_I2_P_L,
  IM_I1_P_L,
  IM_UAB,
  IM_UBC,
  IM_UCA,
  IM_3U0_r,
  IM_U2,
  IM_U1,

  _NUMBER_IM
};

#define PORIG_FOR_FAPCH 10000

/*****************************************/
//��������� ��� ������ �������� �� ��1 � ��2
/*****************************************/
enum _PhK
{
INDEX_PhK_UA = 0,
INDEX_PhK_UB,
INDEX_PhK_UC,

MAX_INDEX_PhK
};
/*****************************************/

enum _full_ort_index
{
FULL_ORT_Ua = 0,
FULL_ORT_Ub,
FULL_ORT_Uc,
FULL_ORT_Uab,
FULL_ORT_Ubc,
FULL_ORT_Uca,
FULL_ORT_3U0_r,
FULL_ORT_U2,
FULL_ORT_U1,
FULL_ORT_Ia_H,
FULL_ORT_Ib_H,
FULL_ORT_Ic_H,
FULL_ORT_3I0_r_H,
FULL_ORT_I2_H,
FULL_ORT_I1_H,
FULL_ORT_Ia_L,
FULL_ORT_Ib_L,
FULL_ORT_Ic_L,
FULL_ORT_3I0_r_L,
FULL_ORT_I2_L,
FULL_ORT_I1_L,

FULL_ORT_MAX
};

#define UNDEF_PHI                              (1 << 31)

#endif
