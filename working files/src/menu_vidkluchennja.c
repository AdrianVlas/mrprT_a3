#include "header.h"

/*****************************************************/
//Формуємо екран відображення повідомдень про відключення від захистів
/*****************************************************/
void make_ekran_vidkluchenja(void)
{
  int index_language = index_language_in_array(current_settings.language);
  
  //очищаємо робочий екран
  for (unsigned int i = 0; i < MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
  }
  int32_t index_position_tmp = current_ekran.index_position;
  unsigned char *point = info_vidkluchennja_vymykachatime[index_position_tmp];

  //День
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY1] = ((*(point + 4)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY2] = ((*(point + 4)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY2 + 1] = '-';

  //Місяць
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY1] = ((*(point + 5)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY2] = ((*(point + 5)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY2 + 1] = '-';

  //Рік
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY1] = ((*(point + 6)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY2] = ((*(point + 6)) & 0xf) + 0x30;

  //Година
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT1] = ((*(point + 3)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT2] = ((*(point + 3)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT2 + 1] = ':';

  //Хвилини
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT1] = ((*(point + 2)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT2] = ((*(point + 2)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT2 + 1] = ':';

  //Секунди
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST1] = ((*(point + 1)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST2] = ((*(point + 1)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST2 + 1] = '.';

  //Соті секунд
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST1] = ((*(point + 0)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST2] = ((*(point + 0)) & 0xf) + 0x30;
  
  const unsigned char information_1[MAX_NAMBER_LANGUAGE][VYMKNENNJA_VID_MAX_NUMBER - NUMBER_UP + 1][7] = 
  {
    {"   ОЗТ1", "   ОЗТ2", "   МТЗ1", "   МТЗ2", "   МТЗ3", "   МТЗ4", "    3U0", "  ТЗНП1", "  ТЗНП2", "  ТЗНП3", "  ТЗНП4", "УРОВ1_1", "УРОВ1_2", "УРОВ2_1", "УРОВ2_2", "   ЗОП1", "   ЗОП2", " ЗНмин1", " ЗНмин2", "ЗНмакc1", "ЗНмакc2", "    ГЗ1", "    ГЗ2", " ГЗ-РПН", "     ТЗ", "    УЗx", " Другие"},
    {"   ОЗТ1", "   ОЗТ2", "   МCЗ1", "   МCЗ2", "   МCЗ3", "   МCЗ4", "    3U0", "  СЗНП1", "  СЗНП2", "  СЗНП3", "  СЗНП4", "ПРВВ1_1", "ПРВВ1_2", "ПРВВ2_1", "ПРВВ2_2", "   ЗЗП1", "   ЗЗП2", " ЗНмін1", " ЗНмін2", "ЗНмакc1", "ЗНмакc2", "    ГЗ1", "    ГЗ2", " ГЗ-РПН", "     ТЗ", "    УЗx", "   Інші"},
    {"   OZT1", "   OZT2", "   OCP1", "   OCP2", "   OCP3", "   OCP4", "    3U0", "  ТЗНП1", "  ТЗНП2", "  ТЗНП3", "  ТЗНП4", "CBFP1_1", "CBFP1_2", "CBFP2_1", "CBFP2_2", "  NPSP1", "  NPSP2", "  Umin1", "  Umin2", "  Umax1", "  Umax2", "    GP1", "    GP2", " GP-RPN", "     TP", "    УЗx", "  Other"},
    {"   ОЗТ1", "   ОЗТ2", "   МТЗ1", "   МТЗ2", "   МТЗ3", "   МТЗ4", "    3U0", "  ТЗНП1", "  ТЗНП2", "  ТЗНП3", "  ТЗНП4", "УРОВ1_1", "УРОВ1_2", "УРОВ2_1", "УРОВ2_2", "   ЗОП1", "   ЗОП2", " ЗНмин1", " ЗНмин2", "ЗНмакc1", "ЗНмакc2", "    ГЗ1", "    ГЗ2", " ГЗ-РПН", "     ТЗ", "    УЗx", " Другие"}
  };
  if ((index_position_tmp < VYMKNENNJA_VID_UP1) || (index_position_tmp >= (VYMKNENNJA_VID_UP1 + NUMBER_UP)))
  {
    if (index_position_tmp < VYMKNENNJA_VID_UP1)
      point = (unsigned char *)information_1[index_language][index_position_tmp];
    else
      point = (unsigned char *)information_1[index_language][index_position_tmp - NUMBER_UP + 1];

    for (unsigned int i = 0; i < 7; i++) working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY2 + 2 + i] = *(point + i);
  }
  else
  {
    point = (unsigned char *)information_1[index_language][VYMKNENNJA_VID_UP1];

    for (unsigned int i = 0; i < 7; i++) 
    {
      working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY2 + 2 + i] = (i != (7 - 1)) ? *(point + i) : (index_position_tmp - VYMKNENNJA_VID_UP1 + 1 + 0x30);
    }
  }
    
  
  const unsigned char information_2[MAX_NAMBER_LANGUAGE][VYMKNENNJA_VID_MAX_NUMBER - NUMBER_UP + 1][4] = 
  {
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "}
  };

  if (index_position_tmp < VYMKNENNJA_VID_UP1)
    point = (unsigned char *)information_2[index_language][index_position_tmp];
  else if (index_position_tmp >= (VYMKNENNJA_VID_UP1 + NUMBER_UP))
    point = (unsigned char *)information_2[index_language][index_position_tmp - NUMBER_UP + 1];
  else
    point = (unsigned char *)information_2[index_language][VYMKNENNJA_VID_UP1];
  for (unsigned int i = 0; i < 4; i++) working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST2 + 2 + i] = *(point + i);

  //Курсор по горизонталі відображається на першій позиції
  current_ekran.position_cursor_x = 0;
  current_ekran.position_cursor_y = 0;
  //Курсор невидимий
  current_ekran.cursor_on = 0;
  //Курсор не мигає
  current_ekran.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
