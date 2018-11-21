#include "header.h"

/*****************************************************/
//Формуємо екран відображення уставок KZ_ZP
/*****************************************************/
void make_ekran_setpoint_kz_zp(unsigned int group)
{
 const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_KZ_ZV][MAX_COL_LCD] = 
  {
    {
      "  Уставка ВВП   ",
      "    Угол ВВП    "
    },
    {
      "  Уставка ВЗП   ",
      "    Кут ВЗП     "
    },
    {
      "  Уставка ВВП   ",
      "    Угол ВВП    "
    },
    {
      "  Уставка ВВП   ",
      "    Угол ВВП    "
    }
  };
  const unsigned char symbols[MAX_NAMBER_LANGUAGE][3] = {"ед.", "од.", "u  ", "ед."};
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    unsigned int view = ((current_ekran.edition == 0) || (position_temp != index_of_ekran_tmp));
    if (index_of_ekran_tmp < MAX_ROW_FOR_SETPOINT_KZ_ZV)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];

        if (index_of_ekran_tmp == INDEX_ML_STP_KZ_ZV)
        {
        vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для уставки ВВП
        if (view == true) value = current_settings.pickup_kz_zv[group]; //у змінну value поміщаємо значення уставки 
        else value = edition_settings.pickup_kz_zv[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_STP_KZ_ZV_ANGLE)
        {
        vaga = 10; //максимальний ваговий коефіцієнт для вилілення старшого розряду для уставки ВВП
        if (view == true) value = current_settings.pickup_kz_zv_angle[group]; //у змінну value поміщаємо значення уставки
        else value = edition_settings.pickup_kz_zv_angle[group];
        }

        first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
         if (index_of_ekran_tmp == INDEX_ML_STP_KZ_ZV)
         {
          if (
              ((j < COL_SETPOINT_KZ_ZV_BEGIN) ||  (j > COL_SETPOINT_KZ_ZV_END )) &&
              (
               !((j >= (COL_SETPOINT_KZ_ZV_END + 2)) && (j <= (COL_SETPOINT_KZ_ZV_END + 4)))
              )    
             )working_ekran[i][j] = ' ';
          else if (j == COL_SETPOINT_KZ_ZV_COMMA )working_ekran[i][j] = ',';
          else if ((j >= (COL_SETPOINT_KZ_ZV_END + 2)) && (j <= (COL_SETPOINT_KZ_ZV_END + 4)))
            working_ekran[i][j] = symbols[index_language][j - (COL_SETPOINT_KZ_ZV_END + 2)];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_KZ_ZV_COMMA, view, 0);
         }
         else if (index_of_ekran_tmp == INDEX_ML_STP_KZ_ZV_ANGLE)
         {
            if (
                ((j < COL_SETPOINT_KZ_ZV_ANGLE_BEGIN) ||  (j > COL_SETPOINT_KZ_ZV_ANGLE_END ))  &&
                (j != (COL_SETPOINT_KZ_ZV_ANGLE_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == (COL_SETPOINT_KZ_ZV_ANGLE_END + 2)) working_ekran[i][j] = '°';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, view);
         }
        }//for
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
  if (current_ekran.edition == 0)
  {
    current_ekran.position_cursor_x = COL_SETPOINT_KZ_ZV_BEGIN;
    int last_position_cursor_x = COL_SETPOINT_KZ_ZV_END;

    //Підтягуємо курсор до першого символу
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //Курсор ставимо так, щоб він був перед числом
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/


/*****************************************************/
//Формуємо екран відображення значення управлінської інформації для ВВП
/*****************************************************/
void make_ekran_control_kz_zp(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_KZ_ZV][MAX_COL_LCD] = 
  {
    {
      "    ВВП         "
    },
    {
      "    ВЗП         "
    },
    {
      "    ВВП         "
    },
    {
      "    ВВП         "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_KZ_ZV)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"     Откл.      ", "      Вкл.      "},
          {"     Вимк.      ", "     Ввімк.     "},
          {"      Off       ", "       On       "},
          {"     Сљнд.      ", "     Косу.      "}
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
          
        if(current_ekran.edition == 0) temp_data = current_settings.control_kz_zv;
        else temp_data = edition_settings.control_kz_zv;
          
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
         if (position_temp == index_of_ekran_tmp)
                                    current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
