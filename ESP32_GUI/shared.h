#include <Arduino.h>

#define    DAUGHTERBOARDCOUNT         16 // MaX 16 !!!!

#define    BITS                       16 // Resolution of the battery measurement data
#define    MAXVOLTAGE                 3300u
#define    MAXCURRENT                 6000u

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

typedef enum {
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

typedef enum {
  BSOff=0,
  BSCurrent,
  BSPower,
  BSResistor,
  BSReserve,
  BSCharge,
  BSVoltage,
  BSPulse
} TBatteryStatus;

typedef struct
{
  word V;
  word I;
  //dword C;
  dword E;
  word T;
  TBatteryStatus Status;
  dword StatusValue;
  bool NeedsGUIUpdate;
  byte DatSendError;
  byte BytesReceived;
  bool CRCError;
  bool Blocked;
  byte Address;
} TBatteryData,*PBatteryData;

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

typedef struct {
  bool Valid;
  byte BoardSerial[12];
  byte BoardNumber;
} TBoardInfo;
