#include "ahrs.h"
#include "CurieTimerOne.h"

Madgwick filter;
Reporter reporter;

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  return (aRaw / 32768.0) * CurieIMU.getAccelerometerRange();
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  return (gRaw / 32768.0) * CurieIMU.getGyroRange();
}

void filterUpdateIsr() {
  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  
  CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);
  ax = convertRawAcceleration(aix);
  ay = convertRawAcceleration(aiy);
  az = convertRawAcceleration(aiz);
  gx = convertRawGyro(gix);
  gy = convertRawGyro(giy);
  gz = convertRawGyro(giz);

  filter.updateIMU(gx, gy, gz, ax, ay, az);

  reporter(filter.getYaw(),filter.getPitch(),filter.getRoll());
  
}

void AHRS::setup(Reporter sendResult) {
  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setGyroRate(400);
  CurieIMU.setAccelerometerRate(400);
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);

  reporter = sendResult;
  const int filterFreqHZ = 100;
  const int oneSecInUsec = 1000000;   // A second in mirco second unit.
  filter.begin(filterFreqHZ);
  int time = oneSecInUsec / filterFreqHZ;
  CurieTimerOne.start(time, &filterUpdateIsr);  // set timer and callback
}


