#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")
#define SRAM1_AR _Pragma("location=\"Analog_Registrator_Buffer\"")

typedef struct
{
  int current_level;                  //Текучий рівень відображуваного екрану
 
  int index_position;                 //Вказує на якій ми зараз є позиції

  int position_cursor_x;              //X - координата курсору
  int position_cursor_y;              //Y - координата курсору
  
  unsigned int edition;               //0 - вікно зараз не в режимі редагується;
                                      //1 - вікно зараз в режимі редагування;
                                      //2 - вікно чекає підтвердження редагування
                                      //3 - у вікні виведено повідомлення про те, що під час введення даних була зафіксована помилка величиниданих
  
  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
  
  unsigned int current_action;        //Дія яку треба виконати з текучим екраном
                                      //0 - Нічого не виконувати
                                      //1 - Перемістити курсор, ш/або змінити стан його відображення
                                      //2 - Повністю обновити інформацію

} __CURRENT_EKRAN;

typedef struct
{
  int position_cursor_x;              //X - координата курсору

  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
} __PREVIOUS_STATE_CURSOR;

typedef struct
{
  //Тип пристрою
  unsigned int device_id;
  
  //Дискретні входи
  unsigned int type_of_input;                          //Тип дискретного входу 0 - прямий, 1 - інверсний
  unsigned int type_of_input_signal;                   //Тип сигналу дискретного входу 0 - постійний , 1 - змінний
  unsigned int dopusk_dv[NUMBER_INPUTS];              //Допуски ДВ
    
  unsigned int ranguvannja_inputs[N_SMALL*NUMBER_INPUTS]; //Ранжування дискретних входів
  unsigned int ranguvannja_outputs[N_BIG*NUMBER_OUTPUTS]; //Ранжування дискретних вхиодів
  unsigned int ranguvannja_leds[N_BIG*NUMBER_LEDS];       //Ранжування свіотіндикаторів

  unsigned int ranguvannja_analog_registrator[N_BIG];     //Ранжування аналогового реєстратора
  unsigned int ranguvannja_digital_registrator[N_BIG];    //Ранжування дискретного реєстратора
  
  //Блок ввімкнення-вимкнення вимикача
  unsigned int ranguvannja_off_cb[NUMBER_ON_OFF][N_BIG];  //Ранжування блоку вимкнення силового вимикача
  unsigned int ranguvannja_on_cb[NUMBER_ON_OFF][N_BIG];   //Ранжування блоку ввімкнення силового вимикача
  
  //Тип дискретних виходів
  unsigned int type_of_output;                        //Тип дискретних виходів
                                                      //0 - Командний
                                                      //1 - Сигналький (постійний або імпульсний)
  
  unsigned int type_of_output_modif;                  //Тип дискретних сигнальних виходів
                                                      //0 - Сигналький (постійний)
                                                      //1 - Сигналький (імпульсний)
  
  //Тип світлоіндикаторів
  unsigned int type_of_led;                           //Тип світлоіндикаторі
                                                      //0 - Нормальний
                                                      //1 - Тригерний
    
  unsigned int number_iteration_el;                                             //Максимадбна кількість ітерацій для розширеної логіки
//  unsigned int number_defined_df;                                               //Кількість визначуваних функцій у конфігурації приладу
//  unsigned int number_defined_dt;                                               //Кількість визначуваних тригерів у конфігурації приладу
//  unsigned int number_defined_and;                                              //Кількість визначуваних "І" у конфігурації приладу
//  unsigned int number_defined_or;                                               //Кількість визначуваних "АБО" у конфігурації приладу
//  unsigned int number_defined_xor;                                              //Кількість визначуваних "Викл.ВБО" у конфігурації приладу
//  unsigned int number_defined_not;                                              //Кількість визначуваних "НЕ" у конфігурації приладу

  //Опреділювальні функції
  unsigned int type_df;                                                 //Тип опреділювальної функції
                                                                        //0 - Пряма
                                                                        //1 - Зворотня
  unsigned int timeout_pause_df[NUMBER_DEFINED_FUNCTIONS];              //Час затримки спрацюваня опреділювальної функції
  unsigned int timeout_work_df[NUMBER_DEFINED_FUNCTIONS];               //Час роботи опреділювальної функції
  unsigned int ranguvannja_df_source_plus[N_BIG*NUMBER_DEFINED_FUNCTIONS];  //Ранжування прямих команд опреділювальниї функцій
  unsigned int ranguvannja_df_source_minus[N_BIG*NUMBER_DEFINED_FUNCTIONS]; //Ранжування інверсних команд опреділювальниї функцій
  unsigned int ranguvannja_df_source_blk[N_BIG*NUMBER_DEFINED_FUNCTIONS];   //Ранжування команд блокування опреділювальниї функцій

  unsigned int ranguvannja_set_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS];   //Ранжування прямих команд встановлення опреділювальних триґерів
  unsigned int ranguvannja_set_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];  //Ранжування інверсних команд встановлення опреділювальних триґерів
  unsigned int ranguvannja_reset_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS]; //Ранжування прямих команд скидання опреділювальних триґерів
  unsigned int ranguvannja_reset_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];//Ранжування інверсних команд скидання опреділювальних триґерів

  unsigned int ranguvannja_d_and[N_BIG*NUMBER_DEFINED_AND];                     //Ранжування команд джерел визначуваних "І"
  unsigned int ranguvannja_d_or[N_BIG*NUMBER_DEFINED_OR];                       //Ранжування команд джерел визначуваних "АБО"
  unsigned int ranguvannja_d_xor[N_BIG*NUMBER_DEFINED_XOR];                     //Ранжування команд джерел визначуваних "Викл.АБО"
  unsigned int ranguvannja_d_not[N_BIG*NUMBER_DEFINED_NOT];                     //Ранжування команд джерел визначуваних "НЕ"
  
  uint32_t ranguvannja_tf[NUMBER_TRANSFER_FUNCTIONS];                           //Ранжування передавальних функцій
  
  uint32_t buttons_mode;                                                        //Режими роботи ФК
                                                                                //0 - Звичайна кнопка
                                                                                //1 - Двопозиційний ключ
  unsigned int ranguvannja_buttons[N_SMALL*NUMBER_DEFINED_BUTTONS];             //Ранжування опреділюваних кнопок
  
  unsigned int configuration;         //Конфігурація приладу
  
  unsigned int grupa_ustavok;         //Група уставок
                                      // 1 - Група 1
                                      // 2 - Група 2
                                      // 3 - Група 3
                                      // 4 - Група 4
  
  //ОЗТ
  int32_t type_con_ozt;                                         //Група з'єднань (0 - Група 1; 1 - Група 1; 2 - Група 11)
  /*Диф.струм*/
  uint32_t pickup_ozt_Id0[NUMBER_GROUP_USTAVOK];                //Уставка Id0 (початкова горизонтальна ділянка)#5.3.29
  uint32_t pickup_ozt_delta_Id[NUMBER_GROUP_USTAVOK];           //Уставка  Дельта Iд.відс. #5.3.20
  /*Гальмування*/
  uint32_t pickup_ozt_Kg1[NUMBER_GROUP_USTAVOK];                //Уставка kг1 (коефіцієнт гальмування ділянки 1) #5.3.31
  uint32_t pickup_ozt_Kg2[NUMBER_GROUP_USTAVOK];                //Уставка kг2 (коефіцієнт гальмування ділянки 2) #5.3.34
  uint32_t pickup_ozt_k[NUMBER_GROUP_USTAVOK];                  //Уставка k коефіцієхнт розподілу для розрахунку струму гальмування) #5.3.27
  uint32_t pickup_ozt_Ig0[NUMBER_GROUP_USTAVOK];                //Уставка Iг0 (струм початкового гальмування) #5.3.32
  uint32_t pickup_ozt_Ig_obm[NUMBER_GROUP_USTAVOK];             //Уставка Iг.обм (струм переходу з ділянки 1 у ділянку 2 гальмування) #5.3.35
  /*Аперіодична складова*/
  uint32_t pickup_ozt_K_aI[NUMBER_GROUP_USTAVOK];                //Уставка відносної величини для аперіодичної складової (з точністю до дисячних, тобто x1000) #5.3.13
  /*Намагнічування*/
  uint32_t pickup_ozt_K_2I[NUMBER_GROUP_USTAVOK];                //Уставка відносної виличини для другої гармоніки (з точністю до дисячних, тобто x1000) #5.3.17
  uint32_t pickup_ozt_K_5I[NUMBER_GROUP_USTAVOK];                //Уставка відносної виличини для п'ятої гармоніки (з точністю до дисячних, тобто x1000) #5.3.18
  /*Коефіцієнт повернення*/
  uint32_t pickup_ozt_kp[NUMBER_GROUP_USTAVOK];                 //Уставка Коефіцієнт повернення для ОЗТ #5.3.39

  /*Вимтримки*/
  int32_t timeout_ozt1[NUMBER_GROUP_USTAVOK];                   //Витримка "Час дії першого ступеня" #5.3.36
  int32_t timeout_ozt2[NUMBER_GROUP_USTAVOK];                   //Витримка "Час дії другого ступеня" #5.3.37
  int32_t timeout_ozt2_a_blk[NUMBER_GROUP_USTAVOK];             //Витримка "Час дії блокування другого ступеня від аперіодичної складової" #5.3.14

  uint32_t control_ozt;                                         //Поле для управління ОЗТ
  
  //МТЗ
  int type_mtz1;                                                //Тип МТЗ1 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_1[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ першої ступені (проста)
  unsigned int setpoint_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ першої ступені (направлена:вперед)
  unsigned int setpoint_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ першої ступені (направлена:назад)
  unsigned int setpoint_mtz_1_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ першої ступені (кут довороту)
           int setpoint_mtz_1_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ першої ступені (косинус кута довороту)
           int setpoint_mtz_1_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ першої ступені (синус кута довороту)
  unsigned int setpoint_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ першої ступені (по напрузі)
  unsigned int setpoint_mtz_1_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ першої ступені (напруга пуску)
  int type_mtz2;                                                //Тип МТЗ2 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі, 3 - Залежна А, 4 - Залежна В, 5 - Залежна С)
  unsigned int setpoint_mtz_2[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ другої ступені
  unsigned int setpoint_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ другої ступені (направлена:вперед)
  unsigned int setpoint_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ другої ступені (направлена:назад)
  unsigned int setpoint_mtz_2_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ другої ступені (кут довороту)
           int setpoint_mtz_2_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ другої ступені (косинус кута довороту)
           int setpoint_mtz_2_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ другої ступені (синус кута довороту)
  unsigned int setpoint_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ другої ступені (по напрузі)
  unsigned int setpoint_mtz_2_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ другої ступені (напруга пуску)
  int type_mtz3;                                                //Тип МТЗ3 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_3[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ третьої ступені
  unsigned int setpoint_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ третьої ступені (направлена:вперед)
  unsigned int setpoint_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ третьої ступені (направлена:назад)
  unsigned int setpoint_mtz_3_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ третьої ступені (кут довороту)
           int setpoint_mtz_3_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ третьої ступені (косинус кута довороту)
           int setpoint_mtz_3_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ третьої ступені (синус кута довороту)
  unsigned int setpoint_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ третьої ступені (по напрузі)
  unsigned int setpoint_mtz_3_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ третьої ступені (напруга пуску)
  int type_mtz4;                                                //Тип МТЗ4 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_4[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ четвертої ступені
  unsigned int setpoint_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ четвертої ступені (направлена:вперед)
  unsigned int setpoint_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ четвертої ступені (направлена:назад)
  unsigned int setpoint_mtz_4_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ четвертої ступені (кут довороту)
           int setpoint_mtz_4_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ четвертої ступені (косинус кута довороту)
           int setpoint_mtz_4_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ четвертої ступені (синус кута довороту)
  unsigned int setpoint_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ четвертої ступені (по напрузі)
  unsigned int setpoint_mtz_4_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ четвертої ступені (напруга пуску)

  int timeout_mtz_1[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ першої ступені
  int timeout_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ першої ступені (направлена:вперед)
  int timeout_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ першої ступені (направлена:назад)
  int timeout_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ першої ступені (по напрузі)
  int timeout_mtz_2[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ другої ступені
  int timeout_mtz_2_pr[NUMBER_GROUP_USTAVOK];                   //Витримка присторення МТЗ другої ступені
  int timeout_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ другої ступені (направлена:вперед)
  int timeout_mtz_2_n_vpered_pr[NUMBER_GROUP_USTAVOK];          //Витримка присторення МТЗ другої ступені (направлена:вперед)
  int timeout_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ другої ступені (направлена:назад)
  int timeout_mtz_2_n_nazad_pr[NUMBER_GROUP_USTAVOK];           //Витримка присторення МТЗ другої ступені (направлена:назад)
  int timeout_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ другої ступені (по напрузі)
  int timeout_mtz_2_po_napruzi_pr[NUMBER_GROUP_USTAVOK];        //Витримка присторення МТЗ другої ступені (по напрузі)
  int timeout_mtz_2_vvid_pr[NUMBER_GROUP_USTAVOK];              //Витримка вводу присорення МТЗ2
  int timeout_mtz_3[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ третьої ступені
  int timeout_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ третьої ступені (направлена:вперед)
  int timeout_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ третьої ступені (направлена:назад)
  int timeout_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ третьої ступені (по напрузі)
  int timeout_mtz_4[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ четвертої ступені
  int timeout_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ третьої ступені (направлена:вперед)
  int timeout_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ третьої ступені (направлена:назад)
  int timeout_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ третьої ступені (по напрузі)

  unsigned int control_mtz;                                     //Поле для управління МТЗ
  
  //3U0
  uint32_t setpoint_P_3U0[NUMBER_GROUP_USTAVOK];                //Уставка 3U0

  int32_t timeout_P_3U0[NUMBER_GROUP_USTAVOK];                  //Витримка 3U0

  uint32_t control_P_3U0;                                       //Поле для управління 3U0

  //ТЗНП
  unsigned int setpoint_tznp_1_3I0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3I0 першої ступені (направлена:вперед)
  unsigned int setpoint_tznp_1_3U0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3U0 першої ступені  (направлена:вперед)
  unsigned int setpoint_tznp_1_3I0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3I0 першої ступені (направлена:назад)
  unsigned int setpoint_tznp_1_3U0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3U0 першої ступені  (направлена:назад)
  unsigned int setpoint_tznp_1_angle[NUMBER_GROUP_USTAVOK];     //Уставка ТЗНП першої ступені (кут довороту)
           int setpoint_tznp_1_angle_cos[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої ступені (косинус кута довороту)
           int setpoint_tznp_1_angle_sin[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої ступені (синус кута довороту)
  unsigned int setpoint_tznp_2_3I0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3I0 другої ступені (направлена:вперед)
  unsigned int setpoint_tznp_2_3U0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3U0 другої ступені  (направлена:вперед)
  unsigned int setpoint_tznp_2_3I0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3I0 другої ступені (направлена:назад)
  unsigned int setpoint_tznp_2_3U0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3U0 другої ступені  (направлена:назад)
  unsigned int setpoint_tznp_2_angle[NUMBER_GROUP_USTAVOK];     //Уставка ТЗНП другої ступені (кут довороту)
           int setpoint_tznp_2_angle_cos[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП другої ступені (косинус кута довороту)
           int setpoint_tznp_2_angle_sin[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП другої ступені (синус кута довороту)
  unsigned int setpoint_tznp_3_3I0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3I0 третьої ступені (направлена:вперед)
  unsigned int setpoint_tznp_3_3U0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3U0 третьої ступені  (направлена:вперед)
  unsigned int setpoint_tznp_3_3I0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3I0 третьої ступені (направлена:назад)
  unsigned int setpoint_tznp_3_3U0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3U0 третьої ступені  (направлена:назад)
  unsigned int setpoint_tznp_3_angle[NUMBER_GROUP_USTAVOK];     //Уставка ТЗНП першої третьої (кут довороту)
           int setpoint_tznp_3_angle_cos[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої третьої (косинус кута довороту)
           int setpoint_tznp_3_angle_sin[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої третьої (синус кута довороту)
  unsigned int setpoint_tznp_4_3I0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3I0 третьої ступені (направлена:вперед)
  unsigned int setpoint_tznp_4_3U0_vpered[NUMBER_GROUP_USTAVOK];//Уставка ТЗНП 3U0 третьої ступені  (направлена:вперед)
  unsigned int setpoint_tznp_4_3I0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3I0 третьої ступені (направлена:назад)
  unsigned int setpoint_tznp_4_3U0_nazad[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП 3U0 третьої ступені  (направлена:назад)
  unsigned int setpoint_tznp_4_angle[NUMBER_GROUP_USTAVOK];     //Уставка ТЗНП першої третьої (кут довороту)
           int setpoint_tznp_4_angle_cos[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої третьої (косинус кута довороту)
           int setpoint_tznp_4_angle_sin[NUMBER_GROUP_USTAVOK]; //Уставка ТЗНП першої третьої (синус кута довороту)

  int timeout_tznp_1_vpered[NUMBER_GROUP_USTAVOK];              //Витримка ТЗНП першої ступені (направлена:вперед)
  int timeout_tznp_1_nazad[NUMBER_GROUP_USTAVOK];               //Витримка ТЗНП першої ступені (направлена:назад)
  int timeout_tznp_2_vpered[NUMBER_GROUP_USTAVOK];              //Витримка ТЗНП другої ступені (направлена:вперед)
  int timeout_tznp_2_nazad[NUMBER_GROUP_USTAVOK];               //Витримка ТЗНП другої ступені (направлена:назад)
  int timeout_tznp_3_vpered[NUMBER_GROUP_USTAVOK];              //Витримка ТЗНП третьої ступені (направлена:вперед)
  int timeout_tznp_3_nazad[NUMBER_GROUP_USTAVOK];               //Витримка ТЗНП третьої ступені (направлена:назад)
  int timeout_tznp_4_vpered[NUMBER_GROUP_USTAVOK];              //Витримка ТЗНП четвертої ступені (направлена:вперед)
  int timeout_tznp_4_nazad[NUMBER_GROUP_USTAVOK];               //Витримка ТЗНП четвертої ступені (направлена:назад)

   unsigned int control_tznp;                                   //Поле для управління ТЗНП
  
  //УРОВ
  unsigned int setpoint_urov[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];//уставка УРОВ
  int timeout_urov_1[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];        //Витримка УРОВ першої ступені
  int timeout_urov_2[NUMBER_PRVV][NUMBER_GROUP_USTAVOK];        //Витримка УРОВ другої ступені
  unsigned int control_urov[NUMBER_PRVV];                       //Поле для управління УРОВ

  //ЗОП
  unsigned int setpoint_zop1[NUMBER_GROUP_USTAVOK];         //уставка ЗОП1
  unsigned int setpoint_zop2[NUMBER_GROUP_USTAVOK];         //уставка ЗОП2
  int timeout_zop1[NUMBER_GROUP_USTAVOK];                   //Витримка  ЗОП1
  int timeout_zop2[NUMBER_GROUP_USTAVOK];                   //Витримка  ЗОП2
  unsigned int control_zop;                                 //Поле для управління ЗОП

  //Umin
  unsigned int setpoint_Umin1[NUMBER_GROUP_USTAVOK];        //уставка Umin1
  unsigned int setpoint_Umin1_Iblk[NUMBER_GROUP_USTAVOK];   //уставка блокування по струму Umin1
  unsigned int setpoint_Umin2[NUMBER_GROUP_USTAVOK];        //уставка Umin2
  unsigned int setpoint_Umin2_Iblk[NUMBER_GROUP_USTAVOK];   //уставка блокування по струму Umin2
  int timeout_Umin1[NUMBER_GROUP_USTAVOK];                    //Витримка  Umin1
  int timeout_Umin2[NUMBER_GROUP_USTAVOK];                    //Витримка  Umin2
  unsigned int control_Umin;                                 //Поле для управління Umin
  
  //Umax
  unsigned int setpoint_Umax1[NUMBER_GROUP_USTAVOK];        //уставка Umax1
  unsigned int setpoint_Umax2[NUMBER_GROUP_USTAVOK];        //уставка Umax2
  uint32_t setpoint_kp_Umax[NUMBER_GROUP_USTAVOK];          //Уставка коефіцієнт повернення ЗНмакс
  int timeout_Umax1[NUMBER_GROUP_USTAVOK];                  //Витримка  Umax1
  int timeout_Umax2[NUMBER_GROUP_USTAVOK];                  //Витримка  Umax2
  unsigned int control_Umax;                                //Поле для управління Umax

  //КЗ З/В
  unsigned int pickup_kz_zv[NUMBER_GROUP_USTAVOK];           //Уставка КЗ З/В
  unsigned int pickup_kz_zv_angle[NUMBER_GROUP_USTAVOK];     //Уставка кут КЗ З/В
           int pickup_kz_zv_angle_cos[NUMBER_GROUP_USTAVOK]; //Уставка косинус кута КЗ З/В
           int pickup_kz_zv_angle_sin[NUMBER_GROUP_USTAVOK]; //Уставка синус кута КЗ З/В
  unsigned int control_kz_zv;                                //Поле для управління КЗ З/В
  
  //ГЗ
  int timeout_GP1[NUMBER_GROUP_USTAVOK];                     //Витримка  ГЗ1
  int timeout_GP2[NUMBER_GROUP_USTAVOK];                     //Витримка  ГЗ2
  int timeout_GP_RPN[NUMBER_GROUP_USTAVOK];                  //Витримка  ГЗ-РПН
  unsigned int control_GP;                                   //Поле для управління ГЗ
  
  //ТЗ
  int timeout_TP[NUMBER_GROUP_USTAVOK];                      //Витримка  ТЗ
  unsigned int control_TP;                                   //Поле для управління ТЗ
  
  //Універсальний захист
  int32_t setpoint_UP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];      //Уставка для всіх ступенів
  uint32_t setpoint_UP_KP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];  //Уставка для "Коефіцієнта повернення" всіх ступенів
  int32_t timeout_UP[NUMBER_UP][1][NUMBER_GROUP_USTAVOK];       //Витримка для Універсального захисту
  uint32_t control_UP;                                          //Поля для управління
  int32_t ctrl_UP_input[NUMBER_UP];                             //Вибір входу Універсального захисту

  unsigned int TCurrent_HV;             //Коефіцієнт трансформації для трансформатора струмів високої сторони
  unsigned int TCurrent_LV;             //Коефіцієнт трансформації для трансформатора струмів низької сторони
  unsigned int TVoltage;                //Коефіцієнт трансформації для трансформатора напруг
  uint32_t pickup_vyr_HV;               //Вирівнювання В – уставка вирівнювання високої сторони #5.3.3 
  uint32_t pickup_vyr_LV;               //Вирівнювання Н – уставка вирівнювання низької сторони  #5.3.3
  unsigned int control_transformator;   //налаштування для меню "Трансформатор"
  
  unsigned int password1;                                       //Пароль для редагування з меню
  unsigned int password2;                                       //Пароль для очистки лічилчників енегії і ресурсу вимикача
  unsigned int timeout_deactivation_password_interface_USB;     //Час деактивації паролю для редагування з інтерфейсу USB
  unsigned int password_interface_USB;                          //Пароль для редагування з інтерфейсу USB
  unsigned int timeout_deactivation_password_interface_RS485;   //Час деактивації паролю для редагування з інтерфейсу RS485
  unsigned int password_interface_RS485;                        //Пароль для редагування з інтерфейсу RS485
  
  unsigned int timeout_idle_new_settings;

  //Вимикач
  int timeout_swch_on;                          //Витримка T вкл.
  int timeout_swch_off;                         //Витримка T відкл.
  int timeout_swch_udl_blk_on;                  //Витримка T "удлинение сигнала блокировки включения"
  int timeout_pryvoda_VV;                       //Витримка T "Привіода ВВ"
  unsigned int control_switch;                  //Поле для управління вимикачем
  
  //Аналоговий реєстратор
  unsigned int prefault_number_periods; //Час доаварійного масиву (кількість періодів промислової частоти)
  unsigned int postfault_number_periods;//Час післяарійного масиву (кількість періодів промислової частоти)

  //Комунікація
  unsigned int name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];//І'мя ячейки
  unsigned short int user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //Регістри користувача
  unsigned int address;                                //Адреса
  int speed_RS485;                                    //швидкість обміну
                                                        // 0 - 9600
                                                        // 1 - 14400
                                                        // 2 - 19200
                                                        // 3 - 28800
                                                        // 4 - 38400
                                                        // 5 - 57600
                                                        // 6 - 115200
  int pare_bit_RS485;                                 //паритет
                                                        // 0 - NONE
                                                        // 1 - ODD
                                                        // 2 - EVEN
  int number_stop_bit_RS485;                          //кількість стоп-біт
                                                        // 0 - 1 stop-bit
                                                        // 1 - 2 stop-bits
  unsigned int time_out_1_RS485;                        //time-out наступного символу = X/10 символу
  
  int language;                                         //мова меню  0= змінна мов не підтримується; 1=RU; 2=UA; 3=EN; 4=KZ; 5=др.
  
  unsigned int control_extra_settings_1;                //Поле для додаткових налаштувань

  
  unsigned char time_setpoints[7+1];                     //Час останніх змін уставок-витримок-управління
                                                         //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
  
  unsigned char time_ranguvannja[7+1];                    //Час останніх змін ранжування
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
} __SETTINGS;

typedef struct
{
  //Стан обміну
  int state_execution;        //-1 - драйвер готовий до початку нових транзакцій
                              // 0 - відбувається обмін
                              // 1 - обмін завершений без помилок
                              // 2 - обмін завершений з помилками
  
  
  //Ідентифікатор пристрою, з яким ведетьсяобмін
  int device_id;              //-1 - пристрій не визначений
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //Код операції
  int action;                 //-1 - не визначений
                              // 0 - запис адреси для подальшого зчитування
                              // 1 - зчитування
                              // 2 - запис адреси і запис даних
  

  //Внутрішня адреса по якій буде іти звертання
  unsigned int internal_address;

  //Кількість байт для читання/запису (корисних)
  unsigned int number_bytes;
  
  //Вказівник на буфер (корисний)
  uint8_t *point_buffer;

} __DRIVER_I2C;

typedef struct
{
  unsigned int next_address;
  unsigned int saving_execution;
  unsigned int number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  unsigned int state_execution;     //стан виконуваної заразоперації
  
  unsigned int code_operation;      //Код виконуваної операції

} __DRIVER_SPI_DF;

typedef struct
{
  unsigned char label_start_record;
  unsigned char time[7]; 
  unsigned int TCurrent;
  unsigned int TVoltage;
  unsigned int control_extra_settings_1;
  unsigned char name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];
} __HEADER_AR;

typedef enum _STATE_READING_ADCs {
STATE_READING_ADCs_NONE = 0,
STATE_READING_WRITE,
STATE_READING_WRITE_READ,
STATE_READING_READ
} STATE_READING_ADCs;

typedef enum _full_ort_index __full_ort_index;
typedef enum _index_energy __index_energy;

typedef struct
{
  uint32_t tick;
  unsigned int value;

} EXTENDED_OUTPUT_DATA;

typedef struct
{
  uint32_t tick;
  int value;
} EXTENDED_SAMPLE;

typedef struct
{
  unsigned int time_p;
  int data_p[NUMBER_ANALOG_CANALES];

  unsigned int time_c;
  int data_c[NUMBER_ANALOG_CANALES];
} ROZSHYRENA_VYBORKA;

typedef struct
{
  unsigned int time_stemp;
  unsigned int DATA_fix;
  int data [NUMBER_ANALOG_CANALES];
  unsigned int active_functions[N_BIG];
  int state_ar_record;
  
} DATA_FOR_OSCYLOGRAPH;


typedef struct 
{
  unsigned int x1;
  int y1;

  unsigned int x2;
  int y2;

} VYBORKA_XY;

typedef struct
{
  unsigned int Ua_x1;
  int Ua_y1;
  unsigned int Ua_x2;
  int Ua_y2;

  unsigned int Ub_x1;
  int Ub_y1;
  unsigned int Ub_x2;
  int Ub_y2;

  unsigned int Uc_x1;
  int Uc_y1;  
  unsigned int Uc_x2;
  int Uc_y2;  

  unsigned int U0_x1;
  int U0_y1;
  unsigned int U0_x2;
  int U0_y2;
} POPEREDNJY_PERECHID;

//typedef struct
//{
//  unsigned int present;
//  int start_index;
//  int stop_index;
//  int number_per_index;
//  int real_number;
//} EL_FILTER_STRUCT;

typedef enum _getting_data
{
  GET_DATA_FOR_EDITING = 0,
  GET_DATA_IMMEDITATE
} __getting_data;

typedef enum _setting_data
{
  SET_DATA_INTO_EDIT_TABLE = 0,
  SET_DATA_IMMEDITATE
} __settings_data;

typedef struct _vd
{
           int sign;
  unsigned int begin;
  unsigned int comma;
  unsigned int end;
  unsigned int u_begin;
  unsigned int u_end;
  const unsigned char *p_unit;
} __vd;

typedef struct _ctrl_info
{
  const uint8_t *information;
  unsigned int cursor_x;
} __ctrl_info;

typedef enum _index_I_U
{
  INDEX_I_H = 0,
  INDEX_I_L,
  INDEX_U,
  
  _NUMBER_FOR_I_U
} __index_I_U;

typedef enum _id_list
{
  ID_INPUT = 0,
  ID_OUTPUT,
  ID_LED,
  ID_DF,
  ID_DB,
  ID_DT,
  ID_AND,
  ID_OR,
  ID_XOR,
  ID_NOT,
  ID_TF,
  ID_PRVV,
    
  MAX_NUMBER_IN_ID_LIST
} __id_list;

#endif
