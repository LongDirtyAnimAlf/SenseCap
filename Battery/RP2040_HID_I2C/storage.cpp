#include "storage.h"

#if defined(ARDUINO_ARCH_SAMD)
// Reserve a portion of SAMD flash memory to store an "BoardInfo" variable
// and call it "my_flash_store".
FlashStorage(my_flash_store, TBoardInfo);
#endif

void storeInit(void)
{
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  EEPROM.begin(512);
  #endif
}

void storePutBoardInfo(TBoardInfo * Info)
{
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  EEPROM.put(0U, *Info);
  EEPROM.commit();      
  #endif
  #if defined(ARDUINO_ARCH_SAMD)
  my_flash_store.write(*Info);
  #endif
}

void storeGetBoardInfo(TBoardInfo * Info)
{
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  EEPROM.get(0U, *Info);
  #endif
  #if defined(ARDUINO_ARCH_SAMD)
  *Info = my_flash_store.read();
  #endif
}
