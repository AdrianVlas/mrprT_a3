
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 350
//конечный регистр в карте памяти
#define END_ADR_REGISTER 519

int getAISmallModbusRegister(int);//получить содержимое регистра
int getAISmallModbusBit(int);//получить содержимое бита
int setAISmallModbusRegister(int, int);//получить содержимое регистра
int setAISmallModbusBit(int, int);//получить содержимое бита

void preAISmallReadAction(void);//action до чтения
void preAISmallWriteAction(void);//action до записи
int  postAISmallWriteAction(void);//action после записи
void loadAISmallActualData(void);

int privateAISmallGetReg2(int adrReg);

COMPONENT_OBJ *aismallcomponent;

/**************************************/
//компонент измерений
/**************************************/
void constructorAISmallComponent(COMPONENT_OBJ *aismallcomp)
{
  aismallcomponent = aismallcomp;

  aismallcomponent->getModbusRegister = getAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->getModbusBit      = getAISmallModbusBit;//получить содержимое бита
  aismallcomponent->setModbusRegister = setAISmallModbusRegister;//получить содержимое регистра
  aismallcomponent->setModbusBit      = setAISmallModbusBit;//получить содержимое бита

  aismallcomponent->preReadAction   = preAISmallReadAction;//action до чтения
  aismallcomponent->preWriteAction  = preAISmallWriteAction;//action до записи
  aismallcomponent->postWriteAction = postAISmallWriteAction;//action после записи

  aismallcomponent->isActiveActualData = 0;
}//constructorIUSmallComponent(COMPONENT_OBJ *iucomp)

#define TRANSFORMATOR_VH if(!transVH_VL)  break;return -1;
#define TRANSFORMATOR_VL if(transVH_VL) break;return -1;

#define TRANSFORMATOR_BAZAVH if(!transVH_VL)  break;return 0;
#define TRANSFORMATOR_BAZAVL if(transVH_VL) break;return 0;

int getAISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
    int offset = adrReg-BEGIN_ADR_REGISTER;
    unsigned int transVH_VL = current_settings_interfaces.control_transformator&(1<<INDEX_ML_CTR_TRANSFORMATOR_VH_VL);

  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < _NUMBER_IM; i++ ) 
  {
    measurement_low[i] = measurement_middle[i];
  }
  semaphore_measure_values_low1 = 0;
    switch (offset)
    {
    case 0://UA H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        //adrReg += transVH_VL;
        return 350;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 1://UB H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 351;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 2://UC H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 352;
#else
       TRANSFORMATOR_VH
#endif
      }

    case 7://P  H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 357;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 8://Q H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 358;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 9://S H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 359;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 10://cos f H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 360;
#else
       TRANSFORMATOR_VH
#endif
      }

    case 25://UAB H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 375;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 26://UBC H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 376;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 27://UCA H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 377;
#else
       TRANSFORMATOR_VH
#endif
      }

//    case 28:

    case 29://3U0  H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 379;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 30://U1 H
#ifdef TESTZBIRKA_VERSII_PZ
        return 380;
#else
       TRANSFORMATOR_VH
#endif
    case 31://U2 H
#ifdef TESTZBIRKA_VERSII_PZ
        return 381;
#else
       TRANSFORMATOR_VH
#endif
    case 45:
       TRANSFORMATOR_BAZAVH
    case 46://OFFSET_ANGLE_UA_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 396;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 47://OFFSET_ANGLE_UB_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 397;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 48://OFFSET_ANGLE_UC_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 398;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 49://OFFSET_ANGLE_UAB_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 399;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 50://OFFSET_ANGLE_UBC_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 400;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 51://OFFSET_ANGLE_UCA_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 401;
#else
       TRANSFORMATOR_VH
#endif
      }

//    case 52:

    case 53://OFFSET_ANGLE_3U0_1  H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 403;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 54://OFFSET_ANGLE_U1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 404;
#else
       TRANSFORMATOR_VH
#endif
      }
    case 55://OFFSET_ANGLE_U2  H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 405;
#else
       TRANSFORMATOR_VH
#endif
      }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    case 78://UA L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 428;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 79://UB L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 429;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 80://UC L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 430;
#else
       TRANSFORMATOR_VL
#endif
      }

    case 85://P L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 435;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 86://Q L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 436;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 87://S L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 437;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 88://cos f L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 438;
#else
       TRANSFORMATOR_VL
#endif
      }

    case 90://Частота ТН2
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 440;
#else
       TRANSFORMATOR_VL
#endif
      }

    case 103://UAB L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 453;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 104://UBC L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 454;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 105://UCA L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 455;
#else
       TRANSFORMATOR_VL
#endif
      }

//    case 28:

    case 107://3U0 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 457;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 108://U1 L
#ifdef TESTZBIRKA_VERSII_PZ
        return 458;
#else
       TRANSFORMATOR_VL
#endif
    case 109://U2 L
#ifdef TESTZBIRKA_VERSII_PZ
        return 459;
#else
       TRANSFORMATOR_VL
#endif

    case 123:
       TRANSFORMATOR_BAZAVL
    case 124://OFFSET_ANGLE_UA_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 474;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 125://OFFSET_ANGLE_UB_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 475;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 126://OFFSET_ANGLE_UC_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 476;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 127://OFFSET_ANGLE_UAB_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 477;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 128://OFFSET_ANGLE_UBC_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 478;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 129://OFFSET_ANGLE_UCA_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 479;
#else
       TRANSFORMATOR_VL
#endif
      }

//    case 52:

    case 131://OFFSET_ANGLE_3U0_1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 481;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 132://OFFSET_ANGLE_U1 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 482;
#else
       TRANSFORMATOR_VL
#endif
      }
    case 133://OFFSET_ANGLE_U2 L
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 483;
#else
       TRANSFORMATOR_VL
#endif
      }

    }//switch
//----------------------------------------------------------------------------
    switch (offset)
    {
    case 78://UA L
    case 0://UA H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 350;
#else
        return (measurement_low[IM_UA] >> 3) &0xFFFF;
#endif
      }
    case 79://UB L
    case 1://UB H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 351;
#else
        return (measurement_low[IM_UB] >> 3) &0xFFFF;
#endif
      }
    case 80://UC L
    case 2://UC H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 352;
#else
        return (measurement_low[IM_UC] >> 3) &0xFFFF;
#endif
      }
    case 3://Ток Ia ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 353;
#else
        return (measurement_low[IM_IA_H] >> 2) &0xFFFF;
#endif
      }
    case 4://Ток Ib ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 354;
#else
        return (measurement_low[IM_IB_H] >> 2) &0xFFFF;
#endif
      }
    case 5://Ток Ic ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 355;
#else
        return (measurement_low[IM_IC_H] >> 2) &0xFFFF;
#endif
      }

    case 85://P L
    case 7://P H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 357;
#else
        return (P[0]/50) &0xFFFF;
#endif
      }
    case 86://Q L
    case 8://Q H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 358;
#else
        return (Q[0]/50) &0xFFFF;
#endif
      }
    case 87://S L
    case 9://S H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 359;
#else
        return (S[0]/50) &0xFFFF;
#endif
      }
    case 88://cos f L
    case 10://cos f H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 360;
#else
        if (S[0] != 0)
          return (cos_phi_x1000) &0xFFFF;
          return 0x0;
#endif
      }

    case 90://freq L
    case 12://freq H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 362;
#else
        int int_frequency = (int)(frequency*100);
        
        if (int_frequency > 0 /*це число означає - частота не визначена*/)
          return (int_frequency) &0xFFFF;
        else
        {
          if (int_frequency == (-1*100))
            return (-1)&0x0000FFFF;
          else if (int_frequency == (-2*100))
            return (-2)&0x0000FFFF;
          else if (int_frequency == (-3*100))
            return (-3)&0x0000FFFF;
          else
            return (-4)&0x0000FFFF;
        }
#endif
      } break;

    case 103://UAB L
    case 25://UAB H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 375;
#else
        return (measurement_low[IM_UAB] >> 3) &0xFFFF;
#endif
      }
    case 104://UBC L
    case 26://UBC H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 376;
#else
        return (measurement_low[IM_UBC] >> 3) &0xFFFF;
#endif
      }
    case 105://UCA L
    case 27://UCA H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 377;
#else
        return (measurement_low[IM_UCA] >> 3) &0xFFFF;
#endif
      }

//    case 28:

    case 107://3U0 L
    case 29://3U0 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 379;
#else
        return (measurement_low[IM_3U0_r] >> 3) &0xFFFF;
#endif
      }
    case 108://U1 L
    case 30://U1 H
#ifdef TESTZBIRKA_VERSII_PZ
        return 380;
#else
        return (measurement_low[IM_U1] >> 3) &0xFFFF;
#endif
    case 109://U2 L
    case 31://U2 H
#ifdef TESTZBIRKA_VERSII_PZ
        return 381;
#else
        return (measurement_low[IM_U2] >> 3) &0xFFFF;
#endif

//    case 32:

    case 33://3I0-1 BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 383;
#else
        return (measurement_low[IM_3I0_r_H] >> 2) &0xFFFF;
#endif
      }
    case 34://IM_I1 BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 384;
#else
        return (measurement_low[IM_I1_H] >> 2) &0xFFFF;
#endif
      }
    case 35://IM_I2 BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 385;
#else
        return (measurement_low[IM_I2_H] >> 2) &0xFFFF;
#endif
      }

//    case 36:
//    case 37:
//    case 38:

    case 39://Приведенный Ток Ia ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 389;
#else
        return (measurement_low[IM_IA_P_H] >> 2) &0xFFFF;
#endif
      }
    case 40://Приведенный Ток Ib ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 390;
#else
        return (measurement_low[IM_IB_P_H] >> 2) &0xFFFF;
#endif
      }
    case 41://Приведенный Ток Ic ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 391;
#else
        return (measurement_low[IM_IC_P_H] >> 2) &0xFFFF;
#endif
      }
    case 42://Приведенный Ток I1 ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 392;
#else
        return (measurement_low[IM_I1_P_H] >> 2) &0xFFFF;
#endif
      }
    case 43://Приведенный Ток I2 ВН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 393;
#else
        return (measurement_low[IM_I2_P_H] >> 2) &0xFFFF;
#endif
      }

//    case 44:
    case 123:
    case 45:
        return (base_index_for_angle + 1) &0xFFFF;

    case 124://OFFSET_ANGLE_UA_1 L
    case 46://OFFSET_ANGLE_UA_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 396;
#else
        return ((unsigned int)phi_angle[IM_UA]) &0xFFFF;
#endif
      }
    case 125://OFFSET_ANGLE_UB_1 L
    case 47://OFFSET_ANGLE_UB_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 397;
#else
        return ((unsigned int)phi_angle[IM_UB]) &0xFFFF;
#endif
      }
    case 126://OFFSET_ANGLE_UC_1 L
    case 48://OFFSET_ANGLE_UC_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 398;
#else
        return ((unsigned int)phi_angle[IM_UC]) &0xFFFF;
#endif
      }
    case 127://OFFSET_ANGLE_UAB_1 L
    case 49://OFFSET_ANGLE_UAB_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 399;
#else
        return ((unsigned int)phi_angle[IM_UAB]) &0xFFFF;
#endif
      }
    case 128://OFFSET_ANGLE_UBC_1 L
    case 50://OFFSET_ANGLE_UBC_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 400;
#else
        return ((unsigned int)phi_angle[IM_UBC]) &0xFFFF;
#endif
      }
    case 129://OFFSET_ANGLE_UCA_1 L
    case 51://OFFSET_ANGLE_UCA_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 401;
#else
        return ((unsigned int)phi_angle[IM_UCA]) &0xFFFF;
#endif
      }

//    case 52:

    case 131://OFFSET_ANGLE_3U0_1 L
    case 53://OFFSET_ANGLE_3U0_1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 403;
#else
        return ((unsigned int)phi_angle[IM_3U0_r]) &0xFFFF;
#endif
      }
    case 132://OFFSET_ANGLE_U1 L
    case 54://OFFSET_ANGLE_U1 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 404;
#else
        return ((unsigned int)phi_angle[IM_U1]) &0xFFFF;
#endif
      }
    case 133://OFFSET_ANGLE_U2 L
    case 55://OFFSET_ANGLE_U2 H
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 405;
#else
        return ((unsigned int)phi_angle[IM_U2]) &0xFFFF;
#endif
      }
    case 56://OFFSET_ANGLE_Ia BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 406;
#else
        return ((unsigned int)phi_angle[IM_IA_H]) &0xFFFF;
#endif
      }
    case 57://OFFSET_ANGLE_Ib BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 407;
#else
        return ((unsigned int)phi_angle[IM_IB_H]) &0xFFFF;
#endif
      }
    case 58://OFFSET_ANGLE_Ic BH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 408;
#else
        return ((unsigned int)phi_angle[IM_IC_H]) &0xFFFF;
#endif
      }

//    case 59:
//    case 60:

    case 61://Угол между 3Io-1 ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 411;
#else
        return ((unsigned int)phi_angle[IM_3I0_r_H]) &0xFFFF;
#endif
      }
    case 62://Угол между I1 ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 412;
#else
        return ((unsigned int)phi_angle[IM_I1_H]) &0xFFFF;
#endif
      }
    case 63://Угол между I2 ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 413;
#else
        return ((unsigned int)phi_angle[IM_I2_H]) &0xFFFF;
#endif
      }
    case 64://Угол между приведенным Ia ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 414;
#else
        return ((unsigned int)phi_angle[IM_IA_P_H]) &0xFFFF;
#endif
      }
    case 65://Угол между приведенным Ib ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 415;
#else
        return ((unsigned int)phi_angle[IM_IB_P_H]) &0xFFFF;
#endif
      }
    case 66://Угол между приведенным Ic ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 416;
#else
        return ((unsigned int)phi_angle[IM_IC_P_H]) &0xFFFF;
#endif
      }
    case 67://Угол между приведенным I1 ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 417;
#else
        return ((unsigned int)phi_angle[IM_I1_P_H]) &0xFFFF;
#endif
      }
    case 68://Угол между приведенным I2 ВН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 418;
#else
        return ((unsigned int)phi_angle[IM_I2_P_H]) &0xFFFF;
#endif
      }


    case 81://Ток Ia HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 431;
#else
        return (measurement_low[IM_IA_L] >> 2) &0xFFFF;
#endif
      }
    case 82://Ток Ib HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 432;
#else
        return (measurement_low[IM_IB_L] >> 2) &0xFFFF;
#endif
      }
    case 83://Ток Ic HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 433;
#else
        return (measurement_low[IM_IC_L] >> 2) &0xFFFF;
#endif
      }

    case 111://3I0-1 HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 461;
#else
        return (measurement_low[IM_3I0_r_L] >> 2) &0xFFFF;
#endif
      }
    case 112://IM_I1 HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 462;
#else
        return (measurement_low[IM_I1_L] >> 2) &0xFFFF;
#endif
      }
    case 113://IM_I2 HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 463;
#else
        return (measurement_low[IM_I2_L] >> 2) &0xFFFF;
#endif
      }


    case 117://Приведенный Ток Ia HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 467;
#else
        return (measurement_low[IM_IA_P_L] >> 2) &0xFFFF;
#endif
      }
    case 118://Приведенный Ток Ib HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 468;
#else
        return (measurement_low[IM_IB_P_L] >> 2) &0xFFFF;
#endif
      }
    case 119://Приведенный Ток Ic HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 469;
#else
        return (measurement_low[IM_IC_P_L] >> 2) &0xFFFF;
#endif
      }
    case 120://Приведенный Ток I1 HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 470;
#else
        return (measurement_low[IM_I1_P_L] >> 2) &0xFFFF;
#endif
      }
    case 121://Приведенный Ток I2 HН
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 471;
#else
        return (measurement_low[IM_I2_P_L] >> 2) &0xFFFF;
#endif
      }


    case 134://OFFSET_ANGLE_Ia HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 484;
#else
        return ((unsigned int)phi_angle[IM_IA_L]) &0xFFFF;
#endif
      }
    case 135://OFFSET_ANGLE_Ib HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 485;
#else
        return ((unsigned int)phi_angle[IM_IB_L]) &0xFFFF;
#endif
      }
    case 136://OFFSET_ANGLE_Ic HH
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 486;
#else
        return ((unsigned int)phi_angle[IM_IC_L]) &0xFFFF;
#endif
      }

//    case 137://
//    case 138://

    case 139://Угол между 3Io-1 HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 489;
#else
        return ((unsigned int)phi_angle[IM_3I0_r_L]) &0xFFFF;
#endif
      }
    case 140://Угол между I1 HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 490;
#else
        return ((unsigned int)phi_angle[IM_I1_L]) &0xFFFF;
#endif
      }
    case 141://Угол между I2 HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 491;
#else
        return ((unsigned int)phi_angle[IM_I2_L]) &0xFFFF;
#endif
      }

    case 142://Угол между приведенным Ia HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 492;
#else
        return ((unsigned int)phi_angle[IM_IA_P_L]) &0xFFFF;
#endif
      }
    case 143://Угол между приведенным Ib HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 493;
#else
        return ((unsigned int)phi_angle[IM_IB_P_L]) &0xFFFF;
#endif
      }
    case 144://Угол между приведенным Ic HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 494;
#else
        return ((unsigned int)phi_angle[IM_IC_P_L]) &0xFFFF;
#endif
      }
    case 145://Угол между приведенным I1 HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 495;
#else
        return ((unsigned int)phi_angle[IM_I1_P_L]) &0xFFFF;
#endif
      }
    case 146://Угол между приведенным I2 HН и базой
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 496;
#else
        return ((unsigned int)phi_angle[IM_I2_P_L]) &0xFFFF;
#endif
      }

    case 158://Ток Ia Dif
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 508;
#else
        return (measurement_low[IM_dIA] >> 2) &0xFFFF;
#endif
      }
    case 159://Ток Ib Dif
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 509;
#else
        return (measurement_low[IM_dIB] >> 2) &0xFFFF;
#endif
      }
    case 160://Ток Ic Dif
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 510;
#else
        return (measurement_low[IM_dIC] >> 2) &0xFFFF;
#endif
      }
    case 161://Ток Ia G
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 511;
#else
        return (measurement_low[IM_gdIA] >> 2) &0xFFFF;
#endif
      }
    case 162://Ток Ib G
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 512;
#else
        return (measurement_low[IM_gdIB] >> 2) &0xFFFF;
#endif
      }
    case 163://Ток Ic G
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 513;
#else
        return (measurement_low[IM_gdIC] >> 2) &0xFFFF;
#endif
      }

    case 164://Iah2 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 514;
#else
        return (measurement_low[IM_2dIA] >> 2) &0xFFFF;
#endif
      }
    case 165://Ibh2 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 515;
#else
        return (measurement_low[IM_2dIB] >> 2) &0xFFFF;
#endif
      }
    case 166://Ich2 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 516;
#else
        return (measurement_low[IM_2dIC] >> 2) &0xFFFF;
#endif
      }
    case 167://Iah5 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 517;
#else
        return (measurement_low[IM_5dIA] >> 2) &0xFFFF;
#endif
      }
    case 168://Ibh5 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 518;
#else
        return (measurement_low[IM_5dIB] >> 2) &0xFFFF;
#endif
      }
    case 169://Ich5 diff
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 519;
#else
        return (measurement_low[IM_5dIC] >> 2) &0xFFFF;
#endif
      }
    }//switch
    return 0;
}//getDVModbusRegister(int adrReg)
int getAISmallModbusBit(int x) {
  //получить содержимое bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setAISmallModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setAISmallModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preAISmallReadAction(void) {
//action до чтения
  aismallcomponent->isActiveActualData = 1;
}//

void preAISmallWriteAction(void) {
//action до записи
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//оперативный маркер
  aismallcomponent->isActiveActualData = 1;
}//
int postAISmallWriteAction(void) {
//action после записи
 return 0;
}//

int privateAISmallGetReg2(int adrReg)
{
  //проверить внешний периметр
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

