#ifndef __EASYLIDAR_HPP__
#define __EASYLIDAR_HPP__

#define LIDAR_HEIGHT  (8)
#define LIDAR_WIDTH   (8)
#define LIDAR_DTMAX   (LIDAR_HEIGHT * LIDAR_WIDTH)

#include <Arduino.h>

class easyLiDAR {
  public:
  easyLiDAR(void) {}
  ~easyLiDAR(void) {}
  
  void begin(void) {
    _area = new uint8_t [LIDAR_DTMAX];
    memset(_area, 0x0, LIDAR_DTMAX);
  }

  void end(void) {
    free(_area);  
  }
  
  void update(void) {
    
  }

  private:
  uint8_t *_area;

};


#endif
