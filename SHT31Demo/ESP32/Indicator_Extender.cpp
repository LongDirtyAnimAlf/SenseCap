#include "Indicator_Extender.h"

/* Install: Anitracks_PCA95x5*/

PCA9555 ioex;

bool extender_init_done = false;

void extender_init(void)
{
  if (!extender_init_done)
  {
    // Extender init.
    Wire.begin(EXTENDER_SDA, EXTENDER_SCL, EXTENDER_SPEED);
    ioex.attach(Wire);

    ioex.polarity(PCA95x5::Polarity::ORIGINAL_ALL);

    // LCD Reset PIN
    ioex.write(EXPANDER_IO_LCD_RESET, PCA95x5::Level::L);
    ioex.direction(EXPANDER_IO_LCD_RESET, PCA95x5::Direction::OUT);

    // Touchscreen interupt PIN
    ioex.direction(EXPANDER_IO_LCD_INT, PCA95x5::Direction::IN);

    // Touchscreen reset PIN
    ioex.write(EXPANDER_IO_TP_RESET, PCA95x5::Level::L);
    ioex.direction(EXPANDER_IO_TP_RESET, PCA95x5::Direction::OUT);

    // RP2040 reset PIN
    ioex.direction(EXPANDER_IO_RP2040_RESET, PCA95x5::Direction::OUT);
    ioex.write(EXPANDER_IO_RP2040_RESET, PCA95x5::Level::H);

    // Expander power PIN
    ioex.direction(EXPANDER_IO_BMP_PWR, PCA95x5::Direction::OUT);
    ioex.write(EXPANDER_IO_BMP_PWR, PCA95x5::Level::H);


    // SX126x init
    ioex.write(EXPANDER_IO_RADIO_NSS, PCA95x5::Level::H);
    ioex.direction(EXPANDER_IO_RADIO_NSS, PCA95x5::Direction::OUT); //output
    ioex.direction(EXPANDER_IO_RADIO_RST, PCA95x5::Direction::OUT); //output
    ioex.direction(EXPANDER_IO_RADIO_BUSY, PCA95x5::Direction::IN); //input
    ioex.direction(EXPANDER_IO_RADIO_DIO_1, PCA95x5::Direction::IN); //input

    delay(5);

    // Reset LCD
    ioex.write(EXPANDER_IO_LCD_RESET, PCA95x5::Level::H);

    // Reset touchscreen
    ioex.write(EXPANDER_IO_TP_RESET, PCA95x5::Level::H);

    delay(5);

    extender_init_done = true;
  }

}
