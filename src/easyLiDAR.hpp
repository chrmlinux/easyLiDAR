#ifndef __EASYLIDAR_HPP__
#define __EASYLIDAR_HPP__

#include <Arduino.h>
#include <Wire.h>

#include "tof64.h"
#include "mpu.h"
#include "leds.h"

class easyLiDAR {
  public:
    easyLiDAR(void) {}
    ~easyLiDAR(void) {}

    void begin(void) {
      setupTof64();
      setupMpu();
    }

    void end(void) {
    }

    void dump(int st, int en) {
      dumpTof64(st, en);  
      dumpMpu();
    }

    void update(void) {
      updateTof64();
      updateMpu();
    }

  private:
};


#endif
