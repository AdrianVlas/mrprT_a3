#include "header.h"

int ekranListIndex_control_urov1=0;//������ ��������� ������ control urov
int ekranListIndex_control_urov2=0;//������ ��������� ������ control urov

int validAction_urov(int poz);

/*****************************************************/
//������� ����� ����������� ������� ����
/*****************************************************/
void make_ekran_setpoint_urov(uint32_t prvv, unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_UROV][MAX_COL_LCD] = 
  {
    {
      "  ������� ����  "
    },
    {
      "  ������� ����  "
    },
    {
      "   CBFP Pickup  "
    },
    {
      "  ������� ����  "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    unsigned int view = ((current_ekran.edition == 0) || (position_temp != index_of_ekran_tmp));
    if (index_of_ekran_tmp < MAX_ROW_FOR_SETPOINT_UROV)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][14] = 0x31;
        if(prvv) working_ekran[i][14] = 0x32;

        vaga = 1000; //������������ ������� ���������� ��� �������� �������� ������� ��� ������� ����
        if (view == true) value = current_settings.setpoint_urov[prvv][group]; //� ����� value ������� �������� ������� ��
        else value = edition_settings.setpoint_urov[prvv][group];
        first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (
              ((j < COL_SETPOINT_UROV_BEGIN) ||  (j > COL_SETPOINT_UROV_END )) &&
              (j != (COL_SETPOINT_UROV_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_SETPOINT_UROV_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_SETPOINT_UROV_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_UROV_COMMA, view, 0);
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    current_ekran.position_cursor_x = COL_SETPOINT_UROV_BEGIN;
    int last_position_cursor_x = COL_SETPOINT_UROV_END;

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����
/*****************************************************/
void make_ekran_timeout_urov(uint32_t prvv, unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_UROV][MAX_COL_LCD] = 
  {
    {
      " 1 ������� ���� ",
      " 2 ������� ���� "
    },
    {
      " 1 ������ ���� ",
      " 2 ������ ���� "
    },
    {
      "   1 Stage CBFP ",
      "   2 Stage CBFP "
    },
    {
      " 1 ������� ���� ",
      " 2 ������� ���� "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    unsigned int view = ((current_ekran.edition == 0) || (position_temp != index_of_ekran_tmp));
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_UROV)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][15] = 0x31;
        if(prvv) working_ekran[i][15] = 0x32;
        if (index_of_ekran_tmp == INDEX_ML_TMOUROV1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� 1 ������ ����
          if (view == true) value = current_settings.timeout_urov_1[prvv][group]; //� ����� value ������� �������� �������� 1 ������ ����
          else value = edition_settings.timeout_urov_1[prvv][group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOUROV2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� 2 ������ ����
          if (view == true) value = current_settings.timeout_urov_2[prvv][group]; //� ����� value ������� �������� �������� 2 ������ ����
          else value = edition_settings.timeout_urov_2[prvv][group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (index_of_ekran_tmp == INDEX_ML_TMOUROV1)
          {
            if (
                ((j < COL_TMO_UROV_1_BEGIN) ||  (j > COL_TMO_UROV_1_END )) &&
                (j != (COL_TMO_UROV_1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_UROV_1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_UROV_1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_UROV_1_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOUROV2)
          {
            if (
                ((j < COL_TMO_UROV_2_BEGIN) ||  (j > COL_TMO_UROV_2_END )) &&
                (j != (COL_TMO_UROV_2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_UROV_2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_UROV_2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_UROV_2_COMMA, view, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOUROV1)
    {
      current_ekran.position_cursor_x = COL_TMO_UROV_1_BEGIN;
      last_position_cursor_x = COL_TMO_UROV_1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOUROV2)
    {
      current_ekran.position_cursor_x = COL_TMO_UROV_2_BEGIN;
      last_position_cursor_x = COL_TMO_UROV_2_END;
    }

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����������� ���������� ��� ����
/*****************************************************/
void make_ekran_control_urov(uint32_t prvv)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_UROV - NUMBER_UP + 1][MAX_COL_LCD] = 
  {
    {
      "      ����      ",
      "  ����� I ����  ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���3  ",
      "  ���� �� ���4  ",
      "  ���� �� 3U0   ",
      " ���� �� ����1  ",
      " ���� �� ����2  ",
      " ���� �� ����3  ",
      " ���� �� ����4  ",
      " ���� �� ���1   ",
      " ���� �� ���2   ",
      " ���� �� �����1 ",
      " ���� �� �����2 ",
      " ���� �� ������1",
      " ���� �� ������2",
      "  ���� �� ��1   ",
      "  ���� �� ��2   ",
      " ���� �� ��-��� ",
      "   ���� �� ��   ",
      "  ���� �� ��x   "
    },
    {
      "      ����      ",
      "  ���� I ����  ",
      " ���� �� ���1  ",
      " ���� �� ���2  ",
      " ���� �� ���1  ",
      " ���� �� ���2  ",
      " ���� �� ���3  ",
      " ���� �� ���4  ",
      "  ���� �� 3U0  ",
      " ���� �� ����1 ",
      " ���� �� ����2 ",
      " ���� �� ����3 ",
      " ���� �� ����4 ",
      " �.�� ���1     ",
      " �.�� ���2     ",
      " ���� �� ����1",
      " ���� �� ����2",
      "���� �� ������1",
      "���� �� ������2",
      "  ���� �� ��1  ",
      "  ���� �� ��2  ",
      " ���� �� ��-���",
      "   ���� �� ��  ",
      "  ���� �� ��x  "
    },
    {
      "      CBFP      ",
      "  Select I CBFP ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      " Start from OCP1",
      " Start from OCP2",
      " Start from OCP3",
      " Start from OCP4",
      " Start from 3U0 ",
      " ���� �� ����1  ",
      " ���� �� ����2  ",
      " ���� �� ����3  ",
      " ���� �� ����4  ",
      "Start from NPSP1",
      "Start from NPSP2",
      "Start from Umin1",
      "Start from Umin2",
      "Start from Umax1",
      "Start from Umax2",
      "  ���� �� ��1   ",
      "  ���� �� ��2   ",
      " ���� �� ��-��� ",
      "   ���� �� ��   ",
      "  ���� �� ��x   "
    },
    {
      "      ����      ",
      "  ����� I ����  ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���3  ",
      "  ���� �� ���4  ",
      "  ���� �� 3U0   ",
      " ���� �� ����1  ",
      " ���� �� ����2  ",
      " ���� �� ����3  ",
      " ���� �� ����4  ",
      " ���� �� ���1   ",
      " ���� �� ���2   ",
      " ���� �� �����1 ",
      " ���� �� �����2 ",
      " ���� �� ������1",
      " ���� �� ������2",
      "  ���� �� ��1   ",
      "  ���� �� ��2   ",
      " ���� �� ��-��� ",
      "   ���� �� ��   ",
      "  ���� �� ��x   "
    }
  };
  const uint32_t index_number_UP[MAX_NAMBER_LANGUAGE] = {12, 13, 12, 12};
  int index_language = index_language_in_array(current_settings.language);
  
  int ekranListIndex_control_urov = ekranListIndex_control_urov1;
  if(prvv) ekranListIndex_control_urov = ekranListIndex_control_urov2;
  current_ekran.index_position = findMenuListIndex_control_urov(ekranListIndex_control_urov);//real menuIndex
  int next_menuIndex = findMenuListIndex_control_urov(ekranListIndex_control_urov+1);//next menuIndex
  int old_menuIndex  = findMenuListIndex_control_urov(ekranListIndex_control_urov-1);//old menuIndex
  int index_of_ekran_tmp = -1;
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
      if (i==0 || i==2)
      {
       if(ekranListIndex_control_urov&1)
        {
         if(i==0) index_of_ekran_tmp = old_menuIndex;
         if(i==2) index_of_ekran_tmp = current_ekran.index_position;
         current_ekran.position_cursor_y =3;
        }//if
       else {
         if(i==0) index_of_ekran_tmp = current_ekran.index_position;
         if(i==2) index_of_ekran_tmp = next_menuIndex;
         current_ekran.position_cursor_y =1;
       }//if
        if(index_of_ekran_tmp<0)
             for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
        //�������� ���������
        else {
          //� ��������� ����� ����� �������� ���������
          if(index_of_ekran_tmp>=INDEX_ML_CTRUROV_STARTED_FROM_UP1) {
             for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][INDEX_ML_CTRUROV_STARTED_FROM_UP1][j];
             working_ekran[i][index_number_UP[index_language]] = 0x31+index_of_ekran_tmp - INDEX_ML_CTRUROV_STARTED_FROM_UP1;
          }//if
          else for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
          if(index_of_ekran_tmp==INDEX_ML_CTRUROV_STATE) working_ekran[i][10] = 0x31+prvv;
        }//�������� ���������
      }//if (i==0 || i==2)
      else
      {
        //� ������� ����� ����� �������� �������� �������
        const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"     ����.      ", "      ���.      "},
          {"     ����.      ", "     ����.     "},
          {"      Off       ", "       On       "},
          {"     њ��.      ", "     ����.      "}
        };
        const unsigned char hi_low_voltage[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"       ��       ", "       ��       "},
          {"       ��       ", "       ��       "},
          {"       HV       ", "       LV       "},
          {"       ��       ", "       ��       "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
        {
         {4, 5},
         {4, 4},
         {5, 6},
         {4, 4}
        };
        if(index_of_ekran_tmp<0) {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
          break;
        }//if
        
        unsigned int index_ctr = index_of_ekran_tmp;
        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_urov[prvv];
        else temp_data = edition_settings.control_urov[prvv];

        if(index_of_ekran_tmp==INDEX_ML_CTRUROV_SEL_I) {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = hi_low_voltage[index_language][(temp_data >> index_ctr) & 0x1][j];
          if (index_of_ekran_tmp == current_ekran.index_position) 
                                    current_ekran.position_cursor_x = 6;
        }//if
        else {
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
         if (index_of_ekran_tmp == current_ekran.index_position) 
                                    current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
       }//else
      }
  }

  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}

int validAction_urov(int poz)
{
  if((current_settings.configuration & (1<<OZT_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_OZT1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_OZT2) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<P_3U0_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_P_3U0) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<TZNP_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP2) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP3) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP4) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_ZOP2) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<GP_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP1) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP2) return -1;//������ �������
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP_RPN) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<TP_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TP) return -1;//������ �������
  }//if
  if((current_settings.configuration & (1<<UP_BIT_CONFIGURATION)) == 0)
  {//��� config
     if(poz >= INDEX_ML_CTRUROV_STARTED_FROM_UP1) return -1;//������ �������
  }//if
  return 1;
}//validAction_urov(int poz)

int normalizEkranIndex_control_urov()
{
//������������ ��������� �������
  if(validAction_urov(current_ekran.index_position)<0) current_ekran.index_position = INDEX_ML_CTRUROV_STATE;
  int ekranIndex = findEkranListIndex_control_urov(current_ekran.index_position);//����� �������� ���e��
  if(ekranIndex<0) return 0;//���-�� ����� �� ���
  return ekranIndex;
}//normalizEkranIndex_control_urov()

int findMenuListIndex_control_urov(int ekranListIndex)
{
//����� ���e�� ���� control �� ��������� �������
  int index = -1;
  if(ekranListIndex<0) return -1;
  for(int i=0; i< MAX_ROW_FOR_CONTROL_UROV; i++)
  {
    if(validAction_urov(i)>0) index++;
    if(index==ekranListIndex) return i;
  }//for
  return -1;//�� �������
}//findMenuListIndex_control_urov(int ekranListIndex)
int findEkranListIndex_control_urov(int menuListIndex)
{
//����� �������� ���e�� ��  ������� ���� control 
  if(menuListIndex<0) return -1;
  int ekranListSize = findEkranListSize_control_urov();
  for(int i=0; i< ekranListSize; i++)
  {
   if(findMenuListIndex_control_urov(i)!=menuListIndex) continue;
   return i;
  }//for
  return -1;//�� �������
}//findEkranListIndex_control_urov(int menuListIndex)

int findEkranListSize_control_urov(void)
{
//����� ������ ��������� ����
  int size = 0;
  for(int i=0; i< MAX_ROW_FOR_CONTROL_UROV; i++)
  {
    if(validAction_urov(i)>0) size++;
  }//for
  return size;
}

/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
