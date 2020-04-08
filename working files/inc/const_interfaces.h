#ifndef __CONST_INTERFACES__
#define __CONST_INTERFACES__

/*****************************************************/
/* ������� ����������� */
/*****************************************************/
#define M_ADDRESS_FIRST_USER_REGISTER_DATA      16
#define M_ADDRESS_LAST_USER_REGISTER_DATA       99
/*****************************************************/

/*****************************************************/
/* �������� ������ ������� ����������� � ����������� ���������� */
/*****************************************************/
#define MA_CLEAR_NUMBER_RECORD_AR     13074
#define CMD_WORD_CLEAR_AR                     0x1312
#define MA_CLEAR_NUMBER_RECORD_DR     13075
#define CMD_WORD_CLEAR_DR                     0x1012
/*****************************************************/

///*****************************************************/
///* �������� ������ ���������� Watch dog*/
///*****************************************************/
//#define MA_TEST_WATCHDOGS                     63472
//#define CMD_TEST_EXTERNAL_WATCHDOG            0xCDEF
///*****************************************************/


#define USB_RECUEST           0
#define RS485_RECUEST         1

enum _data_changed_bit
{
SETTINGS_DATA_CHANGED_BIT = 0,
RANGUVANNJA_DATA_CHANGED_BIT,
USER_REGISTRY_CHANGED_BIT,
NEW_PASSWORD_SET_BIT,
DEFAULT_SETTINGS_SET_BIT
};

#define BROADCAST_ADDRESS_MODBUS_RTU    0

#define BUFFER_RS485          256
#define BUFFER_USB            256

#define MAX_TIMEOUT_PACKET    7500 // 75 ��, ���� ���������, �� ҲM4 ����� � ������� 10 ���

#define ERROR_ILLEGAL_FUNCTION                        1
#define ERROR_ILLEGAL_DATA_ADDRESS                    2 
#define ERROR_ILLEGAL_DATA_VALUE                      3 
#define ERROR_SLAVE_DEVICE_FAILURE                    4
#define ERROR_ACKNOWLEDGE                             5
#define ERROR_SLAVE_DEVICE_BUSY                       6
#define ERROR_MEMORY_PARITY_ERROR                     8
#define ERROR_GATEWAY_PATH_UNAVAILABLE                0xA
#define ERROR_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND 0xB
#define ERROR_BROADCAST_ADDRESS                       0xFF


#endif
