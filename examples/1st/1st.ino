#include "easyLiDAR.hpp"
#include "FastLed.h"

static easyLiDAR lidar;

#define I2C_SDA (25)
#define I2C_SCL (21)
#define I2C_FREQ (1000 * 1000)

void setup(void) {
  Serial.begin( 115200 ); while(!Serial); delay( 100 );
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(I2C_FREQ);
  lidar.begin();
  setupLeds();
}

void loop(void) {
  static int stat = 0;
  static uint32_t tm = millis();

  lidar.update();
  lidar.dump(0, 16);
  if ((millis() - tm) > 1000) {
    tm = millis();
    leds[12] = (stat * 255) << 16; FastLED.show();
    stat = !stat;
  }
}
