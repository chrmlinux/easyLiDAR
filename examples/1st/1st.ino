#include "easyLiDAR.hpp"

static easyLiDAR lidar;

#define I2C_SDA (25)
#define I2C_SCL (21)
#define I2C_FREQ (400 * 1000)

void setup(void) {
  Serial.begin( 115200 ); while(!Serial); delay( 100 );
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(I2C_FREQ);
  lidar.begin();
}

void loop(void) {
  lidar.update();
  lidar.dump(0, 8);
}
