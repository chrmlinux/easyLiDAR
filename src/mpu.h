#include <MPU6050_light.h>

#define MPU_UPDATE_MSEC (10)

static MPU6050 mpu(Wire);
typedef struct {
  float x;
  float y;
  float z;
} AXS_T;

typedef struct {
  AXS_T g;
  AXS_T a;
  AXS_T m;
} SIX_T;

static SIX_T ang;

void setupMpu(void) {
  byte status = mpu.begin();
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();
  memset(&ang, 0x0, sizeof(ang));
}

void dumpMpu(void) {
  Serial.printf("%6.2f,%6.2f,%6.2f\n", ang.m.x, ang.m.y, ang.m.z);  
}

void updateMpu(void) {
  static uint32_t tm = millis();
  if ((millis() - tm) > MPU_UPDATE_MSEC) {
    tm = millis();
    mpu.update();
    ang.a.x = mpu.getAccX();
    ang.a.y = mpu.getAccY();
    ang.a.z = mpu.getAccZ();
    ang.g.x = mpu.getGyroX();
    ang.g.y = mpu.getGyroY();
    ang.g.z = mpu.getGyroZ();
    ang.m.x = mpu.getAngleX();
    ang.m.y = mpu.getAngleY();
    ang.m.z = mpu.getAngleZ();
  }
}
