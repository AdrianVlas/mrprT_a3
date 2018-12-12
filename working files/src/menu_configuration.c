#include "header.h"

/*****************************************************/
//������� ����� ������������
/*****************************************************/
void make_ekran_configuration(unsigned int configuration_edit_temp)
{
#define MAX_COL_LCD_PART1 10

  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_EKRAN_CONFIGURATION][MAX_COL_LCD_PART1] = 
  {
    {
     "��/��     ",
     "���       ",
     "���       ",
     "3U0-1     ",
     "����      ",
     "����      ",
     "���       ",
     "�����     ",
     "������    ",
     "���       ",
     "��        ",
     "��        ",
     "��        ",
     "����.���. "
    },
    {
     "��./���.  ",
     "���       ",
     "���       ",
     "3U0-1     ",
     "����      ",
     "����      ",
     "���       ",
     "����     ",
     "������    ",
     "���       ",
     "��        ",
     "��        ",
     "��        ",
     "����.���. "
    },
    {
     "Off/On    ",
     "���       ",
     "OCP       ",
     "3U0-1     ",
     "����      ",
     "CBFP      ",
     "NPSP      ",
     "Umin      ",
     "Umax      ",
     "���       ",
     "GP        ",
     "TP        ",
     "UP        ",
     "Ext.logic "
    },
    {
     "��/��     ",
     "���       ",
     "��K       ",
     "3U0-1     ",
     "����      ",
     "Ѳ��K     ",
     "�KK       ",
     "�����     ",
     "������    ",
     "���       ",
     "��        ",
     "��        ",
     "��        ",
     "����.���. "
    }
  };

  const unsigned char information_on[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - MAX_COL_LCD_PART1] = 
  {
    "���.  ",
    "����.",
    "On    ",
    "����. "
  };
  const unsigned char information_off[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - MAX_COL_LCD_PART1] = 
  {
    "����. ",
    "����. ",
    "Off   ",
    "њ��. "
  };
  
  unsigned int configuration_temp;
    
  //���� �� �� � ����� �����������, �� ������ ��� �� �������� ������� ���������
  //������ ����� �� ��������� ��� �����������
  if(current_ekran.edition == 0) configuration_temp = current_settings.configuration;
  else configuration_temp = configuration_edit_temp;
  

  /*******************************************************/
  //������� ��������
  /*******************************************************/
  int index_language = index_language_in_array(current_settings.language);
  unsigned char name_string_tmp[MAX_ROW_FOR_EKRAN_CONFIGURATION][MAX_COL_LCD];

  for(unsigned int i = 0; i< MAX_ROW_FOR_EKRAN_CONFIGURATION; i++)
  {
    for(int j = 0; j < MAX_COL_LCD_PART1; j++)
      name_string_tmp[i][j] = name_string[index_language][i][j];
    
    if ((configuration_temp & (1 << i)) == 0)
    {
      for (unsigned int j = MAX_COL_LCD_PART1; j < MAX_COL_LCD; j++)
        name_string_tmp[i][j] = information_off[index_language][j - MAX_COL_LCD_PART1];
    }
    else
    {
      for (unsigned int j = MAX_COL_LCD_PART1; j < MAX_COL_LCD; j++)
        name_string_tmp[i][j] = information_on[index_language][j - MAX_COL_LCD_PART1];
    }
  }
  /*******************************************************/
    
  int position_temp = current_ekran.index_position;
  int index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //������� ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < MAX_ROW_FOR_EKRAN_CONFIGURATION)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = (MAX_COL_LCD_PART1 - 1);
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if (current_ekran.edition == 0)   current_ekran.cursor_blinking_on = 0;
  else   current_ekran.cursor_blinking_on = 1;

  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
  
#undef MAX_COL_LCD_PART1  
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
