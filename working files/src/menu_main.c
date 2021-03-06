#include "header.h"

/*****************************************************/
//������� ����� ��������� ����
/*****************************************************/
void make_ekran_main(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EKRAN_MAIN][MAX_COL_LCD] = 
  {
    {
     " ����           ",
     " ���������      ",
     " �����-������   ",
     " ������������   ",
     " Language       ",
     " ���������      ",
     " �����������    ",
     " ������������   ",
     " ��/��          ",
     " ���            ",
     " ���            ",
     " 3U0-1          ",
     " ����           ",
     " ����           ",
     " ���            ",
     " �����          ",
     " ������         ",
     " ���            ",
     " ��             ",
     " ��             ",
     " ��             "
    },
    {
     " ��������       ",
     " ����������    ",
     " �����-������   ",
     " ����������    ",
     " Language       ",
     " ������������   ",
     " ĳ���������    ",
     " ������������   ",
     " �����./�����. ",
     " ���            ",
     " ���            ",
     " 3U0-1          ",
     " ����           ",
     " ����           ",
     " ���            ",
     " ����          ",
     " ������         ",
     " ���            ",
     " ��             ",
     " ��             ",
     " ��             "
    },
    {
     " Clock          ",
     " Measurement    ",
     " Inputs-Outputs ",
     " Recorders      ",
     " Language       ",
     " Settings       ",
     " Diagnostic     ",
     " Configuration  ",
     " Off/On         ",
     " ���            ",
     " OCP            ",
     " 3U0-1          ",
     " ����           ",
     " CBFP           ",
     " NPSP           ",
     " Umin           ",
     " Umax           ",
     " ���            ",
     " GP             ",
     " TP             ",
     " UP             "
    },
    {
     " ��f��          ",
     " �����          ",
     " ʳ��-��f��    ",
     " ҳ��������    ",
     " Language       ",
     " �������       ",
     " �����������    ",
     " ���������������",
     " ��/��          ",
     " ���            ",
     " ��K            ",
     " 3U0-1          ",
     " ����           ",
     " Ѳ��K          ",
     " �KK            ",
     " �����          ",
     " ������         ",
     " ���            ",
     " ��             ",
     " ��             ",
     " ��             "
    }
  };

  unsigned char name_string_tmp[MAX_ROW_FOR_EKRAN_MAIN][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < MAX_ROW_FOR_EKRAN_MAIN; index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
    {
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
    }
  }
  
  unsigned int additional_current = 0;
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  /******************************************/
  //��������� ����, �� �� ����� ����������
  /******************************************/
  for (unsigned int zachyst = 0; zachyst < (TOTAL_NUMBER_PROTECTION - 1); zachyst++) /*̳��� ���� - �� �������� �� �������� ����� ������������ "��������� �����"*/
  {
    if ((current_settings.configuration & (1 << zachyst)) == 0)
    {
      unsigned int i = INDEX_ML1_Off_On + zachyst - additional_current;
    
      if ((i+1) <= position_temp) position_temp--;
      do
      {
        for(unsigned int j = 0; j < MAX_COL_LCD; j++)
        {
          if ((i+1) < (MAX_ROW_FOR_EKRAN_MAIN - additional_current)) name_string_tmp[i][j] = name_string_tmp[i + 1][j];
          else name_string_tmp[i][j] = ' ';
        }
        i++;
      }
      while (i< (MAX_ROW_FOR_EKRAN_MAIN - additional_current));
      additional_current++;
    }
  }
  /******************************************/
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < (MAX_ROW_FOR_EKRAN_MAIN - additional_current))
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
