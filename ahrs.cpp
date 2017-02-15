#include "ahrs.h"

void AHRS::setup() {
  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setGyroRate(100);
  CurieIMU.setAccelerometerRate(100);
  filter.begin(50);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / 50;
  microsPrevious = micros();
}

bool AHRS::loop(float* pitch, float* roll, float* heading) {
  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    // read raw data from CurieIMU
    CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);

    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    

    // print the heading, pitch and roll
    *roll = filter.getRoll();
    *pitch = filter.getPitch();
    *heading = filter.getYaw();

Serial.print("sure: ");
    Serial.println(micros()-microsNow);
    
    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
    return true;
  }
  return false;
}

float AHRS::convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  return (aRaw / 32768.0) * CurieIMU.getAccelerometerRange();
}

float AHRS::convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  return (gRaw / 32768.0) * CurieIMU.getGyroRange();
}
