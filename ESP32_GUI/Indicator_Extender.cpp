#include "Indicator_Extender.h"

/* Install: Anitracks_PCA95x5*/

PCA9555 ioex;

bool extender_init_done = false;

void extender_init(void)
{
  if (!extender_init_done)
  {
    // Extender init.
    Wire.begin(LCD_SDA, LCD_SCL, LCD_SPEED);
    ioex.attach(Wire);

    ioex.polarity(PCA95x5::Polarity::ORIGINAL_ALL);

    // LCD Reset PIN
    ioex.write(PCA95x5::Port::P05, PCA95x5::Level::L);
    ioex.direction(PCA95x5::Port::P05, PCA95x5::Direction::OUT);

    // Touchscreen interupt PIN
    ioex.direction(PCA95x5::Port::P06, PCA95x5::Direction::IN);

    // Touchscreen reset PIN
    ioex.write(PCA95x5::Port::P07, PCA95x5::Level::L);
    ioex.direction(PCA95x5::Port::P07, PCA95x5::Direction::OUT);

    // RP2040 reset PIN
    ioex.direction(PCA95x5::Port::P07, PCA95x5::Direction::OUT);
    ioex.write(PCA95x5::Port::P07, PCA95x5::Level::H);

    // Expander power PIN
    ioex.direction(PCA95x5::Port::P10, PCA95x5::Direction::OUT);
    ioex.write(PCA95x5::Port::P10, PCA95x5::Level::H);

    delay(5);

    // Reset LCD
    ioex.write(PCA95x5::Port::P05, PCA95x5::Level::H);

    // Reset touchscreen
    ioex.write(PCA95x5::Port::P07, PCA95x5::Level::H);

    delay(5);

    extender_init_done = true;
  }

}
