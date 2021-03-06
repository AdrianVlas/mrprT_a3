#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")
#define SRAM1_AR _Pragma("location=\"Analog_Registrator_Buffer\"")

typedef struct
{
  int current_level;                  //������� ����� �������������� ������
 
  int index_position;                 //����� �� ��� �� ����� � �������

  int position_cursor_x;              //X - ���������� �������
  int position_cursor_y;              //Y - ���������� �������
  
  unsigned int edition;               //0 - ���� ����� �� � ����� ����������;
                                      //1 - ���� ����� � ����� �����������;
                                      //2 - ���� ���� ������������ �����������
                                      //3 - � ���� �������� ����������� ��� ��, �� �� ��� �������� ����� ���� ����������� ������� �������������
  
  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
  
  unsigned int current_action;        //ĳ� ��� ����� �������� � ������� �������
                                      //0 - ͳ���� �� ����������
                                      //1 - ���������� ������, �/��� ������ ���� ���� �����������
                                      //2 - �������� �������� ����������

} __CURRENT_EKRAN;

typedef struct
{
  int position_cursor_x;              //X - ���������� �������

  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
} __PREVIOUS_STATE_CURSOR;

typedef struct
{
  //��� ��������
  unsigned int device_id;
  
  //��������� �����
  unsigned int type_of_input;                          //��� ����������� ����� 0 - ������, 1 - ���������
  unsigned int type_of_input_signal;                   //��� ������� ����������� ����� 0 - �������� , 1 - ������
  unsigned int dopusk_dv[NUMBER_INPUTS];              //������� ��
    
  unsigned int ranguvannja_inputs[N_SMALL*NUMBER_INPUTS]; //���������� ���������� �����
  unsigned int ranguvannja_outputs[N_BIG*NUMBER_OUTPUTS]; //���������� ���������� ������
  unsigned int ranguvannja_leds[N_BIG*NUMBER_LEDS];       //���������� �������������

  unsigned int ranguvannja_analog_registrator[N_BIG];     //���������� ����������� ����������
  unsigned int ranguvannja_digital_registrator[N_BIG];    //���������� ����������� ����������
  
  //���� ���������-��������� ��������
  unsigned int ranguvannja_off_cb[NUMBER_OFF_ON][N_BIG];  //���������� ����� ��������� �������� ��������
  unsigned int ranguvannja_on_cb[NUMBER_OFF_ON][N_BIG];   //���������� ����� ��������� �������� ��������
  
  //��� ���������� ������
  unsigned int type_of_output;                        //��� ���������� ������
                                                      //0 - ���������
                                                      //1 - ���������� (�������� ��� ����������)
  
  unsigned int type_of_output_modif;                  //��� ���������� ���������� ������
                                                      //0 - ���������� (��������)
                                                      //1 - ���������� (����������)
  
  //��� ��������������
  unsigned int type_of_led;                           //��� �������������
                                                      //0 - ����������
                                                      //1 - ���������
    
  unsigned int number_iteration_el;                                             //����������� ������� �������� ��� ��������� �����
//  unsigned int number_defined_df;                                               //ʳ������ ������������ ������� � ������������ �������
//  unsigned int number_defined_dt;                                               //ʳ������ ������������ ������� � ������������ �������
//  unsigned int number_defined_and;                                              //ʳ������ ������������ "�" � ������������ �������
//  unsigned int number_defined_or;                                               //ʳ������ ������������ "���" � ������������ �������
//  unsigned int number_defined_xor;                                              //ʳ������ ������������ "����.���" � ������������ �������
//  unsigned int number_defined_not;                                              //ʳ������ ������������ "��" � ������������ �������

  //������������� �������
  unsigned int type_df;                                                     //��� ������������� �������
                                                                            //0 - �����
                                                                            //1 - ��������
  int timeout_pause_df[NUMBER_DEFINED_FUNCTIONS];                           //��� �������� ���������� ������������� �������
  int timeout_work_df[NUMBER_DEFINED_FUNCTIONS];                            //��� ������ ������������� �������
  unsigned int ranguvannja_df_source_plus[N_BIG*NUMBER_DEFINED_FUNCTIONS];  //���������� ������ ������ ������������� �������
  unsigned int ranguvannja_df_source_minus[N_BIG*NUMBER_DEFINED_FUNCTIONS]; //���������� ��������� ������ ������������� �������
  unsigned int ranguvannja_df_source_blk[N_BIG*NUMBER_DEFINED_FUNCTIONS];   //���������� ������ ���������� ������������� �������

  unsigned int ranguvannja_set_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS];   //���������� ������ ������ ������������ �������������� ������
  unsigned int ranguvannja_set_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];  //���������� ��������� ������ ������������ �������������� ������
  unsigned int ranguvannja_reset_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS]; //���������� ������ ������ �������� �������������� ������
  unsigned int ranguvannja_reset_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];//���������� ��������� ������ �������� �������������� ������

  unsigned int ranguvannja_d_and[N_BIG*NUMBER_DEFINED_AND];                     //���������� ������ ������ ������������ "�"
  unsigned int ranguvannja_d_or[N_BIG*NUMBER_DEFINED_OR];                       //���������� ������ ������ ������������ "���"
  unsigned int ranguvannja_d_xor[N_BIG*NUMBER_DEFINED_XOR];                     //���������� ������ ������ ������������ "����.���"
  unsigned int ranguvannja_d_not[N_BIG*NUMBER_DEFINED_NOT];                     //���������� ������ ������ ������������ "��"
  
  uint32_t ranguvannja_tf[NUMBER_TRANSFER_FUNCTIONS];                           //���������� ������������� �������
  
  uint32_t buttons_mode;                                                        //������ ������ ��
                                                                                //0 - �������� ������
                                                                                //1 - ������������� ����
  unsigned int ranguvannja_buttons[N_SMALL*NUMBER_DEFINED_BUTTONS];             //���������� ������������ ������
  
  unsigned int configuration;         //������������ �������
  
  unsigned int grupa_ustavok;         //����� �������
                                      // 1 - ����� 1
                                      // 2 - ����� 2
                                      // 3 - ����� 3
                                      // 4 - ����� 4
  
  //���
  int32_t type_con_ozt;                                         //����� �'������ (0 - ����� 1; 1 - ����� 1; 2 - ����� 11)
  /*���.�����*/
  uint32_t pickup_ozt_Id0[NUMBER_GROUP_USTAVOK];                //������� Id0 (��������� ������������� ������)#5.3.29
  uint32_t pickup_ozt_delta_Id[NUMBER_GROUP_USTAVOK];           //�������  ������ I�.���. #5.3.20
  /*�����������*/
  uint32_t pickup_ozt_Kg1[NUMBER_GROUP_USTAVOK];                //������� k�1 (���������� ����������� ������ 1) #5.3.31
  uint32_t pickup_ozt_Kg2[NUMBER_GROUP_USTAVOK];                //������� k�2 (���������� ����������� ������ 2) #5.3.34
  uint32_t pickup_ozt_k[NUMBER_GROUP_USTAVOK];                  //������� k ����������� �������� ��� ���������� ������ �����������) #5.3.27
  uint32_t pickup_ozt_Ig0[NUMBER_GROUP_USTAVOK];                //������� I�0 (����� ����������� �����������) #5.3.32
  uint32_t pickup_ozt_Ig_obm[NUMBER_GROUP_USTAVOK];             //������� I�.��� (����� �������� � ������ 1 � ������ 2 �����������) #5.3.35
  /*���������� ��������*/
  uint32_t pickup_ozt_K_aI[NUMBER_GROUP_USTAVOK];                //������� ������� �������� ��� ���������� �������� (� �������� �� ��������, ����� x1000) #5.3.13
  uint32_t pickup_ozt_aI_kp[NUMBER_GROUP_USTAVOK];               //������� ���������� ���������� ��� ���������� �������� #5.3.18
  /*��������������*/
  uint32_t pickup_ozt_K_2I[NUMBER_GROUP_USTAVOK];                //������� ������� �������� ��� ����� ��������� (� �������� �� ��������, ����� x1000) #5.3.17
  uint32_t pickup_ozt_2I_kp[NUMBER_GROUP_USTAVOK];               //������� ���������� ���������� ��� ����� ��������� #5.3.22
  uint32_t pickup_ozt_K_5I[NUMBER_GROUP_USTAVOK];                //������� ������� �������� ��� �'��� ��������� (� �������� �� ��������, ����� x1000) #5.3.18
  uint32_t pickup_ozt_5I_kp[NUMBER_GROUP_USTAVOK];               //������� ���������� ���������� ��� �'��� ��������� #5.3.22
  /*���������� ����������*/
  uint32_t pickup_ozt_kp[NUMBER_GROUP_USTAVOK];                 //������� ���������� ���������� ��� ��� #5.3.44

  /*���������*/
  int32_t timeout_ozt1[NUMBER_GROUP_USTAVOK];                   //�������� "��� 䳿 ������� �������" #5.3.36
  int32_t timeout_ozt2[NUMBER_GROUP_USTAVOK];                   //�������� "��� 䳿 ������� �������" #5.3.37
  int32_t timeout_ozt2_a_blk[NUMBER_GROUP_USTAVOK];             //�������� "��� 䳿 ���������� ������� ������� �� ���������� ��������" #5.3.14

  uint32_t control_ozt;                                         //���� ��� ��������� ���
  
  //���
  int type_mtz1;                                                //��� ���1 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_1[NUMBER_GROUP_USTAVOK];            //������� ��� ����� ������� (������)
  unsigned int setpoint_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ����� ������� (����������:������)
  unsigned int setpoint_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ����� ������� (����������:�����)
  unsigned int setpoint_mtz_1_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ����� ������� (��� ��������)
           int setpoint_mtz_1_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������� (������� ���� ��������)
           int setpoint_mtz_1_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������� (����� ���� ��������)
  unsigned int setpoint_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ����� ������� (�� ������)
  unsigned int setpoint_mtz_1_U[NUMBER_GROUP_USTAVOK];          //������� ��� ����� ������� (������� �����)
  int type_mtz2;                                                //��� ���2 (0 - ������, 1 - ����������, 2 -  � ������ �� ������, 3 - ������� �, 4 - ������� �, 5 - ������� �)
  unsigned int setpoint_mtz_2[NUMBER_GROUP_USTAVOK];            //������� ��� ����� �������
  unsigned int setpoint_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ����� ������� (����������:������)
  unsigned int setpoint_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ����� ������� (����������:�����)
  unsigned int setpoint_mtz_2_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ����� ������� (��� ��������)
           int setpoint_mtz_2_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������� (������� ���� ��������)
           int setpoint_mtz_2_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������� (����� ���� ��������)
  unsigned int setpoint_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ����� ������� (�� ������)
  unsigned int setpoint_mtz_2_U[NUMBER_GROUP_USTAVOK];          //������� ��� ����� ������� (������� �����)
  int type_mtz3;                                                //��� ���3 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_3[NUMBER_GROUP_USTAVOK];            //������� ��� ������ �������
  unsigned int setpoint_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ������ ������� (����������:������)
  unsigned int setpoint_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ������ ������� (����������:�����)
  unsigned int setpoint_mtz_3_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ������ ������� (��� ��������)
           int setpoint_mtz_3_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ������ ������� (������� ���� ��������)
           int setpoint_mtz_3_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ������ ������� (����� ���� ��������)
  unsigned int setpoint_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ������ ������� (�� ������)
  unsigned int setpoint_mtz_3_U[NUMBER_GROUP_USTAVOK];          //������� ��� ������ ������� (������� �����)
  int type_mtz4;                                                //��� ���4 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_4[NUMBER_GROUP_USTAVOK];            //������� ��� �������� �������
  unsigned int setpoint_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� �������� ������� (����������:������)
  unsigned int setpoint_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� �������� ������� (����������:�����)
  unsigned int setpoint_mtz_4_angle[NUMBER_GROUP_USTAVOK];      //������� ��� �������� ������� (��� ��������)
           int setpoint_mtz_4_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� �������� ������� (������� ���� ��������)
           int setpoint_mtz_4_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� �������� ������� (����� ���� ��������)
  unsigned int setpoint_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� �������� ������� (�� ������)
  unsigned int setpoint_mtz_4_U[NUMBER_GROUP_USTAVOK];          //������� ��� �������� ������� (������� �����)

  int timeout_mtz_1[NUMBER_GROUP_USTAVOK];                      //�������� ��� ����� �������
  int timeout_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ����� ������� (����������:������)
  int timeout_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ����� ������� (����������:�����)
  int timeout_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ����� ������� (�� ������)
  int timeout_mtz_2[NUMBER_GROUP_USTAVOK];                      //�������� ��� ����� �������
  int timeout_mtz_2_pr[NUMBER_GROUP_USTAVOK];                   //�������� ����������� ��� ����� �������
  int timeout_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ����� ������� (����������:������)
  int timeout_mtz_2_n_vpered_pr[NUMBER_GROUP_USTAVOK];          //�������� ����������� ��� ����� ������� (����������:������)
  int timeout_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ����� ������� (����������:�����)
  int timeout_mtz_2_n_nazad_pr[NUMBER_GROUP_USTAVOK];           //�������� ����������� ��� ����� ������� (����������:�����)
  int timeout_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ����� ������� (�� ������)
  int timeout_mtz_2_po_napruzi_pr[NUMBER_GROUP_USTAVOK];        //�������� ����������� ��� ����� ������� (�� ������)
  int timeout_mtz_2_vvid_pr[NUMBER_GROUP_USTAVOK];              //�������� ����� ���������� ���2
  int timeout_mtz_3[NUMBER_GROUP_USTAVOK];                      //�������� ��� ������ �������
  int timeout_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ������ ������� (����������:������)
  int timeout_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ������ ������� (����������:�����)
  int timeout_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ������ ������� (�� ������)
  int timeout_mtz_4[NUMBER_GROUP_USTAVOK];                      //�������� ��� �������� �������
  int timeout_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ������ ������� (����������:������)
  int timeout_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ������ ������� (����������:�����)
  int timeout_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ������ ������� (�� ������)

  unsigned int control_mtz;                                     //���� ��� ��������� ���
  
  //3U0
  uint32_t setpoint_P_3U0[NUMBER_GROUP_USTAVOK];                //������� 3U0

  int32_t timeout_P_3U0[NUMBER_GROUP_USTAVOK];                  //�������� 3U0

  uint32_t control_P_3U0;                                       //���� ��� ��������� 3U0

  //����
  unsigned int setpoint_tznp_1_3I0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3I0 ����� ������� (����������:������)
  unsigned int setpoint_tznp_1_3U0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3U0 ����� �������  (����������:������)
  unsigned int setpoint_tznp_1_3I0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3I0 ����� ������� (����������:�����)
  unsigned int setpoint_tznp_1_3U0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3U0 ����� �������  (����������:�����)
  unsigned int setpoint_tznp_1_angle[NUMBER_GROUP_USTAVOK];     //������� ���� ����� ������� (��� ��������)
           int setpoint_tznp_1_angle_cos[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������� (������� ���� ��������)
           int setpoint_tznp_1_angle_sin[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������� (����� ���� ��������)
  unsigned int setpoint_tznp_2_3I0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3I0 ����� ������� (����������:������)
  unsigned int setpoint_tznp_2_3U0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3U0 ����� �������  (����������:������)
  unsigned int setpoint_tznp_2_3I0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3I0 ����� ������� (����������:�����)
  unsigned int setpoint_tznp_2_3U0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3U0 ����� �������  (����������:�����)
  unsigned int setpoint_tznp_2_angle[NUMBER_GROUP_USTAVOK];     //������� ���� ����� ������� (��� ��������)
           int setpoint_tznp_2_angle_cos[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������� (������� ���� ��������)
           int setpoint_tznp_2_angle_sin[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������� (����� ���� ��������)
  unsigned int setpoint_tznp_3_3I0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3I0 ������ ������� (����������:������)
  unsigned int setpoint_tznp_3_3U0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3U0 ������ �������  (����������:������)
  unsigned int setpoint_tznp_3_3I0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3I0 ������ ������� (����������:�����)
  unsigned int setpoint_tznp_3_3U0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3U0 ������ �������  (����������:�����)
  unsigned int setpoint_tznp_3_angle[NUMBER_GROUP_USTAVOK];     //������� ���� ����� ������ (��� ��������)
           int setpoint_tznp_3_angle_cos[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������ (������� ���� ��������)
           int setpoint_tznp_3_angle_sin[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������ (����� ���� ��������)
  unsigned int setpoint_tznp_4_3I0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3I0 ������ ������� (����������:������)
  unsigned int setpoint_tznp_4_3U0_vpered[NUMBER_GROUP_USTAVOK];//������� ���� 3U0 ������ �������  (����������:������)
  unsigned int setpoint_tznp_4_3I0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3I0 ������ ������� (����������:�����)
  unsigned int setpoint_tznp_4_3U0_nazad[NUMBER_GROUP_USTAVOK]; //������� ���� 3U0 ������ �������  (����������:�����)
  unsigned int setpoint_tznp_4_angle[NUMBER_GROUP_USTAVOK];     //������� ���� ����� ������ (��� ��������)
           int setpoint_tznp_4_angle_cos[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������ (������� ���� ��������)
           int setpoint_tznp_4_angle_sin[NUMBER_GROUP_USTAVOK]; //������� ���� ����� ������ (����� ���� ��������)

  int timeout_tznp_1_vpered[NUMBER_GROUP_USTAVOK];              //�������� ���� ����� ������� (����������:������)
  int timeout_tznp_1_nazad[NUMBER_GROUP_USTAVOK];               //�������� ���� ����� ������� (����������:�����)
  int timeout_tznp_2_vpered[NUMBER_GROUP_USTAVOK];              //�������� ���� ����� ������� (����������:������)
  int timeout_tznp_2_nazad[NUMBER_GROUP_USTAVOK];               //�������� ���� ����� ������� (����������:�����)
  int timeout_tznp_3_vpered[NUMBER_GROUP_USTAVOK];              //�������� ���� ������ ������� (����������:������)
  int timeout_tznp_3_nazad[NUMBER_GROUP_USTAVOK];               //�������� ���� ������ ������� (����������:�����)
  int timeout_tznp_4_vpered[NUMBER_GROUP_USTAVOK];              //�������� ���� �������� ������� (����������:������)
  int timeout_tznp_4_nazad[NUMBER_GROUP_USTAVOK];               //�������� ���� �������� ������� (����������:�����)

   unsigned int control_tznp;                                   //���� ��� ��������� ����
  
  //����
  unsigned int setpoint_urov[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];//������� ����
  int timeout_urov_1[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];        //�������� ���� ����� �������
  int timeout_urov_2[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];        //�������� ���� ����� �������
  unsigned int control_urov[NUMBER_PRVV];                       //���� ��� ��������� ����

  //���
  unsigned int setpoint_zop1[NUMBER_GROUP_USTAVOK];         //������� ���1
  unsigned int setpoint_zop2[NUMBER_GROUP_USTAVOK];         //������� ���2
  int timeout_zop1[NUMBER_GROUP_USTAVOK];                   //��������  ���1
  int timeout_zop2[NUMBER_GROUP_USTAVOK];                   //��������  ���2
  unsigned int control_zop;                                 //���� ��� ��������� ���

  //Umin
  unsigned int setpoint_Umin1[NUMBER_GROUP_USTAVOK];        //������� Umin1
  unsigned int setpoint_Umin1_Iblk[NUMBER_GROUP_USTAVOK];   //������� ���������� �� ������ Umin1
  unsigned int setpoint_Umin2[NUMBER_GROUP_USTAVOK];        //������� Umin2
  unsigned int setpoint_Umin2_Iblk[NUMBER_GROUP_USTAVOK];   //������� ���������� �� ������ Umin2
  int timeout_Umin1[NUMBER_GROUP_USTAVOK];                    //��������  Umin1
  int timeout_Umin2[NUMBER_GROUP_USTAVOK];                    //��������  Umin2
  unsigned int control_Umin;                                 //���� ��� ��������� Umin
  
  //Umax
  unsigned int setpoint_Umax1[NUMBER_GROUP_USTAVOK];        //������� Umax1
  unsigned int setpoint_Umax2[NUMBER_GROUP_USTAVOK];        //������� Umax2
  uint32_t setpoint_kp_Umax[NUMBER_GROUP_USTAVOK];          //������� ���������� ���������� ������
  int timeout_Umax1[NUMBER_GROUP_USTAVOK];                  //��������  Umax1
  int timeout_Umax2[NUMBER_GROUP_USTAVOK];                  //��������  Umax2
  unsigned int control_Umax;                                //���� ��� ��������� Umax

  //�� �/�
  unsigned int pickup_kz_zv[NUMBER_GROUP_USTAVOK];           //������� �� �/�
  unsigned int pickup_kz_zv_angle[NUMBER_GROUP_USTAVOK];     //������� ��� �� �/�
           int pickup_kz_zv_angle_cos_1[NUMBER_GROUP_USTAVOK]; //������� ������� ���� �� �/� (���� �����������)
           int pickup_kz_zv_angle_sin_1[NUMBER_GROUP_USTAVOK]; //������� ����� ���� �� �/� (���� �����������)
           int pickup_kz_zv_angle_cos_2[NUMBER_GROUP_USTAVOK]; //������� ������� ���� �� �/� (���� ����������)
           int pickup_kz_zv_angle_sin_2[NUMBER_GROUP_USTAVOK]; //������� ����� ���� �� �/� (���� ����������)
  unsigned int control_kz_zv;                                //���� ��� ��������� �� �/�
  
  //��
  int timeout_GP1[NUMBER_GROUP_USTAVOK];                     //��������  ��1
  int timeout_GP2[NUMBER_GROUP_USTAVOK];                     //��������  ��2
  int timeout_GP_RPN[NUMBER_GROUP_USTAVOK];                  //��������  ��-���
  unsigned int control_GP;                                   //���� ��� ��������� ��
  
  //��
  int timeout_TP[NUMBER_GROUP_USTAVOK];                      //��������  ��
  unsigned int control_TP;                                   //���� ��� ��������� ��
  
  //������������� ������
  int32_t setpoint_UP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];      //������� ��� ��� ��������
  uint32_t setpoint_UP_KP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];  //������� ��� "����������� ����������" ��� ��������
  int32_t timeout_UP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];       //�������� ��� �������������� �������
  uint32_t control_UP;                                          //���� ��� ���������
  int32_t ctrl_UP_input[NUMBER_UP];                             //���� ����� �������������� �������

  unsigned int TCurrent_H;              //���������� ������������� ��� �������������� ������ ������ �������
  unsigned int TCurrent_L;              //���������� ������������� ��� �������������� ������ ������ �������
  unsigned int TVoltage;                //���������� ������������� ��� �������������� ������
  uint32_t pickup_vyr_H;                //����������� � � ������� ����������� ������ ������� #5.3.3 
  uint32_t pickup_vyr_L;                //����������� � � ������� ����������� ������ �������  #5.3.3
  unsigned int control_transformator;   //������������ ��� ���� "�������������"
  
  unsigned int password1;                                       //������ ��� ����������� � ����
//  unsigned int password2;                                       //������ ��� ������� ��������� ���㳿 � ������� ��������
  unsigned int timeout_deactivation_password_interface_USB;     //��� ����������� ������ ��� ����������� � ���������� USB
  unsigned int password_interface_USB;                          //������ ��� ����������� � ���������� USB
  unsigned int timeout_deactivation_password_interface_RS485;   //��� ����������� ������ ��� ����������� � ���������� RS485
  unsigned int password_interface_RS485;                        //������ ��� ����������� � ���������� RS485
  
  unsigned int timeout_idle_new_settings;

  //�������
  int timeout_swch_on[NUMBER_OFF_ON];                          //�������� T ���.
  int timeout_swch_off[NUMBER_OFF_ON];                         //�������� T ����.
  int timeout_swch_udl_blk_on[NUMBER_OFF_ON];                  //�������� T "��������� ������� ���������� ���������"
  int timeout_pryvoda_VV[NUMBER_OFF_ON];                       //�������� T "������� ��"
  unsigned int control_switch[NUMBER_OFF_ON];                  //���� ��� ��������� ���������
  
  //���������� ���������
  unsigned int prefault_number_periods; //��� ����������� ������ (������� ������ ���������� �������)
  unsigned int postfault_number_periods;//��� ����������� ������ (������� ������ ���������� �������)

  //�����������
  unsigned int name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];//�'�� ������
  unsigned short int user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //������� �����������
  unsigned int address;                                //������
  int speed_RS485;                                    //�������� �����
                                                        // 0 - 9600
                                                        // 1 - 14400
                                                        // 2 - 19200
                                                        // 3 - 28800
                                                        // 4 - 38400
                                                        // 5 - 57600
                                                        // 6 - 115200
  int pare_bit_RS485;                                 //�������
                                                        // 0 - NONE
                                                        // 1 - ODD
                                                        // 2 - EVEN
  int number_stop_bit_RS485;                          //������� ����-��
                                                        // 0 - 1 stop-bit
                                                        // 1 - 2 stop-bits
  unsigned int time_out_1_RS485;                        //time-out ���������� ������� = X/10 �������
  
  int language;                                         //���� ����  0= ����� ��� �� �����������; 1=RU; 2=UA; 3=EN; 4=KZ; 5=��.
  
  unsigned int control_extra_settings_1;                //���� ��� ���������� �����������

  
  unsigned char time_setpoints[7+1];                     //��� �������� ��� �������-��������-���������
                                                         //�������� ���� ������ �������� ���� ����� ���� ���� ���������
                                                            //0 - ��������� ���������
                                                            //1 - ���������
                                                            //2 - USB
                                                            //3 - RS-485
  
  unsigned char time_ranguvannja[7+1];                    //��� �������� ��� ����������
                                                            //0 - ��������� ���������
                                                            //1 - ���������
                                                            //2 - USB
                                                            //3 - RS-485
} __SETTINGS;

typedef struct
{
  //���� �����
  int state_execution;        //-1 - ������� ������� �� ������� ����� ����������
                              // 0 - ���������� ����
                              // 1 - ���� ���������� ��� �������
                              // 2 - ���� ���������� � ���������
  
  
  //������������� ��������, � ���� ������������
  int device_id;              //-1 - ������� �� ����������
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //��� ��������
  int action;                 //-1 - �� ����������
                              // 0 - ����� ������ ��� ���������� ����������
                              // 1 - ����������
                              // 2 - ����� ������ � ����� �����
  

  //�������� ������ �� ��� ���� ��� ���������
  unsigned int internal_address;

  //ʳ������ ���� ��� �������/������ (��������)
  unsigned int number_bytes;
  
  //�������� �� ����� (��������)
  uint8_t *point_buffer;

} __DRIVER_I2C;

typedef struct
{
  unsigned int next_address;
  unsigned int saving_execution;
  unsigned int number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  unsigned int state_execution;     //���� ���������� �������������
  
  unsigned int code_operation;      //��� ���������� ��������

} __DRIVER_SPI_DF;

typedef struct
{
  unsigned char label_start_record;
  unsigned char time[7]; 
  unsigned int TCurrent_H;
  unsigned int TCurrent_L;
  unsigned int TVoltage;
  unsigned char name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];
} __HEADER_AR;

typedef enum _STATE_READING_ADCs {
STATE_READING_ADCs_NONE = 0,
STATE_READING_WRITE,
STATE_READING_WRITE_READ,
STATE_READING_READ
} STATE_READING_ADCs;

typedef enum _index_meas __index_meas;
typedef enum _index_energy __index_energy;

typedef struct
{
  uint32_t tick;
  unsigned int value;

} EXTENDED_OUTPUT_DATA;

typedef struct
{
  uint32_t tick;
  int value;
} EXTENDED_SAMPLE;

typedef struct
{
  unsigned int time_p;
  int data_p[NUMBER_ANALOG_CANALES_WITH_CALC];

  unsigned int time_c;
  int data_c[NUMBER_ANALOG_CANALES_WITH_CALC];
} ROZSHYRENA_VYBORKA;

typedef struct
{
  unsigned int time_stemp;
  unsigned int DATA_fix;
  int data [NUMBER_ANALOG_CANALES_WITH_CALC];
  unsigned int active_functions[N_BIG];
  int state_ar_record;
  
} DATA_FOR_OSCYLOGRAPH;


typedef struct 
{
  unsigned int x1;
  int y1;

  unsigned int x2;
  int y2;

} VYBORKA_XY;

typedef struct
{
  unsigned int Ua_x1;
  int Ua_y1;
  unsigned int Ua_x2;
  int Ua_y2;

  unsigned int Ub_x1;
  int Ub_y1;
  unsigned int Ub_x2;
  int Ub_y2;

  unsigned int Uc_x1;
  int Uc_y1;  
  unsigned int Uc_x2;
  int Uc_y2;  

  unsigned int U0_x1;
  int U0_y1;
  unsigned int U0_x2;
  int U0_y2;
} POPEREDNJY_PERECHID;

//typedef struct
//{
//  unsigned int present;
//  int start_index;
//  int stop_index;
//  int number_per_index;
//  int real_number;
//} EL_FILTER_STRUCT;

typedef enum _getting_data
{
  GET_DATA_FOR_EDITING = 0,
  GET_DATA_IMMEDITATE
} __getting_data;

typedef enum _setting_data
{
  SET_DATA_INTO_EDIT_TABLE = 0,
  SET_DATA_IMMEDITATE
} __settings_data;

typedef struct _vd
{
           int sign;
  unsigned int begin;
  unsigned int comma;
  unsigned int end;
  unsigned int u_begin;
  unsigned int u_end;
  const unsigned char *p_unit;
} __vd;

typedef struct _ctrl_info
{
  const uint8_t *information;
  unsigned int cursor_x;
} __ctrl_info;

typedef enum _index_I_U
{
  INDEX_I_H = 0,
  INDEX_I_L,
  INDEX_I_P_H,
  INDEX_I_P_L,
  INDEX_U,
  
  _NUMBER_FOR_I_U
} __index_I_U;

typedef enum _id_list
{
  ID_INPUT = 0,
  ID_OUTPUT,
  ID_LED,
  ID_DF,
  ID_DB,
  ID_DT,
  ID_AND,
  ID_OR,
  ID_XOR,
  ID_NOT,
  ID_TF,
  ID_PRVV,
  ID_OFF_ON,
    
  MAX_NUMBER_IN_ID_LIST
} __id_list;

#endif
