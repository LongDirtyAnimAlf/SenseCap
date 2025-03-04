/*
 * start rewrite from:
 * https://github.com/adafruit/Adafruit-GFX-Library.git
 */
#include "Indicator_SWSPI.h"
#include "Indicator_Extender.h"

extern PCA9555 ioex;

Indicator_SWSPI::Indicator_SWSPI(int8_t dc, int8_t cs, int8_t sck, int8_t mosi, int8_t miso /* = GFX_NOT_DEFINED */)
    : _dc(dc), _cs(cs), _sck(sck), _mosi(mosi), _miso(miso)
{
}

bool Indicator_SWSPI::begin(int32_t, int8_t)
{
  extender_init();

  if (_cs != GFX_NOT_DEFINED)
  {
    // LCD CS PIN
    ioex.write(static_cast<PCA95x5::Port::Port>(_cs), PCA95x5::Level::L);
    ioex.direction(static_cast<PCA95x5::Port::Port>(_cs), PCA95x5::Direction::OUT);
  }
  if (_dc != GFX_NOT_DEFINED)
  {
    pinMode(_dc, OUTPUT);
    digitalWrite(_dc, HIGH); // Data mode
  }
  if (_cs != GFX_NOT_DEFINED)
  {
    ioex.write(static_cast<PCA95x5::Port::Port>(_cs), PCA95x5::Level::H);
  }
  pinMode(_sck, OUTPUT);
  digitalWrite(_sck, LOW);
  pinMode(_mosi, OUTPUT);
  digitalWrite(_mosi, LOW);
  if (_miso != GFX_NOT_DEFINED)
  {
    pinMode(_miso, INPUT);
  }

  return true;
}

void Indicator_SWSPI::beginWrite()
{
  if (_dc != GFX_NOT_DEFINED)
  {
    DC_HIGH();
  }
  CS_LOW();
}

void Indicator_SWSPI::endWrite()
{
  CS_HIGH();
}

void Indicator_SWSPI::writeCommand(uint8_t c)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
    WRITE9BITCOMMAND(c);
  }
  else
  {
    DC_LOW();
    WRITE(c);
    DC_HIGH();
  }
}

void Indicator_SWSPI::writeCommand16(uint16_t c)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
    _data16.value = c;
    WRITE9BITCOMMAND(_data16.msb);
    WRITE9BITCOMMAND(_data16.lsb);
  }
  else
  {
    DC_LOW();
    WRITE16(c);
    DC_HIGH();
  }
}

void Indicator_SWSPI::writeCommandBytes(uint8_t *data, uint32_t len)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
    while (len--)
    {
      WRITE9BITCOMMAND(*data++);
    }
  }
  else
  {
    DC_LOW();
    while (len--)
    {
      WRITE(*data++);
    }
    DC_HIGH();
  }
}


void Indicator_SWSPI::write(uint8_t d)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
    WRITE9BITDATA(d);
  }
  else
  {
    WRITE(d);
  }
}

void Indicator_SWSPI::write16(uint16_t d)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
    _data16.value = d;
    WRITE9BITDATA(_data16.msb);
    WRITE9BITDATA(_data16.lsb);
  }
  else
  {
    WRITE16(d);
  }
}

void Indicator_SWSPI::writeRepeat(uint16_t p, uint32_t len)
{
  if (_dc == GFX_NOT_DEFINED) // 9-bit SPI
  {
// ESP8266 avoid trigger watchdog
#if defined(ESP8266)
    while (len > (ESP8266SAFEBATCHBITSIZE / 9))
    {
      WRITE9BITREPEAT(p, ESP8266SAFEBATCHBITSIZE / 9);
      len -= ESP8266SAFEBATCHBITSIZE / 9;
      yield();
    }
    WRITE9BITREPEAT(p, len);
#else
    WRITE9BITREPEAT(p, len);
#endif
  }
  else
  {
#if defined(ESP8266)
    while (len > (ESP8266SAFEBATCHBITSIZE / 8))
    {
      WRITEREPEAT(p, ESP8266SAFEBATCHBITSIZE / 8);
      len -= ESP8266SAFEBATCHBITSIZE / 8;
      yield();
    }
    WRITEREPEAT(p, len);
#else
    WRITEREPEAT(p, len);
#endif
  }
}

void Indicator_SWSPI::writePixels(uint16_t *data, uint32_t len)
{
  while (len--)
  {
    WRITE16(*data++);
  }
}

#if !defined(LITTLE_FOOT_PRINT)
void Indicator_SWSPI::writeBytes(uint8_t *data, uint32_t len)
{
  while (len--)
  {
    WRITE(*data++);
  }
}
#endif // !defined(LITTLE_FOOT_PRINT)

GFX_INLINE void Indicator_SWSPI::WRITE9BITCOMMAND(uint8_t c)
{
  // D/C bit, command
  SPI_MOSI_LOW();
  SPI_SCK_HIGH();
  SPI_SCK_LOW();

  uint8_t bit = 0x80;
  while (bit)
  {
    if (c & bit)
    {
      SPI_MOSI_HIGH();
    }
    else
    {
      SPI_MOSI_LOW();
    }
    SPI_SCK_HIGH();
    bit >>= 1;
    SPI_SCK_LOW();
  }
}

GFX_INLINE void Indicator_SWSPI::WRITE9BITDATA(uint8_t d)
{
  // D/C bit, data
  SPI_MOSI_HIGH();
  SPI_SCK_HIGH();
  SPI_SCK_LOW();

  uint8_t bit = 0x80;
  while (bit)
  {
    if (d & bit)
    {
      SPI_MOSI_HIGH();
    }
    else
    {
      SPI_MOSI_LOW();
    }
    SPI_SCK_HIGH();
    bit >>= 1;
    SPI_SCK_LOW();
  }
}

GFX_INLINE void Indicator_SWSPI::WRITE(uint8_t d)
{
  uint8_t bit = 0x80;
  while (bit)
  {
    if (d & bit)
    {
      SPI_MOSI_HIGH();
    }
    else
    {
      SPI_MOSI_LOW();
    }
    SPI_SCK_HIGH();
    bit >>= 1;
    SPI_SCK_LOW();
  }
}

GFX_INLINE void Indicator_SWSPI::WRITE16(uint16_t d)
{
  uint16_t bit = 0x8000;
  while (bit)
  {
    if (d & bit)
    {
      SPI_MOSI_HIGH();
    }
    else
    {
      SPI_MOSI_LOW();
    }
    SPI_SCK_HIGH();
    bit >>= 1;
    SPI_SCK_LOW();
  }
}

GFX_INLINE void Indicator_SWSPI::WRITE9BITREPEAT(uint16_t p, uint32_t len)
{
  if (p == 0xffff) // no need to set MOSI level while filling white
  {
    SPI_MOSI_HIGH();
    len *= 18; // 9-bit * 2
    while (len--)
    {
      SPI_SCK_HIGH();
      SPI_SCK_LOW();
    }
  }
  else
  {
    _data16.value = p;
    while (len--)
    {
      WRITE9BITDATA(_data16.msb);
      WRITE9BITDATA(_data16.lsb);
    }
  }
}

GFX_INLINE void Indicator_SWSPI::WRITEREPEAT(uint16_t p, uint32_t len)
{
  if ((p == 0x0000) || (p == 0xffff)) // no need to set MOSI level while filling black or white
  {
    if (p)
    {
      SPI_MOSI_HIGH();
    }
    else
    {
      SPI_MOSI_LOW();
    }
    len *= 16;
    while (len--)
    {
      SPI_SCK_HIGH();
      SPI_SCK_LOW();
    }
  }
  else
  {
    while (len--)
    {
      WRITE16(p);
    }
  }
}

/******** low level bit twiddling **********/

GFX_INLINE void Indicator_SWSPI::DC_HIGH(void)
{
  digitalWrite(_dc, HIGH);
}

GFX_INLINE void Indicator_SWSPI::DC_LOW(void)
{
  digitalWrite(_dc, LOW);
}

GFX_INLINE void Indicator_SWSPI::CS_HIGH(void)
{
  if (_cs != GFX_NOT_DEFINED)
  {
    ioex.write(static_cast<PCA95x5::Port::Port>(_cs), PCA95x5::Level::H);
  }
}

GFX_INLINE void Indicator_SWSPI::CS_LOW(void)
{
  if (_cs != GFX_NOT_DEFINED)
  {
    ioex.write(static_cast<PCA95x5::Port::Port>(_cs), PCA95x5::Level::L);
  }
}

/*!
    @brief  Set the software (bitbang) SPI MOSI line HIGH.
*/
GFX_INLINE void Indicator_SWSPI::SPI_MOSI_HIGH(void)
{
  digitalWrite(_mosi, HIGH);
}

/*!
    @brief  Set the software (bitbang) SPI MOSI line LOW.
*/
GFX_INLINE void Indicator_SWSPI::SPI_MOSI_LOW(void)
{
  digitalWrite(_mosi, LOW);
}

/*!
    @brief  Set the software (bitbang) SPI SCK line HIGH.
*/
GFX_INLINE void Indicator_SWSPI::SPI_SCK_HIGH(void)
{
  digitalWrite(_sck, HIGH);
}

/*!
    @brief  Set the software (bitbang) SPI SCK line LOW.
*/
GFX_INLINE void Indicator_SWSPI::SPI_SCK_LOW(void)
{
  digitalWrite(_sck, LOW);
}

/*!
    @brief   Read the state of the software (bitbang) SPI MISO line.
    @return  true if HIGH, false if LOW.
*/
GFX_INLINE bool Indicator_SWSPI::SPI_MISO_READ(void)
{
  return digitalRead(_miso);
}
