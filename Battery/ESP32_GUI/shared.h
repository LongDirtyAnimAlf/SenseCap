#ifndef _SHARED_H_
#define _SHARED_H_

#include <Arduino.h>

#define    DEBUG

#ifndef ARDUINO_ARCH_SAMD
// Only SenseCap can be standalone !!
#define    STANDALONE
#endif

#define    MAXDAUGHTERBOARDCOUNT      16

#ifdef STANDALONE
#define    DAUGHTERBOARDCOUNT         4
#else
#define    DAUGHTERBOARDCOUNT         MAXDAUGHTERBOARDCOUNT
#endif

#define    FW_MAJOR                   56
#define    FW_MINOR                   12


#define    BITS                       16 // Resolution of the battery measurement data

#define    DATASIZE                   600u

#define    MAXVOLTAGE                 3300u
#define    MAXCURRENT                 6000u

#ifdef CFG_TUD_ENDPOINT0_SIZE
#undef CFG_TUD_ENDPOINT0_SIZE
#endif

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE 16
#endif

#define HID_INT_IN_EP_SIZE     CFG_TUD_ENDPOINT0_SIZE
#define HID_INT_OUT_EP_SIZE    CFG_TUD_ENDPOINT0_SIZE

#define COMMAND_SIZE           CFG_TUD_ENDPOINT0_SIZE

#define    USB_CMD_get_serial         0x64
#define    USB_CMD_set_serial         0x65
#define    USB_CMD_get_firmware       0xC8
#define    USB_CMD_get_board_number   0xCA
#define    USB_CMD_set_board_number   0xCB

#define    USB_CMD_error              0xFF

#define    CMD_controller_reset       0xB0
#define    CMD_set_program_mode       0xB1

typedef uint32_t dword;
typedef uint64_t qword;

typedef union
{
    word Val;
    byte v[2];// __PACKED;
    struct //__PACKED
    {
        byte LB;
        byte HB;
    } bytes;
} WORD_VAL, WORD_BITS;

#define IDDLESTAGENUMBER              0
#define FIXEDDISCHARGESTAGENUMBER     1
#define FIXEDCHARGESTAGENUMBER        2

typedef enum
{
  btn_back = 0,
  btn_next = 1,
  // followed by battery select buttons
  btn_controls = (2 + MAXDAUGHTERBOARDCOUNT), // dummy start placeholder
  btn_test_discharge,  
  btn_start_discharge,
  btn_test_charge,  
  btn_start_charge
} TButtons;


typedef enum
{
  CMD_unknown = 0x4F,
  CMD_get_data,
	CMD_get_hardware,
  CMD_set_cal,
  CMD_get_cal,
  CMD_set_value,
  CMD_get_firmware,
  CMD_error,
  CMD_set_energy,
  CMD_get_timer,
  CMD_set_timer,
  CMD_set_tun,
  CMD_store_tun,
  CMD_get_data_special,
  CMD_set_value_special,
  CMD_get_memory,
  CMD_set_memory,
  CMD_set_caltable,
  CMD_get_caltable,
  CMD_set_localserial,
  CMD_get_localserial
} TCommands;

typedef enum 
{
  smOff = 0,
  smCurrent,
  smPower,
  smResistor,
  smReserve,
  smCharge,
  smVoltage,
  smPulse,
  smTopOff,
  smTrickle,
  smZero,
  smDisabled
} TStageMode;

typedef enum
{
  tmNONE=0,
  tmMAXV,
  tmMINV,
  tmDELTAV,
  tmPLATEAUV,
  tmABST,
  tmDELTAT,
  tmDVT,
  tmTIME,
  tmLast
} TThresholdModes;

typedef struct
{
  TThresholdModes Mode;
  word SetValue;
  bool Enabled;
  bool Triggered;
  word GetValue;
} TThresholdDataItem;

typedef struct
{
  word V;
  word I;
  //dword C;
  //dword E;
  //word T;
} TMeasurementData,*PMeasurementData;

typedef struct
{
  TMeasurementData *BatteryDatas;
  dword Capacity;
  dword Energy;
  word Temperature;
  int16_t Tail;
  int16_t Head;
  byte CurrentStageNumber;
  TThresholdDataItem ThresholdResult[tmLast]; // all threshold possibilities
} TRunDatas,*PRunDatas;

typedef struct
{
  byte I2CBytesReceived;
  byte I2CSendError;
  bool I2CCRCError;
  bool I2CBlocked;
  byte I2CAddress;
} TI2CStatus,*PI2CStatus;

typedef enum
{
  bmIdle = 0,
  bmActive,
  bmPause,
  bmWaiting,
  bmOff,
  bmReady,
  bmError
} TBatteryMode;

typedef struct
{
  TStageMode Status;
  dword SetValue;
  TThresholdDataItem ThresholdSettings[tmLast]; // all threshold possibilities
} TStageData;

typedef struct
{
 TBatteryMode         Active;
 TStageMode           SetStageMode;
 dword                SetStageValue;
 TThresholdModes      ThresholdMode;
 dword                ThresholdValue;
 TRunDatas            RunDatas;
} TTestData;

typedef struct {
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  bool InValid;
  #endif
  #if defined(ARDUINO_ARCH_SAMD)  
  bool Valid;
  #endif
  byte BoardSerial[12];
  byte BoardNumber;
} TBoardInfo;

typedef struct
{
  TMeasurementData MD;
  TStageData BM;
  word Vmax;
  word Imax;
  word Firmware;
  byte Serial[8];
  bool NeedsGUIUpdate;
  bool NeedsDataUpdate;
  TI2CStatus I2CStatus;
} TBatteryBoard,*PBatteryBoard;

typedef struct
{
  char code[10];
  char brand[30];
  char type[30];
  TStageData Stages[3]; // at max three : iddle, discharge and charge to keep it simple
  TTestData TestData;
} TBatterySetting,*PBatterySetting;

typedef struct
{
  byte HIDEPOUTData[HID_INT_OUT_EP_SIZE];
  byte HIDEPINData[HID_INT_IN_EP_SIZE];
  bool DataReceived;
} THIDData;

#endif