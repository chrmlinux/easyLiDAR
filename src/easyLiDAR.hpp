// VL53L5CX
//                FOV-H 45
// +----+----+----+----+----+----+----+----+
// | 56 | 57 | 58 | 59 | 60 | 61 | 62 | 63 |
// +----+----+----+----+----+----+----+----+
// | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 |
// +----+----+----+----+----+----+----+----+
// | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
// +----+----+----+----+----+----+----+----+
// | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | FOV-V 45
// +----+----+----+----+----+----+----+----+
// | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 |
// +----+----+----+----+----+----+----+----+
// | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
// +----+----+----+----+----+----+----+----+
// |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |
// +----+----+----+----+----+----+----+----+
// |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |
// +----+----+----+----+----+----+----+----+
//  2 to 400cm per Zone
//  Max 15Hz:8x8 60Hz:4x4

#ifndef __EASYLIDAR_HPP__
#define __EASYLIDAR_HPP__

#include <Arduino.h>
#include <SparkFun_VL53L5CX_Library.h>

#define TOF64_HEIGHT  (8)
#define TOF64_WIDTH   (8)
#define TOF64_DTMAX   (TOF64_HEIGHT * TOF64_WIDTH)

static SparkFun_VL53L5CX tof64Img;
VL53L5CX_ResultsData tof64Data;
static int tof64Res = 0;
static int tof64Width = 0;

class easyLiDAR {
  public:
    easyLiDAR(void) {}
    ~easyLiDAR(void) {}

    void begin(void) {
      _area = new uint8_t [TOF64_DTMAX];
      Serial.println("Tof64 FW Upload Wait 10sec");
      if (tof64Img.begin() == false) {
        Serial.println("Tof64 not find !");
        while (1) ;
      }
      Serial.println("Tof64 Ready");
      tof64Img.setResolution(TOF64_HEIGHT * TOF64_WIDTH);
      tof64Res = tof64Img.getResolution();
      tof64Width = sqrt(tof64Res);
      tof64Img.setRangingFrequency(15);
      tof64Img.startRanging();
      memset(_area, 0x0, TOF64_DTMAX);
    }

    void end(void) {
      free(_area);
    }

    void dump(int st, int en) {
      for (int y = st; y < en; y++) {
        int pos = (y * tof64Width);
        for (int x = 0; x < tof64Width; x++) {
          Serial.printf("%6d ", _area[pos + x]);
        }
        Serial.println();
      }
      Serial.println();
      Serial.println();
    }

    void update(void) {
      if (tof64Img.isDataReady() == true) {
        if (tof64Img.getRangingData(&tof64Data)) {
          int pos = 0;
          for (int y = 0 ; y <= tof64Width * (tof64Width - 1) ; y += tof64Width) {
            for (int x = tof64Width - 1 ; x >= 0 ; x--) {
              _area[pos] = tof64Data.distance_mm[x + y];
              pos++;
            }
          }
        }
      }
    }

  private:
    uint8_t *_area;

};


#endif
