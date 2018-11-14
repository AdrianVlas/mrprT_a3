#include "header.h"

int ekranListIndex_control_urov1=0;//индекс экранного списка control urov
int ekranListIndex_control_urov2=0;//индекс экранного списка control urov

int validAction_urov(int poz);

/*****************************************************/
//Формуємо екран відображення уставок УРОВ
/*****************************************************/
void make_ekran_setpoint_urov(uint32_t prvv, unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_UROV][MAX_COL_LCD] = 
  {
    {
      "  Уставка УРОВ  "
    },
    {
      "  Уставка ПРВВ  "
    },
    {
      "   CBFP Pickup  "
    },
    {
      "  Уставка УРОВ  "
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_SETPOINT_UROV)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][14] = 0x31;
        if(prvv) working_ekran[i][14] = 0x32;

        vaga = 1000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для уставки УРОВ
        if (view == true) value = current_settings.setpoint_urov[prvv][group]; //у змінну value поміщаємо значення уставки ЗЗ
        else value = edition_settings.setpoint_urov[prvv][group];
        first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
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

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
  if (current_ekran.edition == 0)
  {
    current_ekran.position_cursor_x = COL_SETPOINT_UROV_BEGIN;
    int last_position_cursor_x = COL_SETPOINT_UROV_END;

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
//Формуємо екран відображення витримок УРОВ
/*****************************************************/
void make_ekran_timeout_urov(uint32_t prvv, unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_UROV][MAX_COL_LCD] = 
  {
    {
      " 1 Ступень УРОВ ",
      " 2 Ступень УРОВ "
    },
    {
      " 1 Ступінь ПРВВ ",
      " 2 Ступінь ПРВВ "
    },
    {
      "   1 Stage CBFP ",
      "   2 Stage CBFP "
    },
    {
      " 1 Ступень УРОВ ",
      " 2 Ступень УРОВ "
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
    if (index_of_ekran_tmp < MAX_ROW_FOR_TIMEOUT_UROV)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
        working_ekran[i][15] = 0x31;
        if(prvv) working_ekran[i][15] = 0x32;
        if (index_of_ekran_tmp == INDEX_ML_TMOUROV1)
        {
          vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 1 Ступені УРОВ
          if (view == true) value = current_settings.timeout_urov_1[prvv][group]; //у змінну value поміщаємо значення витримки 1 Ступені УРОВ
          else value = edition_settings.timeout_urov_1[prvv][group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
        else if (index_of_ekran_tmp == INDEX_ML_TMOUROV2)
        {
          vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 2 Ступені УРОВ
          if (view == true) value = current_settings.timeout_urov_2[prvv][group]; //у змінну value поміщаємо значення витримки 2 Ступені УРОВ
          else value = edition_settings.timeout_urov_2[prvv][group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
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

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
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
//Формуємо екран відображення значення управлінської інформації для УРОВ
/*****************************************************/
void make_ekran_control_urov(uint32_t prvv)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_UROV - NUMBER_UP + 1][MAX_COL_LCD] = 
  {
    {
      "      УРОВ      ",
      "  Выбор I УРОВ  ",
      "  Пуск от ОЗТ1  ",
      "  Пуск от ОЗТ2  ",
      "  Пуск от МТЗ1  ",
      "  Пуск от МТЗ2  ",
      "  Пуск от МТЗ3  ",
      "  Пуск от МТЗ4  ",
      "  Пуск от 3U0   ",
      " Пуск от ТЗНП1  ",
      " Пуск от ТЗНП2  ",
      " Пуск от ТЗНП3  ",
      " Пуск от ТЗНП4  ",
      " Пуск от ЗОП1   ",
      " Пуск от ЗОП2   ",
      " Пуск от ЗНмин1 ",
      " Пуск от ЗНмин2 ",
      " Пуск от ЗНмакс1",
      " Пуск от ЗНмакс2",
      "  Пуск от ГЗ1   ",
      "  Пуск от ГЗ2   ",
      " Пуск от ГЗ-РПН ",
      "   Пуск от ТЗ   ",
      "  Пуск от УЗx   "
    },
    {
      "      ПРВВ      ",
      "  Вибір I ПРВВ  ",
      " Пуск від ОЗТ1  ",
      " Пуск від ОЗТ2  ",
      " Пуск від МСЗ1  ",
      " Пуск від МСЗ2  ",
      " Пуск від МСЗ3  ",
      " Пуск від МСЗ4  ",
      "  Пуск від 3U0  ",
      " Пуск від СЗНП1 ",
      " Пуск від СЗНП2 ",
      " Пуск від СЗНП3 ",
      " Пуск від СЗНП4 ",
      " П.від ЗЗП1     ",
      " П.від ЗЗП2     ",
      " Пуск від ЗНмін1",
      " Пуск від ЗНмін2",
      "Пуск від ЗНмакс1",
      "Пуск від ЗНмакс2",
      "  Пуск від ГЗ1  ",
      "  Пуск від ГЗ2  ",
      " Пуск від ГЗ-РПН",
      "   Пуск від ТЗ  ",
      "  Пуск від УЗx  "
    },
    {
      "      CBFP      ",
      "  Select I CBFP ",
      "  Пуск от ОЗТ1  ",
      "  Пуск от ОЗТ2  ",
      " Start from OCP1",
      " Start from OCP2",
      " Start from OCP3",
      " Start from OCP4",
      " Start from 3U0 ",
      " Пуск от ТЗНП1  ",
      " Пуск от ТЗНП2  ",
      " Пуск от ТЗНП3  ",
      " Пуск от ТЗНП4  ",
      "Start from NPSP1",
      "Start from NPSP2",
      "Start from Umin1",
      "Start from Umin2",
      "Start from Umax1",
      "Start from Umax2",
      "  Пуск от ГЗ1   ",
      "  Пуск от ГЗ2   ",
      " Пуск от ГЗ-РПН ",
      "   Пуск от ТЗ   ",
      "  Пуск от УЗx   "
    },
    {
      "      УРОВ      ",
      "  Выбор I УРОВ  ",
      "  Пуск от ОЗТ1  ",
      "  Пуск от ОЗТ2  ",
      "  Пуск от МТЗ1  ",
      "  Пуск от МТЗ2  ",
      "  Пуск от МТЗ3  ",
      "  Пуск от МТЗ4  ",
      "  Пуск от 3U0   ",
      " Пуск от ТЗНП1  ",
      " Пуск от ТЗНП2  ",
      " Пуск от ТЗНП3  ",
      " Пуск от ТЗНП4  ",
      " Пуск от ЗОП1   ",
      " Пуск от ЗОП2   ",
      " Пуск от ЗНмин1 ",
      " Пуск от ЗНмин2 ",
      " Пуск от ЗНмакс1",
      " Пуск от ЗНмакс2",
      "  Пуск от ГЗ1   ",
      "  Пуск от ГЗ2   ",
      " Пуск от ГЗ-РПН ",
      "   Пуск от ТЗ   ",
      "  Пуск от УЗx   "
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
        //виводимо заголовок
        else {
          //У непарному номері рядку виводимо заголовок
          if(index_of_ekran_tmp>=INDEX_ML_CTRUROV_STARTED_FROM_UP1) {
             for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][INDEX_ML_CTRUROV_STARTED_FROM_UP1][j];
             working_ekran[i][index_number_UP[index_language]] = 0x31+index_of_ekran_tmp - INDEX_ML_CTRUROV_STARTED_FROM_UP1;
          }//if
          else for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran_tmp][j];
          if(index_of_ekran_tmp==INDEX_ML_CTRUROV_STATE) working_ekran[i][10] = 0x31+prvv;
        }//виводимо заголовок
      }//if (i==0 || i==2)
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
        const unsigned char hi_low_voltage[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"       ВН       ", "       НН       "},
          {"       ВН       ", "       НН       "},
          {"       HV       ", "       LV       "},
          {"       ВН       ", "       НН       "}
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

  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}

int validAction_urov(int poz)
{
  if((current_settings.configuration & (1<<OZT_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_OZT1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_OZT2) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<P_3U0_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_P_3U0) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<TZNP_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP2) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP3) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TZNP4) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_ZOP2) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<GP_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP1) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP2) return -1;//убрать позицию
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_GP_RPN) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<TP_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz == INDEX_ML_CTRUROV_STARTED_FROM_TP) return -1;//убрать позицию
  }//if
  if((current_settings.configuration & (1<<UP_BIT_CONFIGURATION)) == 0)
  {//нет config
     if(poz >= INDEX_ML_CTRUROV_STARTED_FROM_UP1) return -1;//убрать позицию
  }//if
  return 1;
}//validAction_urov(int poz)

int normalizEkranIndex_control_urov()
{
//нормализация экранного индекса
  if(validAction_urov(current_ekran.index_position)<0) current_ekran.index_position = INDEX_ML_CTRUROV_STATE;
  int ekranIndex = findEkranListIndex_control_urov(current_ekran.index_position);//найти экранный индeкс
  if(ekranIndex<0) return 0;//что-то пошло не так
  return ekranIndex;
}//normalizEkranIndex_control_urov()

int findMenuListIndex_control_urov(int ekranListIndex)
{
//найти индeкс меню control по экранному индексу
  int index = -1;
  if(ekranListIndex<0) return -1;
  for(int i=0; i< MAX_ROW_FOR_CONTROL_UROV; i++)
  {
    if(validAction_urov(i)>0) index++;
    if(index==ekranListIndex) return i;
  }//for
  return -1;//не найдено
}//findMenuListIndex_control_urov(int ekranListIndex)
int findEkranListIndex_control_urov(int menuListIndex)
{
//найти экранный индeкс по  индексу меню control 
  if(menuListIndex<0) return -1;
  int ekranListSize = findEkranListSize_control_urov();
  for(int i=0; i< ekranListSize; i++)
  {
   if(findMenuListIndex_control_urov(i)!=menuListIndex) continue;
   return i;
  }//for
  return -1;//не найдено
}//findEkranListIndex_control_urov(int menuListIndex)

int findEkranListSize_control_urov(void)
{
//найти размер экранного меню
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
