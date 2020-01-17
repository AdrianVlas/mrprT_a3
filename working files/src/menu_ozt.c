#include "header.h"


/*****************************************************/
//������� ����� ����������� ������� OZT
/*****************************************************/
void make_ekran_setpoint_ozt(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_OZT][MAX_COL_LCD] = 
  {
    {
      "  ���.����.���  ",
      " ����.����.���� ",
      "  ���������� 1  ",
      "  ���������� 2  ",
      " �������.����.  ",
      " ���.���������� ",
      " �������.����.  ",
      " ��������� ����.",
      " ���� ����.����.",
      "��������� 2����.",
      "���� ����.2����.",
      "��������� 5����.",
      "���� ����.5����.",
      " ���� ����.���  "
    },
    {
      " ���.���.�����  ",
      " ����.���.������",
      "  ����������� 1 ",
      "  ����������� 2 ",
      " ������i�.�����.",
      " ���.�����������",
      "  �����.�����.  ",
      " ��������� ����.",
      "���� �����.����.",
      "��������� 2����.",
      "���� �����.2����",
      "��������� 5����.",
      "���� �����.5����",
      " ���� �����.��� "
    },
    {
      "  ���.����.���  ",
      " ����.����.���� ",
      "  ���������� 1  ",
      "  ���������� 2  ",
      " �������.����.  ",
      " ���.���������� ",
      " �������.����.  ",
      " ��������� ����.",
      " ���� ����.����.",
      "��������� 2����.",
      "���� ����.2����.",
      "��������� 5����.",
      "���� ����.5����.",
      " ���� ����.���  "
    },
    {
      "  ���.����.���  ",
      " ����.����.���� ",
      "  ���������� 1  ",
      "  ���������� 2  ",
      " �������.����.  ",
      " ���.���������� ",
      " �������.����.  ",
      " ��������� ����.",
      " ���� ����.����.",
      "��������� 2����.",
      "���� ����.2����.",
      "��������� 5����.",
      "���� ����.5����.",
      " ���� ����.���  "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    unsigned int view = ((current_ekran.edition == 0) || (position_temp != index_of_ekran_tmp));
    if (index_of_ekran_tmp < MAX_ROW_FOR_SETPOINT_OZT)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
/*
        if (index_of_ekran_tmp == INDEX_ML_D_OZT_BB)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_BB[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_BB[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_D_OZT_BH)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_BH[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_BH[group];
        }
*/
        if (index_of_ekran_tmp == INDEX_ML_D_OZT_ID0)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_Id0[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_Id0[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_D_OZT_delta)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_delta_Id[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_delta_Id[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_T_OZT_T1)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_Kg1[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_Kg1[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_T_OZT_T2)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_Kg2[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_Kg2[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_T_OZT_TK)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_k[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_k[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_T_OZT_IT0)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_Ig0[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_Ig0[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_T_OZT_ITG1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_Ig_obm[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_Ig_obm[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_A_OZT_AK)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_K_aI[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_K_aI[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_K_OZT_A_KP)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_aI_kp[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_aI_kp[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_N_OZT_N2G)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_K_2I[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_K_2I[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_K_OZT_2G_KP)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_2I_kp[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_2I_kp[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_N_OZT_N5G)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_K_5I[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_K_5I[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_K_OZT_5G_KP)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_5I_kp[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_5I_kp[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_K_OZT_KP)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.pickup_ozt_kp[group]; //� ����� value ������� �������� �������
          else value = edition_settings.pickup_ozt_kp[group];
        }
        
        first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (index_of_ekran_tmp == INDEX_ML_D_OZT_ID0)
          {
            if (
                ((j < COL_SETPOINT_D_OZT_ID0_BEGIN) ||  (j > COL_SETPOINT_D_OZT_ID0_END ))  &&
                (j != (COL_SETPOINT_D_OZT_ID0_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_D_OZT_ID0_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_D_OZT_ID0_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_D_OZT_ID0_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_D_OZT_delta)
          {
            if (
                ((j < COL_SETPOINT_D_OZT_delta_BEGIN) ||  (j > COL_SETPOINT_D_OZT_delta_END ))  &&
                (j != (COL_SETPOINT_D_OZT_delta_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_D_OZT_delta_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_D_OZT_delta_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_D_OZT_delta_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_T_OZT_T1)
          {
            if (
                ((j < COL_SETPOINT_T_OZT_T1_BEGIN) ||  (j > COL_SETPOINT_T_OZT_T1_END ))  &&
                (j != (COL_SETPOINT_T_OZT_T1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_T_OZT_T1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_T_OZT_T1_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_T_OZT_T1_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_T_OZT_T2)
          {
            if (
                ((j < COL_SETPOINT_T_OZT_T2_BEGIN) ||  (j > COL_SETPOINT_T_OZT_T2_END ))  &&
                (j != (COL_SETPOINT_T_OZT_T2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_T_OZT_T2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_T_OZT_T2_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_T_OZT_T2_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_T_OZT_TK)
          {
            if (
                ((j < COL_SETPOINT_T_OZT_TK_BEGIN) ||  (j > COL_SETPOINT_T_OZT_TK_END ))  &&
                (j != (COL_SETPOINT_T_OZT_TK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_T_OZT_TK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_T_OZT_TK_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_T_OZT_TK_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_T_OZT_IT0)
          {
            if (
                ((j < COL_SETPOINT_T_OZT_IT0_BEGIN) ||  (j > COL_SETPOINT_T_OZT_IT0_END ))  &&
                (j != (COL_SETPOINT_T_OZT_IT0_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_T_OZT_IT0_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_T_OZT_IT0_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_T_OZT_IT0_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_T_OZT_ITG1)
          {
            if (
                ((j < COL_SETPOINT_T_OZT_ITG1_BEGIN) ||  (j > COL_SETPOINT_T_OZT_ITG1_END ))  &&
                (j != (COL_SETPOINT_T_OZT_ITG1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_T_OZT_ITG1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_T_OZT_ITG1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_T_OZT_ITG1_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_A_OZT_AK)
          {
            if (
                ((j < COL_SETPOINT_A_OZT_AK_BEGIN) ||  (j > COL_SETPOINT_A_OZT_AK_END ))  &&
                (j != (COL_SETPOINT_A_OZT_AK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_A_OZT_AK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_A_OZT_AK_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_A_OZT_AK_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_K_OZT_A_KP)
          {
            if (
                ((j < COL_SETPOINT_K_OZT_A_KP_BEGIN) ||  (j > COL_SETPOINT_K_OZT_A_KP_END ))  &&
                (j != (COL_SETPOINT_K_OZT_A_KP_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_K_OZT_A_KP_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_K_OZT_A_KP_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_K_OZT_A_KP_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_N_OZT_N2G)
          {
            if (
                ((j < COL_SETPOINT_N_OZT_N2G_BEGIN) ||  (j > COL_SETPOINT_N_OZT_N2G_END ))  &&
                (j != (COL_SETPOINT_N_OZT_N2G_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_N_OZT_N2G_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_N_OZT_N2G_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_N_OZT_N2G_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_K_OZT_2G_KP)
          {
            if (
                ((j < COL_SETPOINT_K_OZT_2I_KP_BEGIN) ||  (j > COL_SETPOINT_K_OZT_2I_KP_END ))  &&
                (j != (COL_SETPOINT_K_OZT_2I_KP_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_K_OZT_2I_KP_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_K_OZT_2I_KP_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_K_OZT_2I_KP_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_N_OZT_N5G)
          {
            if (
                ((j < COL_SETPOINT_N_OZT_N5G_BEGIN) ||  (j > COL_SETPOINT_N_OZT_N5G_END ))  &&
                (j != (COL_SETPOINT_N_OZT_N5G_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_N_OZT_N5G_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_N_OZT_N5G_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_N_OZT_N5G_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_K_OZT_5G_KP)
          {
            if (
                ((j < COL_SETPOINT_K_OZT_5I_KP_BEGIN) ||  (j > COL_SETPOINT_K_OZT_5I_KP_END ))  &&
                (j != (COL_SETPOINT_K_OZT_5I_KP_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_K_OZT_5I_KP_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_K_OZT_5I_KP_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_K_OZT_5I_KP_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_K_OZT_KP)
          {
            if (
                ((j < COL_SETPOINT_K_OZT_KP_BEGIN) ||  (j > COL_SETPOINT_K_OZT_KP_END ))  &&
                (j != (COL_SETPOINT_K_OZT_KP_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_K_OZT_KP_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_K_OZT_KP_END + 2)) working_ekran[i][j] = ' ';//odynyci_vymirjuvannja[index_language][INDEX_A];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_K_OZT_KP_COMMA, view, 0);
          }

        }
      }//for
        
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
/*
    if (current_ekran.index_position == INDEX_ML_D_OZT_BB)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_D_OZT_BB_BEGIN;
      last_position_cursor_x = COL_SETPOINT_D_OZT_BB_END;
    }
    else if (current_ekran.index_position == INDEX_ML_D_OZT_BH)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_D_OZT_BH_BEGIN;
      last_position_cursor_x = COL_SETPOINT_D_OZT_BH_END;
    }
*/
    if (current_ekran.index_position == INDEX_ML_D_OZT_ID0)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_D_OZT_ID0_BEGIN;
      last_position_cursor_x = COL_SETPOINT_D_OZT_ID0_END;
    }
    else if (current_ekran.index_position == INDEX_ML_D_OZT_delta)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_D_OZT_delta_BEGIN;
      last_position_cursor_x = COL_SETPOINT_D_OZT_delta_END;
    }
    else if (current_ekran.index_position == INDEX_ML_T_OZT_T1)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_T_OZT_T1_BEGIN;
      last_position_cursor_x = COL_SETPOINT_T_OZT_T1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_T_OZT_T2)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_T_OZT_T2_BEGIN;
      last_position_cursor_x = COL_SETPOINT_T_OZT_T2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_T_OZT_TK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_T_OZT_TK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_T_OZT_TK_END;
    }
    else if (current_ekran.index_position == INDEX_ML_T_OZT_IT0)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_T_OZT_IT0_BEGIN;
      last_position_cursor_x = COL_SETPOINT_T_OZT_IT0_END;
    }
    else if (current_ekran.index_position == INDEX_ML_T_OZT_ITG1)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_T_OZT_ITG1_BEGIN;
      last_position_cursor_x = COL_SETPOINT_T_OZT_ITG1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_A_OZT_AK)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_A_OZT_AK_BEGIN;
      last_position_cursor_x = COL_SETPOINT_A_OZT_AK_END;
    }
    else if (current_ekran.index_position == INDEX_ML_K_OZT_A_KP)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_K_OZT_A_KP_BEGIN;
      last_position_cursor_x = COL_SETPOINT_K_OZT_A_KP_END;
    }
    else if (current_ekran.index_position == INDEX_ML_N_OZT_N2G)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_N_OZT_N2G_BEGIN;
      last_position_cursor_x = COL_SETPOINT_N_OZT_N2G_END;
    }
    else if (current_ekran.index_position == INDEX_ML_K_OZT_2G_KP)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_K_OZT_2I_KP_BEGIN;
      last_position_cursor_x = COL_SETPOINT_K_OZT_2I_KP_END;
    }
    else if (current_ekran.index_position == INDEX_ML_N_OZT_N5G)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_N_OZT_N5G_BEGIN;
      last_position_cursor_x = COL_SETPOINT_N_OZT_N5G_END;
    }
    else if (current_ekran.index_position == INDEX_ML_K_OZT_5G_KP)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_K_OZT_5I_KP_BEGIN;
      last_position_cursor_x = COL_SETPOINT_K_OZT_2I_KP_END;
    }
    else if (current_ekran.index_position == INDEX_ML_K_OZT_KP)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_K_OZT_KP_BEGIN;
      last_position_cursor_x = COL_SETPOINT_K_OZT_KP_END;
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
//������� ����� ����������� �������� OZT
/*****************************************************/
void make_ekran_timeout_ozt(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_OZT][MAX_COL_LCD] = 
  {
    {
      "  �������� ���1 ",
      "  �������� ���2 ",
      "���������� ����."
    },
    {
      "  �������� ���1 ",
      "  �������� ���2 ",
      "���������� ����."
    },
    {
      "  �������� ���1 ",
      "  �������� ���2 ",
      "���������� ����."
    },
    {
      "  �������� ���1 ",
      "  �������� ���2 ",
      "���������� ����."
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_OZT)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        if (index_of_ekran_tmp == INDEX_ML_TMOOZT1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (view == true) value = current_settings.timeout_ozt1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ozt1[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOOZT2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (view == true) value = current_settings.timeout_ozt2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_ozt2[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOOZT_AB)
        {
          vaga = 1000; //������������ ������� ���������� ��� �������� �������� �������
          if (view == true) value = current_settings.timeout_ozt2_a_blk[group]; //� ����� value ������� �������� �������
          else value = edition_settings.timeout_ozt2_a_blk[group];
        }

        first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (index_of_ekran_tmp == INDEX_ML_TMOOZT1)
          {
            if (
                ((j < COL_TMO_OZT_1_BEGIN) ||  (j > COL_TMO_OZT_1_END )) &&
                (j != (COL_TMO_OZT_1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_OZT_1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_OZT_1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_OZT_1_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOOZT2)
          {
            if (
                ((j < COL_TMO_OZT_2_BEGIN) ||  (j > COL_TMO_OZT_2_END )) &&
                (j != (COL_TMO_OZT_2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_OZT_2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_OZT_2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_OZT_2_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOOZT_AB)
          {
            if (
                ((j < COL_TMO_A_OZT_AB_BEGIN) ||  (j > COL_TMO_A_OZT_AB_END ))  &&
                (j != (COL_TMO_A_OZT_AB_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_A_OZT_AB_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_A_OZT_AB_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_A_OZT_AB_COMMA, view, 0);
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
    if (current_ekran.index_position == INDEX_ML_TMOOZT1) 
    {
      current_ekran.position_cursor_x = COL_TMO_OZT_1_BEGIN;
      last_position_cursor_x = COL_TMO_OZT_1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOOZT2) 
    {
      current_ekran.position_cursor_x = COL_TMO_OZT_2_BEGIN;
      last_position_cursor_x = COL_TMO_OZT_2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOOZT_AB)
    {
      current_ekran.position_cursor_x = COL_TMO_A_OZT_AB_BEGIN;
      last_position_cursor_x = COL_TMO_A_OZT_AB_END;
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
//������� ����� ����������� �������� ����������� ���������� ��� OZT
/*****************************************************/
void make_ekran_control_ozt(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_OZT][MAX_COL_LCD] = 
  {
    {
      " ������ ��������",
      " 1 ������� ���  ",
      " ���������� ���1",
      " 2 ������� ���  ",
      " ���������� ���2",
      "  ����.�������. ",
      " ����.2-� ����. ",
      " ����.5-� ����. "
    },
    {
      " ����� �'�������",
      " 1 ����i�� ���  ",
      "����������� ���1",
      " 2 ����i�� ���  ",
      "����������� ���2",
      "  ����.����i��. ",
      " ����.2-� ����. ",
      " ����.5-� ����. "
    },
    {
      " ������ ��������",
      " 1 ������� ���  ",
      " ���������� ���1",
      " 2 ������� ���  ",
      " ���������� ���2",
      "  ����.�������. ",
      " ����.2-� ����. ",
      " ����.5-� ����. "
    },
    {
      " ������ ��������",
      " 1 ������� ���  ",
      " ���������� ���1",
      " 2 ������� ���  ",
      " ���������� ���2",
      "  ����.�������. ",
      " ����.2-� ����. ",
      " ����.5-� ����. "
    }
  };

  int index_language = index_language_in_array(current_settings.language);

  int position_temp = current_ekran.index_position;
  int index_of_ekran;

  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_OZT)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
      }//if ((i & 0x1) == 0)
      else
      {
        //� ������� ����� ����� �������� �������� �������
        unsigned int index_ctr = index_of_ekran_tmp;
        __SETTINGS *point;
          if(current_ekran.edition == 0) point = &current_settings;
          else point = &edition_settings;
        if (index_ctr == INDEX_ML_CTROZT_TYPE_CON)   
        {
          int value = point->type_con_ozt;

          const unsigned char information[3][MAX_COL_LCD] = 
          {
            "       0        ",
            "       1        ",
            "       11       "
          };
          const unsigned int cursor_x[3] = {6, 6, 6};
          
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[value][j];
          if (index_of_ekran_tmp == current_ekran.index_position) 
                                    current_ekran.position_cursor_x = cursor_x[value];
        }//if (index_ctr == INDEX_ML_CTROZT_TYPE_CON)   
        else
        {
           unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          };

           unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
          {
           {4, 5},
           {4, 4},
           {5, 6},
           {4, 4}
          };

        unsigned int temp_data = point->control_ozt;
        
          unsigned int n_bit = 0;
        //�������� ����� ���
        if      (index_ctr == INDEX_ML_CTROZT_1       ) n_bit = N_BIT_CTROZT_1;
        else if (index_ctr == INDEX_ML_CTROZT_1_G     ) n_bit = N_BIT_CTROZT_1_G;
        else if (index_ctr == INDEX_ML_CTROZT_2       ) n_bit = N_BIT_CTROZT_2;
        else if (index_ctr == INDEX_ML_CTROZT_2_G     ) n_bit = N_BIT_CTROZT_2_G;
        else if (index_ctr == INDEX_ML_CTROZT_2_BLK_A ) n_bit = N_BIT_CTROZT_2_BLK_A;
        else if (index_ctr == INDEX_ML_CTROZT_2_BLK_2G) n_bit = N_BIT_CTROZT_2_BLK_2G;
        else if (index_ctr == INDEX_ML_CTROZT_2_BLK_5G) n_bit = N_BIT_CTROZT_2_BLK_5G;
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> n_bit) & 0x1][j];
        if (position_temp == index_of_ekran_tmp) current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> n_bit) & 0x1];
       }//else if (index_ctr == INDEX_ML_CTROZT_TYPE_CON)   
      }//else if ((i & 0x1) == 0)
    }//if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_OZT)
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
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}

/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
