#ifndef __CONSTANTS_INPUTS__
#define __CONSTANTS_INPUTS__

#define EKRAN_LIST_INPUTS_FOR_RANGUVANNJA        (EKRAN_CONTROL_UP + 1)

#define EKRAN_RANGUVANNJA_INPUT_1                (EKRAN_TRANSFORMATOR_INFO_CONTROL + 1)
#define EKRAN_RANGUVANNJA_INPUT_2                (EKRAN_RANGUVANNJA_INPUT_1 + 1)
#define EKRAN_RANGUVANNJA_INPUT_3                (EKRAN_RANGUVANNJA_INPUT_2 + 1)
#define EKRAN_RANGUVANNJA_INPUT_4                (EKRAN_RANGUVANNJA_INPUT_3 + 1)
#define EKRAN_RANGUVANNJA_INPUT_5                (EKRAN_RANGUVANNJA_INPUT_4 + 1)
#define EKRAN_RANGUVANNJA_INPUT_6                (EKRAN_RANGUVANNJA_INPUT_5 + 1)
#define EKRAN_RANGUVANNJA_INPUT_7                (EKRAN_RANGUVANNJA_INPUT_6 + 1)
#define EKRAN_RANGUVANNJA_INPUT_8                (EKRAN_RANGUVANNJA_INPUT_7 + 1)

//#if ((MODYFIKACIA_VERSII_PZ == 0) || (MODYFIKACIA_VERSII_PZ == 1))

#define EKRAN_RANGUVANNJA_INPUT_9                (EKRAN_RANGUVANNJA_INPUT_8 + 1)
#define EKRAN_RANGUVANNJA_INPUT_10               (EKRAN_RANGUVANNJA_INPUT_9 + 1)
#define EKRAN_RANGUVANNJA_INPUT_11               (EKRAN_RANGUVANNJA_INPUT_10 + 1)
#define EKRAN_RANGUVANNJA_INPUT_12               (EKRAN_RANGUVANNJA_INPUT_11 + 1)
#define EKRAN_RANGUVANNJA_INPUT_13               (EKRAN_RANGUVANNJA_INPUT_12 + 1)
#define EKRAN_RANGUVANNJA_INPUT_14               (EKRAN_RANGUVANNJA_INPUT_13 + 1)
#define EKRAN_RANGUVANNJA_INPUT_15               (EKRAN_RANGUVANNJA_INPUT_14 + 1)
#define EKRAN_RANGUVANNJA_INPUT_16               (EKRAN_RANGUVANNJA_INPUT_15 + 1)

//#if MODYFIKACIA_VERSII_PZ == 0
//
//#define EKRAN_RANGUVANNJA_INPUT_17               (EKRAN_RANGUVANNJA_INPUT_16 + 1)
//#define EKRAN_RANGUVANNJA_INPUT_18               (EKRAN_RANGUVANNJA_INPUT_17 + 1)
//#define EKRAN_RANGUVANNJA_INPUT_19               (EKRAN_RANGUVANNJA_INPUT_18 + 1)
//#define EKRAN_RANGUVANNJA_INPUT_20               (EKRAN_RANGUVANNJA_INPUT_19 + 1)
//
//#endif

//#endif

//#if MODYFIKACIA_VERSII_PZ == 0
//
//#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_20

//#elif MODYFIKACIA_VERSII_PZ == 1

#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_16

//#else
//
//#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_8

//#endif

#define MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA       NUMBER_INPUTS
#define MAX_ROW_RANGUVANNJA_INPUT                 NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL

#define NAME_RANG_SMALL_RU              \
  " ����� ���������",                   \
  "   ����� ����   ",                   \
  " �����./�������.",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.� �� ",                   \
  " ����.���.��(�) ",                   \
  " ��������� ��(�)",                   \
  "   ���.��(�)    ",                   \
  "�������� ���.(�)",                   \
  "   ����.��(�)   ",                   \
  "�������� ����(�)",                   \
  " ����.���.��(�) ",                   \
  " ��������� ��(�)",                   \
  "   ���.��(�)    ",                   \
  "�������� ���.(�)",                   \
  "   ����.��(�)   ",                   \
  "�������� ����(�)",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " �.��.���2 �� ��",                   \
  "�.��.���2 �� I�2",                   \
  "�.��.���2 �� I�5",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.���.���2  ",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "   ����.3U0-1   ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  "   ����.����4   ",                   \
  "���� ����1 �� ��",                   \
  "���� ����2 �� ��",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  "  ����.�����1   ",                   \
  "  ���� �����1   ",                   \
  "  ����.�����2   ",                   \
  "  ���� �����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.���    ",                   \
  "    ����.��     ",                   \
  "     ��.��1     ",                   \
  "     ��.��2     ",                   \
  "   ��.��-���    ",                   \
  "    ����.��     ",                   \
  "     ��.��      ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-��������1",                   \
  " ���.�-��������1",                   \
  " ���.�-��������2",                   \
  " ���.�-��������2",                   \
  " ���.�-��������3",                   \
  " ���.�-��������3",                   \
  " ���.�-��������4",                   \
  " ���.�-��������4"

#define NAME_RANG_SMALL_UA              \
  " ����.��������� ",                   \
  "   ����.����    ",                   \
  " ̳��./�������. ",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.�� ��",                   \
  " ��.�����.��(�)",                   \
  "   ���� ��(�)   ",                   \
  "  ����.��(�)   ",                   \
  " �-�� ����.(�) ",                   \
  "   ����.��(�)   ",                   \
  " �-�� ����.(�)  ",                   \
  " ��.�����.��(�)",                   \
  "   ���� ��(�)   ",                   \
  "  ����.��(�)   ",                   \
  " �-�� ����.(�) ",                   \
  "   ����.��(�)   ",                   \
  " �-�� ����.(�)  ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  "�.��.���2 �� ��",                   \
  "�.�.���2 �� I�2",                   \
  "�.�.���2 �� I�5",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.�����.���2",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "   ����.3U0-1   ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  "   ����.����4   ",                   \
  " �.����1 �� �� ",                   \
  " �.����2 �� �� ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  "  ����.����1   ",                   \
  "  ���� ����1   ",                   \
  "  ����.����2   ",                   \
  "  ���� ����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.���    ",                   \
  "    ����.��     ",                   \
  "     ��.��1     ",                   \
  "     ��.��2     ",                   \
  "   ��.��-���    ",                   \
  "    ����.��     ",                   \
  "     ��.��      ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-������1 ",                   \
  " ��.�-������1  ",                   \
  " ���.�-������2 ",                   \
  " ��.�-������2  ",                   \
  " ���.�-������3 ",                   \
  " ��.�-������3  ",                   \
  " ���.�-������4 ",                   \
  " ��.�-������4  "

#define NAME_RANG_SMALL_EN         \
  "Indication Reset",                   \
  "  Relay Reset   ",                   \
  "  Local/Remote  ",                   \
  " Pick-up Set 1  ",                   \
  " Pick-up Set 2  ",                   \
  " Pick-up Set 3  ",                   \
  " Pick-up Set 4  ",                   \
  " �.���.���.� �� ",                   \
  " ON CB Blc.(H)  ",                   \
  " State of CB(H) ",                   \
  "    On CB(H)    ",                   \
  " On CB Ctrl(H)  ",                   \
  "   Off CB(H)    ",                   \
  " Off CB Ctrl(H) ",                   \
  " ON CB Blc.(L)  ",                   \
  " State of CB(L) ",                   \
  "    On CB(L)    ",                   \
  " On CB Ctrl(L)  ",                   \
  "   Off CB(L)    ",                   \
  " Off CB Ctrl(L) ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " �.��.���2 �� ��",                   \
  "�.��.���2 �� I�2",                   \
  "�.��.���2 �� I�5",                   \
  "  Blc.of OCP1   ",                   \
  "  Blc.of OCP2   ",                   \
  "  OCP2 Acc.Blc. ",                   \
  "  Blc.of OCP3   ",                   \
  "  Blc.of OCP4   ",                   \
  "   ����.3U0-1   ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  "   ����.����4   ",                   \
  "CBFP1 Start f.DI",                   \
  "CBFP2 Start f.DI",                   \
  "  Blc.of NPSP1  ",                   \
  "  Blc.of NPSP2  ",                   \
  "   ����.Umin1   ",                   \
  "   ���� Umin1   ",                   \
  "   ����.Umin2   ",                   \
  "   ���� Umin2   ",                   \
  "   ����.Umax1   ",                   \
  "   ����.Umax2   ",                   \
  "    ����.���    ",                   \
  "    ����.��     ",                   \
  "     ��.��1     ",                   \
  "     ��.��2     ",                   \
  "   ��.��-���    ",                   \
  "    ����.��     ",                   \
  "     ��.��      ",                   \
  "   Blc.of UPx   ",                   \
  "    UDF1 In     ",                   \
  "    UDF2 In     ",                   \
  "    UDF3 In     ",                   \
  "    UDF4 In     ",                   \
  "    UDF5 In     ",                   \
  "    UDF6 In     ",                   \
  "    UDF7 In     ",                   \
  "    UDF8 In     ",                   \
  "UD Flip-Flop1 S.",                   \
  "UD Flip-Flop1 R.",                   \
  "UD Flip-Flop2 S.",                   \
  "UD Flip-Flop2 R.",                   \
  "UD Flip-Flop3 S.",                   \
  "UD Flip-Flop3 R.",                   \
  "UD Flip-Flop4 S.",                   \
  "UD Flip-Flop4 R."
        
#define NAME_RANG_SMALL_KZ         \
  " ����� ���������",                   \
  "   ����� ����   ",                   \
  " �����./�������.",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.� �� ",                   \
  " ����.���.��(�) ",                   \
  " ��������� ��(�)",                   \
  "   ���.��(�)    ",                   \
  "�������� ���.(�)",                   \
  "   ����.��(�)   ",                   \
  "�������� ����(�)",                   \
  " ����.���.��(�) ",                   \
  " ��������� ��(�)",                   \
  "   ���.��(�)    ",                   \
  "�������� ���.(�)",                   \
  "   ����.��(�)   ",                   \
  "�������� ����(�)",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " �.��.���2 �� ��",                   \
  "�.��.���2 �� I�2",                   \
  "�.��.���2 �� I�5",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.���.���2  ",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "   ����.3U0-1   ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  "   ����.����4   ",                   \
  "���� ����1 �� ��",                   \
  "���� ����2 �� ��",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  "  ����.�����1   ",                   \
  "  ���� �����1   ",                   \
  "  ����.�����2   ",                   \
  "  ���� �����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.���    ",                   \
  "    ����.��     ",                   \
  "     ��.��1     ",                   \
  "     ��.��2     ",                   \
  "   ��.��-���    ",                   \
  "    ����.��     ",                   \
  "     ��.��      ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-��������1",                   \
  " ���.�-��������1",                   \
  " ���.�-��������2",                   \
  " ���.�-��������2",                   \
  " ���.�-��������3",                   \
  " ���.�-��������3",                   \
  " ���.�-��������4",                   \
  " ���.�-��������4"
        
#endif 
