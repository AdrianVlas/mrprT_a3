#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ���
/*****************************************************/
void make_ekran_setpoint_zop(unsigned int group)
{
 const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_ZOP][MAX_COL_LCD] = 
  {
    {
      "  ������� ���1  ",
      "  ������� ���2  "
    },
    {
      "  ������� ���1  ",
      "  ������� ���2  "
    },
    {
      "  NPSP1 Pickup  ",
      "  NPSP2 Pickup  "
    },
    {
      "  ������� ���1  ",
      "  ������� ���2  "
    }
  };
  const unsigned char symbols[MAX_NAMBER_LANGUAGE][3] = {"��.", "��.", "u  ", "��."};
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_SETPOINT_ZOP)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];

        if (index_of_ekran_tmp == INDEX_ML_STPZOP1)
        {
        vaga = 1000; //������������ ������� ���������� ��� �������� �������� ������� ��� ������� ����
        if (view == true) value = current_settings.setpoint_zop1[group]; //� ����� value ������� �������� ������� ����
        else value = edition_settings.setpoint_zop1[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_STPZOP2)
        {
        vaga = 1000; //������������ ������� ���������� ��� �������� �������� ������� ��� ������� ����
        if (view == true) value = current_settings.setpoint_zop2[group]; //� ����� value ������� �������� ������� ����
        else value = edition_settings.setpoint_zop2[group];
        }

        first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
         if (index_of_ekran_tmp == INDEX_ML_STPZOP1)
         {
          if (
              ((j < COL_SETPOINT_ZOP1_BEGIN) ||  (j > COL_SETPOINT_ZOP1_END )) &&
              (
               !((j >= (COL_SETPOINT_ZOP1_END + 2)) && (j <= (COL_SETPOINT_ZOP1_END + 4)))
              )    
             )working_ekran[i][j] = ' ';
          else if (j == COL_SETPOINT_ZOP1_COMMA )working_ekran[i][j] = ',';
          else if ((j >= (COL_SETPOINT_ZOP1_END + 2)) && (j <= (COL_SETPOINT_ZOP1_END + 4)))
            working_ekran[i][j] = symbols[index_language][j - (COL_SETPOINT_ZOP1_END + 2)];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_ZOP1_COMMA, view, 0);
         }
         else if (index_of_ekran_tmp == INDEX_ML_STPZOP2)
         {
          if (
              ((j < COL_SETPOINT_ZOP2_BEGIN) ||  (j > COL_SETPOINT_ZOP2_END )) &&
              (
               !((j >= (COL_SETPOINT_ZOP2_END + 2)) && (j <= (COL_SETPOINT_ZOP2_END + 4)))
              )    
             )working_ekran[i][j] = ' ';
          else if (j == COL_SETPOINT_ZOP2_COMMA )working_ekran[i][j] = ',';
          else if ((j >= (COL_SETPOINT_ZOP2_END + 2)) && (j <= (COL_SETPOINT_ZOP2_END + 4)))
            working_ekran[i][j] = symbols[index_language][j - (COL_SETPOINT_ZOP2_END + 2)];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_ZOP2_COMMA, view, 0);
         }
        }//for
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
    current_ekran.position_cursor_x = COL_SETPOINT_ZOP1_BEGIN;
    int last_position_cursor_x = COL_SETPOINT_ZOP1_END;

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
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ���(���)
/*****************************************************/
void make_ekran_timeout_zop(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_ZOP][MAX_COL_LCD] = 
  {
    {
      " �������� ���1  ",
      " �������� ���2  "
    },
    {
      " �������� ���1  ",
      " �������� ���2  "
    },
    {
      "   NPSP1 Delay  ",
      "   NPSP2 Delay  "
    },
    {
      " �������� ���1  ",
      " �������� ���2  "
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_ZOP)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];

        if (index_of_ekran_tmp == INDEX_ML_TMOZOP1)
        {
        vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� ���(���)
        if (view == true) value = current_settings.timeout_zop1[group]; //� ����� value ������� �������� �������� ���(���)
        else value = edition_settings.timeout_zop1[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOZOP2)
        {
        vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� ���(���)
        if (view == true) value = current_settings.timeout_zop2[group]; //� ����� value ������� �������� �������� ���(���)
        else value = edition_settings.timeout_zop2[group];
        }

        first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
         if (index_of_ekran_tmp == INDEX_ML_TMOZOP1)
         {
          if (
              ((j < COL_TMO_ZOP1_BEGIN) ||  (j > COL_TMO_ZOP1_END )) &&
              (j != (COL_TMO_ZOP1_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_TMO_ZOP1_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_TMO_ZOP1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_ZOP1_COMMA, view, 0);
         }
         else if (index_of_ekran_tmp == INDEX_ML_TMOZOP2)
         {
          if (
              ((j < COL_TMO_ZOP2_BEGIN) ||  (j > COL_TMO_ZOP2_END )) &&
              (j != (COL_TMO_ZOP2_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_TMO_ZOP2_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_TMO_ZOP2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_ZOP2_COMMA, view, 0);
         }
        }//for
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
    current_ekran.position_cursor_x = COL_TMO_ZOP1_BEGIN;
    int last_position_cursor_x = COL_TMO_ZOP1_END;

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
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����������� ���������� ��� ���(���)
/*****************************************************/
void make_ekran_control_zop()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_ZOP][MAX_COL_LCD] = 
  {
    {
      "      ���1      ",
      "  ����� I ���1  ",
      "      ���2      ",
      "  ����� I ���2  "
    },
    {
      "      ���1      ",
      "  ���� I ���1  ",
      "      ���2      ",
      "  ���� I ���2  "
    },
    {
      "     NPSP1      ",
      " Select I NPSP1 ",
      "     NPSP2      ",
      " Select I NPSP2 "
    },
    {
      "      ���1      ",
      "  ����� I ���1  ",
      "      ���2      ",
      "  ����� I ���2  "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_ZOP)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
      }
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
        
        unsigned int index_ctr = index_of_ekran_tmp;

        unsigned int temp_data;
          
        if(current_ekran.edition == 0) temp_data = current_settings.control_zop;
        else temp_data = edition_settings.control_zop;
          
//        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
//        if (position_temp == index_of_ekran_tmp) current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
        if(index_of_ekran_tmp==INDEX_ML_CTRZOP_1_SEL_I || index_of_ekran_tmp==INDEX_ML_CTRZOP_2_SEL_I) {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = hi_low_voltage[index_language][(temp_data >> index_ctr) & 0x1][j];
          if (position_temp == index_of_ekran_tmp)
                                    current_ekran.position_cursor_x = 6;
        }//if
        else {
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
         if (position_temp == index_of_ekran_tmp)
                                    current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
       }//else
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
