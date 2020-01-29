#include "header.h"

void actualMeasurement_A(int actualIndex, unsigned char *nameString, unsigned int pervynna_vtorynna);
void actualMeasurement_Y(int actualIndex, unsigned char *nameString);

/*****************************************************/
//Конвертація в рядок і поміщення в масив для відображення на екрані вимірювань
/*****************************************************/
void convert_and_insert_char_for_measurement(unsigned int start_number_digit_after_point, unsigned int temp_meas, unsigned int koef_mul, unsigned int koef_div, unsigned char *name_string, unsigned int start_position)
{
  unsigned long long temp_value_long  = ((unsigned long long)temp_meas)*((unsigned long long)koef_mul)/((unsigned long long)koef_div);
  unsigned int temp_value = (unsigned int)temp_value_long;
  unsigned int number_digit_after_point = start_number_digit_after_point, error = 0, overflow = 0;
  
  //Помічаємо, що зараз ми ще не перейшли ні на шкалу КІЛО ні на шкалу МЕГА
//  *(name_string + start_position + 7) = ' ';

  overflow = ((temp_value_long & 0xffffffff00000000ull) != 0);
  while (
         (
          (overflow != 0) ||
          (temp_value > 999999)
         )
         &&  
         (error == 0)  
        )   
  {
    //Ми не вкладаємося у значення з шести цифр і коми

    //Відкидаємо найменш значуще число
    if (overflow != 0)
    {
      temp_value_long /= 10ull;
      overflow = ((temp_value_long & 0xffffffff00000000ull) != 0);
      if (overflow == 0)
        temp_value = temp_value_long;
    }
    else
      temp_value /=10;
    
    //Змінюємо позицію десяткової коми і, при потрребі, переходимо на іншу шкалу
    switch (number_digit_after_point)
    {
    case 1:
    case 2:
      {
        //Переходимо з формату 1.5 до 2.4 або з формату 2.4 до 3.3
        number_digit_after_point++;
        break;
      }
    case 3:
      {
        //Переходимо з формату 3.3 до 1.5 із встановленням позначки ' '->'k' або 'k'->'M'
        number_digit_after_point = 1;
        if ((*(name_string + start_position + 7)) == ' ') 
        {
          if (current_settings.language == LANGUAGE_EN)
            *(name_string + start_position + 7) = 'k';
          else
            *(name_string + start_position + 7) = 'к';
        }
        else if (
                 ((*(name_string + start_position + 7)) == 'к') ||
                 ((*(name_string + start_position + 7)) == 'k')  
                )
        {
          *(name_string + start_position + 7) = 'М';
        }
        else if ((*(name_string + start_position + 7)) == 'М')
        {
          if (current_settings.language == LANGUAGE_EN)
            *(name_string + start_position + 7) = 'G';
          else
            *(name_string + start_position + 7) = 'Г';
        }
        else
        {
          /*
          теоретично сюди б програма могла зайти у двох випадках:
          1) перехід з шкали МЕГА на вищу шкалу, що при наший числах це не мало ніколи б бути
          2) у 7-мый позицыъ було незрозумлий символ - і це э помилкова ситуація, яка б також ніколи не мала виникати
          
          У такому разі будем виводити повідомлення ***.*** і символ у 7-мый позицыъ ,який призвів до такої ситуації
          */
          error = 2;
        }
        break;
      }
    default:
      {
        /*
        теоретично сюди програма ніколи б не  мала зайти
        
        У такому разі будем виводити повідомлення XXXXXXX
        */
        error = 1;
      }
    }
  }
  
  if (error == 0)
  {
    //При приведені числа до відповідного формату і відповідної шкали помилок не було зафіксовано
    unsigned int first_symbol = 0, value, position = start_position; /*позиція з якої поинається виведення значення - найзначуще число*/
    
    /*
    X?????
    */
    if (temp_value > 99999)
    {
      value = temp_value / 100000; 
      temp_value %= 100000;
      *(name_string + position) = value + 0x30;
      first_symbol = 1;
    }
    else
    {
      if (number_digit_after_point == 1)
      {
        *(name_string + position) = '0';
        first_symbol = 1;
      }
      else *(name_string + position) = ' ';
    }
    position++;

    if (number_digit_after_point == 1)
    {
      //Десяткова "кома"
      *(name_string + position) = '.';
      position++;
    }

    /*
    *X????
    */
    if (temp_value > 9999)
    {
      value = temp_value / 10000; 
      temp_value %= 10000;
      *(name_string + position) = value + 0x30;
      first_symbol = 1;
    }
    else
    {
      if (
          (number_digit_after_point == 2) ||
          (first_symbol             != 0)  
         )   
      {
        *(name_string + position) = '0';
        first_symbol = 1;
      }
      else *(name_string + position) = ' ';
    }
    position++;

    if (number_digit_after_point == 2)
    {
      //Десяткова "кома"
      *(name_string + position) = '.';
      position++;
    }
    
    /*
    **X???
    */
    value = temp_value / 1000; 
    temp_value %= 1000;
    *(name_string + position) = value + 0x30;
    position++;

    if (number_digit_after_point == 3)
    {
      //Десяткова "кома"
      *(name_string + position) = '.';
      position++;
    }
    
    //З цього місця змінна position має обов'язково бути рівною (start_position + 4)
    if (position == (start_position + 4))
    {
      /*
      ***X??
      */
      value = temp_value / 100; 
      temp_value %= 100;
      *(name_string + (position++)) = value + 0x30;
  
      /*
      ****X?
      */
      value = temp_value / 10; 
      temp_value %= 10;
      *(name_string + (position++)) = value + 0x30;
  
      /*
      *****X
      */
      *(name_string + (position++)) = temp_value + 0x30;
    }
    else
    {
      //Помилка, яка б ніколи не мала виникати помічаємо це знаками оклику
      for (unsigned int i = 0; i < 7; i++) *(name_string + start_position + i) = '!';
      *(name_string + start_position + 7) = ' ';
    }
  }
  else if (error == 1)
  {
    //Помилка виникла при аналізі попереднього формату
    for (unsigned int i = 0; i < 7; i++) *(name_string + start_position + i) = 'X';
    *(name_string + start_position + 7) = ' ';
  }
  else if (error == 2)
  {
    //Помилка виникла при переході на іншу шкалу
    for (unsigned int i = 0; i < 7; i++) *(name_string + start_position + i) = '*';
    *(name_string + start_position + 3) = '.';
  }
  else
  {
    //Невизначена помилка
    for (unsigned int i = 0; i < 7; i++) *(name_string + start_position + i) = '?';
    *(name_string + start_position + 7) = ' ';
  }
}
/*****************************************************/

/*****************************************************/
//Конвертація в рядок і поміщення в масив для відображення на екрані частоти
/*****************************************************/
void convert_and_insert_char_for_frequency(int temp_meas_1000, unsigned char *name_string)
{
#define FIRST_POSITION_OF_NUMBER  5

  int temp_value = temp_meas_1000;

  int index_language = index_language_in_array(current_settings.language);
  if ((temp_value >= (MIN_FREQUENCY*1000)) && (temp_value <= ((MAX_FREQUENCY + 1)*1000)))
  {
    const unsigned char Hz[MAX_NAMBER_LANGUAGE][2] = {"Гц", "Гц", "Hz", "Гц"};
    for (unsigned int i = 0; i < 2; i++)  
    {
       *(name_string + FIRST_POSITION_OF_NUMBER + 7 + i) = Hz[index_language][i];
    }

    unsigned int position = FIRST_POSITION_OF_NUMBER; /*позиція з якої поинається виведення значення - найзначуще число*/
    int value;
    
    /*
    X????
    */
    if (temp_value > 9999)
    {
      value = temp_value / 10000; 
      temp_value %= 10000;
      *(name_string + position) = value + 0x30;
    }
    else
    {
      *(name_string + position) = ' ';
    }
    position++;

    /*
    *X???
    */
    value = temp_value / 1000; 
    temp_value %= 1000;
    *(name_string + position) = value + 0x30;
    position++;
    {
      //Десяткова "кома"
      *(name_string + position) = '.';
      position++;
    }
    
    //З цього місця змінна position має обов'язково бути рівною (FIRST_POSITION_OF_NUMBER + 3)
    if (position == (FIRST_POSITION_OF_NUMBER + 3))
    {
      /*
      **X??
      */
      value = temp_value / 100; 
      temp_value %= 100;
      *(name_string + (position++)) = value + 0x30;
  
      /*
      ***X?
      */
      value = temp_value / 10; 
      temp_value %= 10;
      *(name_string + (position++)) = value + 0x30;
  
      /*
      ****X
      */
      *(name_string + (position++)) = temp_value + 0x30;
    }
    else
    {
      //Помилка, яка б ніколи не мала виникати помічаємо це знаками оклику
      for (unsigned int i = 0; i < 6; i++) *(name_string + FIRST_POSITION_OF_NUMBER + i) = '!';
    }
  }
  else if (temp_meas_1000 < 0)
  {
    const unsigned char undefined[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - FIRST_POSITION_OF_NUMBER] =
    {
      "Неопред.   ",
      "Невизнач.  ",
      "Undef.     ",
      "Неопред.   "  
    };
    
    for (int i = 0; i < (MAX_COL_LCD - FIRST_POSITION_OF_NUMBER); i++) *(name_string + FIRST_POSITION_OF_NUMBER + i) = undefined[index_language][i];
  }
  else
  {
    //Помилка, яка б ніколи не мала виникати помічаємо це знаками питання
    for (unsigned int i = 0; i < 6; i++) *(name_string + FIRST_POSITION_OF_NUMBER + i) = '?';
  }
#undef FIRST_POSITION_OF_NUMBER
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення списків вимірювань
/*****************************************************/
void make_ekran_measurement(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_MEASURMENT][MAX_COL_LCD] = 
  {
    {
     " Токи           ",
     " Напряжения     ",
     " Частоты        ",
     " Мощность       "
    },
    {
     " Струми         ",
     " Напруги        ",
     " Частоти        ",
     " Потужність     "
    },
    {
     " Currents       ",
     " Voltages       ",
     " Frequencies    ",
     " Power          "
    },
    {
     " Токи           ",
     " Напряжения     ",
     " Частоты        ",
     " Мощность       "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_MEASURMENT)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
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
//Формуємо екран відображення списків вимірювань
/*****************************************************/
void make_ekran_measurement_voltage_type(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_MEASURMENT_VOLTAGE_TYPE][MAX_COL_LCD] = 
  {
    {
     " Фазные         ",
     " Линейные       ",
     " Симметричные   "
    },
    {
     " Фазні          ",
     " Лінійні        ",
     " Симетричнi     "
    },
    {
     " Фазные         ",
     " Линейные       ",
     " Симметричные   "
    },
    {
     " Фазные         ",
     " Линейные       ",
     " Симметричные   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_MEASURMENT_VOLTAGE_TYPE)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
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
//Формуємо екран відображення списків вимірювань
/*****************************************************/
void make_ekran_measurement_current_type(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_MEASURMENT_CURRENT_TYPE][MAX_COL_LCD] = 
  {
    {
     " Фазные         ",
     " Приведенные    ",
     " Дифференциал   ",
     " Симметричные   "
    },
    {
     " Фазні          ",
     " Приведені      ",
     " Диференцiйнi   ",
     " Симетричнi     "
    },
    {
     " Фазные         ",
     " Приведенные    ",
     " Дифференциал   ",
     " Симметричные   "
    },
    {
     " Фазные         ",
     " Приведенные    ",
     " Дифференциал   ",
     " Симметричные   "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_MEASURMENT_CURRENT_TYPE)
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
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
//Формуємо екран відображення струмів
/*****************************************************/
/*****************************************************/
/*****************************************************/
//Формуємо екран відображення токи фазные
/*****************************************************/
void make_ekran_current_phase(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_CURRENT_PHASE][MAX_COL_LCD] = 
  {
    " Ia_В =         ",
    " Ya_В =         ",
    " Ib_В =         ",
    " Yb_В =         ",
    " Ic_В =         ",
    " Yc_В =         ",
    " Ia_H =         ",
    " Ya_H =         ",
    " Ib_H =         ",
    " Yb_H =         ",
    " Ic_H =         ",
    " Yc_H =         ",
  };

  unsigned int row = 12;
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//Токи фазные
    switch(index_of_ekran)
    {
     case 0://Ia_В
       actualMeasurement_A(IM_IA_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://Ya_В
       actualMeasurement_Y(IM_IA_H, name_string[index_of_ekran]);
       break;
     case 2://Ib_В
       actualMeasurement_A(IM_IB_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://Yb_В
       actualMeasurement_Y(IM_IB_H, name_string[index_of_ekran]);
       break;
     case 4://Ic_В
       actualMeasurement_A(IM_IC_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://Yc_В
       actualMeasurement_Y(IM_IC_H, name_string[index_of_ekran]);
       break;
     case 6://Ia_H
       actualMeasurement_A(IM_IA_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 7://Ya_H
       actualMeasurement_Y(IM_IA_L, name_string[index_of_ekran]);
       break;
     case 8://Ib_H
       actualMeasurement_A(IM_IB_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 9://Yb_H
       actualMeasurement_Y(IM_IB_L, name_string[index_of_ekran]);
       break;
     case 10://Ic_H
       actualMeasurement_A(IM_IC_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 11://Yc_H
       actualMeasurement_Y(IM_IC_L, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення токи приведенные
/*****************************************************/
void make_ekran_current_given(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_CURRENT_GIVEN][MAX_COL_LCD] = 
  {
    " IPa_В=         ",
    " YPa_В=         ",
    " IPb_В=         ",
    " YPb_В=         ",
    " IPc_В=         ",
    " YPc_В=         ",
    " IPa_H=         ",
    " YPa_H=         ",
    " IPb_H=         ",
    " YPb_H=         ",
    " IPc_H=         ",
    " YPc_H=         ",
  };
  unsigned int row = 12;
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//токи приведенные
    switch(index_of_ekran)
    {
     case 0://IPa_В
       actualMeasurement_A(IM_IA_P_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://YPa_В
       actualMeasurement_Y(IM_IA_P_H, name_string[index_of_ekran]);
       break;
     case 2://IPb_В
       actualMeasurement_A(IM_IB_P_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://YPb_В
       actualMeasurement_Y(IM_IB_P_H, name_string[index_of_ekran]);
       break;
     case 4://IPc_В
       actualMeasurement_A(IM_IC_P_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://YPc_В
       actualMeasurement_Y(IM_IC_P_H, name_string[index_of_ekran]);
       break;
     case 6://IPa_H
       actualMeasurement_A(IM_IA_P_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 7://YPa_H
       actualMeasurement_Y(IM_IA_L, name_string[index_of_ekran]);
       break;
     case 8://IPb_H
       actualMeasurement_A(IM_IB_P_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 9://YPb_H
       actualMeasurement_Y(IM_IB_P_L, name_string[index_of_ekran]);
       break;
     case 10://IPc_H
       actualMeasurement_A(IM_IC_P_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 11://YPc_H
       actualMeasurement_Y(IM_IC_P_L, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення токи дифф
/*****************************************************/
void make_ekran_current_diff(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_CURRENT_DIFF][MAX_COL_LCD] = 
  {
    " IDa1=          ",
    " IDb1=          ",
    " IDc1=          ",
    " ITa =          ",
    " ITb =          ",
    " ITc =          ",
    " IDa2=          ",
    " IDb2=          ",
    " IDc2=          ",
    " IDa5=          ",
    " IDb5=          ",
    " IDc5=          "
  };
  unsigned int row = 12;
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//токи дифф
    switch(index_of_ekran)
    {
     case 0://Ia1
       actualMeasurement_A(IM_dIA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://Ib1
       actualMeasurement_A(IM_dIB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 2://Ic1
       actualMeasurement_A(IM_dIC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://IaT
       actualMeasurement_A(IM_gdIA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 4://IbT
       actualMeasurement_A(IM_gdIB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://IcT
       actualMeasurement_A(IM_gdIC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 6://Ia2
       actualMeasurement_A(IM_2dIA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 7://Ib2
       actualMeasurement_A(IM_2dIB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 8://Ic2
       actualMeasurement_A(IM_2dIC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 9://Ia5
       actualMeasurement_A(IM_5dIA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 10://Ib5
       actualMeasurement_A(IM_5dIB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 11://Ic5
       actualMeasurement_A(IM_5dIC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення токи симметричные
/*****************************************************/
void make_ekran_current_sklad(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_CURRENT_SKLAD][MAX_COL_LCD] = 
  {
    " 3I0_В=         ",
    " Y0_В =         ",
    " I2_В =         ",
    " Y2_В =         ",
    " I1_В =         ",
    " Y1_В =         ",
    " 3I0_H=         ",
    " Y0_H =         ",
    " I2_H =         ",
    " Y2_H =         ",
    " I1_H =         ",
    " Y1_H =         ",
    " IP2_В=         ",
    " YP2_В=         ",
    " IP1_В=         ",
    " YP1_В=         ",
    " IP2_H=         ",
    " YP2_H=         ",
    " IP1_H=         ",
    " YP1_H=         ",
  };
  unsigned int row = 20;
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//токи симметричные
    switch(index_of_ekran)
    {
     case 0://A0_В
       actualMeasurement_A(IM_3I0_r_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://Y0_В
       actualMeasurement_Y(IM_3I0_r_H, name_string[index_of_ekran]);
       break;
     case 2://I2_В
       actualMeasurement_A(IM_I2_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://Y2_В
       actualMeasurement_Y(IM_I2_H, name_string[index_of_ekran]);
       break;
     case 4://I1_В
       actualMeasurement_A(IM_I1_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://Y1_В
       actualMeasurement_Y(IM_I1_H, name_string[index_of_ekran]);
       break;
     case 6://I0_H
       actualMeasurement_A(IM_3I0_r_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 7://Y0_H
       actualMeasurement_Y(IM_3I0_r_L, name_string[index_of_ekran]);
       break;
     case 8://I2_H
       actualMeasurement_A(IM_I2_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 9://Y2_H
       actualMeasurement_Y(IM_I2_L, name_string[index_of_ekran]);
       break;
     case 10://I1_H
       actualMeasurement_A(IM_I1_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 11://Y1_H
       actualMeasurement_Y(IM_I1_L, name_string[index_of_ekran]);
       break;
     case 12://AP2_В
       actualMeasurement_A(IM_I2_P_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 13://YP2_В
       actualMeasurement_Y(IM_I2_P_H, name_string[index_of_ekran]);
       break;
     case 14://AP1_В
       actualMeasurement_A(IM_I1_P_H, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 15://YP1_В
       actualMeasurement_Y(IM_I1_P_H, name_string[index_of_ekran]);
       break;
     case 16://AP2_H
       actualMeasurement_A(IM_I2_P_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 17://YP2_H
       actualMeasurement_Y(IM_I2_P_L, name_string[index_of_ekran]);
       break;
     case 18://AP1_H
       actualMeasurement_A(IM_I1_P_L, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 19://YP1_H
       actualMeasurement_Y(IM_I1_P_L, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення фазних напруг 
/*****************************************************/
void make_ekran_voltage_phase(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_VOLTAGE_PHASE][MAX_COL_LCD] = 
  {
    " Ua_В =         ",
    " YUa_В=         ",
    " Ub_В =         ",
    " YUb_В=         ",
    " Uc_В =         ",
    " YUc_В=         ",
  };

  unsigned int row = 6;
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//фазних напруг 
    switch(index_of_ekran)
    {
     case 0://AUa_В
       actualMeasurement_A(IM_UA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://YUa_В
       actualMeasurement_Y(IM_UA, name_string[index_of_ekran]);
       break;
     case 2://AUb_В
       actualMeasurement_A(IM_UB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://YUb_В
       actualMeasurement_Y(IM_UB, name_string[index_of_ekran]);
       break;
     case 4://AUc_В
       actualMeasurement_A(IM_UC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://YUc_В
       actualMeasurement_Y(IM_UC, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення лінійних напруг 
/*****************************************************/
void make_ekran_voltage_line(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_VOLTAGE_LINE][MAX_COL_LCD] = 
  {
    " Uab =          ",
    " Yab =          ",
    " Ubc =          ",
    " Ybc =          ",
    " Uca =          ",
    " Yca =          ",
  };

  unsigned int row = 6;
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//лінійних напруг 
    switch(index_of_ekran)
    {
     case 0://Uab_В
       actualMeasurement_A(IM_UAB, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://Yab_В
       actualMeasurement_Y(IM_UAB, name_string[index_of_ekran]);
       break;
     case 2://Ubc_В
       actualMeasurement_A(IM_UBC, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://Ybc_В
       actualMeasurement_Y(IM_UBC, name_string[index_of_ekran]);
       break;
     case 4://Uca_В
       actualMeasurement_A(IM_UCA, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://Yca_В
       actualMeasurement_Y(IM_UCA, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення симетрич напруг 
/*****************************************************/
void make_ekran_voltage_sklad(unsigned int pervynna_vtorynna)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_VOLTAGE_SKLAD][MAX_COL_LCD] = 
  {
    " 3U0 =          ",
    " Y3U0=          ",
    " U2  =          ",
    " YU2 =          ",
    " U1  =          ",
    " YU1 =          ",
  };

  unsigned int row = 6;
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < row)
    {
      /********************************/
//симетрич напруг 
    switch(index_of_ekran)
    {
     case 0://A3U0
       actualMeasurement_A(IM_3U0_r, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 1://Y3U0
       actualMeasurement_Y(IM_3U0_r, name_string[index_of_ekran]);
       break;
     case 2://AU2
       actualMeasurement_A(IM_U2, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 3://YU2
       actualMeasurement_Y(IM_U2, name_string[index_of_ekran]);
       break;
     case 4://AU1
       actualMeasurement_A(IM_U1, name_string[index_of_ekran], pervynna_vtorynna);
       break;
     case 5://YU1
       actualMeasurement_Y(IM_U1, name_string[index_of_ekran]);
       break;
    }//switch
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      /********************************/
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }//for (unsigned int i=0; i< MAX_ROW_LCD; i++)

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
//Формуємо екран відображення частот
/*****************************************************/
void make_ekran_frequency(void)
{
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_FREQUENCY][MAX_COL_LCD] = 
  {
    " f =            "
  };
  int measurement_fequency = (int)(frequency*1000);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій кофігурації
    if (index_of_ekran < MAX_ROW_FOR_MEASURMENT_FREQUENCY)
    {
      /********************************/
      //Вводимо вимірювальні значення
      if (measurement_fequency < 0)
      {
        if (measurement_fequency == (-2*1000))
        {
          /*Частота нижче порогу визначеного константою MIN_FREQUENCY*/
          name_string[index_of_ekran][3] = '<';
          measurement_fequency = MIN_FREQUENCY*1000;
        }
        if (measurement_fequency == (-3*1000))
        {
          /*Частота вище порогу визначеного константою MAX_FREQUENCY*/
          name_string[index_of_ekran][3] = '>';
          measurement_fequency = MAX_FREQUENCY*1000;
        }
      }
      
      convert_and_insert_char_for_frequency(measurement_fequency, name_string[index_of_ekran]);
      /********************************/

      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
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
//Формуємо екран відображення кутів
/*****************************************************/
/*
void make_ekran_angle(void)
{
  int index_language = index_language_in_array(current_settings.language);
  if (base_index_for_angle < 0)
  {
    //Неможливо визначити кути
    const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        "  Невозможно    ",
        " определить углы"
      },
      {
        "   Неможливо    ",
        " визначити кути "
      },
      {
        "   Impossibly   ",
        "to define angles"
      },
      {
        "  Невозможно    ",
        " определить углы"
      }
    };

    for(int index_1 = 0; index_1 < MAX_ROW_LCD; index_1++)
    {
      for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        working_ekran[index_1][index_2] = (index_1 < 2) ? information[index_language][index_1][index_2] : ' ';
    }

    //Відображення курору по вертикалі
    current_ekran.position_cursor_y = 0;
    //Курсор не видимий
    current_ekran.cursor_on = 0;
  }
  else
  {
    unsigned char name_string[MAX_ROW_FOR_MEASURMENT_ANGLE][MAX_COL_LCD] = 
    {
      " Ua  -          ",
      " Ub  -          ",
      " Uc  -          ",
      " Uab -          ",
      " Ubc -          ",
      " Uca -          ",
      " 3U0 -          ",
      " Ia  -          ",
      " Ib  -          ",
      " Ic  -          ",
      " 3I0 -          ",
      "3I0-1-          ",
      "I0.4 -          "
    };
#define SIZE_UNDEF      6
    const unsigned char undefined[MAX_NAMBER_LANGUAGE][SIZE_UNDEF] =
    {
      "Неопр.",
      "Нев.  ",
      "Undef.",
      "Неопр."  
    };
    const unsigned char number_chars_for_undef[MAX_NAMBER_LANGUAGE] = {SIZE_UNDEF, 4, SIZE_UNDEF, SIZE_UNDEF};
#undef SIZE_UNDEF
    
    int number_charts_for_undef_tmp = number_chars_for_undef[index_language];
    
    //
    Завершуємо формування назв кутів
    //
//    if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_IB_I04) == 0)
//    {
//      if (index_language == INDEX_LANGUAGE_EN) name_string[FULL_ORT_3I0_r][3] = 'c';
//      else name_string[FULL_ORT_3I0_r][3] = 'р';
//    }

#define SIZE_NAME_ANALOG_CANAL   5
    for (int index_1 = 0; index_1 < MAX_ROW_FOR_MEASURMENT_ANGLE; index_1++) 
    {
      for (int index_2 = 0; index_2 < SIZE_NAME_ANALOG_CANAL; index_2++) 
      name_string[index_1][SIZE_NAME_ANALOG_CANAL + 1 + index_2] = name_string[base_index_for_angle][index_2];
    }
#undef SIZE_NAME_ANALOG_CANAL
    //
        
//    unsigned int value_index_shift[MAX_ROW_FOR_MEASURMENT_ANGLE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    unsigned int additional_current = 0;
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
  
//    {
//      int delete_index;
//      if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_IB_I04) == 0)
//        delete_index = FULL_ORT_I04;
//      else
//        delete_index = FULL_ORT_3I0_r;
//
//      unsigned int i = delete_index - additional_current;
//      unsigned int additional_current_new = additional_current + 1;
//      if ((i+1) <= position_temp) position_temp--;
//      do
//      {
//        for(unsigned int j = 0; j < MAX_COL_LCD; j++)
//        {
//          if ((i + 1) < (MAX_ROW_FOR_MEASURMENT_ANGLE - additional_current)) name_string[i][j] = name_string[i + 1][j];
//          else name_string[i][j] = ' ';
//        }
//        value_index_shift[i] = additional_current_new;
//        i++;
//      }
//      while (i< (MAX_ROW_FOR_MEASURMENT_ANGLE - additional_current));
//      additional_current = additional_current_new;
//    }

    index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    //Копіюємо  рядки у робочий екран
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати у текучій кофігурації
      if (index_of_ekran < (MAX_ROW_FOR_MEASURMENT_ANGLE// - additional_current))
      {
        int value = phi_angle[index_of_ekran// + value_index_shift[index_of_ekran]];

#define LAST_POSITION_OF_TITLE  10
        
        //Видаляємо зайві пробіли і по можливості звільняємо першу позицю по горизонталі для курсору
        int shift = 0;
        for (int index_1 = 1; index_1 <= LAST_POSITION_OF_TITLE; index_1++)
        {
          if (name_string[index_of_ekran][index_1 - shift] == ' ')
          {
            //Підтягуємо символи, щоб не було багато пробілів
            for (int index_2 = (index_1 - shift); index_2 <= (LAST_POSITION_OF_TITLE - shift); index_2++)
            {
              name_string[index_of_ekran][index_2] = name_string[index_of_ekran][index_2 + 1];
            }
            shift++;
          }
        }
        if (
            (name_string[index_of_ekran][0] != ' ') && 
            (shift > 0) && 
            (
             ((value >= 0 //0.0°) && (value <= 999 //99.9°)) ||
             (
              (value < 0) &&
              (number_charts_for_undef_tmp < (MAX_COL_LCD - LAST_POSITION_OF_TITLE - 1 - 1))  
             )  
            )
           )
        {
          for (int index_1 = (LAST_POSITION_OF_TITLE - shift); index_1 >= 0 ; index_1--)
            name_string[index_of_ekran][index_1 + 1] = name_string[index_of_ekran][index_1];
          name_string[index_of_ekran][0] = ' ';
          shift--;
        }

        int position = LAST_POSITION_OF_TITLE - shift + 1;

#undef LAST_POSITION_OF_TITLE
        
        if (value >= 0)
        {
          int number_charts_for_value = 4; //число до коми, десяткова кома, десті і знак "°"//
          if (value > 999 //99.9°) number_charts_for_value += 2;
          else if (value > 99 //9.9°) number_charts_for_value += 1;
          
          int free_position = MAX_COL_LCD - position - number_charts_for_value;
          if (free_position >= 3)
          {
            name_string[index_of_ekran][position    ] = ' ';
            name_string[index_of_ekran][position + 1] = '=';
            name_string[index_of_ekran][position + 2] = ' ';
            position += 3;
          }
          else if (free_position == 2)
          {
            name_string[index_of_ekran][position    ] = ' ';
            name_string[index_of_ekran][position + 1] = '=';
            position += 2;
          }
          else
          {
            name_string[index_of_ekran][position    ] = '=';
            position += 1;
          }
          
          //Кут між лінійною напругою і фазним струмом (з точністю до десятих)
          int vaga = 1000, first_symbol = 0;
      
          while (vaga > 0)
          {
            int temp_data;
            temp_data = value / vaga; //виділяємо число, яке треба перетворити у символ і помістити у дану позицію екрану
            value %= vaga; //вираховуємо число без символа, який ми зараз будемо виводити на екран
            vaga /=10; //зменшуємо ваговий коефіцієнт в 10 разів
            
            if (vaga == 0) name_string[index_of_ekran][position++] = '.'; //десяткова кома

            //У випадку, якщо ми не у режимі редагування, то нулі перед найстаршим значущим числом приховуємо
            if ((temp_data != 0) || (first_symbol != 0))
            {
              name_string[index_of_ekran][position] = temp_data + 0x30;
              if (first_symbol == 0) first_symbol = 1;
            }
            else
            {
              //Нуль виводимо тільки у тому випадку, якщо це є символ одиниць числа (текуча вага числа рівна 1)
              if (vaga > 1 ) name_string[index_of_ekran][position] = ' ';
              else
              {
                name_string[index_of_ekran][position] = temp_data + 0x30;
                if (first_symbol == 0) first_symbol = 1;
              }
            }
            if (name_string[index_of_ekran][position] != ' ') position++;
          }
          name_string[index_of_ekran][position] = '°';
        }
        else
        {
          int free_position = MAX_COL_LCD - position - number_charts_for_undef_tmp;
          if (free_position >= 3)
          {
            name_string[index_of_ekran][position    ] = ' ';
            name_string[index_of_ekran][position + 1] = '=';
            name_string[index_of_ekran][position + 2] = ' ';
            position += 3;
          }
          else if (free_position == 2)
          {
            name_string[index_of_ekran][position    ] = ' ';
            name_string[index_of_ekran][position + 1] = '=';
            position += 2;
          }
          else
          {
            name_string[index_of_ekran][position    ] = '=';
            position += 1;
          }
          
          for (int j = 0; j < number_charts_for_undef_tmp; j++) name_string[index_of_ekran][position + j] = undefined[index_language][j];
        }
        
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
      }
      else
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_of_ekran++;
    }

    //Відображення курору по вертикалі
    current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    //Курсор видимий
    current_ekran.cursor_on = 1;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_ekran.position_cursor_x = 0;
  //Курсор не мигає
  current_ekran.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
*/
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення потужностей
/*****************************************************/
void make_ekran_power(unsigned int pervynna_vtorynna)
{
  
  unsigned char name_string[MAX_ROW_FOR_MEASURMENT_POWER][MAX_COL_LCD] = 
  {
    " P =            ",
    " Q =            ",
    " S =            ",
    " cos(phi)=      "
  };
  const unsigned int index_of_start_position[MAX_ROW_FOR_MEASURMENT_POWER] = {5, 5, 5, 11};

#define SIZE_POWER_DIMENSION    3
  const unsigned char power_dimension[MAX_ROW_FOR_MEASURMENT_POWER - 1][MAX_NAMBER_LANGUAGE][SIZE_POWER_DIMENSION] = 
  {
    {"Вт ", "Вт ", "W  ", "Вт "},
    {"ВАр", "ВАр", "VAr", "ВАр"},
    {"ВА ", "ВА ", "VA ", "ВА "}
  };
  
  int index_language = index_language_in_array(current_settings.language);
  
  for (unsigned int i = 0; i < (MAX_ROW_FOR_MEASURMENT_POWER - 1); i++)
  {
    for (unsigned int j = 0; j < SIZE_POWER_DIMENSION; j++)
    name_string[i][MAX_COL_LCD - SIZE_POWER_DIMENSION + j] = power_dimension[i][index_language][j];
  }
#undef SIZE_POWER_DIMENSION
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій кофігурації
    if (index_of_ekran < MAX_ROW_FOR_MEASURMENT_POWER)
    {
      unsigned int start_position = index_of_start_position[index_of_ekran];
      /********************************/
      //Вводимо вимірювальні значення  
      int temp_value;
      switch (index_of_ekran)
      {
      case INDEX_ML_P:
        {
          temp_value = P[0];
          break;
        }
      case INDEX_ML_Q:
        {
          temp_value = Q[0];
          break;
        }
      case INDEX_ML_S:
        {
          temp_value = S[0];
          break;
        }
      case INDEX_ML_COS_PHI:
        {
          temp_value = cos_phi_x1000;
          break;
        }
      default:
        {
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(63);
        }
      }
      
      
      if (temp_value < 0)
      {
        temp_value = -temp_value;
        name_string[index_of_ekran][start_position - 1] = '-';
      }

      if (index_of_ekran != INDEX_ML_COS_PHI)
      {
        if (pervynna_vtorynna == 0) 
          convert_and_insert_char_for_measurement(3, (unsigned int)temp_value, 1, 1, name_string[index_of_ekran], start_position);
        else
          convert_and_insert_char_for_measurement(3, (unsigned int)temp_value, current_settings.TVoltage*current_settings.TCurrent_H, 1, name_string[index_of_ekran], start_position);
      }
      else
      {
        unsigned int position = start_position;
        if (S[0] != 0)
        {
          unsigned int dilnyk = 1000;
          for (unsigned int j = 0; j < 4; j++)
          {
            int value;

            value = temp_value / dilnyk; 
            temp_value %= dilnyk;
            name_string[index_of_ekran][position++] = value + 0x30;
            if (j == 0)
            {
              //Десяткова "кома"
              name_string[index_of_ekran][position++] = '.';
            }
            dilnyk /= 10;
          }
        }
        else
        {
#define SIZE_UNDEF      6
          const unsigned char undefined[MAX_NAMBER_LANGUAGE][SIZE_UNDEF] =
          {
            "Неопр.",
            "Нев.  ",
            "Undef.",
            "Неопр."  
          };
        
          position -= 1;
          for (unsigned int j = 0; j < SIZE_UNDEF; j++) name_string[index_of_ekran][position + j] = undefined[index_language][j];
#undef SIZE_UNDEF
        }
      }
      
      unsigned int shift = 0;
      while (
             (name_string[index_of_ekran][start_position] == ' ') &&
             ((start_position + shift) < MAX_COL_LCD)  
            ) 
      {
        for (unsigned int j = start_position; j < (MAX_COL_LCD - 1); j++ ) name_string[index_of_ekran][j] = name_string[index_of_ekran][j + 1];
        name_string[index_of_ekran][MAX_COL_LCD - 1] = ' ';
        shift++;
      }
      /********************************/

      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
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

void actualMeasurement_A(int actualIndex, unsigned char *nameString, unsigned int pervynna_vtorynna)
{
  int meass = 0;
  //Копіюємо вимірювання які потрібні для відображення
  semaphore_measure_values_low1 = 1;
  meass = measurement_middle[actualIndex];
  semaphore_measure_values_low1 = 0;

  int index_language = index_language_in_array(current_settings.language);

  unsigned int transform = 1;
 //Вводимо вимірювальні значення  
  unsigned int start_number_digit_after_point = 3;

  switch(actualIndex)
  {
   //токи фазные
   case IM_IA_H: case IM_IB_H: case IM_IC_H: //case IM_IA_L: case IM_IB_L: case IM_IC_L:
   //токи приведенные
   case IM_IA_P_H: case IM_IB_P_H: case IM_IC_P_H: //case IM_IA_P_L: case IM_IB_P_L: case IM_IC_P_L:
   //токи дифф
   case IM_dIA:  case IM_dIB:  case IM_dIC:  case IM_gdIA: case IM_gdIB: case IM_gdIC:
   case IM_2dIA: case IM_2dIB: case IM_2dIC: case IM_5dIA: case IM_5dIB: case IM_5dIC:
   //токи симметричные
   case IM_3I0_r_H: case IM_I2_H: case IM_I1_H: //case IM_3I0_r_L: case IM_I2_L: case IM_I1_L:
   case IM_I2_P_H:  case IM_I1_P_H:
    transform = current_settings.TCurrent_H;
    nameString[MAX_COL_LCD - 1] = odynyci_vymirjuvannja[index_language][INDEX_A];
   break;

   //токи фазные
   /*case IM_IA_H: case IM_IB_H: case IM_IC_H:*/ case IM_IA_L: case IM_IB_L: case IM_IC_L:
   //токи приведенные
   /*case IM_IA_P_H: case IM_IB_P_H: case IM_IC_P_H:*/ case IM_IA_P_L: case IM_IB_P_L: case IM_IC_P_L:
   //токи дифф
//   case IM_dIA:  case IM_dIB:  case IM_dIC:  case IM_gdIA: case IM_gdIB: case IM_gdIC:
//   case IM_2dIA: case IM_2dIB: case IM_2dIC: case IM_5dIA: case IM_5dIB: case IM_5dIC:
   //токи симметричные
   /*case IM_3I0_r_H: case IM_I2_H: case IM_I1_H:*/ case IM_3I0_r_L: case IM_I2_L: case IM_I1_L:
   case IM_I2_P_L:  case IM_I1_P_L:
    transform = current_settings.TCurrent_L;
    nameString[MAX_COL_LCD - 1] = odynyci_vymirjuvannja[index_language][INDEX_A];
   break;

   //фазних напруг 
   case IM_UA: case IM_UB: case IM_UC: 
   //лінійних напруг 
   case IM_UAB: case IM_UBC: case IM_UCA:
   //симетрич напруг 
   case IM_3U0_r: case IM_U2: case IM_U1:
    transform = current_settings.TVoltage;
    nameString[MAX_COL_LCD - 1] = odynyci_vymirjuvannja[index_language][INDEX_V];
   break;
  }//switch

  if (pervynna_vtorynna == 0) convert_and_insert_char_for_measurement(start_number_digit_after_point, meass, 1, 1, nameString, 7);
  else
  {
   convert_and_insert_char_for_measurement(start_number_digit_after_point, meass, transform, 1, nameString, 7);
  }

}//actualMeasurement_A(int actualIndex)

void actualMeasurement_Y(int actualIndex, unsigned char *nameString)
{
    const unsigned char undefined[MAX_NAMBER_LANGUAGE][MAX_COL_LCD - 7] =
    {
      "Неопред. ",
      "Невизнач.",
      "Undef.   ",
      "Неопред. "  
    };
  int index_language = index_language_in_array(current_settings.language);

  if (base_index_for_angle < 0)
  {
      for (unsigned int j = 7; j<MAX_COL_LCD; j++) nameString[j] = undefined[index_language][j-7];
      return;
  }//if

  int value = phi_angle[actualIndex];

//  nameString[MAX_COL_LCD - 1] = '°';

#define LAST_POSITION_OF_TITLE  7

        int position = LAST_POSITION_OF_TITLE;// - shift + 1;

//#undef LAST_POSITION_OF_TITLE
        
        if (value >= 0)
        {
          int number_charts_for_value = 4; //число до коми, десяткова кома, десті і знак "°"//
          if (value > 999) /*99.9°)*/ number_charts_for_value += 2;
          else if (value > 99) /*9.9°)*/ number_charts_for_value += 1;
          
          int free_position = MAX_COL_LCD - position - number_charts_for_value;
          if (free_position >= 3)
          {
            nameString[position    ] = ' ';
            //nameString[position + 1] = '=';
            nameString[position + 2] = ' ';
            position += 3;
          }
          else if (free_position == 2)
          {
            nameString[position    ] = ' ';
        //    nameString[position + 1] = '=';
            position += 2;
          }
          else
          {
          //  nameString[position    ] = '=';
            position += 1;
          }
          
          //Кут між лінійною напругою і фазним струмом (з точністю до десятих)
          int vaga = 1000, first_symbol = 0;
      
          while (vaga > 0)
          {
            int temp_data;
            temp_data = value / vaga; //виділяємо число, яке треба перетворити у символ і помістити у дану позицію екрану
            value %= vaga; //вираховуємо число без символа, який ми зараз будемо виводити на екран
            vaga /=10; //зменшуємо ваговий коефіцієнт в 10 разів
            
            if (vaga == 0) nameString[position++] = '.'; //десяткова кома

            //У випадку, якщо ми не у режимі редагування, то нулі перед найстаршим значущим числом приховуємо
            if ((temp_data != 0) || (first_symbol != 0))
            {
              nameString[position] = temp_data + 0x30;
              if (first_symbol == 0) first_symbol = 1;
            }
            else
            {
              //Нуль виводимо тільки у тому випадку, якщо це є символ одиниць числа (текуча вага числа рівна 1)
              if (vaga > 1 ) nameString[position] = ' ';
              else
              {
                nameString[position] = temp_data + 0x30;
                if (first_symbol == 0) first_symbol = 1;
              }
            }
            if (nameString[position] != ' ') position++;
          }
          nameString[position] = '°';
        }
        else
        {
          int free_position = MAX_COL_LCD - position;// - number_charts_for_undef_tmp;
          if (free_position >= 3)
          {
            nameString[position    ] = ' ';
    //        nameString[position + 1] = '=';
            nameString[position + 2] = ' ';
            position += 3;
          }
          else if (free_position == 2)
          {
            nameString[position    ] = ' ';
  //          nameString[position + 1] = '=';
            position += 2;
          }
          else
          {
      //      nameString[position    ] = '=';
            position += 1;
          }
       }


}//actualMeasurement_Y

/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
