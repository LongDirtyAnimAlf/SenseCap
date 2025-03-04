#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "shared.h"

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#include <EEPROM.h>
#else
#include "src/FlashStorage.h"
#endif

void storeInit(void);
void storePutBoardInfo(TBoardInfo * Info);
void storeGetBoardInfo(TBoardInfo * Info);

#endif
