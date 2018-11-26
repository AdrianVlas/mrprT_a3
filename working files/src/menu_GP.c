#include "header.h"

/*****************************************************/
//Формуємо екран відображення витримок газовая защита
/*****************************************************/
void make_ekran_timeout_gp(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_GP][MAX_COL_LCD] = 
  {
    {
      "  Выдержка ГЗ1  ",
      "  Выдержка ГЗ2  ",
      " Выдержка ГЗ РПН"
    },
    {
      "  Витримка ГЗ1  ",
      "  Витримка ГЗ2  ",
      " Витримка ГЗ РПН"
    },
    {
      "  Выдержка ГЗ1  ",
      "  Выдержка ГЗ2  ",
      " Выдержка ГЗ РПН"
    },
    {
      "  Выдержка ГЗ1  ",
      "  Выдержка ГЗ2  ",
      " Выдержка ГЗ РПН"
    }
  };
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_GP)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];

        if (index_of_ekran_tmp == INDEX_ML_TMO_GP1)
        {
        vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 
        if (view == true) value = current_settings.timeout_GP1[group]; //у змінну value поміщаємо значення витримки 
        else value = edition_settings.timeout_GP1[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMO_GP2)
        {
        vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 
        if (view == true) value = current_settings.timeout_GP2[group]; //у змінну value поміщаємо значення витримки 
        else value = edition_settings.timeout_GP2[group];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMO_GP_RPN)
        {
        vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 
        if (view == true) value = current_settings.timeout_GP_RPN[group]; //у змінну value поміщаємо значення витримки 
        else value = edition_settings.timeout_GP_RPN[group];
        }

        first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
         if (index_of_ekran_tmp == INDEX_ML_TMO_GP1)
         {
          if (
              ((j < COL_TMO_GP1_BEGIN) ||  (j > COL_TMO_GP1_END )) &&
              (j != (COL_TMO_GP1_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_TMO_GP1_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_TMO_GP1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_GP1_COMMA, view, 0);
         }
         else if (index_of_ekran_tmp == INDEX_ML_TMO_GP2)
         {
          if (
              ((j < COL_TMO_GP2_BEGIN) ||  (j > COL_TMO_GP2_END )) &&
              (j != (COL_TMO_GP2_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_TMO_GP2_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_TMO_GP2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_GP2_COMMA, view, 0);
         }
         else if (index_of_ekran_tmp == INDEX_ML_TMO_GP_RPN)
         {
          if (
              ((j < COL_TMO_GP_RPN_BEGIN) ||  (j > COL_TMO_GP_RPN_END )) &&
              (j != (COL_TMO_GP_RPN_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_TMO_GP_RPN_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_TMO_GP_RPN_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_GP_RPN_COMMA, view, 0);
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
    current_ekran.position_cursor_x = COL_TMO_GP1_BEGIN;
    int last_position_cursor_x = COL_TMO_GP1_END;

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
//Формуємо екран відображення значення управлінської інформації для газовая защита
/*****************************************************/
void make_ekran_control_gp()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_GP][MAX_COL_LCD] = 
  {
    {
      "       ГЗ       "
    },
    {
      "       ГЗ       "
    },
    {
      "       ГЗ       "
    },
    {
      "       ГЗ       "
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_GP)
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
          
        if(current_ekran.edition == 0) temp_data = current_settings.control_GP;
        else temp_data = edition_settings.control_GP;
          
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
