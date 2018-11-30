#include "header.h"

const uint8_t ind_value[MAX_NAMBER_LANGUAGE][NUMBER_ON_OFF] =
{
  {'В', 'Н'},
  {'В', 'Н'},
  {'H', 'V'},
  {'В', 'Н'}
};

/*****************************************************/
//Формуємо екран відображення вибору ранжування БВвімк./БВимк.
/*****************************************************/
void make_ekran_choose_CBOn_CBOff(uint32_t on_off)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_RANG_SWITCH][MAX_COL_LCD] = 
  {
    {
      " БО(x)          ",
      " БВ(x)          "
    },
    {
      " БВимк.(x)      ",
      " БВвімк.(x)     "
    },
    {
      " Off CB(x)      ",
      " On CB(x)       "
    },
    {
      " БО(x)          ",
      " БВ(x)          "
    }
  };
  const uint8_t ind_index[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_RANG_SWITCH] = 
  {
    {4, 4},
    {8, 9},
    {8, 7},
    {4, 4}
  };
  
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_LIST_OF_REGISTRATORS)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
      working_ekran[i][ind_index[index_language][index_of_ekran]] = ind_value[index_language][on_off];
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_ekran.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  current_ekran.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення витримок Виключателя
/*****************************************************/
void make_ekran_timeout_switch(uint32_t on_off)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_SWITCH][MAX_COL_LCD] = 
  {
    {
      "   T вкл.(x)    ",
      "   T откл.(x)   ",
      "T удл.бл.вкл.(x)",
      " T Привода ВВ(x)"
    },
    {
      "  T ввімк.(x)   ",
      "   T вимк.(x)   ",
      "T п.бл.ввімк.(x)",
      " T Привода ВВ(x)"
    },
    {
      "    On T(x)     ",
      "    Off T(x)    ",
      "  ON Blc.L.(x)  ",
      " CB Act.Time(x) "
    },
    {
      "   T вкл.(x)    ",
      "   T откл.(x)   ",
      "T удл.бл.вкл.(x)",
      " T Привода ВВ(x)"
    }
  };
  const uint8_t ind_index[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_SWITCH] = 
  {
    {10, 11, 14, 14},
    {11, 11, 14, 14},
    { 9, 10, 12, 13},
    {10, 11, 14, 14}
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_SWITCH)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][ind_index[index_language][index_of_ekran_tmp]] = ind_value[index_language][on_off];
        
        if (index_of_ekran_tmp == INDEX_ML_TMOON)
        {
          vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки T вкл.
          if (view == true) value = current_settings.timeout_swch_on[on_off]; //у змінну value поміщаємо значення витримки T вкл.
          else value = edition_settings.timeout_swch_on[on_off];
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOOFF)
        {
          vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки T відкл.
          if (view == true) value = current_settings.timeout_swch_off[on_off]; //у змінну value поміщаємо значення витримки T відкл.
          else value = edition_settings.timeout_swch_off[on_off];
        }
        else  if (index_of_ekran_tmp == INDEX_ML_TMOUDL_BLK_ON)
        {
          vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки T "удлинение сигнала блокировки включения"
          if (view == true) value = current_settings.timeout_swch_udl_blk_on[on_off]; //у змінну value поміщаємо значення итримки T "удлинение сигнала блокировки включения"
          else value = edition_settings.timeout_swch_udl_blk_on[on_off];
        }
        else  if (index_of_ekran_tmp == INDEX_ML_TMOPRYVODA_VV)
        {
          vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки T "Привода ВВ"
          if (view == true) value = current_settings.timeout_pryvoda_VV[on_off]; //у змінну value поміщаємо значення итримки T "Привода ВВ"
          else value = edition_settings.timeout_pryvoda_VV[on_off];
        }
        first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (index_of_ekran_tmp == INDEX_ML_TMOON)
          {
            if (
                ((j < COL_TMO_SWCH_ON_BEGIN) ||  (j > COL_TMO_SWCH_ON_END )) &&
                (j != (COL_TMO_SWCH_ON_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_SWCH_ON_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_SWCH_ON_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_SWCH_ON_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOOFF)
          {
            if (
                ((j < COL_TMO_SWCH_OFF_BEGIN) ||  (j > COL_TMO_SWCH_OFF_END )) &&
                (j != (COL_TMO_SWCH_OFF_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_SWCH_OFF_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_SWCH_OFF_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_SWCH_OFF_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOUDL_BLK_ON)
          {
            if (
                ((j < COL_TMO_SWCH_UDL_BLK_ON_BEGIN) ||  (j > COL_TMO_SWCH_UDL_BLK_ON_END )) &&
                (j != (COL_TMO_SWCH_UDL_BLK_ON_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_SWCH_UDL_BLK_ON_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_SWCH_UDL_BLK_ON_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_SWCH_UDL_BLK_ON_COMMA, view, 0);
          }
          else if (index_of_ekran_tmp == INDEX_ML_TMOPRYVODA_VV)
          {
            if (
                ((j < COL_TMO_PRYVODA_VV_BEGIN) ||  (j > COL_TMO_PRYVODA_VV_END )) &&
                (j != (COL_TMO_PRYVODA_VV_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_PRYVODA_VV_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_PRYVODA_VV_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j,COL_TMO_PRYVODA_VV_COMMA, view, 0);
          }
        }
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
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOON)
    {
      current_ekran.position_cursor_x = COL_TMO_SWCH_ON_BEGIN;
      last_position_cursor_x = COL_TMO_SWCH_ON_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOOFF)
    {
      current_ekran.position_cursor_x = COL_TMO_SWCH_OFF_BEGIN;
      last_position_cursor_x = COL_TMO_SWCH_OFF_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOUDL_BLK_ON)
    {
      current_ekran.position_cursor_x = COL_TMO_SWCH_UDL_BLK_ON_BEGIN;
      last_position_cursor_x = COL_TMO_SWCH_UDL_BLK_ON_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOPRYVODA_VV)
    {
      current_ekran.position_cursor_x = COL_TMO_PRYVODA_VV_BEGIN;
      last_position_cursor_x = COL_TMO_PRYVODA_VV_END;
    }

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
//Формуємо екран відображення значення управлінської інформації для вимикача
/*****************************************************/
void make_ekran_control_switch(uint32_t on_off)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_SWITCH][MAX_COL_LCD] = 
  {
    {
      " Контроль ВВ(x) ",
      "  Ресурс ВВ(x)  "
    },
    {
      " Контроль ВВ(x) ",
      "  Ресурс ВВ(x)  "
    },
    {
      " CB Control(x)  ",
      "  Ресурс ВВ(x)  "
    },
    {
      " Контроль ВВ(x) ",
      "  Ресурс ВВ(x)  "
    }
  };
  const uint8_t ind_index[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_SWITCH] = 
  {
    {13, 12},
    {13, 12},
    {12, 12},
    {13, 12}
  };
  
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int index_of_ekran_tmp = index_of_ekran >> 1;
    if (index_of_ekran_tmp < MAX_ROW_FOR_CONTROL_SWITCH)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][ind_index[index_language][index_of_ekran_tmp]] = ind_value[index_language][on_off];
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
          
        if(current_ekran.edition == 0) temp_data = current_settings.control_switch[on_off];
        else temp_data = edition_settings.control_switch[on_off];
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
        if (position_temp == index_of_ekran_tmp) current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
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
