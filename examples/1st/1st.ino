#include "easyLiDAR.hpp"

static easyLiDAR lidar;

void setup(void) {
  Serial.begin( 115200 ); while(!Serial); delay( 100 );
  lidar.begin();
}

void loop(void) {
  lidar.update();
}
