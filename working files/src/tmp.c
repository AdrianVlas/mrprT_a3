//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================

// ----------------    -------------------------
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
    

Відлаштування другого ступеня від аперіодичної складової
диференційних струмів повинне бути реалізоване блокуванням ступеня за
відносною величиною аперіодичної складової:
І д ап / І д ;
Де:
І д ап - поточне значення аперіодичної складової;
І д - діюче значення поточного диференційного струму.
5.3.13 Діапазон регулювання відносної величини аперіодичної складової – від
0.5 до 10. Ступінь регулювання - не більше 0,01.
Тобто І д ап / І д > 0.5 до 10;
 І д ап / І д > pickup_ozt_K_aI
 (KOEF_POVERNENNJA_GENERAL_UP/100)*1000*І д ап > І д*pickup_ozt_K_aI
 KOEF_POVERNENNJA_GENERAL_UP*10*І д ап > І д*pickup_ozt_K_aI
 100*10                        І д ап > І д*pickup_ozt_K_aI
 
Відлаштування другого ступеня від кидків струму намагнічування
диференційних струмів повинне бути реалізоване блокуванням ступеня за
відносною величиною окремо другої та п’ятої гармонік диференційних струмів по
будь-якій з фаз:
І д 2г / І д ;
Де:
І д 2г – діюче значення другої гармоніки диференційного струму;
І д - діюче значення диференційного струму.
(KOEF_POVERNENNJA_GENERAL_UP/100)*І д 2г*pickup_ozt_K_2I otn > І д
10*(KOEF_POVERNENNJA_GENERAL_UP) *І д 2г  > І д*pickup_ozt_K_2I


І д 5г / І д ;
Де:
І д 5г – діюче значення п’ятої гармоніки диференційного струму;
І д - діюче значення диференційного струму.
(KOEF_POVERNENNJA_GENERAL_UP/100)*І д 5г*pickup_ozt_K_5I  > І д
10*(KOEF_POVERNENNJA_GENERAL_UP)*І д 5г  > І д*pickup_ozt_K_5I

5.3.17 Діапазон регулювання відносної величини другої та п’ятої гармонік
диференційного струму - від 0 до 0.5. Ступінь регулювання - не більше 0,001.
Тобто І д 2г / І д > 0 до 0.5  

(І д 2г*1000/kІ д)>1

Альтернативний варіант з діленням. Т.як 1000*Іх / І д- величина для порівняння з к відносним,
а ще треба і регулювати коеффіцієнт повернення, то пропнується:
1)1000*Іх / І д порівнювати з К. для пуску
2)1000*Іх*(Кпов/100) / І д  для відпускання.
Або
1)1000*Іх / І д порівнювати з К. для пуску
2)10*Іх*Кпов / І д  для відпускання.

//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````

/*****************************************************/
//Перевірка на необхідність завершення роботи аналогового/дискретного реєстраторів
/*****************************************************/
stop_regisrator(unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator)
/*****************************************************/
//Функція обробки черги зформованих записів дискретного реєстратора
/*****************************************************/
inline void routine_for_queue_dr(void)

state_dr_record / /!<< Приймає числа наведені нижче
STATE_DR_NO_RECORD              0 //На даний момент ніких дій з дискретним реєстратором не виконується
STATE_DR_FORCE_START_NEW_RECORD 1 //Оформлені події оформити як запис, але ще не досягнуто умови
 завершення роботи дискретного реєстратора тому при наступному проході розпочати новий запис
STATE_DR_EXECUTING_RECORD       2 //Іде процес запису реєстратора
STATE_DR_MAKE_RECORD            3 //Оформити запис для  запису у Dataflash
STATE_DR_CUT_RECORD             4 //Оформлені події оформити як запис, але ще не досягнуто умови 
завершення роботи дискретного реєстратора тому при наступному проході розпочати новий запис
Що мається на увазі?
number_records_dr_waiting_for_saving_operation / /!<< зараз виглядають як числа 0,1,2 
Визначає вибір буферу, з якого потрібно дані перекидати у  Datafalsh
 0 - buffer_for_save_dr_record 1- buffer_for_save_dr_record_level_1
 Запис завжди ведеться buffer_for_save_dr_record_level_2
 При перекиданні з buffer_for_save_dr_record_level_1 в buffer_for_save_dr_record_level_2
 ще відбувається і перенос з  buffer_for_save_dr_record в buffer_for_save_dr_record_level_1

якщо (control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0 / /!<<  тобто зараз не йде запис

якщо йде 

Поки що основна інформація полягає в тому, що запис безпосередньо у Datafalsh ведеться з буферу
buffer_for_save_dr_record_level_2. 

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void digital_registrator(unsigned int* carrent_active_functions)

 //Переводимо режим роботи із дискретним реєстратором у стан "Іде процес запису реєстратора"
          state_dr_record = STATE_DR_EXECUTING_RECORD;

buffer_for_save_dr_record / /!<<  типо за задумом базовий буфер для формування запису в дискретному реєстраторі       
          

state_current_monitoring  / /!<<  Поле, яке фіксує які блоки моніторингу використовуються 
          
          
typedef struct Setpoints_tag{

 
}Setpoints;

INDEX_ML_CTR_TRANSFORMATOR_VH_VL //0-VH 1 - VL 
unsigned int voltage = (current_settings.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;

   unsigned int type_voltage = (current_settings.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;
//  CTR_EXTRA_SETTINGS_1_CTRL_VH_VL //0-VH 1 - VL 
    if(type_voltage != 0){
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void p_3U0_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
    
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
 ch_type_voltage = (current_settings_prt.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1; 
if(ch_type_voltage){//0-VH 1 - VL 

 if(current_settings_prt.control_mtz &(arL_ctrl_mcp_sel[mtz_level])){

struct{
long Ii,Ip;

}sLV;  
_Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);

GRZU8
git push  --repo 'https://github.com/AdrianVlas/mrprT_a3.git'
getmac
ipconfig /all
arp -g
register union { 
   struct {
    //  unsigned int previous_state_po_dfrp1 : 1;
      unsigned int state_po_dfrp1 : 1;
      unsigned int dfrp1_is_larger_than_dI:1;
   } bool_vars;
  long lVl;
}wrp;

//register unsigned long u32_bit_holder = 0;  
//register union { 
//   struct {
//      unsigned int previous_state_po_3U0_1 : 1;
//    unsigned int KZZV_1r_is_larger_than_3U0_1:1;
//   } bool_vars;
//  long lVl;
//}wrp;wrp.lVl = 0;
struct{
unsigned long I1_lead_ls, I1_lead_hs, I2_lead_ls, I2_lead_hs;
unsigned long  meas_I1_lead_ls, meas_I1_lead_hs, meas_I2_lead_ls, meas_I2_lead_hs;
unsigned long setpoint_ls,setpoint_hs;
long lgI_hysteresis;
long conter_and;
__SETTINGS *p_current_settings_prt;
}sLV; 
   long lV; 
   unsigned long lCmpVl;
   Mcp_stp_state *p_bl;
 sLV.conter_and = 0;sLV.lgI_hysteresis = 0;
  sLV.p_current_settings_prt = &current_settings_prt;
     //ДВ
  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_KZ_ZV);
  register long lAnd = 0;
  if(lV == 0)
    lAnd |= 1;
   lV = (sLV.p_current_settings_prt->control_kz_zv & (1<<INDEX_ML_CTR_KZ_ZV_STATE)) ;
  if(lV != 0)
  lAnd |= 2;
  if(lAnd == 3){
    sLV.conter_and++;
    }
    lCmpVl = MIN_LIMIT_I1_I2_P;
    
        
//    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
//    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
//    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
//    
//    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
//    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
//    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);   
   sLV.meas_I1_lead_ls = measurement[IM_I1_P_L ];
   sLV.meas_I1_lead_hs = measurement[IM_I1_P_H ];
   sLV.meas_I2_lead_ls = measurement[IM_I2_P_L ];
   sLV.meas_I2_lead_hs = measurement[IM_I2_P_H ];
    p_bl = &mcp_stp_state;
    lV = p_bl->bool_val.po_I1_lead_low_side;
    if(lV) 
        sLV.I1_lead_ls = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
    else 
        sLV.I1_lead_ls = lCmpVl;
    if(sLV.meas_I1_lead_ls >= sLV.I1_lead_ls)
        lV = 1; 
    else 
        lV = 0;
    p_bl->bool_val.po_I1_lead_low_side = lV;
    
    lV = p_bl->bool_val.po_I1_lead_high_side ;
    if (lV)
        sLV.I1_lead_hs = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
    else 
        sLV.I1_lead_hs = lCmpVl;
    if(sLV.meas_I1_lead_hs >= sLV.I1_lead_hs)
        lV = 1; 
    else 
        lV = 0; 
    p_bl->bool_val.po_I1_lead_high_side = lV;
    
    lV = p_bl->bool_val.po_I2_lead_low_side;    
    if(lV) 
        sLV.I2_lead_ls = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
    else 
        sLV.I2_lead_ls = lCmpVl;
    if(sLV.meas_I2_lead_ls >= sLV.I2_lead_ls)
        lV = 1; 
    else 
        lV = 0; 
    p_bl->bool_val.po_I2_lead_low_side = lV;    
    
    lV = p_bl->bool_val.po_I2_lead_high_side;   
    if ( lV)
        sLV.I2_lead_hs = lCmpVl*KOEF_POVERNENNJA_ZOP_BLK/100;
    else 
        sLV.I2_lead_hs = lCmpVl;
    if(sLV.meas_I2_lead_hs >= sLV.I2_lead_hs)
        lV = 1; 
    else 
        lV = 0; 
    p_bl->bool_val.po_I2_lead_high_side = lV;
    lV = p_bl->lVl;
    lV &= 0xf;
    if(lV == 0xf){
        lV =  p_bl->bool_val.po_I2_I1_ls_lead;
        if(lV){
            lV = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
            lV *= KOEF_POVERNENNJA_GENERAL_UP/100;
            sLV.setpoint_ls = lV;
            
        }
        else{
            sLV.setpoint_ls = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
            
        }
        lV =  p_bl->bool_val.po_I2_I1_hs_lead;
        if(lV){
            lV = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
            lV *= KOEF_POVERNENNJA_GENERAL_UP/100;
            sLV.setpoint_hs = lV;
            
        }
        else{
            sLV.setpoint_hs = sLV.p_current_settings_prt->pickup_kz_zv[number_group_stp];
            
        }
        //((i2_current*1000) >= (i1_current*setpoint)) 
        if( (sLV.meas_I2_lead_ls*1000) >= (sLV.meas_I1_lead_ls*sLV.setpoint_ls) ){
            lV =  p_bl->bool_val.po_I2_I1_ls_lead;
            if(lV == 0)
                p_bl->bool_val.po_I2_I1_ls_lead = 1;
        }
        else{
            lV =  p_bl->bool_val.po_I2_I1_ls_lead;
            if(lV != 0)
                p_bl->bool_val.po_I2_I1_ls_lead = 0;
            
        }
        if( (sLV.meas_I2_lead_hs*1000) >= (sLV.meas_I1_lead_hs*sLV.setpoint_hs) ){
            lV =  p_bl->bool_val.po_I2_I1_hs_lead;
            if(lV == 0)
                p_bl->bool_val.po_I2_I1_hs_lead = 1;
        }
        else{
            lV =  p_bl->bool_val.po_I2_I1_hs_lead;
            if(lV != 0)
                p_bl->bool_val.po_I2_I1_hs_lead = 0;
            
        }
        //---------------------------------------------
        //Phase sensetive element
        //0- Not
        //1-Internal
        //2-External
        //---------------------------------------------
        lV = sLV.lgI_hysteresis;//Temporarly emulate Phase Calculation
        if( lV == 2 ){
            //Put Cmd  Sector In\Ext
            lV = p_bl->lVl;
            lV &= 0x30;
            if(lV == 0x30)
            sLV.conter_and += 2;
        }else if( lV == 1 ){
            //Put Cmd  Sector In\Ext
            lV = p_bl->lVl;
            lV &= 0x30;
            if(lV == 0x30)
            sLV.conter_and += 1;
        }
        else{
            //Clear Cmd Sector In\Ext
        }
    }
    else{
        ;//Clr Kz
    }
    if(sLV.conter_and == 5){
    
    }else if(sLV.conter_and == 4){
    
    }
    else{//Clr State

    }

 Аварійна несправність розкоментувати
CYCLECOUNTER    631174246   ReadOnly    
631174684
438
CYCLECOUNTER    1659503 ReadOnly    
CYCLECOUNTER    1659861 ReadOnly
358 





Introduction to Application Development with Qt Quick, Release 1.0
page 34
https://doc.qt.io/Qt-5/windows-deployment.html
https://books.google.com.ua/books?id=6F0dDAAAQBAJ&pg=PP9&lpg=PP9&dq=qt+book+pdf&source=bl&ots=ZRtEVMgxk6&sig=OweF-OleTdI3z7yINTcm1vkRWqI&hl=uk&sa=X&ved=2ahUKEwiPloeah47fAhUBDSwKHfugADc4HhDoATAAegQICRAB#v=onepage&q=qt%20book%20pdf&f=false
https://books.google.com.ua/books?id=9uhODwAAQBAJ&pg=PP4&lpg=PP4&dq=qt+book+pdf&source=bl&ots=A5CG0w3Uan&sig=aYI4oXkbewPD5G2ohH2_DqTIxqo&hl=uk&sa=X&ved=2ahUKEwiPloeah47fAhUBDSwKHfugADc4HhDoATABegQICBAB#v=onepage&q=qt%20book%20pdf&f=false
https://github.com/zakariakov/booksorg
http://pllug.org.ua/pllug-roadmaps/
Qt Training: Model/View (part 2/4): Showing Simple Data: Oliver Gutbrod, by e-GITS
Qt Training: Fundamentals of Qt - Objects in Qt, part 1/3 - Qt objects, UI elements
Qt Training: Model/View II (part 1/5): Editing item data, by e-GITS
Qt Training: Application Creation (part 1/3): MainWindows: Justin Noel by ICS
Qt Training: Widgets (part 1/3): Common Widgets: Torsten Rahn by basysKom
Qt Training: Graphics View (part 1/3): Using GraphicsView Classes: Tuukka Ahoniemi
Qt DevDays 2011, Advanced Qt - A Deep Dive 5/6 - ModelView Part 1: Volker Krause, Jesper Pedersen
Qt DevDays 2011, Advanced Qt -A Deep Dive 1/6 Graphics View Part 1: Volker Krause, Jesper Pedersen
QtWS15- Get to know the Qt Installer Framework, Kai Köhne, The Qt Company
QtDD12 - Effective QML: Best practices for Developing with Qt Quick - Adenilson Calvacanti
Introducing Qt Quick Controls in Qt 5.1
Qt DevDays 2011, Getting Started - a Qt fast track 1/4 - Overview: Oliver Gutbrod
Qt DevDays 2011, Programming with Qt Quick 3/6 - Visual Elements Part 1: Justin Noel
QtDD12 - OpenGL with Qt 5 - Dr. Sean Harmer
Qt DevDays 2011, Programming with Qt Quick 1/6 - Meet Qt Quick Part 1: Justin Noel
https://www.qcustomplot.com/
https://dou.ua/lenta/digests/plus-digest-7/

https://www.youtube.com/watch?v=Y4utTBcSjdM&list=PLB22HyVdO1GkLFrvRi5vIo5XcWS0EflxD

 7.18a.4 The FX_FULL_PRECISION pragma
 

//    if(   (measurement[IM_dIA] < 0.05*I_NOM) || (measurement[IM_dIB] < 0.05*I_NOM)
//     || (measurement[IM_dIC] < 0.05*I_NOM) ){
//     
//        _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2);
//        
//    }
//    else{
//        if( _CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2) != 0){
//            if((measurement[IM_dIA] < 0.0525*I_NOM) || (measurement[IM_dIB] < 0.0525*I_NOM)
//            || (measurement[IM_dIC] < 0.0525*I_NOM)){
//            _SET_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2);
//            }else{
//                sLV.lCtrBlock = 0;_CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2);
//            }
//        }else{
//            sLV.lCtrBlock = 0;_CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_A_2G_5G_OZT2);
//            }   
//         
//    }
5/10 = x/64
x = 64*5/10
Де 64 основа дробу, 0.5 -- Інший дріб
32 еквівалент 0.5
1 l L
РПН ГЗ
G:\Arc_PC\G_Copy\OLD_DATA\BLD_DOC\DOCUMENTS\Бьерн Страуструп с++\Cpp-bs.txt
4.5 Как создать библиотеку
G:\Arc_PC\G_Copy\OLD_DATA\BLD_DOC\DOCUMENTS\Turbo C++\GS4
G:\Arc_PC\G_Copy\OLD_DATA\BLD_DOC\DOCUMENTS\Turbo C++\GS5
G:\Arc_PC\G_Copy\OLD_DATA\BLD_DOC\DOCUMENTS\Turbo C++\PG3N
6.5.3 Виртуальные базовые классы
8.1 Введение

 Одним из самых полезных видов классов является контейнерный класс
Using file streams in C++
Chapter 4
Using Abstract Data Types
Declaring a new Vector object

381559166 новий ПК у Н.О. (AnbyDesk пароль той самий)
AnyDesk:
468149286
пароль taras19781210
adnvsp3@gmail.com

Username: adnvsp3@gmail.com
Password: cz7UjLuJB
New  Password
paf6r603p4bYwv1

rza.promav@gmail.com






$PROJ_DIR$\..\..\
$PROJ_DIR$\..\..\lib
$PROJ_DIR$\..\..\prj
$PROJ_DIR$\..\..\svw
$PROJ_DIR$\..\..\svws
$PROJ_DIR$\..\..\wf

$PROJ_DIR$\..\..\wf\inc
$PROJ_DIR$\..\..\wf\inc\a.01.c.d
$PROJ_DIR$\..\..\wf\usb
$PROJ_DIR$\..\..\wf\src\modbusroutine\inc
$PROJ_DIR$\..\..\lib\CMSIS\Dev\ST\STM32F4xx\Include
$PROJ_DIR$\..\..\lib\STM32F4xx_StdPeriph_Driver\inc
$PROJ_DIR$\..\..\lib\STM32_USB_OTG_Driver\inc
$PROJ_DIR$\..\..\lib\STM32_USB_Device_Library\Core\inc
$PROJ_DIR$\..\..\lib\STM32_USB_Device_Library\Class\cdc\inc
$PROJ_DIR$\..\..\svw\Config
$PROJ_DIR$\..\..\svw\OS
$PROJ_DIR$\..\..\svw\SEGGER

$PROJ_DIR$\..\..\prj
$PROJ_DIR$\..\..\svw
$PROJ_DIR$\..\..\svws























