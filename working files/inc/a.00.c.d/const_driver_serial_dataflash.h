#ifndef __CONST_DRIVER_SERIAL_FLASH__
#define __CONST_DRIVER_SERIAL_FLASH__

#define NUMBER_DATAFLASH_CHIP      2

#define INDEX_DATAFLASH_1           0
#define INDEX_DATAFLASH_2           1
#define INDEX_EEPROM                3

#define VAGA_SIZE_PAGE_DATAFLASH_1      8 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 256 � ����� �� 256
#define SIZE_PAGE_DATAFLASH_1           (1 << VAGA_SIZE_PAGE_DATAFLASH_1) //256 ����
#define NUMBER_PAGES_INTO_DATAFLASH_1   512

#define VAGA_SIZE_PAGE_DATAFLASH_2      9 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 512 � ����� �� 512
#define SIZE_PAGE_DATAFLASH_2           (1 << VAGA_SIZE_PAGE_DATAFLASH_2) //512 ����
#define NUMBER_PAGES_INTO_DATAFLASH_2   4096

#if SIZE_PAGE_DATAFLASH_2 >= SIZE_PAGE_DATAFLASH_1
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_2
#else
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_1
#endif

#define NUMBER_PAGES_INTO_AR            NUMBER_PAGES_INTO_DATAFLASH_2
#define NUMBER_PAGES_INTO_DR            480
#define NUMBER_PAGES_INTO_PR_ERR        (NUMBER_PAGES_INTO_DATAFLASH_1 - NUMBER_PAGES_INTO_DR)

#define NUMBER_PAGES_IN_ONE_DR_RECORD         10
#define SIZE_BUFFER_FOR_DR_RECORD             (SIZE_PAGE_DATAFLASH_1*NUMBER_PAGES_IN_ONE_DR_RECORD) 
#define MAX_NUMBER_RECORDS_INTO_DR            48
#define MIN_ADDRESS_DR_AREA                   0x0
#define SIZE_DR_AREA                          (NUMBER_PAGES_INTO_DR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_DR_AREA                   (MIN_ADDRESS_DR_AREA + SIZE_DR_AREA - 1)

#define FIRST_INDEX_START_START_RECORD_DR     0
#define FIRST_INDEX_DATA_TIME_DR              1
#define FIRST_INDEX_EXTRA_SETTINGS_DR         8
#define FIRST_INDEX_NAME_OF_CELL_DR           12
#define FIRST_INDEX_NUMBER_ITEMS_DR           44
#define FIRST_INDEX_NUMBER_CHANGES_DR         45
#define FIRST_INDEX_NUMBER_MAX_PHASE_DR       47
#define FIRST_INDEX_NUMBER_MAX_PHASE04_DR     48
#define FIRST_INDEX_NUMBER_MAX_3I0_DR         49
#define FIRST_INDEX_NUMBER_MAX_3U0_DR         50
#define FIRST_INDEX_NUMBER_MIN_U_DR           51
#define FIRST_INDEX_NUMBER_MAX_U_DR           52
#define FIRST_INDEX_NUMBER_MAX_ZOP_DR         53
#define FIRST_INDEX_NUMBER_MIN_F_ACHR_DR      54
#define FIRST_INDEX_NUMBER_F_CHAPV_DR         55
#define FIRST_INDEX_FIRST_BLOCK_DR            56
#define FIRST_INDEX_FIRST_DATA_DR             1176

#define VAGA_SIZE_ONE_RECORD_PR_ERR           6
#define SIZE_ONE_RECORD_PR_ERR                (1<<VAGA_SIZE_ONE_RECORD_PR_ERR)
#define NUMBER_RECORDS_PR_ERR_INTO_PAGE       (SIZE_PAGE_DATAFLASH_1>>VAGA_SIZE_ONE_RECORD_PR_ERR) //������� ������ ���������� ���� � ����� �������� ��������� ��������� DataFlash
#define MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER 32 //������������������ ������ � ����� ���� FIFO, �� ������� �� ������ DataFlash
#define SIZE_BUFFER_FOR_PR_ERR                (SIZE_ONE_RECORD_PR_ERR*MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER)
#define MAX_NUMBER_RECORDS_INTO_PR_ERR        (NUMBER_PAGES_INTO_PR_ERR*NUMBER_RECORDS_PR_ERR_INTO_PAGE)
#define MIN_ADDRESS_PR_ERR_AREA               (MAX_ADDRESS_DR_AREA + 1)
#define SIZE_PR_ERR_AREA                      (NUMBER_PAGES_INTO_PR_ERR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_PR_ERR_AREA               (MIN_ADDRESS_PR_ERR_AREA + SIZE_PR_ERR_AREA - 1)

#define MASKA_BIT_FOR_PRESCALER               0x1
#define VAGA_NUMBER_POINT_AR                  (VAGA_NUMBER_POINT - 1)
#define NUMBER_POINT_AR                       (1 << VAGA_NUMBER_POINT_AR)
#define MIN_ADDRESS_AR_AREA                   0x0
#define SIZE_AR_AREA                          (NUMBER_PAGES_INTO_AR<<VAGA_SIZE_PAGE_DATAFLASH_2)
#define MAX_ADDRESS_AR_AREA                   (MIN_ADDRESS_AR_AREA + SIZE_AR_AREA - 1)


#define TRANSACTION_EXECUTING_NONE              0
#define TRANSACTION_EXECUTING                   1
#define TRANSACTION_EXECUTED_WAIT_ANALIZE       2

#define CODE_OPERATION_NONE                                 0
#define CODE_OPERATION_STATUS_READ                          1
#define CODE_OPERATION_PAGESIZE_256                         2
#define CODE_OPERATION_ERASE                                3
#define CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER            4
#define CODE_OPERATION_READ_HIGH_FREQ                       5
#define CODE_OPERATION_READ_PAGE_INTO_BUFFER                6
#define CODE_OPERATION_WRITE_BUFFER                         7
#define CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE  8

/*���� 0-15 �������� �� ��������� DataFlash ����������� ���������� � ���������� ���������� ����*/
#define TASK_ERASE_DATAFLASH_1_BIT                                          0
#define TASK_ERASE_DATAFLASH_1                                              (1<<TASK_ERASE_DATAFLASH_1_BIT)
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT                        1
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH                            (1<<TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT        2
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT                          3
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT                      4
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU                          (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT                           5
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT                         6
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT                       7
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB                           (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT                     8
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485                         (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT)

#define  SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2                16

/*���� 16-31 �������� �� ��������� DataFlash ����������� ����������*/
#define TASK_ERASE_DATAFLASH_2_BIT                                          (0 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_ERASE_DATAFLASH_2                                              (1<<TASK_ERASE_DATAFLASH_2_BIT)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT   (1 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR       (1<<TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT        (2 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT                          (3 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT                           (5 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT                         (6 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT)

#define WIGHT_OF_DR_WAITING                       2

#define STATE_DR_NO_RECORD                        0 //�� ����� ������ ����� �� � ���������� ����������� �� ����������
#define STATE_DR_FORCE_START_NEW_RECORD           1 //��������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����
#define STATE_DR_EXECUTING_RECORD                 2 //��� ������ ������ ����������
#define STATE_DR_MAKE_RECORD                      3 //�������� ����� ���  ������ � Dataflash
#define STATE_DR_CUT_RECORD                       4 //��������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����

#define MAX_TIME_OFFSET_FROM_START                      0xFFFFFF // 4 ���. 39 ��. 37 ���. 215 �����.
#define MAX_EVENTS_IN_ONE_RECORD                        36
#define MAX_NUMBER_FIX_MAX_MEASUREMENTS                 10
#define SIZE_ARRAY_FIX_MAX_MEASUREMENTS                 (NUMBER_ANALOG_CANALES + 13)

#define LABEL_START_RECORD_DR           0xA5

#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE          1
#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0            3
#define IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0            4
#define IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE                5
#define IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE                6
#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP            7

#define READING_DR_FOR_MENU             1
#define READING_DR_FOR_USB              2
#define READING_DR_FOR_RS485            3
#define READING_PR_ERR_FOR_MENU         4
#define READING_PR_ERR_FOR_USB          5
#define READING_PR_ERR_FOR_RS485        6

#define READING_AR_FOR_MENU             1
#define READING_AR_FOR_USB              2
#define READING_AR_FOR_RS485            3

#define LABEL_START_RECORD_PR_ERR       0x5A

#define ETAP_NONE                                 0
#define ETAP_READ_MEMORY_INTO_BUFFER              1
#define ETAP_HAVE_READ_MEMORY_INTO_BUFFER         2
#define ETAP_MODIFY_AND_WRITE_BUFFER              3
#define ETAP_MODIFIED_AND_WRITTEN_BUFFER          4
#define ETAP_WRITE_BUFFER_INTO_MEMORY             5
#define ETAP_ERROR_BEFALLEN                       6

#define LABEL_START_RECORD_AR           0xAB

#define STATE_AR_TEMPORARY_BLOCK                  -1//�� ����� ������ ����� �������� �������� �������� ������ ����������� �����������
#define STATE_AR_NO_RECORD                        0 //�� ����� ������ ������ �� � ���������� ����������� �� ����������
#define STATE_AR_START                            1 //������ ������ ������ ����������� ����������
#define STATE_AR_SAVE_SRAM_AND_SAVE_FLASH         2 //���� ������ ����������� ���������� "�������� � ��������"
#define STATE_AR_ONLY_SAVE_FLASH                  3 //���� ������ ����������� ���������� "����� ��������", �� "��������" ��� ����������

/*
�������� � ����, �� ����������� �������� ���������� ����� ���� ���� 5�(����������
�����) + 25�(������������ �����) = 30�
��� ������ ��'�� ����
30(�)�50(������)�16(������� �� �����)�(12(������) + 18(��������� ����� ���������� �������))
�2(����� �� �����) = 1440000(�����)
�� �� ���� 1(���� ���� ������� ������ )+7(����� ���� ����)+4(����� ����.��.��(��))+
4(����� ����.��.��(��))+4(����� ����.��.��)+32(����� ����� ������) = 52 �����

!!!����� ��������� ���������� ����������� ����'������ �� ���� ������ �������� 2, 
��� �� ������ ���, �� ���� �� ������� ����� ��� ������ � DataFlash (����� ������ 
256 ����), �� �� �������� �������� ���� ������ ������� (����� 2-� ����): ��� � 
������� ��������, �� ���� ���� ����� ������ ����� �����������, � ����� ���� - 
��� ������ �����������. �� �������� ���� � ���������� ������ � ���������� �����������. 
���� ����� ���� �������� �������� ���� ����� ������� � ����� ������/������� 
��������� dataFlash � ������� 2, ����� ������ ������� � ������� 2, �� � ����� 
��������� ����������� ���������� �� ���� ������� 2.!!!
52 � ������� 2 - ����, ��� ���������!

����� ����� ������������� ����������� ������ 1440000+52 = 1440052(�����)
� ����������� ����, �� ����� ������� DF ��������� 512 ����, �� ������������
���������� ����� ��������� 1440052/512 = 2812,6015625 �������. ������� ���� ������� 
����� � 2813 ������� DF.

������� ��������� SRAM ��������� 85(��)  - �� ������� � ��������� FSMC. ��� ��� ��������� 512 
���� � ��������� SRAM � �������� SRAM ��������� 512(����)�85(��)=43,52(���)

DF(DataFlsh) ���������� � ����������� ��������������� ����� SPI1, ���� ���������
�� �������� ����� 7.5����/� � ������ 8 �� ����������. ����� �������� ����� 
��������� 0,9375������/�.

� ����������� �������� ����� � ����� ������ ������� ��� ����

1)����� 512 ���� � DF ��������� "Main Memory Page Program Through Buffer" < 25,551(��)
2)������� ������� � ����� ��������� "Main Memory Page to Buffer Transfer" < 205(���)
3)����������� �� 512 ���� � ����� DF ��������� "Buffer Write" < 551(���)
4)����� ������ DF � DF ��������� "Buffer to Main Memory Page Program with 
Built-in Erase" < 25,001(��)

��� ������ ���� ������� ����� �������� ��������:
��������� 512 ���� � ��������� SRAM � �������� SRAM < 43,52(���)
�������� ������� "Main Memory Page Program Through Buffer" < 25,551(��)
��������� ������ �� �������, ���� ������������� ����� 2�� (�� ��� ����������
DataFlash1/DataFlash2). ���� �� 26 �� �� ������� �� ����������� ����������.
��� ������������� �������� �������� 30 ��.

��� ����������� �� 512 ���� �� ����� ������� �����:
��������� 512 ���� � ��������� SRAM � �������� SRAM < 43,52(���)
�������� ������� "Main Memory Page to Buffer Transfer" < 205(���)

����� 2(��) ����������� �������� �������� ��� ������� (���. ��������� ����) ���� 
���������� �� ���� � ����������� ����� �� 202(���) < 2 (�c)
�� ����� 2(�� (���. ��������� ����) ����� ��������� �������� ��������������� � �����.
����� �������� �� ���������� ������ 4(��)
����� ������� �������� ���� �� 202(���), � 4(��)

�������� ����������� ���� � ����� DF < 551(���) 

����� 2(��) ���������� �������� �������� ��� ������� (���. ��������� ����) ���� 
���������� �� ���� � ����������� ����� �� 205(���) < 2 (�c)
�� ����� 2(��) (���. ��������� ����) ����� ��������� �������� ������ � �����.
����� �������� �� ���������� ������ 4(��)
����� ������� �������� ���� �� 138(���), � 4(��)

�������� ������� "Buffer to Main Memory Page Program with 
Built-in Erase" < 25,001(��)
��������� ������ �� �������, ���� ������������� ����� 2�� (���. ��������� ����).
���� �� 26 �� �� ������� �� ����������� ����������.
�������� ���:
43,52(���)+4(��)+4(��)+26(��) = 35(��)
��� ������������� �������� �������� 36 ��.

���������� ����� ����� � ������� ������� ������ ������������ ������ ���������
(� ������������ ��������� ������) � �� ����� ������ ������������ ��������
���������, ��� ��� ����������� �� ���� ������������ - ������� ����������, ���� �������
����������� � ������ ����� - 36(��)

��� ��� ������ 2813 ������� ����� ����
2251(�������)�36(��) = 101 268(��)=101,268(�)

����� ������ ������ ������������� ����������� ������ ���� ������� 101,268(�)

�������� "����������" �������� ��������� � ����������� ��������� � ����������� �������:
(12(������) + 18(��������� ����� ���������� �������))�2(����� �� ��������)/1,25(��
- �������� �� ��������� ��� ������ 50�� � 16 ������� �� �����) = 48,0 (����/��)
������� �� �������� � ������, �� �� �� ������ ��� ������ ��������� �� ������������

������� "��������" ������ ����������� ���������� � DF:
2813(�������)�512(���� �� �������)/101268(��) = 14,(2) (����/��)
������� �� �������� �� � ������, ���� �� �� ��� ������ ������������. �����, �������,
������� �� ���� �� �����, �� ������������ �������� � 
������� ��������� ������� ����� �� ������ �� ���� ����, �������, �� �� ������� 
���������� �� 36(��) - ��� �������� ������ ����� ����������� ��������� ������
(���. ��������� ����)).

���������� ��������� ������ ��� "����������" �� ��������� �� "��������
���� ������������ � ��������: 48,0 - 14,(2) = 33,78(����/��)
�� ���������� ���� ������������� ���� ���������� "����������", ����� �����������
�������� ��� 25(�)  -������������ ��� ������������� ������.
25000(��)*33,78(����/��) = 844500(����) <= 844500(����)
844500(����)/512(����/����.) = 1649,4140625(�������) < 1650(�������)

��� ���� ����� ���� �� ���� ��, �� � ����� ����������� ���������� � 52 ����
���������� �� ������ (����� ������� ������, ���, ����������� �������������, ��'�
������). ��� ���� ������ ���������� "����������" � "��������" �� ������ �� �����
���������� "����������" � ����� �������� "��������" ���� � ����������. ��� ����, ��
������� "��������" ���� ������ �� ������� "����������" - �� � ����� "��������"
������ "����������" � ���� ��������� �� �� ����� �����.

�� ����� �������������� ������� � ����� �������, �� ����� ������ ����������� 
��������� ������� ������� ���� � ��������� � (����� ����������� ������ + 
(1651 + 1) ������� DF). �� ���� ������� �� 1650 ���������� ������������ � ����� 
��� ������������.

����� ����� �� ����
5(� - ����. ������. ���.)�50(����.�������)�16(����. �����.�� ���. ��� ��.�.)�(12(������) + 18(��������� ����� ���������� �������)) +1651*[512(����)/2(���� �� ���� ������ ��������)](������� ������� ������� �� �������)=
= 120000 +1651�256 = 542656

����� �� ���� ������� (������� ���������� ������ + ������� ���������� ��� ���������� �������).
�� ����� ��� ����, ��� �� ��������� ��� ������� ����� �� �� �� ������ �� �����, � 
��� �������� ���������� ��� ����� ������ ����
������ ������� ����������� � ������� ������� (������� ���������� ������ + 
������� ���������� ��� ���������� �������), �� �� ���������
���������, ���� ���������� "������� ��.������ + ��������� ����� ���������� �������"
���� ����� �������� �� ������ ��������
1651(�������)�256(���) = 422656 (���)

422656/(12 + 18)= 14088,533333333333333333333333333
���� ������ �� � ���� �����, �� ����� �������� ��������, ��� �/(12 + 18)
������ ���� �����, ������� � >= 422656 - ����� ������ ��������� ����� X = 422670

����� �����
120000 + 422670 = 542670

!!!������������� �� ���� ������� ������ ������ ���������� 542670 �������� (�����������,
��� �� ����� ������� ���������� �� ���� ����)!!!

*/

#define SIZE_BUFFER_FOR_AR    250830/*542670*/

#define CLEAN_AR_BIT          0
#define CLEAN_AR              (1 << CLEAN_AR_BIT)
#define CLEAN_DR_BIT          1
#define CLEAN_DR              (1 << CLEAN_DR_BIT)
#define CLEAN_PR_ERR_BIT      2
#define CLEAN_PR_ERR          (1 << CLEAN_PR_ERR_BIT)

#endif
